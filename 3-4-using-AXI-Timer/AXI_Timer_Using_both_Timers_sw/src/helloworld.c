
// We've enabled the both channels of AXI_TIMER_0
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtmrctr.h"
#include "xparameters.h"

XTmrCtr tmr;

void tmr_init()
{
	int status = XTmrCtr_Initialize(&tmr, XPAR_AXI_TIMER_0_DEVICE_ID);

	if(status == XST_SUCCESS)
		xil_printf("TMR INIT SUCCESSFUL\n");
	else
		xil_printf("TMR INIT FAILED\n");

	status = XTmrCtr_SelfTest(&tmr, 0); // An AXI Timer IP, has two 32-bit timers by default. Now, we want to use the first one.

	if(status == XST_SUCCESS)
		xil_printf("TMR SELF-TEST SUCCESSFUL\n");
	else
		xil_printf("TMR SELF-TEST FAILED\n");
}
int main()
{
	// The Timer Frequency is 100 MHz
	u32 counter1 = 100000000*5; // We want to generate 5 Sec delay. --> Timer_ID = 0
	u32 counter2 = 100000000*8; // We want to generate 8 Sec delay. --> Timer_ID = 1

    init_platform();
    tmr_init();

    XTmrCtr_Stop(&tmr, 0);
    XTmrCtr_Stop(&tmr, 1);
    XTmrCtr_SetResetValue(&tmr, 0, counter1);
    XTmrCtr_SetResetValue(&tmr, 1, counter2);

    //Now we should reset the timer.
    XTmrCtr_Reset(&tmr, 0);
    XTmrCtr_Reset(&tmr, 1);

    u32 options1 = XTmrCtr_GetOptions(&tmr, 0);
    XTmrCtr_SetOptions(&tmr, 0, options1 | XTC_DOWN_COUNT_OPTION);

    u32 options2 = XTmrCtr_GetOptions(&tmr, 1);
    XTmrCtr_SetOptions(&tmr, 1, options2 | XTC_DOWN_COUNT_OPTION);

    XTmrCtr_Start(&tmr, 0);
    XTmrCtr_Start(&tmr, 1);

    while(!XTmrCtr_IsExpired(&tmr, 0));
    xil_printf("Delay of 5 Sec achieved.\n");

    while(!XTmrCtr_IsExpired(&tmr, 1));
    xil_printf("Delay of 8 Sec achieved.");

    cleanup_platform();
    return 0;
}
