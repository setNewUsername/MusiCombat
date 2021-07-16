#pragma once
#ifndef CLASSES_H
#define CLASSES_H
#include "Graphics.hpp"
#include "globals.h"
#include "cmath"

#define MOVEMENT_SPEED 0.001
#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 800

#define ENEMY_MOVEMENT_SPEED 0.3

#define PI 3.14159
#define AMMO_AMOUNT 50

#define FLOOR SCREEN_HEIGHT
#define L_WALL 0
#define R_WALL SCREEN_WIDTH

using namespace sf;

class ClassObjects
{
	private:
		Image newObjectImg;

	protected:
		Texture _texture;
		Sprite _sprite;
		int _posX;
		int _posY;
		Vector2u _size;

	public:
		ClassObjects(const char* textureName, int startPosX, int startPosY);
		~ClassObjects();

		void setTexture(const char* textureName);

		Sprite getSprite();

		void setPosition(int x, int y);

		int getPositionX();

		int getPositionY();
};

class ClassLiveObjects: public ClassObjects{
	private:
		float currentFrame = 0;
		bool onGround;
		bool aliveState;
		FloatRect rectengle;

		virtual void animation(const char direction);

	protected:
		int _health = 0;
		
	public:
		ClassLiveObjects(const char* textureName, int startPosX, int startPosY, int health);
		~ClassLiveObjects();

		virtual void movement(const char direction, float movementSpeedDiescreaser);

		void gravity();

		void getDamage(int damage);

		void death();

		int getHealth();

		bool getAliveState();

		FloatRect GetRect();
};

class Player : public ClassLiveObjects {
private:
	int currentFrame = 0;

	void animation(const char direction);
protected:

public:
	Player(const char* textureName, int startPosX, int startPosY, int health);
	~Player();

	void setHp(int damage);

	void movement(const char direction, float movementSpeedDiescreaser);

	int getCurrentFrame();
};
 
class Projectile : public ClassObjects {
private:
	bool distracted;
	bool inAir = false;
	int flySide = 1;
	double _posxIncreaser;
	FloatRect _rectangle;

public:
	Projectile(const char* textureName = "", int startPosX = 0, int startPosY = 0);
	~Projectile();

	void fly(double flyAngle);

	void checkForMapCollision();

	FloatRect getProjectileRectangle();

	void projectileDistract();

	bool getDistractedState();
};

class PlayersGun: public ClassObjects {
private:
	double rotationAngle;
	int width = _size.x;
	int height = _size.y;

public:
	PlayersGun(const char* textureName, int startPosX, int startPosY);
	~PlayersGun();

	void followPlayer(const char direction, int posX, int posY);

	void followMouse(int mousePosX, int mousePosY);

	double getAngle();

	void shoot();
};

class Enemy : public ClassLiveObjects {
private:
	float speedDiescreaser = ENEMY_MOVEMENT_SPEED;

public:
	Enemy(const char* textureName = "", int startPosX = 0, int startPosY = 0, int health = 0);
	~Enemy();

	void moveToPlayer(int PlayerPosX);

	bool checkCollisionWithBullet(Projectile* projectile) {
		if (_posX == projectile->getPositionX() && _posY == projectile->getPositionY()) {
			this->death();
			return true;
		}
	}
};
#endif