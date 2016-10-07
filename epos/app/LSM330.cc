#include <machine.h>
#include <alarm.h>
#include <utility/ostream.h>
#include <i2c.h>
#include <gpio.h>
#include <cpu.h>
#include <machine/cortex_m/emote3_gptm.h>

using namespace EPOS;

OStream cout;

class LSM330
{
private:
    //Addresses
    enum Accelerometer {
        
    };
    
    enum Gyroscope {
        
    };

public:

    LSM330() {
        _i2c =  new I2C(MASTER, 'B', 1, 'B', 0); //master, SDA = PB1, SCL = PB0
    }

    int reset(void) {
        return 0;
    }

    int getAngleX() {
        return 0;
    }

    int getAngleY() {
        return 0;
    }

    int getAngleZ() {
        return 0;
    }

    int getAccelerationX() {
        return 0;
    }

    int getAccelerationY() {
        return 0;
    }

    int getAccelerationZ() {
        return 0;
    }

private:
    I2C * _i2c;
};

int main()
{
    LSM330 accelerometer;
    cout << "I2C Test\n";
    GPIO g('c',3, GPIO::OUTPUT);
    while(1) {

    }
    return 0;
}