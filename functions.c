#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)



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

// Drive encoders
int leftEncode(int clicks){
	return(SensorValue[leftEncoder]);
}
int rightEncode(int clicks){
	return(SensorValue[rightEncoder]);
}

// User control drive functions
void driveFunc(int speed1, int speed2){
	motor[left1]= speed1;
	motor[right1]= speed2;
	motor[left2]= speed1;
	motor[right2]= speed2;
	motor[left3]= speed1;
	motor[right3]= speed2;
}
void drive(){
	driveFunc(vexRT[Ch3], vexRT[Ch2]);
}

// Stop motor
void stopMotor(int time){
	wait1Msec(time);
}
