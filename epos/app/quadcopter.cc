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
NIC nic;
Mutex mutNic;
Mutex mutOStream;

long msg[6];

//OStream cout;

int sender(int id) {
    NIC::Address dest(NIC::Address::BROADCAST);
    LSM330 sensor;

    int ret;
    while (true)
    {
        msg[0] = sensor.getAngleX();;
        msg[1] = sensor.getAngleY();;
        msg[2] = sensor.getAngleZ();;
        msg[3] = sensor.getAccelerationX();
        msg[4] = sensor.getAccelerationY();
        msg[5] = sensor.getAccelerationZ();

        do {
            mutNic.lock();
            ret = nic.send(dest, NIC::PTP, &msg, sizeof(long)*6);
            mutNic.unlock();
            Delay(100);
        } while( ret == 0);

        mutOStream.lock();
        cout << "Pacote Enviado" << endl;
        cout << "Sender:\t" << nic.address() << endl;
        cout << "Dest:\t" << dest << endl;
        mutOStream.unlock();
        Delay(1000000);
    }
    return 0;
}

int receiver(int id) {
    NIC::Protocol prot;
    NIC::Address src;
    const int MAX_LEN = 30;
    char msg[MAX_LEN];
    int ret;
    while (true) {
        do {
            mutNic.lock();
            ret = nic.receive(&src, &prot, &msg, sizeof(char)*MAX_LEN);
            mutNic.unlock();
            Delay(100);
        } while(ret <= 0);
        mutOStream.lock();
        cout << "Parse this message:" << endl;
        cout << msg << endl;
        cout << "Then send to PID controller" << endl;
        mutOStream.unlock();
    }
    return 0;
}

int main() {
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
    Thread *t1 = new Thread(&sender, 1);
    Thread *t2 = new Thread(&receiver, 1);
    t1->join();
    t2->join();
    Delay(1000000);
    return 0;
}
