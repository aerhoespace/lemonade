#pragma config(Motor,  port7,           g,             tmotorVex393_MC29, openLoop)

task main(){
	while(true){
		if(vexRT[Btn6U]==1){
			motor[g]=127;
			} else{
			motor[g]=0;
		}
	}
}
