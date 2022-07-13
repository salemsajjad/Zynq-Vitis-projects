#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtmrctr.h"
#include "xparameters.h"

XTmrCtr tmr;

void tmr_init(){
	int status = XTmrCtr_Initialize(&tmr, XPAR_AXI_TIMER_0_DEVICE_ID);

	XTmrCtr_Stop(&tmr, 0);

	u32 option = XTmrCtr_GetOptions(&tmr, 0);
	option = option | XTC_DOWN_COUNT_OPTION;

	XTmrCtr_SetOptions(&tmr, 0 , option);


	u32 count = 100000000*15; // Assume that We want to generate 15 Sec delay.

	XTmrCtr_SetResetValue(&tmr, 0, count);

	XTmrCtr_Reset(&tmr, 0);

}

int main()
{
    init_platform();
    tmr_init();

    XTmrCtr_Start(&tmr, 0);
    u32 start = XTmrCtr_GetValue(&tmr, 0);
    xil_printf("Profile\n");
    u32 end = XTmrCtr_GetValue(&tmr, 0);
    XTmrCtr_Stop(&tmr, 0);
    XTmrCtr_Reset(&tmr, 0);


    xil_printf("No. of Clock Ticks : %0d\n", (start - end));
    printf("Time in uSec : %0f\n", (start - end)* 0.01);
    xil_printf("Time in nSec : %0d\n", (start - end)*10);


    cleanup_platform();
    return 0;
}
