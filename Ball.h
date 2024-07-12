#pragma once				

#include "Common.h"

#define MAX_BALLS 10  // 最多同时存在的小球数量
#define MAX_COINS 5  // 最多同时存在的金币数量



void Ball_startup();
void Ball_show();
void Ball_updateWithoutInput();
void Ball_updateWithInput();
int Ball_main();
