#include "ApplicationManager.h"


static void ApplicationManager_Static_WaitingHandler(void);
static void ApplicationManager_Static_GotCommandHandler(void);
static void ApplicationManager_Static_GotPacketHandler(void);
static void ApplicationManager_Static_GotEncryptedPacketHandler(void);
static void ApplicationManager_Static_DefaultHandler(void);


void ApplicationManager_StateMachine(ApplicationHandler_t *App)
{
	while(1)
	{
		switch(App->ApplicationState)
		{
			case APP_STATE_WAITING :
				ApplicationManager_Static_WaitingHandler();
				break;
			case APP_STATE_GOT_COMMAND :
				ApplicationManager_Static_GotCommandHandler();
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

static void ApplicationManager_Static_GotCommandHandler(void)
{
	// TODO
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
