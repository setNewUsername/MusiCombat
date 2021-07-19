#include "globals.h"
#include "Classes.h"

float globalClocks;

const char* trackName = "music/1.mp3";

void startGame(ClassGame* game) {
	//позиция мыши
	Vector2i mousePosition;

	//часы
	Clock clocks;
	Clock gunCoolDown;

	//объект окна
	RenderWindow gameWindow(sf::VideoMode(), "MusiCombat", sf::Style::Fullscreen);

	//игрок
	ClassPlayer* player = new ClassPlayer("textures/mario.png", SCREEN_WIDTH / 2, 1010, 5, 38, 74);
	player->updateRectCalculateFrameAmount(38, 74);

	//спавнер врагов
	ClassSpawner* spawner = new ClassSpawner();

	//оружие
	ClassPlayersGun* gun = new ClassPlayersGun("textures/gun.png", (*player->getObjectSprite()).getPosition().x + 20, (*player->getObjectSprite()).getPosition().y + 35);
	gun->setParams();

	//плеер музыки
	ClassMusicPlayer* musicPlayer = new ClassMusicPlayer();

	musicPlayer->playMusic(::trackName);

	//снаряды
	Projectile* bullets = new Projectile[50];

	//враги
	ClassEnemy* enemy = new ClassEnemy[musicPlayer->getMusicLength()];

	spawner->setSpawnLimit(musicPlayer->getMusicLength());

	while (gameWindow.isOpen())
	{
		int FriquencySummeryAtStartOfFrame = musicPlayer->getFriquencySummery();

		mousePosition = Mouse::getPosition(gameWindow);

		::globalClocks = clocks.getElapsedTime().asMicroseconds();
		clocks.restart();

		Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				gameWindow.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			musicPlayer->stopMusic();
			if (game->exitMenu()) {
				gameWindow.close();
			}
			else {
				musicPlayer->resumeMusic();
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (gunCoolDown.getElapsedTime().asSeconds() > 0.4) {
				gun->shoot(bullets, musicPlayer, FriquencySummeryAtStartOfFrame);
				gunCoolDown.restart();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::R)) {
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player->movementToLeft(1);
			gun->followPlayer((*player->getObjectSprite()).getPosition().x, (*player->getObjectSprite()).getPosition().y);
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player->movementToRight(1);
			gun->followPlayer((*player->getObjectSprite()).getPosition().x, (*player->getObjectSprite()).getPosition().y);
		}

		gun->followMouse(mousePosition.x, mousePosition.y);
		//spawner->spawn(enemy);

		gameWindow.clear();

		gameWindow.draw(game->getTextObj(std::to_string(gun->getAngle()), 0, 0));

		//отрисовка объектов
		gameWindow.draw(*(player->getObjectSprite()));

		for (int i = 0; i < gun->getShots(); i++) {
			if (!bullets[i].getDestractedState()) {
				gameWindow.draw(*bullets[i].getObjectSprite());
				bullets[i].fly(gun->getAngle());
			}
		}

		for (int i = 0; i < musicPlayer->getMusicLength(); i++) {
			if (enemy[i].getAliveState()) {
				gameWindow.draw(*enemy[i].getObjectSprite());
				enemy[i].moveToPlayer((*(player->getObjectSprite())).getPosition().x, 4);
				enemy[i].cheForBulletCollision(bullets);
			}
		}

		gameWindow.draw(*(gun->getObjectSprite()));
		//отрисовка объектов

		/*if (player->checkCollisionWithEnemy(enemy, musicPlayer->getMusicLength())) {
			musicPlayer->stopMusic();
			if (game->endMenu()) {
				gameWindow.close();
			}
		}*/

		if (musicPlayer->endOfMusic()) {
			if (game->endMenu()) {
				gameWindow.close();
			}
		}

		gameWindow.display();
	}
}

void main(void) {
	ClassGame* game = new ClassGame();

	//стартовое меню
	if (!game->gameStartMenu()) {
		return;
	}
	//стартовое меню

	startGame(game);
}