#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xtmrctr.h"
#include "xil_exception.h"
#include "xscugic.h"

XTmrCtr tmr;

XScuGic_Config *gic_config;
XScuGic gic;

void tmrHandler()
{
	if (XTmrCtr_IsExpired(&tmr,0))
		xil_printf("Interrupt\n");

	XTmrCtr_Reset(&tmr, 0);
}

void timerInit()
{
	int status = 0;
	status = XTmrCtr_Initialize(&tmr, XPAR_AXI_TIMER_0_DEVICE_ID);

	if(status == XST_SUCCESS)
		xil_printf("TMR Init Successful\n");
	else
		xil_printf("TMR Init Failed\n");

	u32 Count = 100000000*2; // Our timer operates at 100MHz freq and we want a delay of 2 Sec.
	XTmrCtr_SetResetValue(&tmr, 0, Count);
	XTmrCtr_SetOptions(&tmr, 0, XTC_INT_MODE_OPTION | XTC_DOWN_COUNT_OPTION );
}


void gicInit()
{
	int status = 0;
	gic_config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

	status = XScuGic_CfgInitialize(&gic, gic_config, gic_config->CpuBaseAddress);
	if(status == XST_SUCCESS)
		xil_printf("GIC Init Successful\n");
	else
		xil_printf("GIC Init Failed\n");

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler,	&gic);
	Xil_ExceptionEnable();

	XScuGic_Connect(&gic, XPAR_FABRIC_TMRCTR_0_VEC_ID, (Xil_InterruptHandler)tmrHandler, &tmr);
	XScuGic_Enable(&gic, XPAR_FABRIC_TMRCTR_0_VEC_ID);
}

int main()
{
    init_platform();
    timerInit();
    gicInit();
	XTmrCtr_Start(&tmr, 0);

	while(1)
	{


	}
    cleanup_platform();
    return 0;
}
