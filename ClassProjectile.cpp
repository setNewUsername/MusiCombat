#include "Classes.h"

Projectile::Projectile(const char* textureName, int startPosX, int startPosY) :ClassObjects(textureName, startPosX, startPosY) {
	//_sprite.setOrigin(_size.x / 2, _size.y / 2);
	_rectangle = FloatRect(0, 0, 10, 10);
	distracted = false;
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

		_posxIncreaser = tan(flyAngle * PI / 180) * flySide;

		inAir = true;
	}

	_sprite.move(flySide * 0.004 * ::globalClocks, _posxIncreaser);
	_posX = _sprite.getPosition().x;
	_posY = _sprite.getPosition().y;
}

void Projectile::checkForMapCollision() {
	if (_posX == 0 || _posX == SCREEN_WIDTH) {
		this->projectileDistract();
	}
	else if(_posY == 0 || _posY == SCREEN_HEIGHT){
		this->projectileDistract();
	}
}

FloatRect Projectile::getProjectileRectangle() {
	return _rectangle;
}

void Projectile::projectileDistract() {
	this->~Projectile();
	distracted = true;
}

bool Projectile::getDistractedState() {
	return distracted;
}