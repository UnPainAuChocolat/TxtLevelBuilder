#include "general.h"

int		main(void)
{
		int	screenWidth = 800;
		int	screenHeight = 450;
		char str[] = "Level/level1";
		
		LoadLevel(str);
		Player player(50, levelCollision);
		player.checkHealth();

		InitWindow(screenWidth, screenHeight, "test");

		SetTargetFPS(60);
		while (!WindowShouldClose())
		{
				player.handleMovement();
				//player.handleGravity(grounds);

				BeginDrawing();
				ClearBackground(RAYWHITE);
				displayLevel();
				DrawCircleV(player.Pos, 10, RED);
				EndDrawing();
		}

		CloseWindow();
}
