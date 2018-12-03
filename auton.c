#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)



// Auton drive
void leftDrive(int clicks1){
	SetMotor(left1,clicks1);
	SetMotor(left2,clicks1);
	SetMotor(left3,clicks1);
}
void rightDrive(int clicks2){
	SetMotor(right1,clicks2);
	SetMotor(right2,clicks2);
	SetMotor(right3,clicks2);
}
// Stop motors
// Drive
void driveStop(int speed){
	leftDrive(speed);
	rightDrive(speed);
}


// Puncher
void puncherStop(int time){
	wait1Msec(time);
}
// Flipper
void flipperStop(int time){
	wait1Msec(time);
}


// Auton functions
// Puncher
void autoShoot(int time){
	SetMotor(puncher,127);
	puncherStop(50);
}

// Flipper
void autoFlipUp(int time){
	SetMotor(flipper,127);
	flipperStop(50);
}
void autoFlipDown(int time){
	SetMotor(flipper,-127);
	flipperStop(50);
}
