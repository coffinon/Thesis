#include "ApplicationManager.h"

extern CommandLineInterfaceControllerHandle_t hCLI;

static void ApplicationManager_Static_WaitingHandler(void);
static void ApplicationManager_Static_GotCommandHandler(ApplicationHandler_t *App);


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
			default :
				ApplicationManager_Static_WaitingHandler();
		}
	}
}

static void ApplicationManager_Static_WaitingHandler(void)
{
	// Wait, and listen to the radio channel - default state
}

static void ApplicationManager_Static_GotCommandHandler(ApplicationHandler_t *App)
{
	// Check command type
	CommandLineInterfaceController_GetCommand(&hCLI, hCLI.pCLI_Buffer, App->MessageLength);

	// Reset application state
	App->ApplicationState = APP_STATE_WAITING;
}
