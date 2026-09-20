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
				float		gravity;
				bool		grounded;
				bool		touchingWallR;
				bool		touchingWallL;

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
				int			radius;

				void	checkHealth();
				void	handleMovement();
				void	handlePhysics();
				void	handleJump();
				void	takeDamage(int damage);
				void	displayPlayer();
};

#endif
