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
	motor[left1]= power1;
	motor[right1]= power2;
	motor[left2]= power1;
	motor[right2]= power2;
	motor[left3]= power1;
	motor[right3]= power2;
}

// User control drive functions
void drive(){
	driveFunc(vexRT[Ch3], vexRT[Ch2]);
}

// Lift function
void liftFunc(int power){
	motor[leftlift]= power;
	motor[rightlift]= power;
}

// User control lift functions
void liftUp(){
	liftFunc(127);
}
void liftDown(){
	liftFunc(-127);
}
void liftStay(){
	liftFunc(0);
}

// User control flipper functions
//void flipperUp(){
//	motor[flipper]= 127;
//}
//void flipperDown(){
//	motor[flipper]= -(127/2);
//}
//void flipperStay(){
//	motor[flipper]= 0;
//}

// User control claw functions
//void clawOpen(){
//	motor[claw]= (127/4);
//}
//void clawClose(){
//	motor[claw]= (-127/2);
//}
//void clawStay(){
//	motor[claw]= 0;
//}

// User control intake functions
void intakeUp(){
	motor[intake]= 127;
}
void intakeDown(){
	motor[intake]= -127;
}
void intakeStay(){
	motor[intake]= 0;
}

// User control puncher functions
void puncherShoot(){
	motor[puncher]= 127;
}
void puncherStay(){
	motor[puncher]= 0;
}
