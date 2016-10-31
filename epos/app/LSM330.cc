
#include <machine.h>
#include <alarm.h>
#include <utility/ostream.h>
#include <i2c.h>
#include <gpio.h>
#include <cpu.h>

using namespace EPOS;

OStream cout;

// class LSM330
// {
// private:
//     //Addresses
//     enum Accelerometer {
//         
//     };
//     
//     enum Gyroscope {
//         
//     };
// 
// public:
// 
//     LSM330() {
//         _i2c =  new I2C(MASTER, 'B', 1, 'B', 0); //master, SDA = PB1, SCL = PB0
//     }
// 
//     int reset(void) {
//         return 0;
//     }
// 
//     float getAngleX() {
//         return 0;
//     }
// 
//     float getAngleY() {
//         return 0;
//     }
// 
//     float getAngleZ() {
//         return 0;
//     }
// 
//     float getAccelerationX() {
//         return 0;
//     }
// 
//     float getAccelerationY() {
//         return 0;
//     }
// 
//     float getAccelerationZ() {
//         return 0;
//     }
// 
// private:
//     I2C * _i2c;
// };

int main()
{
//     LSM330 gyro;
    cout << "I2C test" << endl;
    GPIO g('C',3, GPIO::OUTPUT);
    
    cout << "Start" << endl;
    while(1) {
        Delay(100000);
        cout << "Set" << endl;
        g.set(1);
        Delay(100000);
        cout << "reset" << endl;
        g.set(0);
    }
    return 0;
}
