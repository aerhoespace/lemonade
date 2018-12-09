#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// Drive
void autoDrive(){
	SetMotor(left1,127);
	SetMotor(right1,127);
	SetMotor(left2,127);
	SetMotor(right2,127);
	SetMotor(left3,127);
	SetMotor(right3,127);
}

void driveStop(){
	SetMotor(left1,0);
	SetMotor(right1,0);
	SetMotor(left2,0);
	SetMotor(right2,0);
	SetMotor(left3,0);
	SetMotor(right3,0);
}

// Puncher
void autoShoot(int time){
	SetMotor(puncher,127);
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

// Blue flagSide auton
void autonB1 (){ // Blue flag auton
// Start facing flags (on ende of tile)
  // Drive forward to top falg position
  autoDrive();{
  }
  wait1Msec(150);
  driveStop();{
  }
  wait1Msec(50);
  // Shoot top flag
	autoShoot(1300);{
	}
	SetMotor(puncher,0);
	wait1Msec(50);
	// Drive forward to hit bottom flag
	autoDrive();{
  }
  wait1Msec(1700);
  driveStop();{
  }
  wait1Msec(50);
}

// Blue capSide auton
void autonB2 (){ // Blue cap auton

}

// Red flagSide auton
void autonR1 (){ // Red flag auton
// Start facing flags (on ende of tile)
  // Drive forward to top falg position
  autoDrive();{
  }
  wait1Msec(150);
  driveStop();{
  }
  wait1Msec(50);
  // Shoot top flag
	autoShoot(1300);{
	}
	SetMotor(puncher,0);
	wait1Msec(50);
	// Drive forward to hit bottom flag
	autoDrive();{
  }
  wait1Msec(1700);
  driveStop();{
  }
  wait1Msec(50);
}

// Red capSide auton
void autonR2 (){ // Red cap auton

}
