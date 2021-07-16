#include "Classes.h"

Player::Player(const char* textureName, int startPosX, int startPosY, int health) :ClassLiveObjects(textureName, startPosX, startPosY, health) {
	_sprite.setTextureRect(IntRect(0, 0, 38, 74));
};
Player::~Player() {};

void Player::setHp(int damage) {
	this->getDamage(damage);
}

int Player::getCurrentFrame() {
	return currentFrame;
};

void Player::movement(const char direction, float movementSpeedDiescreaser) {
	switch (direction) {
	case 'l':
		_posX = _sprite.getPosition().x;
		if (_posX > L_WALL) {
			_sprite.move(-MOVEMENT_SPEED * movementSpeedDiescreaser * ::globalClocks, 0);
		}
		break;

	case 'r':
		_posX = _sprite.getPosition().x;
		if (_posX < R_WALL - 38) {
			_sprite.move(MOVEMENT_SPEED * movementSpeedDiescreaser * ::globalClocks, 0);
		}
		break;

	default:
		break;
	}
	this->animation(direction);
	currentFrame += 1;
}

void Player::animation(const char direction) {
	if (currentFrame >= 9) {
		currentFrame = 0;
	}
	switch (direction) {
	case 'l':
		_sprite.setTextureRect(IntRect(40 * currentFrame + 40, 0, -40, 74));
		break;

	case 'r':
		_sprite.setTextureRect(IntRect(40 * currentFrame, 0, 40, 74));
		break;
	}
}