/*
1- First we should go to modify BSP settings and is the standalone tab choose "true" ...
	option for the "enable_sw_intrusive_profiling.
	The profiling will use the ARM's SCU timer.
2- After that we should go to drivers tab and we need to add "-g -pg" infront of the ...
	extra_compiler_flags
	Now, we need to rebuild the Platform Project

3- In this section, we shlould right click on "Vitis-Profiler-sw" and go to C/C++ Build Settings
	then we need to open the profiling and check the "enable profiling" check box.

4- After that we should right click on "Vitis-Profiler-sw" and go to Run As --> Run Configurations ...
	then double click on "Single Application Debug" and a debugger option will appear.
	we double click on this and open the settings.
	In Applications tab we should go to edit and enable profiling and ...
	customize the frequency = 1000000 and address = 0x10000000
	then click on Apply.
	After that we need to connect the FPGA board to PC and click "Run".

*/

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"


XGpio_Config *gpio_c;
XGpio gpio;

void gpio_init(){

	gpio_c = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
	int status = XGpio_CfgInitialize(&gpio, gpio_c, gpio_c->BaseAddress );
	if(status == XST_SUCCESS)
		 xil_printf("GPIO SUCCESSFULLY INITIALIZED\n");
	else
		xil_printf("GPIO INIT FAILED");

    XGpio_SetDataDirection(&gpio, 1, 0x0000);
}

void led_1(){
	XGpio_DiscreteWrite(&gpio, 1, 0xffff);
	XGpio_DiscreteWrite(&gpio, 1, 0x0000);
}


void led_3(){
	XGpio_DiscreteWrite(&gpio, 1, 0xffff);
	XGpio_DiscreteWrite(&gpio, 1, 0x0000);
}


void led_5(){
	XGpio_DiscreteWrite(&gpio, 1, 0xffff);
	XGpio_DiscreteWrite(&gpio, 1, 0x0000);
}


int main()
{
    init_platform();
    gpio_init();
    led_1();
    led_3();
    led_5();
    print("Hello World\n\r");

    cleanup_platform();
    return 0;
}
