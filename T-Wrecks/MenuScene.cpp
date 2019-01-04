#include "MenuScene.h"

MenuScene::MenuScene() {
	backgroundRect = {0, 0, 1280, 720};

	// Button Related Stuffs -----------------------------------------------------------------------------------
	// Button default is (370 * 50), But it also takes two params Button(w, h);
	playButton = new Button();
	playButton->setRenderer(Globals::renderer);
	playButton->pos.x = 40;
	playButton->pos.y = 385;

	renderObjects.push_back(playButton);

	leaderboardButton = new Button();
	leaderboardButton->setRenderer(Globals::renderer);
	leaderboardButton->pos.x = 40;
	leaderboardButton->pos.y = 460;

	renderObjects.push_back(leaderboardButton);

	settingButton = new Button();
	settingButton->setRenderer(Globals::renderer);
	settingButton->pos.x = 40;
	settingButton->pos.y = 535;

	renderObjects.push_back(settingButton);

	exitButton = new Button();
	exitButton->setRenderer(Globals::renderer);
	exitButton->pos.x = 40;
	exitButton->pos.y = 610;

	renderObjects.push_back(exitButton);

	// Font Related Stuffs -----------------------------------------------------------------------------------

	font = TTF_OpenFont("Assets/MONO.ttf", 32);
	fontColor = { 83, 83, 83, 100 };

	// Add title --------------------------------------------------------------------------------------------------------------------------------------------------------
	TTF_Font *titleFont = TTF_OpenFont("Assets/MONO.ttf", 75);
	SDL_Surface *titleTextSurface = TTF_RenderText_Blended(titleFont, "T-WRECKS", fontColor);
	titleTexture = SDL_CreateTextureFromSurface(Globals::renderer, titleTextSurface);
	SDL_FreeSurface(titleTextSurface);

	titleRect.x = 40;
	titleRect.y = 40;
	SDL_QueryTexture(titleTexture, NULL, NULL, &titleRect.w, &titleRect.h);

	
	// Add play button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *playTextSurface = TTF_RenderText_Blended(font, "PLAY GAME", fontColor);
	playButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, playTextSurface);
	SDL_FreeSurface(playTextSurface);

	playButtonRect.x = 70;
	playButtonRect.y = 395;
	SDL_QueryTexture(playButtonTexture, NULL, NULL, &playButtonRect.w, &playButtonRect.h);

	
	// Add leaderboard button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *leaderboardTextSurface = TTF_RenderText_Blended(font, "LEADERBOARD", fontColor);
	leaderboardButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, leaderboardTextSurface);
	SDL_FreeSurface(leaderboardTextSurface);

	leaderboardButtonRect.x = 70;
	leaderboardButtonRect.y = 470;
	SDL_QueryTexture(leaderboardButtonTexture, NULL, NULL, &leaderboardButtonRect.w, &leaderboardButtonRect.h);

	// Add setting button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *settingTextSurface = TTF_RenderText_Blended(font, "SETTING", fontColor);
	settingButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, settingTextSurface);
	SDL_FreeSurface(settingTextSurface);

	settingButtonRect.x = 70;
	settingButtonRect.y = 545;
	SDL_QueryTexture(settingButtonTexture, NULL, NULL, &settingButtonRect.w, &settingButtonRect.h);


	// Add exit button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *exitTextSurface = TTF_RenderText_Blended(font, "EXIT GAME", fontColor);
	exitButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, exitTextSurface);
	SDL_FreeSurface(exitTextSurface);

	exitButtonRect.x = 70;
	exitButtonRect.y = 620;
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonRect.w, &exitButtonRect.h);

	// Input Handlers
	mouseHandler = new MouseHandler();

	// Prepare Player
	player = new Player(800, 560);
	player->setRenderer(Globals::renderer);

	// Keyboard Handler for player object
	keyboardHandler = new KeyboardHandler();
	keyboardHandler->p = player;

	// Setup ground
	groundTexture = IMG_LoadTexture(Globals::renderer, "Assets/ground.png");
	groundRect.x = 0;
	groundRect.y = 670;
	groundRect.w = 2560;
	groundRect.h = 32;

	// Setup Cactus
	srand(time(NULL));
	randNum = rand() % 4 + 1;
	cout << "  Random Number for this Cactus is " << randNum << endl;
	c1 = new Cactus(randNum, 20 , 700);
	randNum = rand() % 4 + 1;
	cout << "  Random Number for this Cactus is " << randNum << endl;
	c2 = new Cactus(randNum, 400, 720);
	randNum = rand() % 4 + 1;
	cout << "  Random Number for this Cactus is " << randNum << endl;
	c3 = new Cactus(randNum, 700, 710);


	lastUpdate = SDL_GetTicks(); // Milliseconds since the start of the game running

}

MenuScene::~MenuScene() {
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(playButtonTexture);
	SDL_DestroyTexture(leaderboardButtonTexture);
	SDL_DestroyTexture(settingButtonTexture);
	SDL_DestroyTexture(exitButtonTexture);
}


void MenuScene::update() {
	Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
	dt = timeDiff / 1000.0;
	lastUpdate = SDL_GetTicks();

	// ---------------------------------------------------------------------------------------

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Check if the window is closed
		if (event.type == SDL_QUIT) {
			Globals::quitGame = true;
			Globals::gsm.popScene();
			return;
		}

		// Exit game when "Esc" is pressed
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				Globals::quitGame = true;
				Globals::gsm.popScene();
				return;
			}
		}

		// Switch to Level Selection when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= playButton->pos.x && event.button.x <= playButton->pos.x + 320
				&&
				event.button.y >= playButton->pos.y && event.button.y <= playButton->pos.y + 60) {
				// Switch to "Level Selection" Scene
				Globals::gsm.pushScene(new PlayerSelectionScene());
			}
		}
		
		// Switch to Leaderboard Scene when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= leaderboardButton->pos.x && event.button.x <= leaderboardButton->pos.x + 320
				&&
				event.button.y >= leaderboardButton->pos.y && event.button.y <= leaderboardButton->pos.y + 60) {
				// Switch to "Leaderboard" Scene
				Globals::gsm.pushScene(new LeaderboardScene());
			}
		}

		// Exit game when clicked "Exit Game" button
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= exitButton->pos.x && event.button.x <= exitButton->pos.x + 320
				&&
				event.button.y >= exitButton->pos.y && event.button.y <= exitButton->pos.y + 60) {
				Globals::quitGame = true;
				Globals::gsm.popScene();
				return;
			}
		}

		keyboardHandler->update(&event);

	}

	player->update(dt);

	// Monitor Mouse Coordinate
	mousePos = mouseHandler->getMouseState();
	//cout << "  Mouse Coordinate (" << mousePos.x << ", " << mousePos.y << ")\n";

}

void MenuScene::render() {
	// Render Background
	SDL_SetRenderDrawColor(Globals::renderer, 244, 244, 244, 100);
	SDL_RenderFillRect(Globals::renderer, &backgroundRect);

	// Draw each menu objects
	for (GameObject *ro : renderObjects) {
		ro->draw(ro->checkIfHover(mousePos));
	}

	player->draw(false);

	c1->draw();
	c2->draw();
	c3->draw();

	// Render textTexture
	SDL_RenderCopy(Globals::renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, playButtonTexture, NULL, &playButtonRect);
	SDL_RenderCopy(Globals::renderer, leaderboardButtonTexture, NULL, &leaderboardButtonRect);
	SDL_RenderCopy(Globals::renderer, settingButtonTexture, NULL, &settingButtonRect);
	SDL_RenderCopy(Globals::renderer, exitButtonTexture, NULL, &exitButtonRect);
	SDL_RenderCopy(Globals::renderer, groundTexture, NULL, &groundRect);


	// Present all our renderings to the window when you have enough drawing stuffs
	SDL_RenderPresent(Globals::renderer);
}

bool MenuScene::onEnter() {
	cout << "Pushed Menu Scene" << endl;
	return true;
}

bool MenuScene::onExit() {
	cout << "Popped Menu Scene" << endl;
	return true;
}
