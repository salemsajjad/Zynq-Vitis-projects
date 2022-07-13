#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

XGpio_Config *gpio_config;
XGpio gpio;

void init()
{
	int status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID);
	if(status == XST_SUCCESS)
		xil_printf("Device Init Successful\n");
	else
		xil_printf("Device Init Failed");

}


int main()
{

	u32 swValue = 0;

    init_platform();
    init();
    XGpio_SetDataDirection(&gpio, 1, 0xf);
    XGpio_SetDataDirection(&gpio, 2, 0x0);

    while(1)
    {
    	swValue = XGpio_DiscreteRead(&gpio, 1);
    	XGpio_DiscreteWrite(&gpio, 2, swValue);
    	xil_printf("Switch Value Read : %0d\n", swValue);
    	sleep(2);
    }





    cleanup_platform();
    return 0;
}
