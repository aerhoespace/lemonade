#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

//PID
#define PID_INTEGRAL_LIMIT  50
#define PD_INTEGRAL_LIMIT  50

#define LEFT_SENSOR_INDEX    leftEncode()
#define RIGHT_SENSOR_INDEX   rightEncode()
#define PID_SENSOR_SCALE     -1

#define LEFT_MOTOR_INDEX    left1
#define RIGHT_MOTOR_INDEX   right1
#define PID_MOTOR_SCALE     -1

#define PID_DRIVE_MAX       80
#define PID_DRIVE_MIN     (-80)

// Auton vars
float  pid_Kp = 0.7;
float  pid_Ki = 0.04;
float  pid_Kd = 0.5;

float pd_Kp = 0.7;
float  pd_Ki = 0.04;
float pd_Kd = 0.5;

// Encoders
int leftEncode(){
	return(SensorValue[leftEncoder]);
}
int rightEncode(){
	return(SensorValue[rightEncoder]);
}

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

static int   pidRunning = 1;
static float pidRequestedValue;

static int   pdRunning = 1;
static float pdRequestedValue;


// These could be constants but leaving


// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  PID control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task leftPIDController()
{
	float  pidSensorCurrentValue;
	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;

	float  pdSensorCurrentValue;
	float  pdError;
	float  pdLastError;
	float  pdIntegral;
	float  pdDerivative;
	float  pidDrive2;

	// If we are using an encoder then clear it
	if( SensorType[ LEFT_SENSOR_INDEX ] == sensorQuadEncoder )
		SensorValue[ LEFT_SENSOR_INDEX ] = 0;

	if( SensorType[ RIGHT_SENSOR_INDEX ] == sensorQuadEncoder )
		SensorValue[ RIGHT_SENSOR_INDEX ] = 0;

	// Init the variables - thanks Glenn :)
	pidLastError  = 0;
	pidIntegral   = 0;

	pdLastError  = 0;
	pdIntegral   = 0;

	while( true )
	{
		// Is PID control active ?
		if( pdRunning && pidRunning )
		{
			// Read the sensor value and scale
			pdSensorCurrentValue = SensorValue[ RIGHT_SENSOR_INDEX ] * PID_SENSOR_SCALE;

			// Read the sensor value and scale
			pidSensorCurrentValue = SensorValue[ LEFT_SENSOR_INDEX ] * PID_SENSOR_SCALE;


			// Calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// Calculate error
			pdError = pdSensorCurrentValue - pdRequestedValue;

			// Integral - if Ki is not 0
			if( pd_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pdError) < PD_INTEGRAL_LIMIT )
					pdIntegral = pdIntegral + pdError;
				else
					pdIntegral = 0;
			}
			else
				pdIntegral = 0;

			// Integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// Calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// Calculate the derivative
			pdDerivative = pdError - pdLastError;
			pdLastError  = pdError;

			// Calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

			pidDrive2 = (pd_Kp * pidError) + (pd_Ki * pidIntegral) + (pd_Kd * pidDerivative);

			// Limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			if( pidDrive2 > PID_DRIVE_MAX )
				pidDrive2 = PID_DRIVE_MAX;
			if( pidDrive2 < PID_DRIVE_MIN )
				pidDrive2 = PID_DRIVE_MIN;

			leftDrive(pidDrive);
			rightDrive(pidDrive2);

			}else{
			// Clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;

			// Clear all
			pdError      = 0;
			pdLastError  = 0;
			pdIntegral   = 0;
			pdDerivative = 0;

			leftDrive(0);
			rightDrive(0);
		}

		// Run at 50Hz
		wait1Msec( 25 );
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
	pidRequestedValue= clicks*-1;
	pdRequestedValue=  clicks2*-1;

	// Start the PID task
	startTask( leftPIDController );
	//	StartTask( rightPIDController );

	// Use joystick to modify the requested position
	while(pidRequestedValue!=leftEncode()){
		// Maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
		// Free spinning motor is 100rmp so 1.67 rotations per second
		// 1.67 * 360 counts is 600
		wait1Msec(20);
	}
	stopTask(leftPIDController);
}

/*-----------------------------------------------------------------------------*/
/*
*/
/*  Auton functions
/*
*/
/*-----------------------------------------------------------------------------*/

// Drive
void driveStop(int time){
	SetMotor(left1,0);
	SetMotor(right1,0);
	SetMotor(left2,0);
	SetMotor(right2,0);
	SetMotor(left3,0);
	SetMotor(right3,0);
	wait1Msec(time);
}

// Puncher
void autoShoot(int time){
	SetMotor(puncher,127);
	wait1Msec(time);
}
void puncherStop(int time){
	SetMotor(puncher,0);
	wait1Msec(time);
}

// Intake
void autoTake(int time){
	SetMotor(intakeT,127);
	SetMotor(intakeB,127);
	wait1Msec(time);
}
void intakeStop(int time){
	SetMotor(intakeT,0);
	SetMotor(intakeB,0);
	wait1Msec(time);
}

/*-----------------------------------------------------------------------------*/
/*
*/
/*  Red alliance auton modes
/*
*/
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/*  Flag side
/*-----------------------------------------------------------------------------*/

void autonR1(){ // 6pt -- cap, all flags
	// Start facing cap
	// Drive forward to hit cap
	drivePID(850,850);
	driveStop(50);{
	}
	// Intake ball
	autoTake(800);{
		} intakeStop(50);{
	}
	// Drive back
	drivePID(-850,-850);
	driveStop(50);{
	}
	// Turn left
	drivePID(-300,300);
	driveStop(50);{
	}
	// Drive forward
	drivePID(400,400);
	driveStop(50);{
	}
	// Shoot top flag
	autoShoot(1300);{
		} puncherStop(50);{
	}
	// Drive forward
	drivePID(400,400);
	driveStop(50);{
	}
	// Shoot middle flag
	autoShoot(1300);{
		} puncherStop(50);{
	}
	// Drive forward to hit bottom flag
	drivePID(400,400);
	driveStop(50);{
	}
}

void autonR2(){ // 3pt -- top flag, bottom flag
	// Start facing flags
	// Drive forward
	drivePID(400,400);
	driveStop(50);{
	}
	// Shoot top flag
	autoShoot(1300);{
		} puncherStop(50);{
	}
	// Drive forward to hit bottom flag
	drivePID(800,800);
	driveStop(50);{
	}
}

/*-----------------------------------------------------------------------------*/
/*  Cap side
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/*
*/
/*  Blue alliance auton modes
/*
*/
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/*  Flag side
/*-----------------------------------------------------------------------------*/

void autonB1(){ // 6pt -- cap, all flags
	// Start facing cap
	// Drive forward to hit cap
	drivePID(850,850);
	driveStop(50);{
	}
	// Intake ball
	autoTake(800);{
		} intakeStop(50);{
	}
	// Drive back
	drivePID(-850,-850);
	driveStop(50);{
	}
	// Turn right
	drivePID(300,-300);
	driveStop(50);{
	}
	// Drive forward
	drivePID(400,400);
	driveStop(50);{
	}
	// Shoot top flag
	autoShoot(1300);{
		} puncherStop(50);{
	}
	// Drive forward
	drivePID(400,400);
	driveStop(50);{
	}
	// Shoot middle flag
	autoShoot(1300);{
		} puncherStop(50);{
	}
	// Drive forward to hit bottom flag
	drivePID(400,400);
	driveStop(50);{
	}
}

/*-----------------------------------------------------------------------------*/
/*  Cap side
/*-----------------------------------------------------------------------------*/
