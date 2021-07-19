#include "Classes.h"

ClassObject::ClassObject(string textureName, int posX, int posY) {
	if (objectImage.loadFromFile(textureName)) {
		size = objectImage.getSize();
		texture.loadFromFile(textureName);
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}
};
ClassObject::~ClassObject() {};

Sprite* ClassObject::getObjectSprite() {
	return &sprite;
}

Vector2u* ClassObject::getTextureSize() {
	return &size;
}