/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "Beep.h"
int qua = 150;
uint8 a[] = {0,0,0,0,251,224,199};
uint8 b[] = {188,167,149,141,125,111,99};
uint8 c[] = {93,83,74,70,62,55,49};

void Beep(uint32 length, uint8 pitch)
{
    uint8 cmp = pitch / 2;
    Buzzer_PWM_Start();
    Buzzer_PWM_WriteCompare(cmp);
    Buzzer_PWM_WritePeriod(pitch);
    CyDelay(length);
    Buzzer_PWM_Stop();
}

void Beep_black(uint8 pitch) {
    Beep(qua - 10, pitch);
    CyDelay(10);
}

void Beep_white(uint8 pitch) {
    Beep (qua * 2 - 10, pitch);
    CyDelay(10);
}

void Beep_half(uint8 pitch) {
    Beep (qua/2-10, pitch);
    CyDelay(10);
}

void Beep_third(uint8 pitch) {
    Beep (qua*2/3-10, pitch);
    CyDelay(10);
}

void Beep_whole(uint8 pitch) {
    Beep (qua*4-10, pitch);
    CyDelay(10);
}

void Beep_a(uint8 pitch) {
    Beep (qua*4/3-10, pitch);
    CyDelay(10);
}

void Beep_fourth(uint8 pitch) {
    Beep (qua/4-10, pitch);
    CyDelay(10);
}

void Mario_Victory() {
    qua = 200;
    Beep_third(a[4]); Beep_third(b[0]); Beep_third(b[2]); Beep_third(b[4]); Beep_third(c[0]); Beep_third(c[2]); Beep_white(c[4]); Beep_white(c[2]);
    Beep_third(237); Beep_third(b[0]); Beep_third(158); Beep_third(118); Beep_third(c[0]); Beep_third(78); Beep_white(59); Beep_white(78);
    Beep_third(211); Beep_third(b[1]); Beep_third(b[3]); Beep_third(105); Beep_third(c[1]); Beep_third(c[3]); Beep_white(52); Beep_third(52);  Beep_third(52); Beep_third(52); Beep_whole(46);
}

void Mario_Death() {
    qua = 150;
    Beep_black(b[6]); Beep_black(c[3]); CyDelay(250); Beep_black(c[3]);
    Beep_a(c[3]); Beep_a(c[2]); Beep_a(c[1]);
    Beep_black(c[0]); Beep_black(b[2]); Beep_black(c[2]); Beep_black(b[2]);
    Beep_black(b[0]);
}

void kissTheRain() {
    qua = 640;
    Beep_fourth(a[4]); Beep_fourth(b[0]); Beep_fourth(b[1]);
    Beep_half(b[1]); Beep_half(b[2]); Beep(qua*2.25-10, b[2]); CyDelay(10); Beep_fourth(b[0]); Beep_fourth(b[1]); Beep_fourth(b[2]);
    Beep_half(b[1]); Beep_half(b[4]); Beep(qua*2.25-10, b[4]); CyDelay(10); Beep_fourth(b[4]); Beep_fourth(b[5]); Beep_fourth(b[6]);
    Beep_half(b[6]); Beep_half(c[0]); Beep(qua*1.5 -10, c[0]); CyDelay(10); Beep_half(c[1]); CyDelay(qua/2); Beep_half(c[2]); Beep_half(c[1]); Beep_half(c[0]);
    Beep_black(b[6]); Beep_black(a[6]); Beep_half(b[2]); Beep_half(c[0]); Beep_half(b[6]); Beep_half(b[4]); 
    Beep_fourth(b[4]); Beep_fourth(b[5]); Beep(qua*2.5-10, b[5]); CyDelay(10); Beep_fourth(b[4]); Beep_fourth(b[3]);
    Beep_half(b[3]); Beep_half(b[4]); Beep_black(b[5]); Beep(qua*1.5-10, b[5]); CyDelay(10); Beep_fourth(b[0]); Beep_fourth(b[1]);
    Beep_half(b[2]); Beep_half(b[3]); Beep_white(b[3]); Beep_half(b[4]); Beep_half(b[3]);
}

void saxguys() {
    qua = 420;
    for(;;) {
    Beep_black(b[5]);CyDelay(qua);Beep_half(b[5]);Beep_fourth(b[5]);Beep_fourth(b[5]); Beep_fourth(b[4]); Beep_fourth(b[5]); CyDelay(qua/2);
    Beep_black(b[5]);CyDelay(qua);Beep_half(b[5]);Beep_fourth(b[5]);Beep_fourth(b[5]); Beep_fourth(b[4]); Beep_fourth(b[5]); CyDelay(qua/2);
    Beep_black(b[5]);CyDelay(qua/2);Beep_black(c[0]); Beep_half(b[5]); CyDelay(qua/2); Beep_half(b[4]); 
    Beep_half(b[4]);Beep_half(b[3]); CyDelay(qua/2); Beep_half(b[1]); Beep_half(b[1]); Beep_half(b[2]); Beep_half(b[3]); Beep_half(b[1]);}
    
}
/* [] END OF FILE */
