#include "../general.h"

float	screenHeight = 400;
float	screenWidth = 800;
Rectangle continueButton = {screenWidth / 2 - 150, screenHeight / 2 - 50,300,20};
Rectangle loadButton = {screenWidth / 2 - 150, screenHeight / 2 - 30, 300, 20};
Rectangle optionButton = {screenWidth / 2 - 150, screenHeight / 2 -10, 300, 20};
Rectangle exitButton = {screenWidth / 2 -150, screenHeight/ 2 + 10, 300, 20};
Color Green = {24, 255, 63, 255};
Color Black = {13, 13, 13, 255};

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
		ClearBackground(Black);

		if (buttonHandler(mousePos, continueButton, "continue"))
				*currentScreen = GAME;
		else if (buttonHandler(mousePos, loadButton, "load"))
				*currentScreen = GAME;
		else if (buttonHandler(mousePos, optionButton, "option"))
				*currentScreen = GAME;
		else if (buttonHandler(mousePos, exitButton, "exit"))
				*currentScreen = EXIT;
}
