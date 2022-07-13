#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

XGpio led, sw;

void gpio_init(){

	int status1 = XGpio_Initialize(&led, XPAR_RGB_LED_DEVICE_ID);
	int status2 = XGpio_Initialize(&sw, XPAR_SWITCH_DEVICE_ID);

	if((status1 & status2) == XST_SUCCESS)
		xil_printf("Device Init Successful\n");
	else
		xil_printf("Device Init Failed\n");


}

int main()
{
	u32 swRead = 0;
    init_platform();
    gpio_init();

    XGpio_SetDataDirection(&sw, 1, 0xf);
    XGpio_SetDataDirection(&led, 1, 0x0);

    while(1){
    	swRead = XGpio_DiscreteRead(&sw, 1);
    	XGpio_DiscreteWrite(&led, 1, swRead);
    	xil_printf("Sw Read : %0d\n", swRead);
    	sleep(1);
    }




    cleanup_platform();
    return 0;
}
