
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartps.h"
#include "xparameters.h"

XUartPs_Config *uart_config;
XUartPs uart;

void uart_init()
{
	uart_config = XUartPs_LookupConfig(XPAR_PS7_UART_1_DEVICE_ID);
	s32 status = XUartPs_CfgInitialize(&uart, uart_config, uart_config->BaseAddress);

	XUartPs_SetBaudRate(&uart, 9600);
	XUartPs_SetOperMode(&uart, XUARTPS_OPER_MODE_NORMAL);

	if(status == XST_SUCCESS)
		xil_printf("UART INIT SUCCESSFUL\n");
	else
		xil_printf("UART INIT FAILED\n");
}

int main()
{
	u8 data[12] = "Hello World\n";
	u8 RecvData[11];
	s32 count = 0;

    init_platform();
    uart_init();

	XUartPs_Send(&uart, &data[0], 12); // send "Hello World" by UART1
	while(XUartPs_IsSending(&uart));

	while(count != 11)
		count += XUartPs_Recv(&uart, &RecvData[count], 1);

	for(int i=0; i<11; i++)
	{
		xil_printf("%0c", RecvData[i]);
	}


    cleanup_platform();
    return 0;
}
