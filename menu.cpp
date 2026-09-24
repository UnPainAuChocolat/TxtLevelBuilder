#include "general.h"

Rectangle button = {300,200,300,20};
Color color = BLUE;
Color txtColor = LIME;

void menuHandler(screen* currentScreen)
{
		Vector2 mousePos = GetMousePosition();

		if (CheckCollisionPointRec(mousePos, button))
		{
				color = LIME;
				txtColor = BLACK;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						*currentScreen = GAME;
		}
		else
		{
				color = BLACK;
				txtColor = LIME;
		}
}

void menuDisplay()
{
		ClearBackground(BLACK);
		DrawText("Platformer", 300, 100, 50, PINK);
		DrawRectangleRec(button, color);
		DrawText("start", button.x + 10, button.y, 20, txtColor);
}
