// EPOS PLASMA Timer Mediator

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <timer.h>

__BEGIN_SYS

void PLASMA_Timer::init() {
    db<PLASMA_Timer>(TRC) << "PLASMA_Timer::init()\n";
    //PLASMA_IC::enable(PLASMA_IC::IRQ_TIMER);
}

__END_SYS

