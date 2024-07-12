#pragma once		

#include "Common.h"			

#define MAX_BARRIERS 3 // 障碍物数量


void Bird_startup();
void Bird_show();
void Bird_updateWithoutInput();
void Bird_updateWithInput();
int Bird_main();