#include "general.h"

int		main(void)
{
		int	screenWidth = 800;
		int	screenHeight = 450;
		screen currentScreen = MENU;
		char str[] = "Level/level1";
		Vector2 spawn_point;
		
		LoadLevel(str, &spawn_point);
		Player player(50, spawn_point);
		player.checkHealth();

		InitWindow(screenWidth, screenHeight, "test");

		SetTargetFPS(60);
		while (!WindowShouldClose())
		{

				BeginDrawing();
				if (currentScreen == MENU)
				{
						menuDisplay();
						menuHandler(&currentScreen);
				}
				else
				{
						player.handlePlayer();
						ClearBackground(RAYWHITE);
						displayLevel();
						DrawCircleV(player.Pos, 10, RED);
				}
				EndDrawing();
		}

		CloseWindow();
}
