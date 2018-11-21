#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)


// Drive encoders
int leftEncode(int clicks){
	return(SensorValue[leftEncoder]);
}
int rightEncode(int clicks){
	return(SensorValue[rightEncoder]);
}

// Drive PID
void leftDrivePID(int clicks){
	pidRequestedValue = clicks;
}
void rightDrivePID(int clicks){
	pidRequestedValue = clicks;
}
void drivePID(int power1, int power2){
	leftDrivePID(power1);
	rightDrivePID(power2);
}

// Auton functions
// Stop motor
void stopMotor(int time){
	wait1Msec(time);
}

// Intake
void autoTake(int time){
	SetMotor(intake,127);
	wait1Msec(time);
	stopMotor(50);
}
void autoGive(int time){
	SetMotor(intake,-127);
	wait1Msec(time);
	stopMotor(50);
}

// Puncher
void autoShoot(int time){
	SetMotor(puncher,80);
	wait1Msec(time);
	stopMotor(50);
}
