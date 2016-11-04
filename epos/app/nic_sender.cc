#include <alarm.h>
#include <machine.h>
#include <nic.h>
#include <utility/ostream.h>

__USING_SYS

const unsigned char SINK_ID = 0xdfef;

OStream cout;

struct Msg {
    int id;
    int x;
    int y;
};

void sender(unsigned char id) {
    NIC nic;
    //NIC::Protocol prot;
    NIC::Address dest;
    //NIC::Address dest(SINK_ID);

    //unsigned char src, prot;
    unsigned int size;

    Msg msg;

    int i;
    GPIO g('C', 3, GPIO::OUTPUT);
    while (true) {
        for (i = 5; i < 8; i++) {
            g.set(i & 0x01);

            msg.id = 1;
            msg.x  = 10;
            msg.y  = 20;

            while( (nic.send(dest, 0, &msg, sizeof(msg))) == 0){
                cout << dest << endl;
            }
            /*while( (nic.send(NIC::Address::BROADCAST, (NIC::Protocol) 1, &msg, sizeof(msg))) == 0){
                cout << "Falha" << endl;
            }*/

            Delay(100000);
            cout << "Sender:\t" << nic.address() << endl;
            cout << "Dest:\t" << dest << endl;
        }
    }
}

int main() {
    sender(1);
//    receiver();
}