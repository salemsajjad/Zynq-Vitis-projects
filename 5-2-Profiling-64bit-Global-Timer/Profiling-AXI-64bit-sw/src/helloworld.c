#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"



int main()
{
	// For the Global Timer we don't need to perform initialization step.
	XTime startg , endg ; // data type = u64 --> long long unsigned.



    init_platform();

    XTime_GetTime(&startg);
    xil_printf("Profile\n");
    XTime_GetTime(&endg);


    /////// AXI Timer = 2.46 usec --> in AXI Timer we had a 32-bit counter.
    /////// Now, we have 64-bit counter and we will see that the operating time will be 2.57 usec.

    printf("Number of Clock Ticks :  %0llu\n",endg - startg);  ///u64 --> long long unsigned --> llu
    printf("Time Elapsed in nSec :  %0f\n", (endg - startg)* (2000000000.0 / XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ));
    printf("Time Elapsed in uSec :  %0f\n", (endg - startg)* (2000000.0 / XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ));


    cleanup_platform();
    return 0;
}
