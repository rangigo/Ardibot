/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "I2C_made.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "IR.h"
#include "Ambient.h"
#include "Beep.h"
#include <time.h>
#include <stdlib.h>


int rread(void);

/**
 * @file    main.c
 * @brief   
 * @details  ** You should enable global interrupt for operating properly. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

/*//Sumo
//
int check()
{
    struct sensors_ asdf;
    reflectance_digital(&asdf);
    if (asdf.l1 == 0 || asdf.r1 == 0 || asdf.l3 == 0 || asdf.r3 == 0) return(1);
    return(0);
}
int main()
{
    CyGlobalIntEnable; 
    UART_1_Start(); 
    sensor_isr_StartEx(sensor_isr_handler); 
    reflectance_start(); 
    IR_led_Write(1);
    ADC_Battery_Start();
    CyDelay(2000);        
    BatteryLed_Write(1);
    motor_start();
    struct sensors_ ref;
    srand(time(NULL));
    do 
    {
        reflectance_digital(&ref);
        if (ref.l1 == 1 && ref.r1 == 0) motor_turn(100, -100, 1);
        else if (ref.l1 == 0 && ref.r1 == 1) motor_turn(-100, 100, 1);
        else if (ref.l1 == 0 && ref.r1 == 0) motor_forward(100, 1);
    }
    while (!(ref.l1 == 0 && ref.r1 == 0 && ref.l3 == 0 && ref.r3 == 0));
    motor_stop();
    get_IR();
    motor_start();
    while (ref.l1 == 0 || ref.r1 == 0 || ref.l3 == 0 || ref.r3 == 0) {motor_forward(255, 10); reflectance_digital(&ref);}
    motor_turn(255, 100, 500);
    for(;;) 
    {
        int r = rand()%2; int delay = rand()%750; int back = rand()%500; int dev = rand()%256;
        if (check() == 1) 
        {
            motor_backward(255, back + 250);
            if (r == 0) motor_turn(255, dev-255, delay);
            else motor_turn(dev-255, 255, delay);
        }
        while (check() == 0) motor_forward(255, 1);
    }
}
//*/

//Line Follower
//
int main()
{
    //Set constants and variables declaration
    float ki = 0.025, kp = 1.75, kd = 25, volts = 0;
    float pred = 0, diff = 0, pro, integral, aval = 0, derv;
    int driver, count = 0;
    int i,j;
    int max_speed = 255, mina = 80, limit = 20000;
    int breaking_point = 0;
    struct sensors_ ref, cal;
    int16 adcresult = 0;
    int min[] = {24000, 24000, 24000, 24000}, max[] = {0, 0, 0, 0};
    int time = -1;
    
    //Warming up
    CyGlobalIntEnable; UART_1_Start(); sensor_isr_StartEx(sensor_isr_handler); reflectance_start(); IR_led_Write(1);
    Ultra_Start();
    ADC_Battery_Start();
    CyDelay(2000);        
    BatteryLed_Write(1);
    motor_start();
    for(i = 0; i < 700; i++) 
    {
        if (i < 75 || (i > 225 && i < 375) || i > 525) motor_turn(100,-100,1);
        else motor_turn(-100,100,1);
        CyDelay(5);
        reflectance_read(&ref);
        if (ref.l3 > max[0]) max[0] = ref.l3;
        if (ref.l1 > max[1]) max[1] = ref.l1;
        if (ref.r1 > max[2]) max[2] = ref.r1;
        if (ref.r3 > max[3]) max[3] = ref.r3;
        if (ref.l3 < min[0]) min[0] = ref.l3;
        if (ref.l1 < min[1]) min[1] = ref.l1;
        if (ref.r1 < min[2]) min[2] = ref.r1;
        if (ref.r3 < min[3]) min[3] = ref.r3;
    }
    BatteryLed_Write(0);
    reflectance_set_threshold((min[0] + max[0]*4)/5, (min[1] + max[1]*3)/4, (min[2] + max[2]*3)/4, (min[3] + max[3]*4)/5);
    cal.l3 = (min[0] + max[0]*3)/4; cal.l1 = (min[1] + max[1]*3)/4; cal.r1 = (min[2] + max[2]*3)/4; cal.r3 = (min[3] + max[3]*3)/4;
    printf("%d %d %d %d\n", min[0], min[1], min[2], min[3]);
    printf("%d %d %d %d\n", max[0], max[1], max[2], max[3]);
    printf("%d %d %d %d\n", (min[0] + max[0]*3)/4, (min[1] + max[1]*3)/4, (min[2] + max[2]*3)/4, (min[3] + max[3]*3)/4);
    mina = ((min[1] + max[1]*3)/4 - min[1] + (min[2] + max[2]*3)/4 - min[2])/((max_speed + 1) * 2);
    do {
        motor_static_turn_l(1);
        reflectance_digital(&ref);
    } while(ref.r1 != 0 && ref.l1 != 0);
    while (!(ref.l1 == 0 && ref.r1 == 0 && ref.l3 == 0 && ref.r3 == 0))
    {
                reflectance_read(&ref);
                i = (cal.l1 - ref.l1)/mina; j = (cal.r1 - ref.r1)/mina;
                if (time >= 1 || time == -1)
                {
                    if (time == -1) time = 1;
                    if (i <= 5) i = 0; if (j <= 5) j = 0;
                    pred = diff;
                    diff = j - i;
                    pro = diff * kp;
                    aval += diff*time;
                    if (aval > limit) aval = limit;
                    if (aval < -limit) aval = -limit;
                    integral = aval*ki;
                    derv = (diff - pred)/time;
                    derv *= kd;
                    driver = (pro + integral + derv);
                    time = 0;
                }
                if (driver > max_speed*2) driver = max_speed*2;
                if (driver < -max_speed*2) driver = -max_speed*2;
                if (driver > breaking_point) motor_turn(max_speed - driver, max_speed, 1);
                else if (driver < -breaking_point) motor_turn(max_speed, max_speed + driver, 1);
                else motor_forward(max_speed, 1);
                time += 1;
                reflectance_digital(&ref);
    }
    aval = 0; pred = 0;
    motor_stop();
    get_IR();
    motor_start();
    do {motor_forward(255, 1); reflectance_digital(&ref);} while (ref.l3 == 0 || ref.r3 == 0);
    for(;;)
    {
        ADC_Battery_StartConvert();
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) 
        {
            adcresult = ADC_Battery_GetResult16();
            volts = ADC_Battery_CountsTo_Volts(adcresult);                  // convert value to Volts
            adcresult *= 1.5;
        }
        if (adcresult > 5) 
        {
            reflectance_digital(&ref);
            if (ref.r3 == 1 && ref.l3 == 1) 
            {
                reflectance_read(&ref);
                i = (cal.l1 - ref.l1)/mina; j = (cal.r1 - ref.r1)/mina;
                if (time >= 1 || time == -1)
                {
                    if (time == -1) time = 1;
                    if (i <= 5) i = 0; if (j <= 5) j = 0;
                    pred = diff;
                    diff = j - i;
                    pro = diff * kp;
                    aval += diff*time;
                    if (aval > limit) aval = limit;
                    if (aval < -limit) aval = -limit;
                    integral = aval*ki;
                    derv = (diff - pred)/time;
                    derv *= kd;
                    driver = (pro + integral + derv);
                    time = 0;
                }
                if (driver > max_speed*2) driver = max_speed*2;
                if (driver < -max_speed*2) driver = -max_speed*2;
                if (driver > breaking_point) motor_turn(max_speed - driver, max_speed, 1);
                else if (driver < -breaking_point) motor_turn(max_speed, max_speed + driver, 1);
                else motor_forward(max_speed, 1);
                time += 1;
            }
            else if (ref.r3 == 0)
            {
                printf("Turning left\n");
                while (ref.l1 != 1 || ref.r1 != 1) 
                {                
                    motor_forward(125, 2);
                    if (ref.l3 == 0 && ref.r3 == 0) {
                        if (count < 1) 
                        {
                            while (ref.l3 == 0 || ref.r3 == 0) {motor_forward(255, 1); reflectance_digital(&ref);}
                            count++; for (i = 0; i < count; i++) {Beep(100, 100); CyDelay(10);}
                            break;
                        }
                        else {motor_stop(); Mario_Victory(); return 0;}
                    }
                    reflectance_digital(&ref);
                };
                if (count == 0) 
                {
                    while (ref.l1 != 0 && ref.r1 != 0) 
                        {
                            motor_turn(-100, 100, 1);
                            reflectance_digital(&ref);
                        }
                        pred = 0;
                        integral = 0;
                }
            }
            else if (ref.l3 == 0)
            {
                printf("Turning right\n");
                while (ref.l1 != 1 || ref.r1 != 1) 
                {                
                    motor_forward(125, 2);
                    if (ref.l3 == 0 && ref.r3 == 0) {
                        if(count < 1) 
                        {
                            while (ref.l3 == 0 || ref.r3 == 0) {motor_forward(255, 1); reflectance_digital(&ref);}
                            count++;  for (i = 0; i < count; i++) {Beep(100, 100); CyDelay(10);}
                            break;
                        }
                        else {motor_stop(); Mario_Victory(); return 0;}
                    }
                    reflectance_digital(&ref);
                };
                if (count == 0) 
                {
                    while (ref.l1 != 0 && ref.r1 != 0) 
                        {
                            motor_turn(-100, 100, 1);
                            reflectance_digital(&ref);
                        }
                        pred = 0;
                        integral = 0;
                }
            }
        }
        else {motor_stop(); Mario_Death(); return 0;}
    }
}
//*/
 
#if 0
int rread(void)
{
    SC0_SetDriveMode(PIN_DM_STRONG);
    SC0_Write(1);
    CyDelayUs(10);
    SC0_SetDriveMode(PIN_DM_DIG_HIZ);
    Timer_1_Start();
    uint16_t start = Timer_1_ReadCounter();
    uint16_t end = 0;
    while(!(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC)) {
        if(SC0_Read() == 0 && end == 0) {
            end = Timer_1_ReadCounter();
        }
    }
    Timer_1_Stop();
    
    return (start - end);
}
#endif

/* Don't remove the functions below */
int _write(int file, char *ptr, int len)
{
    (void)file; /* Parameter is not used, suppress unused argument warning */
	int n;
	for(n = 0; n < len; n++) {
        if(*ptr == '\n') UART_1_PutChar('\r');
		UART_1_PutChar(*ptr++);
	}
	return len;
}

int _read (int file, char *ptr, int count)
{
    int chs = 0;
    char ch;
 
    (void)file; /* Parameter is not used, suppress unused argument warning */
    while(count > 0) {
        ch = UART_1_GetChar();
        if(ch != 0) {
            UART_1_PutChar(ch);
            chs++;
            if(ch == '\r') {
                ch = '\n';
                UART_1_PutChar(ch);
            }
            *ptr++ = ch;
            count--;
            if(ch == '\n') break;
        }
    }
    return chs;
}
/* [] END OF FILE */

