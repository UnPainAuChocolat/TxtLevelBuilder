#include "../general.h"

Camera2D startCamera()
{
		Camera2D camera;
		camera.target = (Vector2){0,0};
		camera.offset = (Vector2){screenWidth/2, screenHeight/2};
		camera.rotation = 0.0f;
		camera.zoom = 1.0f;
		return camera;
}

void updateCamera(Camera2D* camera, Player* player)
{
		camera->target = player->Pos;
}
