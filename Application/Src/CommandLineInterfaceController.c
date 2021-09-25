#include "CommandLineInterfaceController.h"

extern UART_HandleTypeDef huart2;




void CommandLineInterfaceController_WriteMessage(CommandLineInterfaceControllerHandle_t *CLI, const char *msg)
{
	uint16_t Size;

    // Check message length
	if(strlen(msg) <= 250u)
	{
		Size = sprintf(CLI->pCLI_TX_Buffer, msg);
	}
	else
	{
		Size = sprintf(CLI->pCLI_TX_Buffer, "ERROR : Message is too long !\r");
	}

    // Send the message
	HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_TX_Buffer, Size, 100u);
}