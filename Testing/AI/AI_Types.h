#ifndef _AI_TYPES_
#define _AI_TYPES_

#include "AI.h"
#include "Bot.h"
#include "Movement.h"
#include "Simulation.h"

void addBotA(Simulation &sim);
Movement AI_TypeA(AI &ai);

void addBotB(Simulation &sim);
Movement AI_TypeB(AI &ai);

#endif