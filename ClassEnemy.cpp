#include "Classes.h"

Enemy::Enemy(const char* textureName, int startPosX, int startPosY, int health) :ClassLiveObjects(textureName, startPosX, startPosY, health) {
	_sprite.setTextureRect(IntRect(0, 0, 60, 150));
};
Enemy::~Enemy() {

};

void Enemy::moveToPlayer(int PlayerPosX) {
	if (_posX < PlayerPosX) {
		this->movement('r', speedDiescreaser);
	}
	else if (_posX > PlayerPosX) {
		this->movement('l', speedDiescreaser);
	}
	else {
	}
}
