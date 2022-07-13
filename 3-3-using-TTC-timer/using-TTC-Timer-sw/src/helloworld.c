#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xttcps.h"
#include "xparameters.h"

XTtcPs_Config *ttc_config;
XTtcPs ttc;

typedef struct {
	u32 output_freq;
	u8 prescale;
	XInterval interval;
	u32 option;

} ttc_setup;

void ttc_init()
{
	ttc_config = XTtcPs_LookupConfig(XPAR_PS7_TTC_0_DEVICE_ID);
	s32 status = XTtcPs_CfgInitialize(&ttc, ttc_config, ttc_config->BaseAddress);

	if(status == XST_SUCCESS)
		xil_printf("TTC INIT SUCCESSFUL\n");
	else
		xil_printf("TTC INIT FAILED\n");

	status = XTtcPs_SelfTest(&ttc);

	if(status == XST_SUCCESS)
			xil_printf("TTC SELF TEST SUCCESSFUL\n");
		else
			xil_printf("TTC SELF TEST FAILED\n");

}

int main()
{
	ttc_setup data = {1,0,0,0}; // freq = 1 Hz | Now, we want to calculate prescaler,
								// interval, option.
    init_platform();
    ttc_init();
    XTtcPs_Stop(&ttc);
    // Now, we want to use a function to explore the prescaler and the interval from the given frequency.
    XTtcPs_CalcIntervalFromFreq(&ttc, data.output_freq, &(data.interval), &(data.prescale));
    XTtcPs_SetPrescaler(&ttc, data.prescale);
    XTtcPs_SetInterval(&ttc, data.interval);

    data.option = data.option | XTTCPS_OPTION_INTERVAL_MODE | XTTCPS_OPTION_DECREMENT;
    XTtcPs_SetOptions(&ttc, data.option);

    // We've successfully initialized the TTC.

    /*XTtcPs_Start(&ttc);
    usleep(100000);
    // For Zynq7000 TTC counter is a u16 value and for Ultrascale is a u32 value.
    // Now, we want to check that when the timer expires.
    u16 count = XTtcPs_GetCounterValue(&ttc);
    xil_printf("Count Value : %0d\n", count);*/

    while(1)
    {
    	XTtcPs_Start(&ttc);
    	while(XTtcPs_GetCounterValue(&ttc));// This function always returns a number and it's "True", except when the counter is zero.
    	XTtcPs_Stop(&ttc);
    	xil_printf("Delay of 1 Sec achieved\n");
    	XTtcPs_ResetCounterValue(&ttc);

    }
    cleanup_platform();
    return 0;
}
