#ifndef _APPLICATION_MANAGER_H_
#define _APPLICATION_MANAGER_H_

#include <stdint.h>

#include "stm32f4xx_hal.h"


#define APP_STATE_WAITING				0u
#define APP_STATE_GOT_COMMAND			1u
#define APP_STATE_GOT_PACKET			2u
#define APP_STATE_GOT_ENCRYPTED_PACKET	3u


typedef struct
{
	uint8_t ApplicationState;
} ApplicationHandler_t;


void ApplicationManager_StateMachine(ApplicationHandler_t *App);


#endif /* _APPLICATION_MANAGER_H_ */
