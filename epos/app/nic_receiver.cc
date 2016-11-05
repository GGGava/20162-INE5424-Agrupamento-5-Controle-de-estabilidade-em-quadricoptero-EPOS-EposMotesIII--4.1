#include <alarm.h>
#include <machine.h>
#include <nic.h>
#include <utility/ostream.h>

__USING_SYS

OStream cout;

const unsigned char SINK_ID = 0x33;

struct Msg {
    float angleX;
    float angleY;
    //float angleZ;
    //float accelerationX;
    //float accelerationY;
    //float accelerationZ;
};

int receiver() {
    NIC nic;
    NIC::Protocol prot;
    NIC::Address src; // 77f0

    Msg msg;


    //unsigned char src, prot;
    int i;
    
    cout << "Sink\n";

    while (true) {/*
        while (nic.receive(&src, &prot, &msg, sizeof(msg)) <= 0) {
            //cout << nic.address() << '\t';
            cout << src << endl;
        }*/
        cout << nic.address() << '\t';
        //char *info = (char *)&msg;
        long rece[6];
        while(!(nic.receive(&src, &prot, &rece, sizeof(long)*6) > 0)){
        }
        //cout << (const char *)info << endl;
        cout << rece[0] << endl;
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

int main() {
    receiver();
}