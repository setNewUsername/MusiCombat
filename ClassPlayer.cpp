#include "Classes.h"

ClassPlayer::ClassPlayer(string textureName, int startPosX, int startPosY, int health, int rectWidth, int rectHeight) : ClassLiveObject(textureName, startPosX, startPosY, health, rectWidth, rectHeight) {};
ClassPlayer::~ClassPlayer() {};

bool ClassPlayer::checkCollisionWithEnemy(ClassEnemy* enemyArray, int enemyAmount) {
	for (int i = 0; i < enemyAmount; i++) {
		if (enemyArray[i].getAliveState()) {
			if ((*this->getObjectSprite()).getGlobalBounds().intersects((*enemyArray[i].getObjectSprite()).getGlobalBounds())) {
				this->death();
				return true;
			}
			else {
				return false;
			}
		}
	}
}
