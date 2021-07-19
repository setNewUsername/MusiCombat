#include "Classes.h"

ClassStartupMenuButtons::ClassStartupMenuButtons(string text, int posX, int posY) {
	textFont.loadFromFile("fonts/20951.ttf");
	buttonText.setFont(textFont);
	buttonText.setPosition(posX, posY);
	buttonText.setCharacterSize(fontSize);
	buttonText.setString(text);
};
ClassStartupMenuButtons::~ClassStartupMenuButtons() {};

FloatRect ClassStartupMenuButtons::getButtonRectangle() {
	return buttonText.getGlobalBounds();
}

Text ClassStartupMenuButtons::getButtonText() {
	return buttonText;
}

void ClassStartupMenuButtons::setNewTextPosition(int posX, int posY) {
	buttonText.setPosition(posX, posY);
}

void ClassStartupMenuButtons::colorTo(Color color) {
	buttonText.setFillColor(color);
}
