#include <alarm.h>
#include <machine.h>
#include <nic.h>
#include <utility/ostream.h>
#include <thread.h>
#include <usb.h>
#include <mutex.h>

#include <utility/string.h>

__USING_SYS

OStream cout;

Mutex mutUSB;
Mutex mutNic;
NIC nic;

const unsigned char SINK_ID = 0x33;

int receiver(int id) {
    NIC::Protocol prot;
    NIC::Address src; // 77f0

    int ret;

    while (true) {
        float rece[3];
        do {
            mutNic.lock();
            ret = nic.receive(&src, &prot, &rece, sizeof(float)*3);
            mutNic.unlock();
            Delay(100);
        } while (ret <= 0);
        mutUSB.lock();
        cout << endl;
//         cout << "Controlador de Estabilidade para Quadricoptero - EPOS\n";
        cout << "Angle X : " << rece[0] << "\n";
        cout << "Angle Y : " << rece[1] << "\n";
        cout << "Angle Z : " << rece[2] << "\n";
        mutUSB.unlock();
    }
    return 0;
}

int sender(int id) {
    NIC::Address dest(NIC::Address::BROADCAST);
    const int MAX_LEN = 31;
    char msg[MAX_LEN];
    int index = 0, i, paramIndex;
    int parameters[2];
    Delay(1000000);
    cout << "teste" << endl;
    Delay(1000000);
    while (true) {
        do {
            mutUSB.lock();
            if (USB::ready_to_get()) {
                msg[0] = USB::get();
//                 cout << msg[0];
            }
            mutUSB.unlock();
            Delay(100);
        } while (msg[0] != ':');
        
        index = 0;
        
        while ((index < (MAX_LEN-1))) {
            mutUSB.unlock();
            if(USB::ready_to_get()) {
                msg[index] = USB::get();
//                 cout << msg[index];
                if (msg[index] == '\n' || msg[index] == '\r') {
                    break;
                }
                index++;
            }
            mutUSB.unlock();
            Delay(100);
        }
        
        memset(msg + index, '\0', MAX_LEN - index);
        
        cout << endl << msg << endl;
        
        paramIndex = 0;
        index = 0;
        for (i = 0; i < MAX_LEN; i++) {
          if (msg[i] > '9' || msg[i] < '0') {
            msg[i] = '\0';
            parameters[paramIndex++] = atoi(&msg[index]);
            index = ++i;
            if (paramIndex == 2)
              break;
          }
        }
        
        mutNic.lock();
        nic.send(dest, NIC::PTP, &parameters, sizeof(int)*2);
        mutNic.unlock();
    }
    return 0;
}


int main() {
    char msg;
    Delay(3000000);
    cout << "Controle de Estabilidade em Quadricoptero - EPOS" << endl;
//     Delay(1000000);
    Thread *t1 = new Thread(&receiver,1);
    Thread *t2 = new Thread(&sender,1);
    t1->join();
    t2->join();
    while (1);
    return 0;
}
