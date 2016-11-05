#include <alarm.h>
#include <machine.h>
#include <nic.h>
#include <utility/ostream.h>
#include <thread.h>
#include <usb.h>
#include <mutex.h>

__USING_SYS

OStream cout;


const unsigned char SINK_ID = 0x33;

int receiver(NIC *nic, Mutex *mutNic) {
    NIC::Protocol prot;
    NIC::Address src; // 77f0

    int ret;

    while (true) {
        long rece[6];
        do {
            mutNic->lock();
            ret = nic->receive(&src, &prot, &rece, sizeof(long)*6);
            mutNic->unlock();
            Delay(100);
        } while (ret <= 0);
        cout << endl;
        cout << "Controlador de Estabilidade para Quadricoptero - EPOS\n";
        cout << "Angle X : " << rece[0] << "\n";
        cout << "Angle Y : " << rece[1] << "\n";
        cout << "Angle Z : " << rece[2] << "\n";
        cout << "Acceleration X : " << rece[3] << "\n";
        cout << "Acceleration Y : " << rece[4] << "\n";
        cout << "Acceleration Z : " << rece[5] << "\n";
    }
    return 0;
}

int sender(NIC *nic, Mutex *mutNic) {
    NIC::Address dest("0:0");
    const int MAX_LEN = 30;
    char msg[MAX_LEN];
    int index = 0;
    
    while (true) {
        do {
            msg[0] = USB::get();
        } while (msg[0] != ':');
        
        index = 0;
        
        while ((index < MAX_LEN) && (msg[index] != '\n')) {
            msg[index] = USB::get();
        }
        msg[index] = '\0';
        memset(msg + index, '\0', MAX_LEN - index);
        
        mutNic->lock();
        nic->send(dest, NIC::PTP, &msg, sizeof(char)*MAX_LEN);
        mutNic->unlock();
    }
    return 0;
}


int main() {
    NIC nic;
    Mutex mut;
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
    Thread *t1 = new Thread(&receiver, &nic, &mut);
    Thread *t2 = new Thread(&sender, &nic, &mut);
    t1->join();
    t2->join();
    Delay(1000000);
    return 0;
}