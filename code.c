#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    leftPotent,     sensorPotentiometer)
#pragma config(Sensor, in2,    rightPotent,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           leftdrive,     tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           leftlift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           flipper,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           intake,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           puncher,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightlift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightdrive,    tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"  //Main competition background code...do not modify!

//State all functions

//Lift potentiometers
int liftPotent(){
	return(((SensorValue[leftPotent])*(SensorValue[rightPotent]))/2);
}

//Drive encoders
int leftDriveEncode(){
	return(SensorValue[leftEncoder]);
}

int rightDriveEncode(){
	return(SensorValue[rightEncoder]);
}

//Drive function
void driveFunc(int power1, int power2){
	motor[leftdrive]= power1;
	motor[rightdrive]= power2;
}

//User control drive functions
void drive(){
	driveFunc(vexRT[Ch3], vexRT[Ch2]);
}

void driveForward(){
	driveFunc(127,127);
}

void driveBack(){
	driveFunc(-127,-127);
}

void driveTurnLeft(){
	driveFunc(-127,127);
}

void driveTurnRight(){
	driveFunc(127,-127);
}

void driveStop(){
	driveFunc(0,0);
}

//Lift function
void liftFunc(int power){
	motor[leftlift]= power;
	motor[rightlift]= power;
}

//User control lift functions
void liftUp(){
	liftFunc(127);
}

void liftDown(){
	liftFunc(-127);
}

void liftStay(){
	liftFunc(0);
}

//Flipper function
void flipperFunc(int power){
	motor[flipper]= power;
}

//Flipper user control functions
void flipperUp(){
	motor[flipper]= 127;
}
void flipperDown(){
	motor[flipper]= -(127/2);
}
void flipperStay(){
	motor[flipper]= 0;
}

//Claw functon
void clawFunc(int power){
	motor[flipper]= power;
}

//User control claw functions
void clawOpen(){
	motor[claw]= (127/4);
}
void clawClose(){
	motor[claw]= (-127/2);
}
void clawStay(){
	motor[claw]= 0;
}

//Intake function
void intakeFunc(int power){
	motor[intake]= power;
}

//User control claw functions
void intakeUp(){
	motor[intake]= (127);
}
void intakeDown(){
	motor[intake]= (-127);
}
void intakeStay(){
	motor[intake]= (0);
}

	//Puncher function
	void puncherFunc(int power){
		motor[puncher]= power;
	}

	//User control claw functions
	void puncherShoot(){
		motor[puncher]= (127);
	}
	void puncherStay(){
		motor[puncher]= (0);
	}

  /*---------------------------------------------------------------------------*/
	/*                                                                           */
	/*        Description: Autonomous Functions                                  */
	/*                                                                           */
	/*---------------------------------------------------------------------------*/
	
	//Auton functions
	void autonForward(){
		while((leftDriveEncode()<840)&&(rightDriveEncode()<840)){
			driveForward();
		}
		driveStop();
	}
	
	void autonForward2(){
		while((leftDriveEncode()<680)&&(rightDriveEncode()<680)){
			driveForward();
		}
			driveStop();
	}
	
	//void autonPuncher(){
	
	void autonBack(){
		while((leftDriveEncode()>-1800)&&(rightDriveEncode()>-1800)){
			driveBack();
		}
		driveStop();
	}

	void autonTurnLeft(){
		while((leftDriveEncode()>-1800)&&(rightDriveEncode()<1800)){
			driveTurnLeft();
		}
		driveStop();
	}

	void autonBack2(){
		while((leftDriveEncode()<1800)&&(rightDriveEncode()>-1800)){
			driveTurnRight();
		}
		driveStop();
	}

	/*---------------------------------------------------------------------------*/
	/*                                                                           */
	/*        Description: Competition template for VEX EDR                      */
	/*                                                                           */
	/*---------------------------------------------------------------------------*/

	// This code is for the VEX cortex platform
#pragma platform(VEX2)

	// Select Download method as "competition"
#pragma competitionControl(Competition)

	//Main competition background code...do not modify!

	/*---------------------------------------------------------------------------*/
	/*                          Pre-Autonomous Functions                         */
	/*                                                                           */
	/*  You may want to perform some actions before the competition starts.      */
	/*  Do them in the following function.  You must return from this function   */
	/*  or the autonomous and usercontrol tasks will not be started.  This       */
	/*  function is only called once after the cortex has been powered on and    */
	/*  not every time that the robot is disabled.                               */
	/*---------------------------------------------------------------------------*/

	void pre_auton()
	{
		// Set bStopTasksBetweenModes to false if you want to keep user created tasks
		// running between Autonomous and Driver controlled modes. You will need to
		// manage all user created tasks if set to false.
		bStopTasksBetweenModes = true;

		// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
		// used by the competition include file, for example, you might want
		// to display your team name on the LCD in this function.
		// bDisplayCompetitionStatusOnLcd = false;

		// All activities that occur before the competition starts
		// Example: clearing encoders, setting servo positions, ...
	}

	/*---------------------------------------------------------------------------*/
	/*                                                                           */
	/*                              Autonomous Task                              */
	/*                                                                           */
	/*  This task is used to control your robot during the autonomous phase of   */
	/*  a VEX Competition.                                                       */
	/*                                                                           */
	/*  You must modify the code to add your own robot specific commands here.   */
	/*---------------------------------------------------------------------------*/

	task autonomous()
	{

//Blue1 auton
//Drive forward
	

//Puncher shoot


//Drive forward


//Drive backwards


//Turn left


//Drive backwards
	
	
	}

	/*---------------------------------------------------------------------------*/
	/*                                                                           */
	/*                              User Control Task                            */
	/*                                                                           */
	/*  This task is used to control your robot during the user control phase of */
	/*  a VEX Competition.                                                       */
	/*                                                                           */
	/*  You must modify the code to add your own robot specific commands here.   */
	/*---------------------------------------------------------------------------*/

	task usercontrol()
	{
		// User control code here, inside the loop

		//Drive program
		while(true){
			drive();
		}

		//Lift program
		if(vexRT[Btn6U]==1){
			liftUp();
			}else if (vexRT[Btn6D]==1){
			liftDown();
			}else {
			liftStay();
		}

		//Flipper program
		if (vexRT[Btn8U]==1){
			flipperUp();
			}else if(vexRT[Btn8D]==1){
			flipperDown();
			}else {
			flipperStay();
		}

		//Claw program
		if (vexRT[Btn8R]==1){
			clawOpen();
			}else if(vexRT[Btn8L]==1){
			clawClose();
			}else {
			clawStay();
		}

		//Intake program
if (vexRT[


		//Puncher program

	}


	// This is the main execution loop for the user control program.
	// Each time through the loop your program should update motor + servo
	// values based on feedback from the joysticks.

	// ........................................................................
	// Insert user code here. This is where you use the joystick values to
	// update your motors, etc.
	// ........................................................................
