#include "objects.h"

Ground::Ground(float x, float y, float width, float height, Color color) : Pos({x, y}), color(color){
		collision = {Pos.x, Pos.y, width, height};
}
