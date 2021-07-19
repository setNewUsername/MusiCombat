#pragma once
#ifndef CLASSEES_H
#define CLASSEES_H
#include "globals.h"

class ClassMusicPlayer {
private:
	DWORD chan;

public:
	ClassMusicPlayer() {};
	~ClassMusicPlayer() {};

	int getFriquencySummery();

	void playMusic(const char* fileName);

	void stopMusic();

	int getMusicLength();

	void resumeMusic();

	void setMusicPosition(int secondsAmount);

	int getMusicPosition();

	bool endOfMusic();
};//

class ClassObject {
private:
	Image objectImage;
	Texture texture;
	Sprite sprite;
	Vector2u size;

public:
	ClassObject(string textureName = "", int posX = 0, int posY = 0);
	~ClassObject();

	Sprite* getObjectSprite();

	Vector2u* getTextureSize();
};

class ClassLiveObject:public ClassObject{
private:
	bool alive;
	int currentFrame = 0;
	int maxFrameAmount;
	int frameHeight;
	int frameWidth;
	float movementSpeed;
	int health;
	bool _movementToLeft = false;
	bool _movementToRight = false;

public:
	ClassLiveObject(string textureName = "", int posX = 0, int posY = 0, int healthOnStart = 0, int rectWidth = 0, int rectHeight = 0);
	~ClassLiveObject();

	void updateRectCalculateFrameAmount(int rectWidth, int rectHeight);

	void movementToLeft(int movementSpeedDiescreaser);
	
	void movementToRight(int movementSpeedDiescreaser);

	void death();

	bool getAliveState();

	void getDamage(int damageAmount);

	void animation();
};

class ClassStartupMenuButtons {
private:
	Font textFont;
	Text buttonText;
	int fontSize = 40;

public:
	ClassStartupMenuButtons(string text, int posX, int posY);
	~ClassStartupMenuButtons();

	FloatRect getButtonRectangle();

	Text getButtonText();

	void setNewTextPosition(int posX, int posY);

	void colorTo(Color color);

}; 

class ClassGame {
private:
	int startMenuWidth = 800;
	int startMenuHeight = 600;
	int fontSize = 40;
	bool gameStarted = false;
	Font gameFont;

public:
	ClassGame();
	~ClassGame();
	
	Text getTextObj(string textOfTextObj, int posX, int posY);

	bool gameStartMenu();

	bool exitMenu();

	bool endMenu();

};

class Projectile : public ClassObject {
private:
	bool distracted;
	bool inAir;
	int flySide = 1;
	double posYincreaser;
	int damage = 1;

public:
	Projectile(string textureName = "", int startPosX = 0, int startPosY = 0);
	~Projectile();

	void fly(double flyAngle);

	void checkForMapCollision();

	bool getDestractedState();

	bool getInAirState();

	void setDistracted();

	void setNotDistracted();

	void setBulletDamage(unsigned int damage);

	int getBulletDamage();

};

class ClassPlayersGun : public ClassObject {
private:
	double rotationAngle;
	int width;
	int height;
	int shots = 0;

public:
	ClassPlayersGun(string textureName, int startPosX, int startPosY);
	~ClassPlayersGun();

	void setParams();

	void followPlayer(int posX, int posY);

	void followMouse(int mousePosX, int mousePosY);

	double getAngle();

	void shoot(Projectile* bulletsArray, ClassMusicPlayer* music, int FriquencySummeryAtStartOfFrame);

	int getShots();
};

class ClassEnemy :public ClassLiveObject {
private:
	int enemyAmount;

public:
	ClassEnemy(string textureName = "", int startPosX = 0, int startPosY = 0, int health = 0, int rectWidth = 0, int rectHeight = 0);
	~ClassEnemy();

	void moveToPlayer(int PlayerPosX, int movementSpeedDiescreaser);


	void cheForBulletCollision(Projectile* bulletsArray);
};

class ClassPlayer :public ClassLiveObject {
private:

public:
	ClassPlayer(string textureName = "", int startPosX = 0, int startPosY = 0, int health = 0, int rectWidth = 0, int rectHeight = 0);
	~ClassPlayer();

	bool checkCollisionWithEnemy(ClassEnemy* enemyArray, int enemyAmount);
};

class ClassSpawner {
private:
	int enemyAmount = 0;
	int spawnLimit;
	Clock spawnCoolDown;

public:
	ClassSpawner();
	~ClassSpawner();

	void setSpawnLimit(int newSpawnLimit);

	void spawn(ClassEnemy* enemyArray);

	int getEnemyAmount();
};
#endif