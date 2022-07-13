#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xscuwdt.h"
#include "xparameters.h"

XScuWdt_Config *wdt_config;
XScuWdt wdt;

void wdt_init()
{
	wdt_config = XScuWdt_LookupConfig(XPAR_PS7_SCUWDT_0_DEVICE_ID);
	s32 status = XScuWdt_CfgInitialize(&wdt, wdt_config, wdt_config->BaseAddr);

	if(status == XST_SUCCESS)
		xil_printf("WDT INIT SUCCESSFUL\n");
	else
		xil_printf("WDT INIT FAILED\n");

	status = XScuWdt_SelfTest(&wdt);
	if(status == XST_SUCCESS)
		xil_printf("WDT SELF TEST SUCCESSFUL\n");
	else
		xil_printf("WDT SELF TEST FAILED\n");
}


int main()
{
    init_platform();
    wdt_init();

    u32 count = 333333333 * 5; //the Timer Freq: 333.3 MHz (and) the wanted delay : 5 sec
    u32 temp = 0;
    //First, we want to stop the timer and perform the required operations.

    XScuWdt_Stop(&wdt);
    XScuWdt_SetWdMode(&wdt);

    //Now, we want to set the delay equal to 5 seconds.
    //After 5 seconds, if we don't reload the timer, the CPU will restart itself.

    XScuWdt_LoadWdt(&wdt, count);

    // Now we can start the wdt

    XScuWdt_Start(&wdt);

    while(temp < 10)
    {
    	sleep(1);
    	xil_printf("Temp : %0d\n", temp);
    	temp++;
    	XScuWdt_RestartWdt(&wdt);
    }

    while(1)
    {
    	xil_printf("I'm already alive.\n");
    	sleep(1);
    }

    cleanup_platform();
    return 0;
}
