#include <alarm.h>
#include <machine.h>
#include <nic.h>
#include <utility/ostream.h>

__USING_SYS

OStream cout;

const unsigned char SINK_ID = 0x33;

struct Msg {
    int id;
    float angleX;
    float angleY;
    float angleZ;
    float accelerationX;
    float accelerationY;
    float accelerationZ;
};

int receiver() {
    NIC nic;
    NIC::Protocol prot;
    NIC::Address src; // 77f0

    Msg msg;


    //unsigned char src, prot;
    int i;
    
    cout << "Sink\n";

    while (true) {
        /*while (nic.receive(&src, &prot, &msg, sizeof(msg)) <= 0) {
            //cout << nic.address() << '\t';
            cout << src << endl;
        }*/
        while(!(nic.receive(&src, &prot, &msg, sizeof(msg)) > 0)){
            cout << nic.address() << endl;
        }


        cout << src << endl;
        cout << "Controlador de Estabilidade para Quadricoptero - EPOS\n";
        cout << "Angle X : " << msg.angleX << "\n";
        cout << "Angle Y : " << msg.angleY << "\n";
        cout << "Angle Z : " << msg.angleZ << "\n";
        cout << "Acceleration X : " << msg.accelerationX << "\n";
        cout << "Acceleration Y : " << msg.accelerationY << "\n";
        cout << "Acceleration Z : " << msg.accelerationZ << "\n";
    }

    return 0;
}

int main() {

    receiver();
}