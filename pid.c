<<<<<<< HEAD
// PID using optical shaft encoder
//
// Shaft encoder has 360 pulses per revolution
//

#define PID_SENSOR_INDEX    leftEncoder
#define PID_SENSOR_SCALE    1

#define PID_MOTOR_INDEX     left1
#define PID_MOTOR_SCALE     -1

#define PID_DRIVE_MAX       127
#define PID_DRIVE_MIN     (-127)

#define PID_INTEGRAL_LIMIT  50

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"
float  pid_Kp = 2.0;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

static int   pidRunning = 1;
static float pidRequestedValue;

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  pid control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task pidController()
{
    float  pidSensorCurrentValue;

    float  pidError;
    float  pidLastError;
    float  pidIntegral;
    float  pidDerivative;
    float  pidDrive;

    // If we are using an encoder then clear it
    if (SensorType[leftEncoder] == sensorQuadEncoder)
        SensorValue[leftEncoder] = 0;
      if (SensorType[rightEncoder] == sensorQuadEncoder)
      	SensorValue[rightEncoder] = 0;

    // Init the variables - thanks Glenn :)
    pidLastError  = 0;
    pidIntegral   = 0;

    while(true)
        {
        // Is PID control active ?
        if(pidRunning)
            {
            // Read the sensor value and scale
            pidSensorCurrentValue = SensorValue[PID_SENSOR_INDEX] * PID_SENSOR_SCALE;

            // calculate error
            pidError = pidSensorCurrentValue - pidRequestedValue;

            // integral - if Ki is not 0
            if(pid_Ki != 0)
                {
                // If we are inside controlable window then integrate the error
                if(abs(pidError) < PID_INTEGRAL_LIMIT)
                    pidIntegral = pidIntegral + pidError;
                else
                    pidIntegral = 0;
                }
            else
                pidIntegral = 0;

            // calculate the derivative
            pidDerivative = pidError - pidLastError;
            pidLastError  = pidError;

            // calculate drive
            pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

            // limit drive
            if( pidDrive > PID_DRIVE_MAX)
                pidDrive = PID_DRIVE_MAX;
            if( pidDrive < PID_DRIVE_MIN)
                pidDrive = PID_DRIVE_MIN;

            // send to motor
            motor[PID_MOTOR_INDEX] = pidDrive * PID_MOTOR_SCALE;
            }
        else
            {
            // clear all
            pidError      = 0;
            pidLastError  = 0;
            pidIntegral   = 0;
            pidDerivative = 0;
            motor[PID_MOTOR_INDEX] = 0;
            }

        // Run at 50Hz
        wait1Msec(25);
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  main task                                                                  */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

void pidForward(int clicks){
    // send the motor off somewhere
    pidRequestedValue = clicks;

    // start the PID task
    startTask(pidController);

    // use joystick to modify the requested position
    while(true)
        {
        // maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
        // free spinning motor is 100rmp so 1.67 rotations per second
        // 1.67 * 360 counts is 600

        //pidRequestedValue = pidRequestedValue + (vexRT[Ch2]/4);

        wait1Msec(50);
        }

}
=======
// PID using optical shaft encoder
//
// Shaft encoder has 360 pulses per revolution
//

#define PID_SENSOR_INDEX    leftEncoder
#define PID_SENSOR_SCALE    1

#define PID_MOTOR_INDEX     left1
#define PID_MOTOR_SCALE     -1

#define PID_DRIVE_MAX       127
#define PID_DRIVE_MIN     (-127)

#define PID_INTEGRAL_LIMIT  50

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"
float  pid_Kp = 2.0;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

static int   pidRunning = 1;
static float pidRequestedValue;

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  pid control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task pidController()
{
    float  pidSensorCurrentValue;

    float  pidError;
    float  pidLastError;
    float  pidIntegral;
    float  pidDerivative;
    float  pidDrive;

    // If we are using an encoder then clear it
    if (SensorType[leftEncoder] == sensorQuadEncoder)
        SensorValue[leftEncoder] = 0;
      if (SensorType[rightEncoder] == sensorQuadEncoder)
      	SensorValue[rightEncoder] = 0;

    // Init the variables - thanks Glenn :)
    pidLastError  = 0;
    pidIntegral   = 0;

    while(true)
        {
        // Is PID control active ?
        if(pidRunning)
            {
            // Read the sensor value and scale
            pidSensorCurrentValue = SensorValue[PID_SENSOR_INDEX] * PID_SENSOR_SCALE;

            // calculate error
            pidError = pidSensorCurrentValue - pidRequestedValue;

            // integral - if Ki is not 0
            if(pid_Ki != 0)
                {
                // If we are inside controlable window then integrate the error
                if(abs(pidError) < PID_INTEGRAL_LIMIT)
                    pidIntegral = pidIntegral + pidError;
                else
                    pidIntegral = 0;
                }
            else
                pidIntegral = 0;

            // calculate the derivative
            pidDerivative = pidError - pidLastError;
            pidLastError  = pidError;

            // calculate drive
            pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

            // limit drive
            if( pidDrive > PID_DRIVE_MAX)
                pidDrive = PID_DRIVE_MAX;
            if( pidDrive < PID_DRIVE_MIN)
                pidDrive = PID_DRIVE_MIN;

            // send to motor
            motor[PID_MOTOR_INDEX] = pidDrive * PID_MOTOR_SCALE;
            }
        else
            {
            // clear all
            pidError      = 0;
            pidLastError  = 0;
            pidIntegral   = 0;
            pidDerivative = 0;
            motor[PID_MOTOR_INDEX] = 0;
            }

        // Run at 50Hz
        wait1Msec(25);
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  main task                                                                  */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

void pidForward(int clicks){
    // send the motor off somewhere
    pidRequestedValue = clicks;

    // start the PID task
    startTask(pidController);

    // use joystick to modify the requested position
    while(true)
        {
        // maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
        // free spinning motor is 100rmp so 1.67 rotations per second
        // 1.67 * 360 counts is 600

        //pidRequestedValue = pidRequestedValue + (vexRT[Ch2]/4);

        wait1Msec(50);
        }

}
>>>>>>> af7f859e7a24c30d3787730daa4e27fadfcfeb5f
