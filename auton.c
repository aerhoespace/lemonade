#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

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
/*  Auton modes
/*
*/
/*-----------------------------------------------------------------------------*/

// Flag side auton
void autonB1(){ // Blue flag auton
	// Start facing flags
	// Drive forward to top falg position
	autoDrive(127,127);{
	}
	wait1Msec(270);
	driveStop(50);{
	}
	wait1Msec(50);
	// Shoot top flag
	autoShoot(1200);{
	}
	puncherStop(50);{
	}
	// Drive forward to hit bottom flag
	autoDrive(127,127);{
	}
	wait1Msec(1300);
	driveStop(50);{
	}
	wait1Msec(50);
}

// Higher scoring flag auton
void autonB2(){ // Blue flag auton
	// Start facing cap
	// Drive forward to hit cap
	// Intake ball halfway
	// Backup
	// Turn left
	// Drive forward
	// Shoot top flag
	// Move ball up intake
	// Drive forward
	// Shoot middle flag
	// Drive forward to hit botom flag
}
