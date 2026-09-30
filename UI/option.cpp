#include "../general.h"

//option menu
Rectangle resolutionButton = {screenWidth / 2 - 50, screenHeight / 2 - 80,300,20};
Rectangle volumeButton = {screenWidth / 2 - 50, screenHeight / 2 - 60, 300, 20};
Rectangle mappingButton = {screenWidth / 2 - 50, screenHeight / 2 - 40, 300, 20};
Rectangle backButton = {screenWidth / 2 - 50, screenHeight/ 2 - 20, 300, 20};

//resolution menu
Rectangle firstButton = {screenWidth / 2 - 50, screenHeight / 2 - 80,300,20};
Rectangle secondButton = {screenWidth / 2 - 50, screenHeight / 2 - 60, 300, 20};
Rectangle thirdButton = {screenWidth / 2 - 50, screenHeight / 2 - 40, 300, 20};

void optionHandler(screen* currentScreen, Vector2 mousePos)
{
		if (buttonHandler(mousePos, resolutionButton, "resolution"))
				*currentScreen = RESO;
		else if (buttonHandler(mousePos, volumeButton, "volume"))
				*currentScreen = OPTION;
		else if (buttonHandler(mousePos, mappingButton, "map your keyboard"))
				*currentScreen = OPTION;
		else if (buttonHandler(mousePos, backButton, "back"))
				*currentScreen = MENU;
}

void resolutionHandler(screen* currentScreen, Vector2 mousePos)
{
		if (buttonHandler(mousePos, firstButton, "800x450"))
				*currentScreen = RESO;
		else if (buttonHandler(mousePos, secondButton, "1280x720"))
				*currentScreen = RESO;
		else if (buttonHandler(mousePos, thirdButton, "1920x1080"))
				*currentScreen = RESO;
		else if (buttonHandler(mousePos, backButton, "back"))
				*currentScreen = OPTION;

}
