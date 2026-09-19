#include "objects.h"

Ground::Ground(float x, float y, Color color) : Pos({x, y}), color(color){
		collision = {Pos.x, Pos.y, 50, 50};
}
