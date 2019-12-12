#include "mbed.h"
#include "Team/Team.h"
// #include "Microphone/Microphone.h"
// #include "Battery/Battery.h"
// #include "KWS/main_functions.h"

int main()
{   
    Serial pc(SERIAL_TX, SERIAL_RX);
    DigitalOut led2(LED2);
    Team team_2(PB_0, PA_14, PC_0, PD_2, PB_6, PB_5);
    // Team team_1(PA_0, USER_BUTTON, PC_0, PA_1, PA_2, PA_3);
    Team team_1(PB_1, PC_3, PF_13, PB_7, PB_6, PB_5);
    // Battery battery(I2C_ADDR, PC_11, PC_12, CHARGE_LIMIT, SYS_MIN);
    pc.printf("Program start\n");
    // setup();
    while(1){
        // loop();
        led2 = !led2;
        pc.printf("Team 1: %d | Team 2: %d\n", team_1.read_score(), team_2.read_score());
        wait(2);
    }
}
    