#include "mach_dxc.h"

int main(void) 
{ 
    MachDxcCompiler comp = machDxcInit(); 
    machDxcDeinit(comp); 
}

