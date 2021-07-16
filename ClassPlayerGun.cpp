#include "Classes.h"

PlayersGun::PlayersGun(const char* textureName, int startPosX, int startPosY) :ClassObjects(textureName, startPosX, startPosY) {
	_sprite.setOrigin(_size.x, _size.y / 2);
};
PlayersGun::~PlayersGun() {};

void PlayersGun::followPlayer(const char direction, int posX, int posY) {
	this->setPosition(posX + 20, posY + 35);
}

void PlayersGun::followMouse(int mousePosX, int mousePosY) {
	mousePosX -= 20;
	mousePosY -= 168;

	float perpendicularToFloor;
	float distanceToPerpendicular;

	perpendicularToFloor = _posY - mousePosY;
	distanceToPerpendicular = _posX - mousePosX;

	if (distanceToPerpendicular == 0) {
		distanceToPerpendicular = 1;
	}

	rotationAngle = atan2(perpendicularToFloor, distanceToPerpendicular) * (180 / PI);

	if (rotationAngle > 90 || rotationAngle < -90) {
		_sprite.setTextureRect(IntRect(width, height, -width, -height));
	}
	else if (rotationAngle < 90 || rotationAngle > -90) {
		_sprite.setTextureRect(IntRect(width, 0, -width, height));
	}

	_sprite.setRotation(rotationAngle);
}

double PlayersGun::getAngle() {
	return rotationAngle;
}

void PlayersGun::shoot() {

}