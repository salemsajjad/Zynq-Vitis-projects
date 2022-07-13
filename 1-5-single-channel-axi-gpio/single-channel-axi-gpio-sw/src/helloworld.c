#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

XGpio_Config *gpio_config;
XGpio gpio;

void gpio_init()
{

	int status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID);
	if(status == XST_SUCCESS)
		xil_printf("Device INIT Successful\n");
	else
		xil_printf("Device INIT Failed\n");

}


int main()
{
    init_platform();
    gpio_init();
    XGpio_SetDataDirection(&gpio, 1, 0x0); // bits set to 1 -> input and bits set to 0 -> output

    while(1)
    {
    	// Driving RGB LEDs
    	XGpio_DiscreteWrite(&gpio, 1, 0x6);
    	sleep(1);

    	XGpio_DiscreteWrite(&gpio, 1, 0x5);
    	sleep(1);

    	XGpio_DiscreteWrite(&gpio, 1, 0x3);
    	sleep(1);

    	XGpio_DiscreteWrite(&gpio, 1, 0xf);
		sleep(1);
    }




    cleanup_platform();
    return 0;
}
