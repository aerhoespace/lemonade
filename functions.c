#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// User control
// Drive
void leftDrive(int speed1){
	SetMotor(left1,speed1);
	SetMotor(left2,speed1);
}
void rightDrive(int speed2){
	SetMotor(right1,speed2);
	SetMotor(right2,speed2);
}
void drive(){
	leftDrive(vexRT[Ch3]);
	rightDrive(vexRT[Ch2]);
}

// Puncher
void puncherShoot(){
	SetMotor(puncher1,100);
	SetMotor(puncher2,100);
	SetMotor(puncher3,100);
}
void puncherStay(){
	SetMotor(puncher1,0);
	SetMotor(puncher2,0);
	SetMotor(puncher3,0);
}

// Intake
void intakeIn(){
	SetMotor(intake1,127);
	SetMotor(intake2,127);
}
void intakeOut(){
	SetMotor(intake1,-127);
	SetMotor(intake2,-127);
}
void intakeStay(){
	SetMotor(intake1,0);
	SetMotor(intake2,0);
}
