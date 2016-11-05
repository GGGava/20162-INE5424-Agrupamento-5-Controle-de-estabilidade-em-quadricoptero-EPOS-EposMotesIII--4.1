#include <alarm.h>
#include <thread.h>
#include <machine.h>
#include <nic.h>
#include <mutex.h>
#include <utility/ostream.h>
#include "LSM330.cc"

__USING_SYS

using namespace EPOS;

const unsigned char SINK_ID = 0x01;
Mutex mut;

long msg[6];

//OStream cout;

int sender(int id) {
    NIC nic;
    NIC::Address dest("223:239");
    LSM330 sensor;

    int i;
    //GPIO g('C', 3, GPIO::OUTPUT);
    mut.lock();
    while (true)
    {
        msg[0] = sensor.getAngleX();;
        msg[1] = sensor.getAngleY();;
        msg[2] = sensor.getAngleZ();;
        msg[3] = sensor.getAccelerationX();
        msg[4] = sensor.getAccelerationY();
        msg[5] = sensor.getAccelerationZ();

        while( (nic.send(dest, NIC::PTP, &msg, sizeof(long)*6)) == 0){
            cout << "Falha" << endl;
        }

        cout << "Pacote Enviado" << endl;
        cout << "Sender:\t" << nic.address() << endl;
        cout << "Dest:\t" << dest << endl;
        Delay(1000000);
    }
    mut.unlock();
    return 0;
}

int main() {
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
    Thread *t1 = new Thread(&sender, 1);
    int ret = t1->join();
    Delay(1000000);
    return 0;
}