#ifndef _COMMAND_LINE_INTERFACE_CONTROLLER_H_
#define _COMMAND_LINE_INTERFACE_CONTROLLER_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"


#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_HELP			0u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_CONNECT		1u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_DISCONNECT	2u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MESSAGE		3u


// Struct to improve !!!
typedef struct
{
	char *pCLI_TX_Buffer;
	char *pCLI_RX_Buffer;
	uint16_t CLI_TX_BufferSize;
	uint16_t CLI_RX_BufferSize;
	uint8_t CLI_TX_BufferHead;
	uint8_t CLI_RX_BufferHead;
	uint8_t State;
} CommandLineInterfaceControllerHandle_t;


void CommandLineInterfaceController_Init(CommandLineInterfaceControllerHandle_t *CLI);

void CommandLineInterfaceController_WriteMessage(CommandLineInterfaceControllerHandle_t *CLI, const char *msg);

void CommandLineInterfaceController_GetCommand(CommandLineInterfaceControllerHandle_t *CLI, char *msg, uint8_t length);

#endif /* _COMMAND_LINE_INTERFACE_CONTROLLER_H_ */
