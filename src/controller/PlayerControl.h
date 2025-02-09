#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "raylib.h"
#include "model/World.h"
#include "model/Person.h"
#include "ChoiceMenu.h"


void HandleInputs(World*, Person*);
ChoiceMenu* getOpenChoiceMenu();
void InitializeChoiceMenus();
void DestroyChoiceMenus();

#endif
#pragma once
