#include "general.h"

float screenWidth = 800;
float screenHeight = 450;

int		main(void)
{
		screen currentScreen = MENU;
		char str[] = "Level/level1";
		Vector2 spawn_point;
		
		LoadLevel(str, &spawn_point);
		Player player(50, spawn_point);
		player.checkHealth();

		InitWindow(screenWidth, screenHeight, "test");

		loadMenu();
		player.loadPlayer();
		SetTargetFPS(60);
		while (!WindowShouldClose() && currentScreen != EXIT)
		{

				BeginDrawing();
				//BeginBlendMode(BLEND_ALPHA);
				if (currentScreen == MENU)
				{
						menuHandler(&currentScreen);
				}
				else if (currentScreen == GAME)
				{
						player.handlePlayer();
						ClearBackground(RAYWHITE);
						displayLevel();
						player.displayPlayer();
				}
				else
				{
						currentScreen = EXIT;
				}
				//EndBlendMode();
				EndDrawing();
		}

		unloadMenu();
		player.unloadPlayer();
		CloseWindow();
}
