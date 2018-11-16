#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)



// Auton functions
// Drive
void autoDrive(){
	drivePID(127,127);
}
void autoStop(){
	wait1Msec(100);
}

// Intake
//void autoTake(int time){
//	motor[intake]=127;
//	wait1Msec(time);
//	stopMotor(intake);
//}
//void autoGive(int time){
//	SetMotor(intake,-100);
//	wait1Msec(time);
//	stopMotor(intake);
//}

// Puncher
//void autoShoot(int time){
//	SetMotor(puncher,80);
//	wait1Msec(time);
//	stopMotor(puncher);
//}
