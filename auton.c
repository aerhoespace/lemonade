#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// Drive encoders
int leftEncode(){
	return(SensorValue[leftEncoder]);
}
int rightEncode(){
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

// Auton Middle Level
// Drive functions
// Drive Function Middle Level
void driveStraight(int power){
	drivePID(power,power);
}
void driveStop(){
	drivePID(0,0);
}

// Auton High Level
void auton(){
	drivePID(100,100);
	wait1Msec(100);
}
void driveStop(){
	wait1Msec(100);
}
