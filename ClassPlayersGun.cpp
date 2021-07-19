#include "Classes.h"

ClassPlayersGun::ClassPlayersGun(string textureName, int startPosX, int startPosY) :ClassObject(textureName, startPosX, startPosY) {};
ClassPlayersGun::~ClassPlayersGun() {};

void ClassPlayersGun::setParams() {
	width = (*this->getTextureSize()).x;
	height = (*this->getTextureSize()).y;
	(*this->getObjectSprite()).setOrigin((*this->getTextureSize()).x, (*this->getTextureSize()).y / 2);
}

void ClassPlayersGun::followPlayer(int posX, int posY) {
	(*this->getObjectSprite()).setPosition(posX + 20, posY + 35);
}

void ClassPlayersGun::followMouse(int mousePosX, int mousePosY) {

	float perpendicularToFloor;
	float distanceToPerpendicular;

	perpendicularToFloor = (*this->getObjectSprite()).getPosition().y - mousePosY;
	distanceToPerpendicular = (*this->getObjectSprite()).getPosition().x - mousePosX;

	if (distanceToPerpendicular == 0) {
		distanceToPerpendicular = 1;
	}

	rotationAngle = atan2(perpendicularToFloor, distanceToPerpendicular) * (180 / PI);

	if (rotationAngle > 90 || rotationAngle < -90) {
		(*this->getObjectSprite()).setTextureRect(IntRect(width, height, -width, -height));
	}
	else if (rotationAngle < 90 || rotationAngle > -90) {
		(*this->getObjectSprite()).setTextureRect(IntRect(width, 0, -width, height));
	}

	(*this->getObjectSprite()).setRotation(rotationAngle);
}

double ClassPlayersGun::getAngle() {
	return rotationAngle;
}

void ClassPlayersGun::shoot(Projectile* bulletsArray, ClassMusicPlayer* music, int FriquencySummeryAtStartOfFrame) {
	if (shots == 50) {
		shots = 0;
	}

	int bulletStartPosXCorrector = (*this->getTextureSize()).x * cos(this->getAngle() * PI / 180);
	int bulletStartPosYCorrector = (*this->getTextureSize()).x * sin(this->getAngle() * PI / 180);

	(&bulletsArray[shots])->Projectile::Projectile("textures/bullet.png", (*this->getObjectSprite()).getPosition().x - bulletStartPosXCorrector, (*this->getObjectSprite()).getPosition().y - bulletStartPosYCorrector - 10);

	if (music->getFriquencySummery() > FriquencySummeryAtStartOfFrame) {
		bulletsArray[shots].setBulletDamage(5);
	}
	else {
		bulletsArray[shots].setBulletDamage(1);
	}

	shots++;
}

int ClassPlayersGun::getShots() {
	return shots;
}