
/* On Z-turn board, we have 4 Dip switches connected to PL part.
 * In this example two of them connected to first AXI GPIO IP and others connected to second AXi GPIO.
 * And we've just enabled the PL-PS interrupt controller.
 * We should initialize each interrupt controller independently.
*/

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xscugic.h"
#include "xil_exception.h"

XGpio slide, btn;
XScuGic_Config *gic_config;
XScuGic gic;

void slide_handler()
{
	XGpio_InterruptDisable(&slide, XGPIO_IR_CH1_MASK);
	u32 dataRead = XGpio_DiscreteRead(&slide, 1);
	xil_printf("SLIDE SW Data Read : %0d\n", dataRead);
	XGpio_InterruptClear(&slide, XGPIO_IR_CH1_MASK);
	XGpio_InterruptEnable(&slide, XGPIO_IR_CH1_MASK);
}

void btn_handler()
{
	XGpio_InterruptDisable(&btn, XGPIO_IR_CH1_MASK);
	u32 dataRead = XGpio_DiscreteRead(&btn, 1);
	xil_printf("PUSH BUTTON Data Read : %0d\n", dataRead);
	XGpio_InterruptClear(&btn, XGPIO_IR_CH1_MASK);
	XGpio_InterruptEnable(&btn, XGPIO_IR_CH1_MASK);
}

void gpio_init()
{
	int statuss = XGpio_Initialize(&slide,XPAR_SLIDE_DEVICE_ID );
	int statusb = XGpio_Initialize(&btn,XPAR_BTN_DEVICE_ID);

	if((statuss & statusb) == XST_SUCCESS)
		xil_printf("GPIO INTI SUCCESSFUL\n");
	else
		xil_printf("GPIO INIT FAILED\n");

	XGpio_SetDataDirection(&slide, 1, 0xf);
	XGpio_SetDataDirection(&btn, 1, 0xf);
}

void gic_init()
{
	gic_config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
	s32 status = XScuGic_CfgInitialize(&gic, gic_config, gic_config->CpuBaseAddress);

	if(status== XST_SUCCESS)
		xil_printf("GIC INTI SUCCESSFUL\n");
	else
		xil_printf("GIC INIT FAILED\n");

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, &gic);
	Xil_ExceptionEnable();

	XScuGic_Connect(&gic, XPAR_FABRIC_SLIDE_IP2INTC_IRPT_INTR,(Xil_InterruptHandler)slide_handler, &slide);

	XScuGic_Connect(&gic, XPAR_FABRIC_BTN_IP2INTC_IRPT_INTR,(Xil_InterruptHandler)btn_handler, &btn);


	XScuGic_Enable(&gic, XPAR_FABRIC_SLIDE_IP2INTC_IRPT_INTR);
	XScuGic_Enable(&gic, XPAR_FABRIC_BTN_IP2INTC_IRPT_INTR);


	XGpio_InterruptGlobalEnable(&slide);
	XGpio_InterruptGlobalEnable(&btn);

	XGpio_InterruptEnable(&slide, XGPIO_IR_CH1_MASK);
	XGpio_InterruptEnable(&btn, XGPIO_IR_CH1_MASK);
}

int main()
{
    init_platform();
    gpio_init();
    gic_init();

	while(1)
	{

	}

	cleanup_platform();
	return 0;
}
