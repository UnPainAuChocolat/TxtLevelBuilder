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
void create_top_box(std::string line, std::string prev_line, int* height, int* width, int* i, Vector2 Pos);

#endif
