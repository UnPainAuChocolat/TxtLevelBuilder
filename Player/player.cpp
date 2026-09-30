#include "player.h"
#include "../general.h"

int wallJumped = 0;

//anim values
int frameCount = 0;
int orientation = 1;
Texture2D idleSprite;
Texture2D sprintSprite;
Texture2D wallslideSprite;

void Player::checkSpike()
{
		int		i = 0;
		int		size_list = spikes.size();
		while (i < size_list)
		{
				if (CheckCollisionCircleRec(Pos, radius, spikes[i]))
				{
						takeDamage(1000);
				}
				i++;
		}
}

Player::Player(int health, Vector2 spawn) : health(health), Pos(spawn){ 
		speed = 2;
		start_pos = spawn;
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

void Player::handlePlayer()
{
		handleMovement();
		handlePhysics();
		handleJump();
		checkSpike();
		if (health <= 0)
		{
				Pos = start_pos;
				health = 50;
		}
}

void Player::handleMovement(){
		if (IsKeyDown(KEY_LEFT_SHIFT) && stamina > 0 && !grounded)
		{
				speed = 10;
				stamina -= 0.25f;
		}
		if (IsKeyDown(KEY_D) && (wallJumped == 0))
		{
				deltaX = 2.0f;
				orientation = 1;
		}
		if (IsKeyDown(KEY_A) && (wallJumped == 0))
		{
				deltaX = -2.0f;
				orientation = -1;
		}
		if (deltaX > -0.10f && deltaX < 0.10f)
		{
				deltaX = 0.0f;
				state = IDLE;
		}
		if (deltaX > 0.0f)
		{
				deltaX -= grounded ? 0.15f : 0.0f;
				state = MOVING;
		}
		else if (deltaX < 0.0f)
		{
				deltaX += grounded ? 0.15f : 0.0f;
				state = MOVING;
		}
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

				const Rectangle& coll = levelCollision[i].collision;

				bool onTop = (feet >= coll.y && feet <= (coll.y + radius));
				bool onBot = (head >= coll.y + coll.height - radius && 
								head <= (coll.y + coll.height));

				bool verticalOverlap = (feet >= coll.y && head <= coll.y + coll.height);
				bool onSideL = verticalOverlap && (Pos.x + radius >= coll.x && 
								Pos.x - radius <= coll.x);
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
								state = ONWALL;
								orientation = -1;
								wallJumped = 0;
								deltaX = 0;
						}
						else if (onSideR)
						{
								Pos.x = coll.x + coll.width + radius;
								gravity = 0.25f;
								touchingWallR = true;
								state = ONWALL;
								orientation = 1;
								wallJumped = 0;
								deltaX = 0;
						}
				}
				i++;
		}
}

void Player::handleJump()
{
		if (grounded)
		{
				wallJumped = 0;
				stamina = 1.0f;
				deltaY = 0.0f;
				speed = 2;
				if (IsKeyPressed(KEY_SPACE))
						deltaY = 10.0f;
		}
		else if (touchingWallR && IsKeyPressed(KEY_SPACE))
		{
				wallJumped = 12;
				deltaY = 10.0f;
				deltaX = 2.0f;
				touchingWallR = false;
				speed = 2;
		}
		else if (touchingWallL && IsKeyPressed(KEY_SPACE))
		{
				wallJumped = 12;
				deltaY = 10.0f;
				deltaX = -2.0f;
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

				if (wallJumped > 0)wallJumped -= 1;
				speed = touchingWallR || touchingWallL ? 0 : 2;
		}
		Pos.y -= (deltaY * gravity);
}

void Player::displayPlayer()
{
		int nbrFrames = 0;
		Texture2D currentTexture;
		Rectangle frame = {(float)frameCount * (float)(idleSprite.width/10), 0.0f,
				(float)idleSprite.width/10 * orientation, (float)idleSprite.height};

		if (state == IDLE)
		{
				nbrFrames = 10;
				currentTexture = idleSprite;
		}
		else if (state == ONWALL)
		{
				nbrFrames = 1;
				currentTexture = wallslideSprite;
		}
		else if (state == MOVING)
		{
				nbrFrames = 8;
				currentTexture = sprintSprite;
		}
		frameCount++;
		if (frameCount > nbrFrames)
		{
				frameCount = 0;
		}
		DrawTextureRec(currentTexture, frame, {Pos.x - 23, Pos.y - idleSprite.height + 17}, WHITE);
}

void Player::loadPlayer()
{
		sprintSprite = LoadTexture("Assets/Player/Run.png");
		wallslideSprite = LoadTexture("Assets/Player/WallSlide.png");
		idleSprite = LoadTexture("Assets/Player/Idle.png");
}

void Player::unloadPlayer()
{
		UnloadTexture(idleSprite);
		UnloadTexture(wallslideSprite);
		UnloadTexture(sprintSprite);
}
