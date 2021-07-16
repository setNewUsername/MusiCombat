#include "Classes.h"

//����������� �������
ClassObjects::ClassObjects(const char* textureName, int startPosX, int startPosY) {
	if (newObjectImg.loadFromFile(textureName)) {
		_size = newObjectImg.getSize();

		setTexture(textureName);
		_sprite.setTexture(_texture);
		setPosition(startPosX, startPosY);
		_sprite.setTextureRect(IntRect(0, 0, _size.x, _size.y));
	}
};

//���������� �������
ClassObjects::~ClassObjects() {

};

//��������� ��������� �������
void ClassObjects::setTexture(const char* textureName) {
	_texture.loadFromFile(textureName);
}

//�������� ������ �������
Sprite ClassObjects::getSprite() {
	return _sprite;
}

//�������� ������� �������
void ClassObjects::setPosition(int x, int y) {
	_posX = x;
	_posY = y;
	_sprite.setPosition(_posX, _posY);
}

//�������� ���������� � �������
int ClassObjects::getPositionX() {
	return _sprite.getPosition().x;
}

//�������� ���������� Y �������
int ClassObjects::getPositionY() {
	return _sprite.getPosition().y;
}