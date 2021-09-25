#include "ApplicationManager.h"

extern CommandLineInterfaceControllerHandle_t hCLI;

static void ApplicationManager_Static_WaitingHandler(void);
static void ApplicationManager_Static_GotCommandHandler(ApplicationHandler_t *App);
static void ApplicationManager_Static_GotPacketHandler(void);
static void ApplicationManager_Static_GotEncryptedPacketHandler(void);
static void ApplicationManager_Static_DefaultHandler(void);


void ApplicationManager_Init(ApplicationHandler_t *App)
{
	App->ApplicationState = APP_STATE_WAITING;
	App->MessageLength = 0u;
}

void ApplicationManager_StateMachine(ApplicationHandler_t *App)
{
	while(1u)
	{
		switch(App->ApplicationState)
		{
			case APP_STATE_WAITING :
				ApplicationManager_Static_WaitingHandler();
				break;
			case APP_STATE_GOT_COMMAND :
				ApplicationManager_Static_GotCommandHandler(App);
				break;
			case APP_STATE_GOT_PACKET :
				ApplicationManager_Static_GotPacketHandler();
				break;
			case APP_STATE_GOT_ENCRYPTED_PACKET :
				ApplicationManager_Static_GotEncryptedPacketHandler();
				break;
			default :
				ApplicationManager_Static_DefaultHandler();
		}
	}
}

static void ApplicationManager_Static_WaitingHandler(void)
{
	// TODO
}

static void ApplicationManager_Static_GotCommandHandler(ApplicationHandler_t *App)
{
	// Check command type
	CommandLineInterfaceController_GetCommand(&hCLI, hCLI.pCLI_Buffer, App->MessageLength);

	// Reset application state
	App->ApplicationState = APP_STATE_WAITING;
}

static void ApplicationManager_Static_GotPacketHandler(void)
{
	// TODO
}

static void ApplicationManager_Static_GotEncryptedPacketHandler(void)
{
	// TODO
}

static void ApplicationManager_Static_DefaultHandler(void)
{
	// TODO
}
