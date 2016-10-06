// EPOS PLASMA Timer Mediator Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <mach/plasma/timer.h>

__BEGIN_SYS

PLASMA_Timer::Count PLASMA_Timer::_count = (1<<18);  //fixed by hardware

void PLASMA_Timer::int_handler(unsigned int interrupt) {
	//will be overrided by alarm
	db<PLASMA_Timer>(TRC) << "<Timer::int_handler>";
}

__END_SYS
