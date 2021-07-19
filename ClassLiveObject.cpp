#include "Classes.h"

ClassLiveObject::ClassLiveObject(string textureName, int posX, int posY, int healthOnStart, int rectWidth, int rectHeight) :ClassObject(textureName, posX, posY) {
	alive = true;
	health = healthOnStart;
	frameHeight = rectHeight;
};
ClassLiveObject::~ClassLiveObject() {};

void ClassLiveObject::updateRectCalculateFrameAmount(int rectWidth, int rectHeight) {
	(*getObjectSprite()).setTextureRect(IntRect(0, 0, rectWidth, rectHeight));
	maxFrameAmount = (*this->getTextureSize()).x / rectWidth;
	frameWidth = (*this->getTextureSize()).x / maxFrameAmount;
}

void ClassLiveObject::movementToLeft(int movementSpeedDiescreaser) {
	_movementToLeft = true;
	_movementToRight = false;

	if (_movementToLeft == true) {
		if ((*this->getObjectSprite()).getPosition().x > 1) {
			(*this->getObjectSprite()).move(-0.001 * ::globalClocks / movementSpeedDiescreaser, 0);
		}
	}
	currentFrame += 1;
	animation();
}

void ClassLiveObject::movementToRight(int movementSpeedDiescreaser) {
	_movementToRight = true;
	_movementToLeft = false;

	if (_movementToRight == true) {
		if ((*this->getObjectSprite()).getPosition().x < 1880) {
			(*this->getObjectSprite()).move(0.001 * ::globalClocks / movementSpeedDiescreaser, 0);
		}
	}
	currentFrame += 1;
	animation();
}

void ClassLiveObject::death() {
	this->alive = false;
}

bool ClassLiveObject::getAliveState() {
	return alive;
}

void ClassLiveObject::getDamage(int damageAmount) {
	health -= damageAmount;
	if (health <= 0) {
		this->death();
	}
}

void ClassLiveObject::animation() {
	if (currentFrame >= maxFrameAmount) {
		currentFrame = 0;
	}
	if (_movementToLeft == true) {
		(*this->getObjectSprite()).setTextureRect(IntRect(frameWidth * currentFrame + frameWidth, 0, -frameWidth, frameHeight));
	}
	else if (_movementToRight == true) {
		(*this->getObjectSprite()).setTextureRect(IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
	}
}