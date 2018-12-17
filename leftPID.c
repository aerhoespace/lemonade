#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// PID
// PID using optical shaft encoder
//
// Shaft encoder has 360 pulses per revolution

#define LEFT_SENSOR_INDEX    leftEncoder
#define RIGHT_SENSOR_INDEX   rightEncoder
#define PID_SENSOR_SCALE     1

#define PID_MOTOR_SCALE     -1

#define PID_DRIVE_MAX       80
#define PID_DRIVE_MIN     (-80)

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

static int   pidRunning = 1;
static float pidRequestedValue;

static int   pdRunning = 1;
static float pdRequestedValue;


// These could be constants but leaving

// Auton vars
float pid_Kp = 0.7;
float pid_Kd = 0.5;

float pd_Kp = 0.7;
float pd_Kd = 0.5;

// PID drive
void leftDrivePID(int clicks1){
	SetMotor(left1,clicks1);
	SetMotor(left2,clicks1);
	SetMotor(left3,clicks1);
}
void rightDrivePID(int clicks2){
	SetMotor(right1,clicks2);
	SetMotor(right2,clicks2);
	SetMotor(right3,clicks2);
}

/*-----------------------------------------------------------------------------*/
/*
*/
/*  PID control task
*/
/*
*/
/*-----------------------------------------------------------------------------*/

task leftPIDController(){

	float  pidSensorCurrentValue;
	float  pidError;
	float  pidLastError;
	float  pidDerivative;
	float  pidDrive;

	// If we are using an encoder then clear it
	if(SensorType[ LEFT_SENSOR_INDEX ] == sensorQuadEncoder )
		SensorValue[ LEFT_SENSOR_INDEX ] = 0;

	// Init the variables - thanks Glenn :)
	pidLastError  = 0;

	while( true ){
		// Is PID control active ?
		if( pidRunning ){
			// Read the sensor value and scale
			pidSensorCurrentValue = SensorValue[ LEFT_SENSOR_INDEX ] * PID_SENSOR_SCALE;

			// Calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// Calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// Calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Kd * pidDerivative);

			// Limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// Send to motor
			leftDrivePID(pidDrive * PID_MOTOR_SCALE);
			}else{
			// Clear all
			pidError      = 0;
			pidLastError  = 0;
			pidDerivative = 0;
			leftDrivePID(0);
			rightDrivePID(0);
		}

		// Run at 50Hz
		wait1Msec( 25 );
	}
}

task rightPIDController(){

	float  pidSensorCurrentValue;
	float  pidError;
	float  pidLastError;
	float  pidDerivative;
	float  pidDrive;

	// If we are using an encoder then clear it
	if(SensorType[ RIGHT_SENSOR_INDEX ] == sensorQuadEncoder )
		SensorValue[ RIGHT_SENSOR_INDEX ] = 0;

	// Init the variables - thanks Glenn :)
	pidLastError  = 0;

	while( true ){
		// Is PID control active ?
		if( pdRunning ){
			// Read the sensor value and scale
			pidSensorCurrentValue = SensorValue[ RIGHT_SENSOR_INDEX ] * PID_SENSOR_SCALE;

			// Calculate error
			pidError = pidSensorCurrentValue - pdRequestedValue;

			// Calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// Calculate drive
			pidDrive = (pd_Kp * pidError) + (pd_Kd * pidDerivative);

			// Limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// Send to motor
			rightDrivePID(pidDrive * PID_MOTOR_SCALE);
			}else{
			// Clear all
			pidError      = 0;
			pidLastError  = 0;
			pidDerivative = 0;
			leftDrivePID(0);
			rightDrivePID(0);
		}

		// Run at 50Hz
		wait1Msec( 25 );
	}
}


/*-----------------------------------------------------------------------------*/
/*
*/
/*  main task
/*
*/
/*-----------------------------------------------------------------------------*/

void drivePID(int clicks, int clicks2){
	// send the motor off somewhere
	pidRequestedValue = clicks;
	pdRequestedValue=clicks2;

	// start the PID task
	startTask( leftPIDController );
	startTask( rightPIDController );

	// use joystick to modify the requested position
	for(int i=0; i<=5; i++ ){
		// maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
		// free spinning motor is 100rmp so 1.67 rotations per second
		// 1.67 * 360 counts is 600
		wait1Msec(1000);

	}
}
