#include "CommandLineInterfaceController.h"

extern UART_HandleTypeDef huart2;

extern uint8_t myTxBuffer[1000u];

char CommandLineInterfaceController_Buffer[COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH];
char CommandLineInterfaceController_MsgBuffer[COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH];

static void CommandLineInterfaceController_Controller_Static_HelpHandler(CommandLineInterfaceControllerHandle_t *CLI);
static void CommandLineInterfaceController_Controller_Static_ConnectHandler(CommandLineInterfaceControllerHandle_t *CLI);
static void CommandLineInterfaceController_Controller_Static_DisconnectHandler(CommandLineInterfaceControllerHandle_t *CLI);
static void CommandLineInterfaceController_Controller_Static_MessageHandler(CommandLineInterfaceControllerHandle_t *CLI, char *msg, uint8_t length);

void CommandLineInterfaceController_ClearBuffer(CommandLineInterfaceControllerHandle_t *CLI)
{
	memset(CLI->pCLI_Buffer, '\0', CLI->CLI_BufferSize);
	memset(CLI->pCLI_MsgBuffer, '\0', CLI->CLI_MsgBufferSize);

	CLI->CLI_BufferHead = 0u;
	CLI->CLI_MsgBufferHead = 0u;
}

void CommandLineInterfaceController_Init(CommandLineInterfaceControllerHandle_t *CLI)
{
	CLI->pCLI_Buffer = CommandLineInterfaceController_Buffer;
	CLI->pCLI_MsgBuffer = CommandLineInterfaceController_MsgBuffer;

	CLI->CLI_BufferSize = COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH;
	CLI->CLI_MsgBufferSize = COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH;

	CLI->CLI_BufferHead = 0u;
	CLI->CLI_MsgBufferHead = 0u;
}


void CommandLineInterfaceController_WriteMessage(CommandLineInterfaceControllerHandle_t *CLI, const char *msg)
{
	uint16_t Size;

    // Check message length
	if(strlen(msg) <= COMMAND_LINE_INTERFACE_CONTROLLER_CMD_MAX_LENGTH)
	{
		Size = sprintf(CLI->pCLI_MsgBuffer, msg);
	}
	else
	{
		Size = sprintf(CLI->pCLI_MsgBuffer, "ERROR : Message is too long !\r\n");
	}

    // Send the message
	HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_MsgBuffer, Size, 100u);

	// Clear the buffer
	CommandLineInterfaceController_ClearBuffer(CLI);
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
			CommandLineInterfaceController_Controller_Static_MessageHandler(CLI, msg, length);
	}
}


static void CommandLineInterfaceController_Controller_Static_HelpHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	CommandLineInterfaceController_WriteMessage(CLI, ">> connect - show list of available connections\r\n");
	CommandLineInterfaceController_WriteMessage(CLI, ">> disconnect - disconnect from all connections\r\n");
}

static void CommandLineInterfaceController_Controller_Static_ConnectHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	CommandLineInterfaceController_WriteMessage(CLI, "List of available connections : \r\n");
	// TODO - connections list
}

static void CommandLineInterfaceController_Controller_Static_DisconnectHandler(CommandLineInterfaceControllerHandle_t *CLI)
{
	// TODO - disconnect part of the code
	CommandLineInterfaceController_WriteMessage(CLI, "Disconnected from all connections\r\n");
}

static void CommandLineInterfaceController_Controller_Static_MessageHandler(CommandLineInterfaceControllerHandle_t *CLI, char *msg, uint8_t length)
{
	// TODO - pack the message and send
	uint8_t status;
	uint16_t Size;
	uint8_t packets;

	msg[length++ + 1u] = '\n';
	msg[length++ + 1u] = '\0';

	packets = (length / 32u) + 1u;

	for(uint8_t i = 0u; i < packets; ++i)
	{
		status = NRF24_write(msg + 32u * i, 32u);

		if(status & _BV(BIT_TX_DS))
		{
			Size = sprintf(CLI->pCLI_MsgBuffer, "Transmitted Successfully\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_MsgBuffer, Size, 100u);
		}
		else if(status & _BV(BIT_MAX_RT))
		{
			Size = sprintf(CLI->pCLI_MsgBuffer, "Max retransmission level reached\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_MsgBuffer, Size, 100u);
		}
		else
		{
			do
			{
				status = NRF24_write(msg + 32u * i, 32u);

				Size = sprintf(CLI->pCLI_MsgBuffer, "Message not sent - trying to retransmit\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_MsgBuffer, Size, 100u);

				HAL_Delay(500u);
			}
			while(!(status & _BV(BIT_TX_DS)));

			Size = sprintf(CLI->pCLI_MsgBuffer, "Retransmitted Successfully\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) CLI->pCLI_MsgBuffer, Size, 100u);
		}

		HAL_Delay(100u);
	}
	CommandLineInterfaceController_ClearBuffer(CLI);

	NRF24_startListening();
}
