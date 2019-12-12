#include "mbed.h"
#include "Battery.h"

Battery::Battery (
    uint8_t i2c_addr,
    PinName i2c_sda,
    PinName i2c_scl,
    int charge_cutoff_voltage,
    int discharge_cutoff_voltage
) : _charge_ctrl(i2c_sda, i2c_scl)
{
    _i2c_addr = i2c_addr << 1;
    _max_voltage = charge_cutoff_voltage;
    _min_voltage = discharge_cutoff_voltage;

    char reg = REG03;
    _charge_ctrl.write(_i2c_addr, &reg, 1);
    
    //check battery life and shutdown if too low
}

Battery::ChargeStatus Battery::get_charge_status()
{
    char data = REG0B;
    _charge_ctrl.write(_i2c_addr, &data, 1);
    
    //wait
    
    _charge_ctrl.read(_i2c_addr, &data, 1);
    
    uint8_t charge_status = (data & CHRG_STAT_MASK) >> 3;
    ChargeStatus ret;
    
    switch(charge_status) {
        case 0x00:
            ret = NOT_CHARGING;
            break;
        case 0x01:
            ret = PRE_CHARGE;
            break;
        case 0x02:
            ret = FAST_CHARGE;
            break;
        case 0x03:
            ret = DONE;
            break;
    };
    
    return ret;
}

int Battery::get_battery_life()
{
    char data = REG0E;
    _charge_ctrl.write(_i2c_addr, &data, 1);
    
    //wait ThisThread::sleep_for()
    
    _charge_ctrl.read(_i2c_addr, &data, 1);
    uint8_t batv = (data & BATV_MASK);
    
    //map bits to voltage according to datasheet and sum to get current Vbat
    int battery_percent = ((convert_bits_to_voltage(batv) + 2304) - _min_voltage)/ (_max_voltage - _min_voltage);
    
    return battery_percent;
    
}

int Battery::convert_bits_to_voltage(uint8_t bits)
{
    int voltages[7] = {20, 40, 80, 160, 320, 640, 1280};
    int ret_voltage = 0;
    for(int i = 1; i < 8; i++){
         ret_voltage += is_bit_set(bits, i) ? voltages[i] : 0;
    }
    return ret_voltage;
}   

bool Battery::is_bit_set(int n, int k)
{
    if((n >> (k-1)) & 1)
        return true;
    return false;
}