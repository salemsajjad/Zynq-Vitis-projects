#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xscutimer.h"
#include "xparameters.h"

XScuTimer_Config *tmr_config;
XScuTimer tmr;

void tmr_init()
{
	tmr_config = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
	s32 status = XScuTimer_CfgInitialize(&tmr, tmr_config, tmr_config ->BaseAddr);

	if (status == XST_SUCCESS)
		xil_printf("SCU TIMER INIT SUCCESSFUL\n");
	else
		xil_printf("SCU TIMER INIT FAILED\n");

	status = XScuTimer_SelfTest(&tmr);

	if (status == XST_SUCCESS)
		xil_printf("SCU TIMER TEST SUCCESSFUL\n");
	else
		xil_printf("SCU TIMER TEST FAILED\n");

}

int main()
{
	u32 tmrCount = 333333333 * 5;
	u32 counterValue = 0;
    init_platform();
    tmr_init();

    // We want to perform the Normal mode initialization.
    XScuTimer_Stop(&tmr);

    // For the Auto-Reload mode, First, we should enable the Auto-Reload mode.
    XScuTimer_EnableAutoReload(&tmr);
    XScuTimer_LoadTimer(&tmr, tmrCount);

    // Now we can start the timer.
    XScuTimer_Start(&tmr);

    while(1)
    {
		// Now we want to wait until the timer expires.
		while(!XScuTimer_IsExpired(&tmr))
		{
			usleep(500000); // 500 mSec delay.
			counterValue = XScuTimer_GetCounterValue(&tmr);
			xil_printf("Current Count Value : %0d\n", counterValue);
		}

		// The counter has expired.
		xil_printf("TMR Expired : 5 seconds delay achieved. \n");
		XScuTimer_Stop(&tmr);
		// When the timer overflows, it drops into the interrupt status.
		// We should clear the interrupt status to proceed the Auto-Reload mode.
		XScuTimer_ClearInterruptStatus(&tmr);
		// Now, we can start the timer happily. ;)
		XScuTimer_Start(&tmr);

    }
    cleanup_platform();
    return 0;
}
