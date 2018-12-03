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

// User control drive functions
void driveFunc(int speed1, int speed2){
	SetMotor(left1,speed1);
	SetMotor(right1,speed2);
	SetMotor(left2,speed1);
	SetMotor(right2,speed2);
	SetMotor(left3,speed1);
	SetMotor(right3,speed2);
}
void drive(){
	driveFunc(vexRT[Ch3]/0.7,vexRT[Ch2]/0.7);
	// Change speed = driveFunc(vexRT[Ch3]/0.7,vexRT[Ch2]/0.7);
}
