#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xwdttb.h"
#include "xparameters.h"



XWdtTb_Config *wdt_config;
XWdtTb wdt;

void wdt_init(){
	wdt_config = XWdtTb_LookupConfig(XPAR_AXI_TIMEBASE_WDT_0_DEVICE_ID);
	s32 status = XWdtTb_CfgInitialize(&wdt, wdt_config, wdt_config->BaseAddr);

	if(status == XST_SUCCESS)
           xil_printf("WDT INIT SUCCESSFUL\n");
	else
		xil_printf("WDT INIT FAILED\n");

	status = XWdtTb_SelfTest(&wdt);

	if(status == XST_SUCCESS)
           xil_printf("WDT SELF TEST SUCCESSFUL\n");
	else
		xil_printf("WDT SELF TEST FAILED\n");


}


// We've set the watchdog period in Vivado => the period is = (2^width)*clock_period
					   //  In this case the period is = (2^30) * 10e-9 = 10.73741824 Sec
int main()
{

    init_platform();
    wdt_init();



    XWdtTb_Stop(&wdt);

    XWdtTb_Start(&wdt);
    while(!XWdtTb_IsWdtExpired(&wdt));
    // After 10 Seconds.
    xil_printf("WDT Expired\n");

    cleanup_platform();
    return 0;
}
