#ifndef OBJECTS_H
#define OBJECTS_H

#pragma once
#include "raylib.h"
#include <vector>

class Ground{
		private:
				Vector2		Pos;
		public:
				Rectangle	collision;
				Color		color;

				Ground(float x, float y, Color color);
};

#endif
