#include "Classes.h"

//конструктор объекта
ClassObjects::ClassObjects(const char* textureName, int startPosX, int startPosY) {
	if (newObjectImg.loadFromFile(textureName)) {
		_size = newObjectImg.getSize();

		setTexture(textureName);
		_sprite.setTexture(_texture);
		setPosition(startPosX, startPosY);
		_sprite.setTextureRect(IntRect(0, 0, _size.x, _size.y));
	}
};

//деструктор объекта
ClassObjects::~ClassObjects() {

};

//установка тектстуры объекта
void ClassObjects::setTexture(const char* textureName) {
	_texture.loadFromFile(textureName);
}

//получить спрайт объекта
Sprite ClassObjects::getSprite() {
	return _sprite;
}

//изменить позицию объекта
void ClassObjects::setPosition(int x, int y) {
	_posX = x;
	_posY = y;
	_sprite.setPosition(_posX, _posY);
}

//получить координату Х объекта
int ClassObjects::getPositionX() {
	return _sprite.getPosition().x;
}

//получить координату Y объекта
int ClassObjects::getPositionY() {
	return _sprite.getPosition().y;
}