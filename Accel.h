// Create sensor instances.
Adafruit_L3GD20_Unified       gyro(20);
Adafruit_LSM303_Accel_Unified accel(30301);
Adafruit_LSM303_Mag_Unified   mag(30302);

const float Pi = 3.14159;

// This is the desired direction of travel
// expressed as a 0-360 degree compass heading
// 0.0 = North
// 90.0 = East
// 180.0 = South
// 270 = West
const float targetHeading[] = {147.0, 87.0};

// Mag calibration values are calculated via ahrs_calibration.
// These values must be determined for each baord/environment.
// See the image in this sketch folder for the values used
// below.

// THESE MUST BE RECALIBRATED IN NEW LOCATIONS
// USE MOTIONCAL: https://www.pjrc.com/store/prop_shield.html > MotionCal

//Offsets applied to ray x,y and z values 
float mag_offsets[3] = {29.46, 21.00, -114.66}; 

//Honestly, I have no idea what these numbers are 
float mag_softiron_matrix[3][3] = {{0.944, 0.027, 0.026}, 
                                   {0.027, 0.993, 0.024}, 
                                   {0.026, 0.024, 1.069}}; 
  
float mag_field_strength = 39.33F; 

// filter for orientation calculation
Madgwick filter;

void getMagHeading(int num){// might need to pass values by reference for this one
  sensors_event_t mag_event;

  float heading = (atan2(mag_event.magnetic.y,mag_event.magnetic.x) * 180) / Pi;
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  
  // Calculate the error between tha measured heading and the target heading.
  float error = heading - targetHeading[num];
  if (error > 180)
  {
    error = error - 360;  // for angles > 180, correct in the opposite direction.
  }

  Serial.print("Mag heading: ");
  Serial.println(heading);
  Serial.print("Mag error value: ");
  Serial.println(error);
}

float getAccelHeading() {
  sensors_event_t gyro_event;
  sensors_event_t accel_event;
  sensors_event_t mag_event;

  // Get new data samples
  gyro.getEvent(&gyro_event);
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  // Apply mag offset compensation (base values in uTesla)
  float x = mag_event.magnetic.x - mag_offsets[0];
  float y = mag_event.magnetic.y - mag_offsets[1];
  float z = mag_event.magnetic.z - mag_offsets[2];

  // Apply mag soft iron error compensation
  float mx = x * mag_softiron_matrix[0][0] + y * mag_softiron_matrix[0][1] + z * mag_softiron_matrix[0][2];
  float my = x * mag_softiron_matrix[1][0] + y * mag_softiron_matrix[1][1] + z * mag_softiron_matrix[1][2];
  float mz = x * mag_softiron_matrix[2][0] + y * mag_softiron_matrix[2][1] + z * mag_softiron_matrix[2][2];

  // The filter library expects gyro data in degrees/s, but adafruit sensor
  // uses rad/s so we need to convert them first (or adapt the filter lib
  // where they are being converted)
  float gx = gyro_event.gyro.x * 57.2958F;
  float gy = gyro_event.gyro.y * 57.2958F;
  float gz = gyro_event.gyro.z * 57.2958F;

  // Update the filter
  filter.update(gx, gy, gz,
                accel_event.acceleration.x, accel_event.acceleration.y, accel_event.acceleration.z,
                mx, my, mz);

  return filter.getYaw();
  // debug
  //Serial.print("Accel heading: ");
  //Serial.println(heading);
  
}

void initSensors() {
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }
  
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303DLHC ... check your connections */
    Serial.println("Ooops, no L3M303DLHC accel detected ... Check your wiring!");
    while(1);
  }
  
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303DLHC ... check your connections */
    Serial.println("Ooops, no L3M303DLHC mag detected ... Check your wiring!");
    while(1);
  }

  // Filter expects 50 samples per second
  filter.begin(50);
}

