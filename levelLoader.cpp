#include "general.h"

int size_list;
std::vector<Ground> levelCollision;
std::vector<Rectangle> spikes;

int LoadLevel(const char* filepath, Vector2* spawn)
{
		int i;

		Vector2 Pos = {0, 0};
		Rectangle spike;
		std::ifstream file(filepath);

		if (!file.is_open()){
				return 0;
		}

		std::string line;
		std::string prev_line;

        if (!std::getline(file, line))
        {
            return 0;
        }

		while (true)
		{
                if (line.empty())
                    break;

                i = 0;
				while (line[i] != '\0')
				{
                    switch (line[i])
                    {
                        case 'x':
                            handle_boxes(&Pos, line, prev_line, &i);
                            break;

                        case 'o':
							*spawn = {Pos.x, Pos.y};
							Pos.x += 50;
							i++;
                            break;

						case 'y':
							spike = {Pos.x, Pos.y, 50, 50};
							spikes.push_back(spike);
							Pos.x += 50;
							i++;
							break;

                        default:
                            i++;
                            Pos.x += 50;
                            break;
                    }
                }
				Pos.x = 0;
				Pos.y += 50;
                prev_line = line;

                if (!std::getline(file, line))
                    break;
		}
		file.close();
		size_list = levelCollision.size();
		return size_list;
}

void    handle_boxes(Vector2* Pos, std::string line, std::string prev_line, int* i)
{
    int width;
    int height;

    width = 0;
    height = 50;
    while (line[*i] == 'x')
    {
        if (prev_line[*i] == 'x' && width == 0)
        {
            width = 50;
            height = 100;
            create_top_box(line, prev_line, &height, &width, i, *Pos);
            height = 50;
        }
        else
        {
            width += 50;
        }
        *i += 1;
    }
    Ground newGround(Pos->x, Pos->y, width, height, GRAY);
    levelCollision.push_back(newGround);
    Pos->x += width;
}

void create_top_box(std::string line, std::string prev_line, int* height, int* width, int* i, Vector2 Pos)
{
    while (prev_line[*i] == 'x') 
    {
        if (prev_line[*i+1] == 'x' && line[*i+1] == 'x')
        {
            *width += 50;
            *i = *i + 1;
        }
        else
        {
            //std::cout << "New Vertical ground -> x=" << Pos.x << " y=" << Pos.y - 50 << " height=" << *height << " width=" << *width << '\n';
            Ground newGround(Pos.x, Pos.y - 50, *width, *height, GRAY);
            levelCollision.push_back(newGround);
            break;
        }
    }
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
