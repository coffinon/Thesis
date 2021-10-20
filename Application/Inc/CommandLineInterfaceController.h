#ifndef _COMMAND_LINE_INTERFACE_CONTROLLER_H_
#define _COMMAND_LINE_INTERFACE_CONTROLLER_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"
#include "MY_NRF24.h"

// General purpose macro definitions
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_COUNT			3u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH	250u

// Command ID macro definitions
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_HELP			0u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_CONNECT		1u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_DISCONNECT	2u
#define COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MESSAGE		3u


// Command line interface controller handle structure definition
typedef struct
{
	char *pCLI_Buffer;
	uint16_t CLI_BufferSize;
	uint8_t CLI_BufferHead;
} CommandLineInterfaceControllerHandle_t;

void CommandLineInterfaceController_ClearBuffer(CommandLineInterfaceControllerHandle_t *CLI);

void CommandLineInterfaceController_Init(CommandLineInterfaceControllerHandle_t *CLI);

void CommandLineInterfaceController_WriteMessage(CommandLineInterfaceControllerHandle_t *CLI, const char *msg);

void CommandLineInterfaceController_GetCommand(CommandLineInterfaceControllerHandle_t *CLI, char *msg, uint8_t length);

#endif /* _COMMAND_LINE_INTERFACE_CONTROLLER_H_ */
