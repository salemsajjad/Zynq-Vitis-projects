#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartlite.h"
#include "xparameters.h"

XUartLite_Config *uart_config1, *uart_config2;
XUartLite uart1,uart2;

void uart_init()
{
	uart_config1 = XUartLite_LookupConfig(XPAR_UART0_DEVICE_ID);
	int status1 = XUartLite_CfgInitialize(&uart1, uart_config1, uart_config1->RegBaseAddr);

	uart_config2 = XUartLite_LookupConfig(XPAR_UART1_DEVICE_ID);
	int status2 = XUartLite_CfgInitialize(&uart2, uart_config2, uart_config2->RegBaseAddr);

	if((status1 && status2) == XST_SUCCESS)
		xil_printf("UART INIT SUCCESSFUL\n");
	else
		xil_printf("UART INIT FAILED\n");
}



int main()
{
    init_platform();
    uart_init();

    u8 data1[] = "UART 0->1";
    u8 data2[] = "UART 1->0";
    u8 Rx[9];

    xil_printf("Sending Data from UART0 -> UART1 \n");

    XUartLite_Send(&uart1, &data1[0], 9);
    while(XUartLite_IsSending(&uart1));

    int byteRcvd = 0;

    while(byteRcvd != 9)
    	byteRcvd = byteRcvd + XUartLite_Recv(&uart2, &Rx[byteRcvd], 9);

    xil_printf("Transmission Completed UART0 -> UART1 \n");

    for(int i=0; i<9; i++)
    	xil_printf("%0c",Rx[i]);

    xil_printf("\n");

    ////////////////////////////////////////////////////////////////////

    xil_printf("Sending Data from UART1 -> UART0 \n");

	XUartLite_Send(&uart2, &data2[0], 9);
	while(XUartLite_IsSending(&uart2));

	byteRcvd = 0;

	while(byteRcvd != 9)
		byteRcvd = byteRcvd + XUartLite_Recv(&uart1, &Rx[byteRcvd], 9);

	xil_printf("Transmission Completed UART1 -> UART0 \n");

	for(int i=0; i<9; i++)
		xil_printf("%0c",Rx[i]);

	xil_printf("\n");

    cleanup_platform();
    return 0;
}
