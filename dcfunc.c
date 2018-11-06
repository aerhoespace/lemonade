// Lift potentiometers
int liftPotent(){
	return(((SensorValue[leftPotent])*(SensorValue[rightPotent]))/2);
}

// Drive encoders
int leftDriveEncode(){
	return(SensorValue[leftEncoder]);
}
int rightDriveEncode(){
	return(SensorValue[rightEncoder]);
}

// Drive function
void driveFunc(int power1, int power2){
	SetMotor(left1,power1);
	SetMotor(right1,power2);
	SetMotor(left2,power1);
	SetMotor(right2,power2);
	SetMotor(left3,power1);
	SetMotor(right3,power2);
}

// User control drive functions
void drive(){
	driveFunc(vexRT[Ch2], vexRT[Ch3]);
}

// Lift function
//void liftFunc(int power){
//	SetMotor(leftlift,power);
//	SetMotor(rightlift,power);
//}

// User control lift functions
//void liftUp(){
//	SetMotor(leftlift,100);
//	SetMotor(rightlift,100);
//}
//void liftDown(){
//	SetMotor(leftlift,-100);
//	SetMotor(rightlift,-100);
//}
//void liftStay(){
//	SetMotor(leftlift,0);
//	SetMotor(rightlift,0);
//}

// User control flipper functions
//void flipperUp(){
//	SetMotor(flipper,100);
//}
//void flipperDown(){
//	SetMotor(flipper,-50);
//}
//void flipperStay(){
//	SetMotor(flipper,0);
//}

// User control claw functions
//void clawOpen(){
//	SetMotor(claw,25);
//}
//void clawClose(){
//	SetMotor(claw,-50);
//}
//void clawStay(){
//	SetMotor(claw,0);
//}

// User control intake functions
void intakeUp(){
	SetMotor(intake,100);
}
void intakeDown(){
	SetMotor(intake,-100);
}
void intakeStay(){
	SetMotor(intake,0);
}

// User control puncher functions
void puncherShoot(){
	SetMotor(puncher,80);
}
void puncherStay(){
	SetMotor(puncher,0);
}
