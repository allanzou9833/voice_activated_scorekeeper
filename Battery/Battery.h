#ifndef BATTERY_H
#define BATTERY_H

#include "mbed.h"

#define REG0B 0x0B
#define REG0E 0x0E
#define REG03 0x03
#define CHRG_STAT_MASK 0x18
#define BATV_MASK 0x7F

#define I2C_ADDR 107 //0x6B
#define CHARGE_LIMIT 4200 //mV
#define SYS_MIN  3000 //mV

class Battery {

public:
    Battery( //may need battery cutoff voltages?
        uint8_t i2c_addr,
        PinName i2c_sda,
        PinName i2c_scl,
        int charge_cutoff_voltage,
        int discharge_cutoff_voltage
    );
    
    enum ChargeStatus { NOT_CHARGING, PRE_CHARGE, FAST_CHARGE, DONE };
    
    ChargeStatus get_charge_status();
    int get_battery_life();

private:
    I2C _charge_ctrl;
    uint8_t _i2c_addr;
    int _max_voltage;
    int _min_voltage;
    
    int convert_bits_to_voltage(uint8_t bits);
    bool is_bit_set(int n, int k);

};

#endif