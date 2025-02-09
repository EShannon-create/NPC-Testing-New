#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "raylib.h"
#include "model/Person.h"
#include "controller/ChoiceMenu.h"

void DrawGUI(Person* player, ChoiceMenu* menu);

#endif