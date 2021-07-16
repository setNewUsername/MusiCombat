#include "Classes.h"

//анимация живых объектов
void ClassLiveObjects::animation(const char direction) {
	if (currentFrame > 5) {
		currentFrame = 0;
	}
	switch (direction) {
	case 'l':
		_sprite.setTextureRect(IntRect(60 * currentFrame + 60, 0, -60, 150));
		break;

	case 'r':
		_sprite.setTextureRect(IntRect(60 * currentFrame, 0, 60, 150));
		break;
	}
}

//конструктор живых объектов
ClassLiveObjects::ClassLiveObjects(const char* textureName, int startPosX, int startPosY, int health) :ClassObjects(textureName, startPosX, startPosY) {
	this->_health = health;
	//rectengle = FloatRect(0, 0, 60, 150);
	this->aliveState = true;
};

//деструктор живых объектов
ClassLiveObjects::~ClassLiveObjects() {
};

//движение живых объектов
void ClassLiveObjects::movement(const char direction, float movementSpeedDiescreaser) {
	switch (direction) {
	case 'l':
		_posX = _sprite.getPosition().x;
		if (_posX > L_WALL) {
			_sprite.move(-MOVEMENT_SPEED * movementSpeedDiescreaser * ::globalClocks, 0);
		}
		break;

	case 'r':
		_posX = _sprite.getPosition().x;
		if (_posX < R_WALL - 60) {
			_sprite.move(MOVEMENT_SPEED* movementSpeedDiescreaser * ::globalClocks, 0);
		}
		break;

	default:
		break;
	}
	this->animation(direction);
	currentFrame += 0.01 * ::globalClocks;
}

//"гравитация" живых объектов
void ClassLiveObjects::gravity() {
	if (_posY <= 0) {
		this->setPosition(_posX, (_posY + 0.005 * ::globalClocks));
	}
}

//получение урона живых объектов
void ClassLiveObjects::getDamage(int damage) {
	this->_health -= damage;
	if (_health <= 0) {
		death();
	}
}

//смерть живых объектов
void ClassLiveObjects::death() {
	this->~ClassLiveObjects();
	this->aliveState = false;
}

FloatRect ClassLiveObjects::GetRect(){
	return rectengle;
}

bool ClassLiveObjects::getAliveState() {
	return aliveState;
}

//вернуть здоровье живых объектов
int ClassLiveObjects::getHealth() {
	return _health;
}