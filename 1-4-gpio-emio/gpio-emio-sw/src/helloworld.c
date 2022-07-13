#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpiops.h"
#include "xparameters.h"


XGpioPs_Config *emio_config;
XGpioPs emio;


void gpio_init(){

	emio_config = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	s32 status = XGpioPs_CfgInitialize(&emio, emio_config, emio_config->BaseAddr);

	if(status == XST_SUCCESS)
		xil_printf("DEVICE INTI SUCCESSFUL\n");
	else
		xil_printf("DEVICE INIT FAILED\n");

}



int main()
{
    init_platform();
    gpio_init();

    // from zero to 53 are MIO pins and after them we have EMIo pins.

    XGpioPs_SetDirectionPin(&emio, 54, 1);
    XGpioPs_SetDirectionPin(&emio, 55, 1);
    XGpioPs_SetDirectionPin(&emio, 56, 1);
    XGpioPs_SetDirectionPin(&emio, 57, 1);

    XGpioPs_SetOutputEnablePin(&emio, 54, 1);
    XGpioPs_SetOutputEnablePin(&emio, 55, 1);
    XGpioPs_SetOutputEnablePin(&emio, 56, 1);
    XGpioPs_SetOutputEnablePin(&emio, 57, 1);


    while(1){


    	XGpioPs_WritePin(&emio, 54, 1);
    	XGpioPs_WritePin(&emio, 55, 1);
    	XGpioPs_WritePin(&emio, 56, 1);
    	XGpioPs_WritePin(&emio, 57, 1);
    	usleep(500000);
    	XGpioPs_WritePin(&emio, 54, 0);
    	XGpioPs_WritePin(&emio, 55, 0);
    	XGpioPs_WritePin(&emio, 56, 0);
    	XGpioPs_WritePin(&emio, 57, 0);
    	usleep(500000);


    }


    cleanup_platform();
    return 0;
}
