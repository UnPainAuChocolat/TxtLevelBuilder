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
				std::vector<Ground> collisionLayer;
				Vector2 Pos;
				Player(int health, std::vector<Ground> Layer, Vector2 spawn);
				int			radius;

				void	checkHealth();
				void	handleMovement();
				void	handlePhysics();
				void	handleJump();
				void	takeDamage(int damage);
				void	displayPlayer();
};

#endif
