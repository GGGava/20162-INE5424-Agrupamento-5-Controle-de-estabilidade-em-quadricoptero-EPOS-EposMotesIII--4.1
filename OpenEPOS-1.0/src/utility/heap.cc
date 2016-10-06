// EPOS Heap Utility Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <utility/heap.h>
#include <machine.h>

__BEGIN_SYS

// Methods
void Heap_Common::out_of_memory()
{
    db<Heap>(ERR) << "Heap::alloc(this=" << this
				  << "): out of memory!\n";
    Machine::panic();
}

__END_SYS
