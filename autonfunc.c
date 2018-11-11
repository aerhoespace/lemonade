void autoDrive(int speed3, int speed4){
	SetMotor(left1,speed3);
	SetMotor(right1,speed4);
	SetMotor(left2,speed3);
	SetMotor(right2,speed4);
	SetMotor(left3,speed3);
	SetMotor(right3,speed4);
}
void autoShoot(int power1){
	SetMotor(puncher,power1);
}
