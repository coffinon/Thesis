#ifndef _APPLICATION_MANAGER_H_
#define _APPLICATION_MANAGER_H_

#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "CommandLineInterfaceController.h"


#define APP_STATE_WAITING				0u
#define APP_STATE_GOT_COMMAND			1u


typedef struct
{
	uint8_t ApplicationState;
	uint8_t MessageLength;
} ApplicationHandler_t;


void ApplicationManager_Init(ApplicationHandler_t *App);

void ApplicationManager_StateMachine(ApplicationHandler_t *App);


#endif /* _APPLICATION_MANAGER_H_ */
