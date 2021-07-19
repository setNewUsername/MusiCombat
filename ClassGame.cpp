#include "Classes.h"

ClassGame::ClassGame() {
	gameFont.loadFromFile("fonts/20951.ttf");
};
ClassGame::~ClassGame() {};

Text ClassGame::getTextObj(string textOfTextObj, int posX, int posY) {
	Text textOfObj;

	textOfObj.setFont(gameFont);
	textOfObj.setPosition(posX, posY);
	textOfObj.setCharacterSize(fontSize);
	textOfObj.setString(textOfTextObj);

	return textOfObj;
}

bool ClassGame::gameStartMenu() {
	RenderWindow window(sf::VideoMode(startMenuWidth, startMenuHeight, 32), "MusiCombat");

	ClassStartupMenuButtons* startButton = new ClassStartupMenuButtons("Start", 0, 0);
	ClassStartupMenuButtons* exitButton = new ClassStartupMenuButtons("Exit", 0, 0);
	ClassStartupMenuButtons* firstTrack = new ClassStartupMenuButtons("1", 0, 0);
	ClassStartupMenuButtons* secondTrack = new ClassStartupMenuButtons("2", 0, 0);
	ClassStartupMenuButtons* thirdTrack = new ClassStartupMenuButtons("3", 0, 0);


	startButton->setNewTextPosition(startMenuWidth / 2 - startButton->getButtonRectangle().width / 2, startMenuHeight / 2 - startButton->getButtonRectangle().height * 3);
	exitButton->setNewTextPosition(startMenuWidth / 2 - exitButton->getButtonRectangle().width / 2, startMenuHeight / 2 - exitButton->getButtonRectangle().height);

	//выбор музыки
	firstTrack->setNewTextPosition(0 + firstTrack->getButtonRectangle().width, 0);
	secondTrack->setNewTextPosition(0 + secondTrack->getButtonRectangle().width * 2, 0);
	thirdTrack->setNewTextPosition(0 + thirdTrack->getButtonRectangle().width * 4, 0);

	firstTrack->colorTo(Color::Green);

	if (gameStarted == true) {
		startButton->~ClassStartupMenuButtons();
	}

	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			mousePosition = Mouse::getPosition(window);

			FloatRect mouseRect(mousePosition.x, mousePosition.y, 20, 20);

			if (firstTrack->getButtonRectangle().intersects(mouseRect)) {
				::trackName = "music/1.mp3";
				firstTrack->colorTo(Color::Green);
				secondTrack->colorTo(Color::White);
				thirdTrack->colorTo(Color::White);
			}
			else if (secondTrack->getButtonRectangle().intersects(mouseRect)) {
				::trackName = "music/2.mp3";

				firstTrack->colorTo(Color::White);
				secondTrack->colorTo(Color::Green);
				thirdTrack->colorTo(Color::White);
			}
			else if (thirdTrack->getButtonRectangle().intersects(mouseRect)) {
				::trackName = "music/3.mp3";
				firstTrack->colorTo(Color::White);
				secondTrack->colorTo(Color::White);
				thirdTrack->colorTo(Color::Green);
			}

			if (startButton->getButtonRectangle().intersects(mouseRect)) {
				gameStarted = true;
				window.close();
				return true;
			}
			else if (exitButton->getButtonRectangle().intersects(mouseRect)) {
				window.close();
				return false;
			}
		}

		window.clear();

		window.draw(startButton->getButtonText());

		window.draw(exitButton->getButtonText());

		window.draw(firstTrack->getButtonText());
		window.draw(secondTrack->getButtonText());
		window.draw(thirdTrack->getButtonText());

		window.display();
	}
}

bool ClassGame::exitMenu() {
	RenderWindow window(sf::VideoMode(startMenuWidth, startMenuHeight, 32), "MusiCombat");
	ClassStartupMenuButtons* exitButton = new ClassStartupMenuButtons("Exit", 0, 0);

	exitButton->setNewTextPosition(startMenuWidth / 2 - exitButton->getButtonRectangle().width / 2, startMenuHeight / 2 - exitButton->getButtonRectangle().height);

	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
			return false;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			mousePosition = Mouse::getPosition(window);

			FloatRect mouseRect(mousePosition.x, mousePosition.y, 20, 20);

			if (exitButton->getButtonRectangle().intersects(mouseRect)) {
				window.close();
				return true;
			}
		}

		window.clear();

		window.draw(exitButton->getButtonText());

		window.display();
	}
}

bool ClassGame::endMenu() {
	RenderWindow window(sf::VideoMode(startMenuWidth, startMenuHeight, 32), "MusiCombat");
	ClassStartupMenuButtons* exitButton = new ClassStartupMenuButtons("Exit", 0, 0);

	exitButton->setNewTextPosition(startMenuWidth / 2 - exitButton->getButtonRectangle().width / 2, startMenuHeight / 2 - exitButton->getButtonRectangle().height);

	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			mousePosition = Mouse::getPosition(window);

			FloatRect mouseRect(mousePosition.x, mousePosition.y, 20, 20);

			if (exitButton->getButtonRectangle().intersects(mouseRect)) {
				window.close();
				return true;
			}
		}

		window.clear();

		window.draw(this->getTextObj("End of game!", 290, 200));

		window.draw(exitButton->getButtonText());

		window.display();
	}
}
