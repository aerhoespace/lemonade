// Auton High Level
void auton(){
	leftDrivePID(-100);
	rightDrivePID(-100);
}

// Puncher auton
void autonPunch(){
	SetMotor(puncher,80);
}
