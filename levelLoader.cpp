#include "general.h"

int size_list;
std::vector<Ground> levelCollision;

int LoadLevel(const char* filepath)
{
		int i;
		Vector2 Pos = {0, 0};
		std::ifstream f(filepath);

		if (!f.is_open()){
				return 0;
		}

		std::string s;

		while (std::getline(f, s))
		{
				i = 0;
				while (s[i] != '\0')
				{
						if (s[i] == 'x')
						{
								Ground newGround(Pos.x, Pos.y, GRAY);
								levelCollision.push_back(newGround);
						}
						Pos.x += 50;
						i++;
				}
				Pos.x = 0;
				Pos.y += 50;
		}
		f.close();
		size_list = levelCollision.size();
		return size_list;
}

void displayLevel()
{
		int i = 0;

		while (i < size_list)
		{
				Ground ground = levelCollision[i];
				DrawRectangleRec(ground.collision, ground.color);
				i++;
		}
}

Texture2D LoadTexture(char* filepath)
{
		Image temp = LoadImage(filepath);
		ImageResize(&temp, 50, 50);

		Texture2D res = LoadTextureFromImage(temp);
		return res;
}
