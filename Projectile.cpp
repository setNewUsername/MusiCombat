#include "Classes.h"

Projectile::Projectile(string textureName, int startPosX, int startPosY) :ClassObject(textureName, startPosX, startPosY) {
	distracted = false;
	inAir = false;
};
Projectile::~Projectile() {};

void Projectile::fly(double flyAngle) {
	if (inAir == false) {
		if (flyAngle > 90 || flyAngle < -90) {
			flySide *= 1;
		}
		else if (flyAngle < 90 || flyAngle > -90) {
			flySide *= -1;
		}

		posYincreaser = tan(flyAngle * PI / 180) * flySide;

		inAir = true;
	}

	(*this->getObjectSprite()).move(flySide * 0.004 * ::globalClocks, posYincreaser);

	this->checkForMapCollision();
}

void Projectile::checkForMapCollision() {
	if ((*this->getObjectSprite()).getPosition().x == 0 || (*this->getObjectSprite()).getPosition().x == 1920) {
		this->distracted = true;
	}
	else if ((*this->getObjectSprite()).getPosition().y == 0 || (*this->getObjectSprite()).getPosition().y == 1080) {
		this->distracted = true;
	}
}

bool Projectile::getDestractedState() {
	return distracted;
}

bool Projectile::getInAirState() {
	return inAir;
}

void Projectile::setDistracted() {
	this->distracted = true;
}

void Projectile::setNotDistracted() {
	this->distracted = false;
}

void Projectile::setBulletDamage(unsigned int damage) {
	this->damage = damage;
}

int Projectile::getBulletDamage() {
	return damage;
}