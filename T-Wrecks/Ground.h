#pragma once
#include "GameObject.h"
#

class Ground :
	public GameObject
{
public:
	Ground(bool);
	~Ground();

	virtual void update(float);
	virtual void draw(bool);

	void checkBoundry();

private:
	SDL_Texture *groundTexture;
	SDL_Rect groundRect;

	int w, h;
	bool inGame;
	int groundVel = 5;
};
