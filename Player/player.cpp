#include "player.h"

Player::Player(int health, std::vector<Ground> Layer) : health(health), collisionLayer(Layer){ 
		Pos = {400, 225};
		speed = 2;
		stamina = 1.0f;
		deltaX = 0.0f;
		deltaY = 0.0f;
		radius = 10;
		grounded = false;
		gravity = 1.0f;
		touchingWallR = false;
		touchingWallL = false;
}

void Player::checkHealth(){
		std::cout << "Player have: " << health << " hp" << std::endl;
}

void Player::handleMovement(){
		handlePhysics();
		handleJump();
		if (IsKeyDown(KEY_LEFT_SHIFT) && stamina > 0 && !grounded)
		{
				speed = 10;
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

void Player::handlePhysics(){
		int		i = 0;
		grounded = false;
		touchingWallR = false;
		touchingWallL = false;
		gravity = 1.0f;

		while (i < size_list)
		{
				float feet = Pos.y + 10;
				float head = Pos.y - 10;

				const Rectangle& coll = collisionLayer[i].collision;

				bool onTop = (feet >= coll.y && feet <= (coll.y + radius));
				bool onBot = (head >= coll.y + coll.height - radius && head <= (coll.y + coll.height));

				bool verticalOverlap = (feet >= coll.y && head <= coll.y + coll.height);
				bool onSideL = verticalOverlap && (Pos.x + radius >= coll.x && Pos.x - radius <= coll.x);
				bool onSideR = verticalOverlap && (Pos.x + radius >= coll.x + coll.width &&
						Pos.x - radius <= coll.x + coll.width);

				if (CheckCollisionCircleRec(Pos, radius, coll))
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
								Pos.x = coll.x - radius;
								gravity = 0.25f;
								touchingWallL = true;
						}
						else if (onSideR)
						{
								Pos.x = coll.x + coll.width + radius;
								gravity = 0.25f;
								touchingWallR = true;
						}
				}
				i++;
		}
}

void Player::handleJump()
{
		if (grounded)
		{
				stamina = 1.0f;
				deltaY = 0.0f;
				speed = 2;
				if (IsKeyDown(KEY_SPACE))
						deltaY = 10.0f;
		}
		if (touchingWallR && IsKeyDown(KEY_SPACE))
		{
				deltaY = 10.0f;
				deltaX = 4.0f;
				touchingWallR = false;
				speed = 2;
		}
		if (touchingWallL && IsKeyDown(KEY_SPACE))
		{
				deltaY = 10.0f;
				deltaX = -4.0f;
				touchingWallL = false;
				speed = 2;
		}
		else
		{
				if (IsKeyReleased(KEY_SPACE) && deltaY > 0)
						deltaY *= 0.5f;
				if (deltaY > -9.0f)
				{
						deltaY -= 0.5f;
				}

				speed = touchingWallR || touchingWallL ? 0 : 2;
		}
		Pos.y -= (deltaY * gravity);
}

void Player::displayPlayer()
{
	return;
}
