
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xbram.h"
#include "xparameters.h"

XBram_Config *bram_config;
XBram bram;

void bram_init()
{
	bram_config = XBram_LookupConfig(XPAR_AXI_BRAM_CTRL_0_DEVICE_ID);
	int status = XBram_CfgInitialize(&bram, bram_config, bram_config->CtrlBaseAddress);

	if(status == XST_SUCCESS)
		xil_printf("BRAM INIT SUCCESSFUL.\n");
	else
		xil_printf("BRAM INIT FAILED.\n");
}
int main()
{
    init_platform();
    bram_init();

    int *baseAddr;
    baseAddr = XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR;

    // Now we want to store some data in Memory
    for(int i = 0; i<50; i++)
    {
    	*(baseAddr + i) = 5*i; // each memory address has a byte(8-bit) capacity
    							// and an integer length is 4 bytes
    }
    // in Debug mode we can use the memory window to view the memory occupying.
    // We should add the 0x40000000U address to monitors section and view the memory.
    cleanup_platform();
    return 0;
}
