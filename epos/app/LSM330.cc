
#include <machine.h>
#include <alarm.h>
#include <utility/ostream.h>
#include <i2c.h>
#include <gpio.h>
#include <cpu.h>
#include <utility/math.h>

using namespace EPOS;

OStream cout;

class LSM330
{
private:
    //Addresses
    enum Addr {
        I2C_Accl = 0x1D,
        I2C_Gyro = 0x6B,
    };
    enum Accelerometer {
        WHO_AM_I_A   = 0x0F,
        CTRL4_A      = 0x23,
        CTRL5_A      = 0x20,
        CTRL6_A      = 0x24,
        CTRL7_A      = 0x25,
        STATUS_A     = 0x27,
        OFF_X_A      = 0x10,
        OFF_Y_A      = 0x11,
        OFF_Z_A      = 0x12,
        CS_X_A       = 0x13,
        CS_Y_A       = 0x14,
        CS_Z_A       = 0x15,
        LC_L_A       = 0x16,
        LC_H_A       = 0x17,
        STAT_A       = 0x18,
        VFC_1_A      = 0x1B,
        VFC_2_A      = 0x1C,
        VFC_3_A      = 0x1D,
        VFC_4_A      = 0x1E,
        THRS3        = 0x1F,
        OUT_X_L_A    = 0x28,
        OUT_X_H_A    = 0x29,
        OUT_Y_L_A    = 0x2A,
        OUT_Y_H_A    = 0x2B,
        OUT_Z_L_A    = 0x2C,
        OUT_Z_H_A    = 0x2D,
        FIFO_CTRL_A  = 0x2E,
        FIFO_SRC_A   = 0x2F,
        CTRL2_A      = 0x21,
        STX_BASE_1_A = 0x40,
        TIM4_1_A     = 0x50,
        TIM3_1_A     = 0x51,
        TIM2_L_1_A   = 0x52,
        TIM2_H_1_A   = 0x53,
        TIM1_L_1_A   = 0x54,
        TIM1_H_1_A   = 0x55,
        THRS2_1_A    = 0x56,
        THRS1_1_A    = 0x57,
        MASKB_1_A    = 0x59,
        MASKA_1_A    = 0x5A,
        SETT1_A      = 0x5B,
        PR1_A        = 0x5C,
        TC1_L_A      = 0x5D,
        TC1_H_A      = 0x5E,
        OUTS1_A      = 0x5F,
        PEAK1_A      = 0x19,
        CTRL3_A      = 0x22,
        STX_BASE_2_A = 0x60,
        TIM4_2_A     = 0x70,
        TIM3_2_A     = 0x71,
        TIM2_L_2_A   = 0x72,
        TIM2_H_2_A   = 0x73,
        TIM1_L_2_A   = 0x74,
        TIM1_H_2_A   = 0x75,
        THRS2_2_A    = 0x76,
        THRS1_2_A    = 0x77,
        MASKB_2_A    = 0x79,
        MASKA_2_A    = 0x7A,
        SETT2_A      = 0x7B,
        PR2_A        = 0x7C,
        TC2_L_A      = 0x7D,
        TC2_H_A      = 0x7E,
        OUTS2_A      = 0x7F,
        PEAK2_A      = 0x1A,
        DES2         = 0x78,
    };
    
    enum Gyroscope {
        WHO_AM_I_G        = 0x0F,
        CTRL1_G           = 0x20,
        CTRL2_G           = 0x21,
        CTRL3_G           = 0x22,
        CTRL4_G           = 0x23,
        CTRL5_G           = 0x24,
        REFERENCE_G       = 0x25,
        OUT_TEMP_G        = 0x26,
        STATUS_G          = 0x27,
        OUT_X_L_G         = 0x28,
        OUT_X_H_G         = 0x29,
        OUT_Y_L_G         = 0x2A,
        OUT_Y_H_G         = 0x2B,
        OUT_Z_L_G         = 0x2C,
        OUT_Z_H_G         = 0x2D,
        FIFO_CTRL_G       = 0x2E,
        FIFO_SRC_G        = 0x2F,
        INT1_CFG_G        = 0x30,
        INT1_SRC_G        = 0x31,
        INT1_THS_XH_G     = 0x32,
        INT1_THS_XL_G     = 0x33,
        INT1_THS_YH_G     = 0x34,
        INT1_THS_YL_G     = 0x35,
        INT1_THS_ZH_G     = 0x36,
        INT1_THS_ZL_G     = 0x37,
        INT1_DURATION_G   = 0x38,
    };
    static const char AUTO_INC = 0x80;

    void init() {
//         char msg_g[2] = {CTRL1_G, 0x0F};
//          _i2c->put(I2C_Gyro, msg_g, 2) ;
//         msg_g[0] = CTRL4_G;
//         msg_g[1] = 0x3 << 4;
//          _i2c->put(I2C_Gyro, msg_g, 2) ;
//          _i2c->put(I2C_Gyro, WHO_AM_I_G) ;
//          _i2c->get(I2C_Gyro, msg_g);
//          _i2c->get(I2C_Gyro, &msg_g[1]);
//         cout << "Gyro: " << (int)msg_g[0] << '\t' << (int)msg_g[1] << endl;
//         Delay(10000000);
        char msg_a[] = {CTRL5_A, 0x97};
         _i2c->put(I2C_Accl, msg_a, 2) ;
         _i2c->put(I2C_Accl, WHO_AM_I_A) ;
         _i2c->get(I2C_Accl, msg_a);
         _i2c->get(I2C_Accl, &msg_a[1]);
//         cout << "Acce: " << (int)msg_a[0] << '\t' << (int)msg_a[1] << endl;
    }
    
    
    float acos(float x) {
        return (-0.69813170079773212f * x * x - 0.87266462599716477f) * x + 1.5707963267948966f;
    }
public:
    LSM330() {
//         cout << "Initializing LSM330" << endl;
        _i2c = new I2C(EPOS::S::I2C_Common::MASTER, 'B', 1, 'B', 0);
        init();
    }

    int reset(void) {
        init();
        return 0;
    }

    float getAngleX() {
        return 180*acos(accel[0] / norm)/3.14;
    }

    float getAngleY() {
        return 180*acos(accel[1] / norm)/3.14;
    }

    float getAngleZ() {
        return 180*acos(accel[2] / norm)/3.14;
    }

    short getAccelerationX() {
        char byte[2] = {0, 0};
         _i2c->get(I2C_Accl, OUT_X_L_A | AUTO_INC, byte, 2);
        return (byte[1] << 8) | byte[0];
    }

    short getAccelerationY() {
        char byte[2] = {0, 0};
         _i2c->get(I2C_Accl, OUT_Y_L_A | AUTO_INC, byte, 2);
        return (byte[1] << 8) | byte[0];
    }

    short getAccelerationZ() {
        char byte[2] = {0, 0};
         _i2c->get(I2C_Accl, OUT_Z_L_A | AUTO_INC, byte, 2);
        return (byte[1] << 8) | byte[0];
    }
    
    void readValues(void) {
        char byte[6];
         _i2c->get(I2C_Accl, OUT_X_L_A | AUTO_INC, byte, 6);
        accel[0] = (float)((signed short int)((byte[1] << 8) | byte[0]))/16384.0;
        accel[1] = (float)((signed short int)((byte[3] << 8) | byte[2]))/16384.0;
        accel[2] = (float)((signed short int)((byte[5] << 8) | byte[4]))/16384.0;
        norm = sqrt(accel[0] * accel[0] +
                    accel[1] * accel[1] +
                    accel[2] * accel[2]);
    }

private:
    I2C * _i2c;
    float accel[3];
    float norm;
};

// int main()
// {
//     Delay(3000000);
//     cout << "I2C/Accelerometer/Gyroscope test" << endl;
//     cout << "Start" << endl;
//     LSM330 gyro;
//     int value;
//     while(1) {
//         gyro.readValues();
//         cout << "V: " << gyro.getAngleX() << '\t' << gyro.getAngleY() << '\t' << gyro.getAngleZ() << endl;
//         Delay(10000);
//     }
//     return 0;
// }
