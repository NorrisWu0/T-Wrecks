#include "Pterosaur.h"

Pterosaur::Pterosaur() {
	vel.x = -(rand() % 100 + 250);
	setupSprite();
}

Pterosaur::~Pterosaur() {
	SDL_DestroyTexture(pterosaurTexture);
}

void Pterosaur::update(float dt) {
	updateMovement(dt);
	animation->update(dt);
	checkBoundry();
	//checkPosition();
}

void Pterosaur::draw(bool) {
	animation->draw(pos.x, pos.y);
}

void Pterosaur::setupSprite() {
	pterosaurTexture = IMG_LoadTexture(Globals::renderer, "Assets/Dinos/Pterosaur.png");
	SDL_QueryTexture(pterosaurTexture, NULL, NULL, &frameWidth, &frameHeight);
	animation = new Animation(pterosaurTexture, Globals::renderer, 2, frameWidth/2, frameHeight, 0.2);
	
	pos.x = rand() % 1280 + 1281;
	pos.y = rand() % 30 + 300;
}

void Pterosaur::checkBoundry() {
	if (pos.x <= -frameWidth*2) {
		pos.x = rand() % 1280 + 1281;
		pos.y = rand() % 30 + 300;
		vel.x = -(rand() % 100 + 250);

		if ((rand() % 5 + 1) <= 2) {
			pos.y = rand() % 30 + 500;
			vel.x = -(rand() % 100 + 1000);
		}
	}
}

void Pterosaur::checkPosition() {
	cout << "  Pterosaur Position: " << pos.x << ", " << pos.y << endl;
}