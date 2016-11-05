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

int sender(NIC *nic, Mutex *mutNic) {
    NIC::Address dest("223:239");
    LSM330 sensor;

    int ret;
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

        do {
            mutNic->lock();
            ret = nic->send(dest, NIC::PTP, &msg, sizeof(long)*6);
            mutNic->unlock();
            Delay(100);
        } while( ret == 0);

        cout << "Pacote Enviado" << endl;
        cout << "Sender:\t" << nic->address() << endl;
        cout << "Dest:\t" << dest << endl;
        Delay(1000000);
    }
    mut.unlock();
    return 0;
}

int receiver(NIC *nic, Mutex *mutNic) {
    NIC::Protocol prot;
    NIC::Address src;
    const int MAX_LEN = 30;
    char msg[MAX_LEN];
    int ret;
    while (true) {
        do {
            mutNic->lock();
            ret = nic->receive(&src, &prot, &msg, sizeof(char)*MAX_LEN);
            mutNic->unlock();
            Delay(100);
        } while(ret <= 0);
        cout << "Parse this message:" << endl;
        cout << msg << endl;
        cout << "Then send to PID controller" << endl;
    }
    return 0;
}

int main() {
    NIC nic;
    Mutex mut;
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
    Thread *t1 = new Thread(&sender, &nic, &mut);
    Thread *t2 = new Thread(&receiver, &nic, &mut);
    t1->join();
    t2->join();
    Delay(1000000);
    return 0;
}
