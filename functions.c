// Drive encoders
int leftEncode(){
	return(SensorValue[leftEncoder]);
}
int rightEncode(){
	return(SensorValue[rightEncoder]);
}

// Drive function
void driveFunc(int speed1, int speed2){
	SetMotor(left1,speed1);
	SetMotor(right1,speed2);
	SetMotor(left2,speed1);
	SetMotor(right2,speed2);
	SetMotor(left3,speed1);
	SetMotor(right3,speed2);
}

// User control drive functions
void drive(){
	driveFunc(vexRT[Ch3], vexRT[Ch2]);
}
void driveStop(){
	driveFunc(0,0);
}

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
