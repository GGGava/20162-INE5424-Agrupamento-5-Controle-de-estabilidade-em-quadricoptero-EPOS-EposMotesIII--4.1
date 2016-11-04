#include <alarm.h>
#include <thread.h>
#include <machine.h>
#include <nic.h>
#include <mutex.h>
#include <utility/ostream.h>

__USING_SYS

using namespace EPOS;

const unsigned char SINK_ID = 0x01;
Mutex mut;

int abc = 1;

OStream cout;

struct Msg {
    float angleX;
    float angleY;
    float angleZ;
    //float accelerationX;
    //float accelerationY;
    //float accelerationZ;
};

int sender(int id) {
    NIC nic;
    //NIC::Protocol prot;
    NIC::Address dest("223:239");

    //unsigned char src, prot;
    unsigned int size;

    Msg msg;

    int i;
    GPIO g('C', 3, GPIO::OUTPUT);
    while (true)
    {
        for (i = 5; i < 8; i++) {
            g.set(i & 0x01);

            msg.angleX  = 10;
            //msg.accelerationX  = 20;

            cout << nic.mtu() << endl;
            char *info = (char *)&msg;
            while( (nic.send(dest, NIC::PTP, info, sizeof(Msg))) == 0){
                cout << "Falha" << endl;
            }

            Delay(1000000);
            cout << "Sender:\t" << nic.address() << endl;
            cout << "Dest:\t" << dest << endl;
        }
    }
    //abc = 2;
    //mut.lock();
    //while(true)
        { cout << id << endl;};
      //  mut.unlock();
    return 0;
}

int main() {
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
    Thread *t1 = new Thread(&sender, 1);
    //sender(2);
    int ret = t1->join();
    Delay(1000000);
    //while(true){ cout << 3 << endl;};
    return 0;
}