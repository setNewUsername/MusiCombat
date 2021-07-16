#include "Classes.h"
#include <thread>
#include "bass.h"
#include <cstdlib>

float globalClocks;

DWORD chan;
float fft[512];



void main(void) {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "MusiCombat");

	BASS_Init(-1, 44100, 0, 0, NULL);
	BASS_SetVolume(0.5);
	if (!(chan = BASS_StreamCreateFile(FALSE, "da.mp3", 0, 0, BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT))
		&& !(chan = BASS_MusicLoad(FALSE, "da.mp3", 0, 0, BASS_MUSIC_RAMPS | BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT, 1))) {
		
	}
	BASS_ChannelPlay(chan, FALSE);
	BASS_ChannelGetData(chan, fft, BASS_DATA_FFT1024);

	std::string a;

	Font font;
	font.loadFromFile("fonts/20951.ttf");

	Text txt;
	txt.setFont(font);
	txt.setPosition(0, 0);
	txt.setCharacterSize(18);

	float tempoInscreaser = 0;
	unsigned int shots = 0;
	unsigned int enemyCount = 0;
	char playerMovementDirection;

	int bulletStartPosYCorrector;
	int bulletStartPosXCorrector;
	int gunSpriteWidth = 100;
	

	Vector2i mousePosition;

	Clock clock;
	Clock gunCoolDown;
	Clock enemyCoolDown;
	Clock askFormTempoClock;
	Clock askFormTempoClock2;

	Player* player = new Player("textures/mario.png", SCREEN_WIDTH/2-30, SCREEN_HEIGHT-74, 10);
	PlayersGun* gun = new PlayersGun("textures/gun.png", player->getPositionX()+20, player->getPositionY() + 35);
	Projectile* bullets = new Projectile[AMMO_AMOUNT];
	Enemy* enemy = new Enemy[AMMO_AMOUNT];

	std::string coords;

	while (window.isOpen())
	{

		BASS_ChannelGetData(chan, fft, BASS_DATA_FFT1024);
		int frik = 0;

		for (int i = 0; i < 512; i++) {
			if (int(fft[i] * 1000) > 5) {
				frik = frik + int(fft[i] * 1000);
			}
		}

		mousePosition = Mouse::getPosition();

		bulletStartPosYCorrector = gunSpriteWidth * sin(gun->getAngle() * PI / 180);
		bulletStartPosXCorrector = gunSpriteWidth * cos(gun->getAngle() * PI / 180);

		::globalClocks = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			playerMovementDirection = 'l';
			player->movement(playerMovementDirection, 1);
			gun->followPlayer(playerMovementDirection, player->getPositionX(), player->getPositionY());
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			playerMovementDirection = 'r';
			player->movement(playerMovementDirection, 1);
			gun->followPlayer(playerMovementDirection, player->getPositionX(), player->getPositionY());
		} 

		if (Keyboard::isKeyPressed(Keyboard::E)) {
			//BASS_ChannelPause(channel);
		}
		
		if (Keyboard::isKeyPressed(Keyboard::F)) {
			if (enemyCoolDown.getElapsedTime().asSeconds() > 0.1) {
				enemyCoolDown.restart();
				if (enemyCount > AMMO_AMOUNT - 1) {
					for (int i = 0; i < enemyCount; i++) {
						enemy[i].death();
					}
					enemyCount = 0;
				}
				else {
					enemy[enemyCount].Enemy::Enemy("textures/enemy.png", 0, SCREEN_HEIGHT-150, 5);

					enemyCount++;
				}
			}
		}

		

		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (gunCoolDown.getElapsedTime().asSeconds() > 0.5 - tempoInscreaser) {
				BASS_ChannelGetData(chan, fft, BASS_DATA_FFT1024);
				int frik2 = 0;

				for (int i = 0; i < 512; i++) {
					if (int(fft[i] * 1000) > 5) {
						frik2 = frik2 + int(fft[i] * 1000);
					}
				}

				if (frik2 >= frik) {
					coords = "popal";
				}
				else if(frik2 < frik){
					coords = "ne popal";
				}

				if (shots > AMMO_AMOUNT-1) {
					for (int i = 0; i < shots; i++) {
						bullets[i].Projectile::~Projectile();
					}
					shots = 0;
				}
				else {
					bullets[shots].Projectile::Projectile("textures/bullet.png", gun->getPositionX() - bulletStartPosXCorrector, gun->getPositionY() - bulletStartPosYCorrector - 10);

					shots++;
				}

				gunCoolDown.restart();
			}
		}

		txt.setString(coords);
		
		gun->followMouse(mousePosition.x, mousePosition.y);

		window.clear(Color::Black);
		window.draw(txt);
		window.draw(gun->getSprite());
		window.draw(player->getSprite());

		for (int i = 0; i < shots; i++) {
			if (bullets[i].getDistractedState() == false) {
				window.draw(bullets[i].getSprite());
				bullets[i].fly(gun->getAngle());
				bullets[i].checkForMapCollision();
				for (int m = 0; m < enemyCount; m++) {
					if (bullets[i].getPositionX() == enemy[m].getPositionX() && bullets[i].getPositionY() > enemy[m].getPositionY()) {
						enemy[m].death();
						bullets[i].projectileDistract();
						enemyCount--;
						shots--;
					}
				}
			}
		}

		for (int i = 0; i < enemyCount; i++) {
			if (enemy[i].getAliveState() == true) {
				window.draw(enemy[i].getSprite());
				enemy[i].moveToPlayer(player->getPositionX());
			}
		}

		window.display();
	}
}