#include "Classes.h"

//�������� ����� ��������
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

//����������� ����� ��������
ClassLiveObjects::ClassLiveObjects(const char* textureName, int startPosX, int startPosY, int health) :ClassObjects(textureName, startPosX, startPosY) {
	this->_health = health;
	//rectengle = FloatRect(0, 0, 60, 150);
	this->aliveState = true;
};

//���������� ����� ��������
ClassLiveObjects::~ClassLiveObjects() {
};

//�������� ����� ��������
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

//"����������" ����� ��������
void ClassLiveObjects::gravity() {
	if (_posY <= 0) {
		this->setPosition(_posX, (_posY + 0.005 * ::globalClocks));
	}
}

//��������� ����� ����� ��������
void ClassLiveObjects::getDamage(int damage) {
	this->_health -= damage;
	if (_health <= 0) {
		death();
	}
}

//������ ����� ��������
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

//������� �������� ����� ��������
int ClassLiveObjects::getHealth() {
	return _health;
}