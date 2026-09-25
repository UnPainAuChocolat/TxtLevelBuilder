#include "../general.h"

float	screenHeight = 450;
float	screenWidth = 800;

Rectangle continueButton = {screenWidth / 2 - 150, screenHeight / 2 - 50,300,20};
Rectangle loadButton = {screenWidth / 2 - 150, screenHeight / 2 - 30, 300, 20};
Rectangle optionButton = {screenWidth / 2 - 150, screenHeight / 2 -10, 300, 20};
Rectangle exitButton = {screenWidth / 2 -150, screenHeight/ 2 + 10, 300, 20};
Color Green = {24, 255, 63, 255};
Color Black = {13, 13, 13, 255};

Texture2D texture;

RenderTexture2D menuCanvas;
Shader crtShader;
int timeLoc;
int resLoc;
Rectangle img = {0, 0, 0, 0};
Rectangle dest = {0, 0, screenWidth, screenHeight};

void loadMenu()
{
		texture = LoadTexture("Assets/Screen.png");
		img.width = texture.width;
		img.height = texture.height;

		menuCanvas = LoadRenderTexture(800, 450);

		crtShader = LoadShader(NULL, "Assets/Shaders/crt.fs");

		timeLoc = GetShaderLocation(crtShader, "iTime");
		resLoc = GetShaderLocation(crtShader, "iResolution");

		float resolution[2] = {800.0f, 450.0f};
		SetShaderValue(crtShader,resLoc, resolution, SHADER_UNIFORM_VEC2);
}

bool buttonHandler(Vector2 mousePos, Rectangle button, const char* name)
{
		bool res = false;
		Color color = Black;
		Color txtColor = Green;

		if (CheckCollisionPointRec(mousePos, button))
		{
				color = Green;
				txtColor = Black;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						res = true;
		}
		else
		{
				color = Black;
				txtColor = Green;
				res = false;
		}
		DrawRectangleRec(button, color);
		DrawText(name, button.x + 10, button.y, 20, txtColor);
		return res;
}

void menuHandler(screen* currentScreen)
{
		Vector2 mousePos = GetMousePosition();

		float time = (float)GetTime();
		SetShaderValue(crtShader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

		ClearBackground(Black);

		BeginTextureMode(menuCanvas);
		ClearBackground(Black);
		if (buttonHandler(mousePos, continueButton, "continue"))
				*currentScreen = GAME;
		else if (buttonHandler(mousePos, loadButton, "load"))
				*currentScreen = GAME;
		else if (buttonHandler(mousePos, optionButton, "option"))
				*currentScreen = GAME;
		else if (buttonHandler(mousePos, exitButton, "exit"))
				*currentScreen = EXIT;
		EndTextureMode();

		//ClearBackground(Black);


		BeginShaderMode(crtShader);
		Rectangle srcRec = { 0, 0, (float)menuCanvas.texture.width, -(float)menuCanvas.texture.height };
		DrawTexturePro(menuCanvas.texture, srcRec, dest, (Vector2){0,0}, 0.0f, WHITE);
		EndShaderMode();

		DrawTexturePro(texture, img, dest, (Vector2){0,0},0.0f,WHITE);
}

void unloadMenu()
{
		UnloadTexture(texture);
		UnloadRenderTexture(menuCanvas);
		UnloadShader(crtShader);
}
