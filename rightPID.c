#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)



/*-----------------------------------------------------------------------------*/
/*
*/
/*  PID control task
*/
/*
*/
/*-----------------------------------------------------------------------------*/

task rightPIDController(){

 float  pidSensorCurrentValue;
 float  pidError;
 float  pidLastError;
 float  pidDerivative;
 float  pidDrive;

 // If we are using an encoder then clear it
 if(SensorType[RIGHT_SENSOR_INDEX] == sensorQuadEncoder)
   SensorValue[RIGHT_SENSOR_INDEX] = 0;

  	// Init the variables - thanks Glenn :)
  pidLastError  = 0;

  while(true){
    // Is PID control active ?
    if(pidRunning){
      // Read the sensor value and scale
      pidSensorCurrentValue = SensorValue[RIGHT_SENSOR_INDEX] * PID_SENSOR_SCALE;

      // Calculate error
      pidError = pidSensorCurrentValue - pidRequestedValue;

        // Calculate the derivative
        pidDerivative = pidError - pidLastError;
        pidLastError  = pidError;

        // Calculate drive
        pidDrive = (pid_Kp * pidError) + (pid_Kd * pidDerivative);

        // Limit drive
        if(pidDrive > PID_DRIVE_MAX)
          pidDrive = PID_DRIVE_MAX;
        if(pidDrive < PID_DRIVE_MIN)
          pidDrive = PID_DRIVE_MIN;

            // Send to motor
           	rightDrive(pidDrive * PID_MOTOR_SCALE);
    }else{
       // Cear all
       pidError      = 0;
       pidLastError  = 0;
       pidDerivative = 0;
       leftDrive(0);
       rightDrive(0);
     }

    // Run at 50Hz
    wait1Msec(25);
  }
}

task leftPIDController(){

 float  pidSensorCurrentValue;
 float  pidError;
 float  pidLastError;
 float  pidDerivative;
 float  pidDrive;

 // If we are using an encoder then clear it
 if(SensorType[LEFT_SENSOR_INDEX] == sensorQuadEncoder)
   SensorValue[LEFT_SENSOR_INDEX] = 0;

  	// Init the variables
  pidLastError  = 0;

  while(true){
    // Is PID control active ?
    if(pdRunning){
      // Read the sensor value and scale
      pidSensorCurrentValue = SensorValue[LEFT_SENSOR_INDEX] * PID_SENSOR_SCALE;

      // Calculate error
      pidError = pidSensorCurrentValue - pdRequestedValue;

        // Calculate the derivative
        pidDerivative = pidError - pidLastError;
        pidLastError  = pidError;

        // Calculate drive
        pidDrive = (pd_Kp * pidError) + (pd_Kd * pidDerivative);

        // Limit drive
        if(pidDrive > PID_DRIVE_MAX)
          pidDrive = PID_DRIVE_MAX;
        if(pidDrive < PID_DRIVE_MIN)
          pidDrive = PID_DRIVE_MIN;

            // Send to motor
           	leftDrive(pidDrive * PID_MOTOR_SCALE);
    }else{
       // Clear all
       pidError      = 0;
       pidLastError  = 0;
       pidDerivative = 0;
       leftDrive(0);
       rightDrive(0);
     }

    // Run at 50Hz
    wait1Msec(25);
  }
}

/*-----------------------------------------------------------------------------*/
/*
*/
/*  Main task
/*
*/
/*-----------------------------------------------------------------------------*/

void drivePID(int clicks, int clicks2){
	// Send the motor off somewhere
  pidRequestedValue = clicks;
  pdRequestedValue=clicks2;

	// Start the PID task
  startTask(leftPIDController);
	startTask(rightPIDController);

  // Use the joystick to modify the requested position
  for(int i=0; i<=5; i++){
  	// Maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
  	// Free spinning motor is 100rmp so 1.67 rotations per second
		// 1.67 * 360 counts is 600
  	wait1Msec(1000);

  }
}
