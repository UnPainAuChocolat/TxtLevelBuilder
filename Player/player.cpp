#include "player.h"

Player::Player(int health, std::vector<Ground> Layer) : health(health), collisionLayer(Layer){ 
		Pos = {400, 225};
		speed = 2;
		stamina = 1.0f;
		deltaX = 0.0f;
		deltaY = 0.0f;
}

void Player::checkHealth(){
		std::cout << "Player have: " << health << " hp" << std::endl;
}

void Player::handleMovement(){
		handleJump();
		if (IsKeyDown(KEY_LEFT_SHIFT) && stamina > 0)
		{
				speed *= 5;
				stamina -= 0.25f;
		}
		if (IsKeyDown(KEY_D))
				deltaX = 2.0f;
		if (IsKeyDown(KEY_A))
				deltaX = -2.0f;
		if (deltaX > -0.10f && deltaX < 0.10f)
				deltaX = 0.0f;
		if (deltaX > 0.0f)
				deltaX -= 0.15f;
		if (deltaX < 0.0f)
				deltaX += 0.15f;
		Pos.x += deltaX * speed;
}

void Player::takeDamage(int damage)
{
		health -= damage;
}

void Player::handleJump(){
		//appliquer cinematique du movement
		int		i = 0;
		float	gravity = 1.0f;
		bool	grounded = false;

		bool	touchingWall = false;

		while (i < size_list)
		{
				float feet = Pos.y + 10;
				float head = Pos.y - 10;

				const Rectangle& coll = collisionLayer[i].collision;

				bool onTop = (feet >= coll.y && feet <= (coll.y + 10));
				bool onBot = (head >= coll.y + 40 && head <= (coll.y + 50));

				bool verticalOverlap = (feet >= coll.y && head <= coll.y + 50);
				bool onSideL = verticalOverlap && (Pos.x + 10 >= coll.x && Pos.x - 10 <= coll.x);
				bool onSideR = verticalOverlap && (Pos.x + 10 >= coll.x + 50 && Pos.x - 10 <= coll.x + 50);

				if (CheckCollisionCircleRec(Pos, 10, coll))
				{
						if (onTop)
						{
								grounded = true;
								Pos.y = coll.y - 9.0f;
						}
						else if (onBot)
						{
								deltaY = 0.0f;
						}
						else if (onSideL)
						{
								Pos.x = coll.x - 10;
								gravity = 0.25f;
								touchingWall = true;
						}
						else if (onSideR)
						{
								Pos.x = coll.x + 60;
								gravity = 0.25f;
								touchingWall = true;
						}
				}
				i++;
		}
		if (grounded)
		{
				stamina = 1.0f;
				deltaY = 0.0f;
				speed = 2;
				if (IsKeyDown(KEY_SPACE))
						deltaY = 10.0f;
		}
		else
		{
				if (IsKeyReleased(KEY_SPACE) && deltaY > 0)
						deltaY *= 0.5f;
				if (deltaY > -9.0f)
				{
						deltaY -= 0.5f;
				}

				speed = touchingWall ? 0 : 2;
		}
		Pos.y -= (deltaY * gravity);
}

void Player::displayPlayer()
{
	return;	
}
