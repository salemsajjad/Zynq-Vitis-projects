// When we make a change to the Dip switches, the interrupt handler is called.


#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xscugic.h"       // Interrupt controller Library.
#include "xil_exception.h" // It can provide useful drivers.


XGpio_Config *gpio_config;
XGpio gpio;

void intr_handler(){

	XGpio_InterruptDisable(&gpio, XGPIO_IR_CH1_MASK);

	u32 dataRead = XGpio_DiscreteRead(&gpio, 1);
	xil_printf("Dip SW VALUE READ : %0d\n", dataRead);

	XGpio_InterruptClear(&gpio, XGPIO_IR_CH1_MASK);
	XGpio_InterruptEnable(&gpio, XGPIO_IR_CH1_MASK);
}





void gpio_init(){

	gpio_config = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
	int status = XGpio_CfgInitialize(&gpio, gpio_config, gpio_config->BaseAddress);

	if(status == XST_SUCCESS)
		xil_printf("GPIO INIT SUCCESSFUL\n");
	else
		xil_printf("GPIO INIT FAILED\n");

	XGpio_SetDataDirection(&gpio, 1, 0xf);

}

XScuGic_Config *intc_config;
XScuGic intc;



void intc_init(){
	intc_config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
	s32 status = XScuGic_CfgInitialize(&intc, intc_config, intc_config->CpuBaseAddress);

	if(status == XST_SUCCESS)
		xil_printf("GIC INIT SUCCESSFUL\n");
	else
		xil_printf("GIC INIT FAILED\n");


	///////INIT and ENABLE EXCEPTION HANDLER
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, &intc);
	Xil_ExceptionEnable();


	// connecting the interrupt port and interrupt handler.
	XScuGic_Connect(&intc,XPAR_FABRIC_GPIO_0_VEC_ID,(Xil_InterruptHandler)intr_handler, 0);
	XScuGic_Enable(&intc,XPAR_FABRIC_GPIO_0_VEC_ID);

	XGpio_InterruptGlobalEnable(&gpio);
	XGpio_InterruptEnable(&gpio, XGPIO_IR_CH1_MASK);

}


int main()
{
    init_platform();
    gpio_init();
    intc_init();

    while(1){


    }


    cleanup_platform();
    return 0;
}
