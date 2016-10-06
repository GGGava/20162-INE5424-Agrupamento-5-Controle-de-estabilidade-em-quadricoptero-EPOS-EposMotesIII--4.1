// EPOS PLASMA_IC Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <mach/plasma/machine.h>
#include <mach/plasma/ic.h>


__BEGIN_SYS

void PLASMA_IC::int_handler(unsigned int interrupt) {
    static bool cnt_lo = false;
    //static unsigned int lastcnt = 0;

    unsigned int bit = *reinterpret_cast<unsigned int*>(IC_STATUS_ADDRESS) & *reinterpret_cast<unsigned int*>(IC_MASK_ADDRESS);
    switch (bit) {
	case 1: 
           interrupt = 0;
	   break;
	case 2: 
	   interrupt = 1;
	   break;
	case 4: 
	   interrupt = 2;
	   break;
	case 8: 
	   interrupt = 3;
	   break;
	case 16: 
	   interrupt = 4;
	   break;
	case 32: 
	   interrupt = 5;
	   break;
	default: 
	   interrupt = 7;
	   break;
    }

    // Gambiarra do Timer ...
    if(cnt_lo){
        disable(2);
        enable(3);
        cnt_lo = false;
    } else {
 	disable(3);
        enable(2);
        cnt_lo = true;
    }

    //dispatch specific handler
    void (*h)(unsigned int);
    h = PLASMA::int_vector(interrupt);
    h(interrupt);
    *(unsigned int*)Traits<PLASMA_Timer>::WRITE_ADDRESS = 0x00;
}

__END_SYS
