#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// User control
// Drive
void leftDrive(int speed1){
	SetMotor(left1,speed1);
	SetMotor(left2,speed1);
	SetMotor(left3,speed1);
}
void rightDrive(int speed2){
	SetMotor(right1,speed2);
	SetMotor(right2,speed2);
	SetMotor(right3,speed2);
}
void drive(){
	rightDrive(vexRT[Ch2]);
	leftDrive(vexRT[Ch3]);
}

// Puncher
void puncherShoot(){
	SetMotor(puncher,127);
}
void puncherStay(){
	SetMotor(puncher,0);
}

// Intake
void intakeIn(){
	SetMotor(intakeT,127);
	SetMotor(intakeB,127);
}
void intakeOut(){
	SetMotor(intakeT,-127);
	SetMotor(intakeB,-127);
}
void intakeStay(){
	SetMotor(intakeT,0);
	SetMotor(intakeB,0);
}

// Flipper
void flipperUp(){
	SetMotor(flipper,127);
}
void flipperDown(){
	SetMotor(flipper,-127);
}
void flipperStay(){
	SetMotor(flipper,0);
}
