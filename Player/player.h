#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include "../Objects/objects.h"
#include "../general.h"

class Player{
		private:
				int 		health;
				int			speed;
				float		deltaX;
				float		deltaY;
				float		stamina;

				enum Anim{
						IDLE,
						MOVING,
						FALLING,
						ONWALL
				};
		public:
				Vector2 Pos;
				std::vector<Ground> collisionLayer;
				Player(int health, std::vector<Ground> Layer);

				void	checkHealth();
				void	handleMovement();
				void	handleJump();
				void	takeDamage(int damage);
				void	handleWallRun();
				void	displayPlayer();
};

#endif
