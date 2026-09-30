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

		Camera2D camera = startCamera();
		loadMenu();
		player.loadPlayer();
		SetTargetFPS(60);
		while (!WindowShouldClose() && currentScreen != EXIT)
		{

				BeginDrawing();
				BeginMode2D(camera);
				//BeginBlendMode(BLEND_ALPHA);
				if (currentScreen == MENU)
				{
						menuHandler(&currentScreen);
				}
				else if (currentScreen == GAME)
				{
						player.handlePlayer();
						updateCamera(&camera, &player);
						ClearBackground(RAYWHITE);
						displayLevel();
						player.displayPlayer();
				}
				else
				{
						currentScreen = EXIT;
				}
				//EndBlendMode();
				EndMode2D();
				EndDrawing();
		}

		unloadMenu();
		player.unloadPlayer();
		CloseWindow();
}
