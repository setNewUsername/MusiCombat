#include "Classes.h"

ClassSpawner::ClassSpawner() {};
ClassSpawner::~ClassSpawner() {};

void ClassSpawner::setSpawnLimit(int newSpawnLimit) {
	spawnLimit = newSpawnLimit;
}

void ClassSpawner::spawn(ClassEnemy* enemyArray) {
	if (spawnCoolDown.getElapsedTime().asSeconds() > 1) {
		srand(time(0));
		int side;

		if (enemyAmount == spawnLimit) {
			enemyAmount = 0;
		}

		side = 1 + rand() % 2;

		if (side == 1) {
			side = 10;
		}
		else if (side == 2) {
			side = 1900;
		}

		(&enemyArray[enemyAmount])->ClassEnemy::ClassEnemy("textures/enemy.png", side, 1010, 3, 100, 80);
		(&enemyArray[enemyAmount])->updateRectCalculateFrameAmount(100, 80);

		enemyAmount++;

		spawnCoolDown.restart();
	}
}

int ClassSpawner::getEnemyAmount() {
	return enemyAmount;
}