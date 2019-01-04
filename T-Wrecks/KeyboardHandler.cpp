#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler() { }
KeyboardHandler::~KeyboardHandler() { }

void KeyboardHandler::update(SDL_Event *e) {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	p->vel.x = 0;

	int playerVel = 700;

	////key is considered down if = 1, no held down = 0
	//if (e->type == SDL_KEYDOWN) {
	//	if (e->key.keysym.scancode == SDL_SCANCODE_SPACE && e->key.repeat == 0) {
	//		cout << "  Jump!!\n";
	//		p->vel.y = -1000;
	//	}
	//}

	if ((keystates[SDL_SCANCODE_UP] && e->key.repeat == 0) || (keystates[SDL_SCANCODE_W] && e->key.repeat == 0)) {
		p->vel.y = -1000;
	}
	if ((keystates[SDL_SCANCODE_LEFT]) || (keystates[SDL_SCANCODE_A]))
		p->vel.x = -playerVel;
	if ((keystates[SDL_SCANCODE_RIGHT]) || (keystates[SDL_SCANCODE_D]))
		p->vel.x = playerVel;
}