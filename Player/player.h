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
				Vector2		start_pos;

				enum Anim{
						IDLE,
						MOVING,
						FALLING,
						ONWALL
				};
				Anim		state;

				void	handleMovement();
				void	handleJump();
				void	handlePhysics();
				void	checkSpike();
		public:
				Vector2 Pos;
				Player(int health, Vector2 spawn);
				int			radius;

				void	loadPlayer();
				void	unloadPlayer();
				void	checkHealth();
				void	handlePlayer();
				void	takeDamage(int damage);
				void	displayPlayer();
};

#endif
