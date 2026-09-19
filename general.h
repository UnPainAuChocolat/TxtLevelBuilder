#ifndef GENERAL_H
#define GENERAL_H

#include <iostream>
#include <fstream>
#include <vector>
#include "raylib.h"
#include "Objects/objects.h"
#include "Player/player.h"

//global value
extern std::vector<Ground>	levelCollision;
extern int 					size_list;

//level loader
int		LoadLevel(const char* filepath);
void	displayLevel();

#endif
