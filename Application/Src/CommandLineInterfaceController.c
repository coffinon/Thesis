#include "CommandLineInterfaceController.h"

extern UART_HandleTypeDef huart2;

char CommandLineInterfaceController_Buffer[COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH];

static void CommandLineInterfaceController_Controller_Static_HelpHandler(CommandLineInterfaceControllerHandle_t *CLI);
static void CommandLineInterfaceController_Controller_Static_ConnectHandler(CommandLineInterfaceControllerHandle_t *CLI);
static void CommandLineInterfaceController_Controller_Static_DisconnectHandler(CommandLineInterfaceControllerHandle_t *CLI);
static void CommandLineInterfaceController_Controller_Static_MessageHandler(CommandLineInterfaceControllerHandle_t *CLI);


void CommandLineInterfaceController_Init(CommandLineInterfaceControllerHandle_t *CLI)
{
	CLI->pCLI_Buffer = CommandLineInterfaceController_Buffer;

	CLI->CLI_BufferSize = COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH;

	CLI->CLI_BufferHead = 0u;
}


void CommandLineInterfaceController_WriteMessage(CommandLineInterfaceControllerHandle_t *CLI, const char *msg)
{
	uint16_t Size;

    // Check message length
	if(strlen(msg) <= COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH)
	{
		Size = sprintf(CLI->pCLI_Buffer, msg);
	}
	else
	{
		Size = sprintf(CLI->pCLI_Buffer, "ERROR : Message is too long !\r");
	}

    // Send the message
	HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_Buffer, Size, 100u);
}


void CommandLineInterfaceController_GetCommand(CommandLineInterfaceControllerHandle_t *CLI, char *msg, uint8_t length)
{
	uint8_t CommandNumber = 0xFFu;

	const char commands[COMMAND_LINE_INTERFACE_CONTROLLER_CMD_COUNT][COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH] =
	{
		"help",
		"connect",
		"disconnect"
	};

    // Check the given string for command patterns
	for(uint8_t i = 0u; i < COMMAND_LINE_INTERFACE_CONTROLLER_CMD_COUNT; ++i)
	{
		for(uint8_t j = 0u; j < length; ++j)
		{
			if(commands[i][j] != msg[j])
			{
				break;
			}
			else if((j == strlen(commands[i]) - 1u) && (length == strlen(commands[i])))
			{
				CommandNumber = i;
				break;
			}
		}
	}

    // Execute the given command
	switch(CommandNumber)
	{
		case 0u :
			CommandLineInterfaceController_Controller_Static_HelpHandler(CLI);
			break;
		case 1u :
			CommandLineInterfaceController_Controller_Static_ConnectHandler(CLI);
			break;
		case 2u :
			CommandLineInterfaceController_Controller_Static_DisconnectHandler(CLI);
			break;
		default :
			CommandLineInterfaceController_Controller_Static_MessageHandler(CLI);
	}
}


static void CommandLineInterfaceController_Controller_Static_HelpHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	CommandLineInterfaceController_WriteMessage(CLI, ">> connect - show list of available connections\r");
	CommandLineInterfaceController_WriteMessage(CLI, ">> disconnect - disconnect from all connections\r");
}

static void CommandLineInterfaceController_Controller_Static_ConnectHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	CommandLineInterfaceController_WriteMessage(CLI, "List of available connections : \r");
	// TODO - connections list
}

static void CommandLineInterfaceController_Controller_Static_DisconnectHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	// TODO - disconnect part of the code
	CommandLineInterfaceController_WriteMessage(CLI, "Disconnected from all connections\r");
}

static void CommandLineInterfaceController_Controller_Static_MessageHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	// TODO - pack the message and send
}
