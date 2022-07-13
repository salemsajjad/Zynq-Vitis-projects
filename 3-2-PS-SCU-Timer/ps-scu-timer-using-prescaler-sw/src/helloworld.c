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
	u32 temp = 0;
	u32 tmrCount = 333333333 * 5;
	u32 counterValue = 0;
    init_platform();
    tmr_init();

    // We want to perform the Normal mode initialization.
    XScuTimer_Stop(&tmr);

    // For the Normal mode, First, we should disable the Auto-Reload mode.
    XScuTimer_DisableAutoReload(&tmr);

    // Now, we can perform the prescaler constant.
    XScuTimer_SetPrescaler(&tmr, 1); // new_freq = orig_freq / 2^ prescaler_value
    								// orig_freq = CPU_freq/2 = 333.3 MHz

    XScuTimer_LoadTimer(&tmr, tmrCount);

    // Now we can start the timer.
    XScuTimer_Start(&tmr);


	// Now we want to wait until the timer expires.
	while(!XScuTimer_IsExpired(&tmr))
	{
		usleep(500000); // 500 mSec delay.
		temp++;
	}

	// The counter has expired.
	xil_printf("TMR Expired : 10 seconds delay achieved. \n");
	xil_printf("TEMP VALUE : %0d\n", temp);


    cleanup_platform();
    return 0;
}
