#include <alarm.h>
#include <machine.h>
#include <nic.h>
#include <utility/ostream.h>
#include <thread.h>
#include <mutex.h>

__USING_SYS

OStream cout;

Mutex mut;

const unsigned char SINK_ID = 0x33;

int receiver(int id) {
    NIC nic;
    NIC::Protocol prot;
    NIC::Address src; // 77f0



    //unsigned char src, prot;
    int i;

    mut.lock();
    while (true) {
        long rece[6];
        while(!(nic.receive(&src, &prot, &rece, sizeof(long)*6) > 0)){
        }
        cout << endl;
        cout << "Controlador de Estabilidade para Quadricoptero - EPOS\n";
        cout << "Angle X : " << rece[0] << "\n";
        cout << "Angle Y : " << rece[1] << "\n";
        cout << "Angle Z : " << rece[2] << "\n";
        cout << "Acceleration X : " << rece[3] << "\n";
        cout << "Acceleration Y : " << rece[4] << "\n";
        cout << "Acceleration Z : " << rece[5] << "\n";
    }
    mut.unlock();

    return 0;
}

int main() {
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
    Thread *t1 = new Thread(&receiver, 2);
    int ret = t1->join();
    Delay(1000000);
    return 0;
}