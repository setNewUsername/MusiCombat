#include "Classes.h"

ClassEnemy::ClassEnemy(string textureName, int startPosX, int startPosY, int health, int rectWidth, int rectHeight) : ClassLiveObject(textureName, startPosX, startPosY, health, rectWidth, rectHeight) {};
ClassEnemy::~ClassEnemy() {};

void ClassEnemy::moveToPlayer(int PlayerPosX, int movementSpeedDiescreaser) {
	if ((*this->getObjectSprite()).getPosition().x < PlayerPosX) {
		this->movementToRight(movementSpeedDiescreaser);
	}
	else if ((*this->getObjectSprite()).getPosition().x > PlayerPosX) {
		this->movementToLeft(movementSpeedDiescreaser);
	}
	else {}
}

void ClassEnemy::cheForBulletCollision(Projectile* bulletsArray) {
	for (int i = 0; i < 50; i++) {
		if (!bulletsArray[i].getDestractedState()) {
			if ((*this->getObjectSprite()).getGlobalBounds().intersects((*bulletsArray[i].getObjectSprite()).getGlobalBounds())) {
				this->getDamage(bulletsArray[i].getBulletDamage());
				bulletsArray[i].setDistracted();
			}
		}
	}
}