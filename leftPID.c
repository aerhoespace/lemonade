#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// PID using optical shaft encoder

#define PID_INTEGRAL_LIMIT  50
#define PD_INTEGRAL_LIMIT  50

#define LEFT_SENSOR_INDEX    leftEncoder
#define RIGHT_SENSOR_INDEX   rightEncoder
#define PID_SENSOR_SCALE     -1

#define LEFT_MOTOR_INDEX    left1
#define RIGHT_MOTOR_INDEX   right1
#define PID_MOTOR_SCALE     -1

#define PID_DRIVE_MAX       80
#define PID_DRIVE_MIN     (-80)

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"

static int   pidRunning = 1;
static float pidRequestedValue;

static int   pdRunning = 1;
static float pdRequestedValue;

bool taskRunning=false;

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  PID control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task leftPIDController()
{
	taskRunning=true;
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

	while( true ){
		if( pidRunning ){
			if(pidSensorCurrentValue==pidRequestedValue){
				taskRunning = false;
				stopTask(leftPIDController);
			}

			// Is PID control active ?
			if( pdRunning )
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

				// calculate the derivative
				pdDerivative = pdError - pdLastError;
				pdLastError  = pdError;

				// calculate drive
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
			}
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
	taskRunning=true;
	//	startTask( rightPIDController );

	// Use joystick to modify the requested position
	while(taskRunning){
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

// Puncher
void autoShoot(int time){
	SetMotor(puncher1,127);
	SetMotor(puncher2,127);
	wait1Msec(time);
}
void puncherStop(int time){
	SetMotor(puncher1,0);
	SetMotor(puncher2,0);
	wait1Msec(time);
}
task shoot(){
	while(true){
		autoShoot(2000);
	}
}
task dontShoot(){
	while(true){
		puncherStop(10);
	}
}

// Intake
void autoTake(int time){
	SetMotor(intake1,127);
	SetMotor(intake2,127);
	wait1Msec(time);
}
void intakeStop(int time){
	SetMotor(intake1,0);
	SetMotor(intake2,0);
	wait1Msec(time);
}
task halfway(){
	while(true){
		autoTake(300);
	}
}
task up(){
	while(true){
		autoTake(450);
	}
}
task urdone(){
	while(true){
		intakeStop(10);
	}
}

// Wait to start next task
void wait(){
	wait1Msec(10);
}

/*----------------------------------------------------------------------------------------------------*\
|*                                   - Point Turns with Encoders -                                    *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to turn left, and then right, using feedback from the encoders   *|
|*  to determine how much.  There is a 2 second pause at the beginning of the program.                *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/

// Drive
void resetEncoders(){
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}

// Drive
void autoDrive(int speed1, int speed2){
	SetMotor(left1,speed1);
	SetMotor(right1,speed2);
	SetMotor(left2,speed1);
	SetMotor(right2,speed2);
	SetMotor(left3,speed1);
	SetMotor(right3,speed2);
}
void driveStop(int time){
	SetMotor(left1,0);
	SetMotor(right1,0);
	SetMotor(left2,0);
	SetMotor(right2,0);
	SetMotor(left3,0);
	SetMotor(right3,0);
	wait1Msec(time);
}

// Turn left
void turnLeft(int leftVal){
	resetEncoders();
	while(SensorValue(rightEncoder) < leftVal)
	{
		rightDrive(127);
		leftDrive(-127);
	}
}

// Turn right
void turnRight(int rightVal){
	resetEncoders();
	while(SensorValue(leftEncoder) < rightVal)
	{
		rightDrive(-127);
		leftDrive(127);
	}
}

/*-----------------------------------------------------------------------------*/
/*
*/
/*  Auton modes
/*
*/
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/*  Blue alliance auton
/*-----------------------------------------------------------------------------*/

// Flag side (+6)
void auton1(){

	// Reset encoders
	resetEncoders();

	// Drive forward to hit cap (+1)
	drivePID(1150,1150);

	// Intake ball halfway
  startTask(halfway);
  stopTask(halfway);
  startTask(urdone);
  stopTask(urdone);

	// Drive back
	resetEncoders();
	drivePID(-1150,-1150);

	// Turn left to face flags
	resetEncoders();
	turnLeft(360);

	// Drive forward to top flag position
	//resetEncoders();
	//drivePID(300,300);

	// Shoot top flag (+2)
	//autoShoot(2000);
	//puncherStop(50);

	// Drive forward to middle flag position
	//resetEncoders();
	//drivePID(300,300);

	// Intake ball rest of the way
	//autoTake(600);
	//intakeStop(50);

	// Shoot middle flag (+2)
	//autoShoot(2000);
	//puncherStop(50);

	// Drive forward to hit bottom flag (+1)
	//resetEncoders();
	//drivePID(600,600);
}

/*-----------------------------------------------------------------------------*/
/*  Red alliance auton
/*-----------------------------------------------------------------------------*/

// Simple auton
void auton(){
// Start facing flags
// Drive forward to middle flag position
autoDrive(127,127);
wait1Msec(600);
driveStop(10);
// Shoot flag
autoShoot(2500);
puncherStop(10);
// Drive forward to hit bottom flag
autoDrive(127,127);
wait1Msec(600);
driveStop(10);
}
