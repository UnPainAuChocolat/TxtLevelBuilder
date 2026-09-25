#include "general.h"

int		main(void)
{
		float	screenHeight = 450;
		float	screenWidth = 800;
		screen currentScreen = MENU;
		char str[] = "Level/level1";
		Vector2 spawn_point;
		
		LoadLevel(str, &spawn_point);
		Player player(50, spawn_point);
		player.checkHealth();

		InitWindow(screenWidth, screenHeight, "test");

		SetTargetFPS(60);
		while (!WindowShouldClose() && currentScreen != EXIT)
		{

				BeginDrawing();
				if (currentScreen == MENU)
				{
						menuHandler(&currentScreen);
				}
				else if (currentScreen == GAME)
				{
						player.handlePlayer();
						ClearBackground(RAYWHITE);
						displayLevel();
						DrawCircleV(player.Pos, 10, RED);
				}
				else
				{
						currentScreen = EXIT;
				}
				EndDrawing();
		}

		CloseWindow();
}
