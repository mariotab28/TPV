#include "Game.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Wall.h"

typedef unsigned int uint;

//Constructora de Game
Game::Game() {
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
	// We now create the textures

	for (uint i = 0; i < NUM_TEXTURES; i++)
	{
		textures[i] = new Texture(renderer, TEXTURE_ATRIBS[i].filename, TEXTURE_ATRIBS[i].rows, TEXTURE_ATRIBS[i].cols);
	}


	// We finally create the game objects
	topWall = new Wall(-WALL_OFFSET, 0, WIN_WIDTH + WALL_OFFSET * 2, WALL_WIDTH, textures[TopText]);
	sideWall1 = new Wall(0, 0, WALL_WIDTH, WIN_HEIGHT, textures[SideText]);
	sideWall2 = new Wall(WIN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, WIN_HEIGHT, textures[SideText]);
	blockMap = new BlocksMap(MAP_FILENAME, MAP_WIDTH, MAP_HEIGHT, textures[BrickText]);
	paddle = new Paddle(PADDLE_X_INI, PADDLE_Y_INI, PADDLE_WIDTH, PADDLE_HEIGHT, 0, 0, PADDLE_SPEED, textures[PaddleText]);
	ball = new Ball(BALL_X_INI, BALL_Y_INI, BALL_RADIUS, BALL_RADIUS, 0, 0, BALL_SPEED, textures[BallText], this);
}

//Destructora de Game
Game::~Game() {
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Función principal
void Game::run() {
	uint32_t startTime = SDL_GetTicks(), frameTime;
	while (!exit) {
		handleEvents();

		frameTime = SDL_GetTicks() - startTime; //Tiempo desde última actualización
		if (frameTime >= FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();
		}

		render();
		SDL_Delay(FRAME_RATE);
	}
}


void Game::update() {
	paddle->update();
	ball->update();
}


void Game::render() const {
	SDL_RenderClear(renderer);

	sideWall1->render();
	sideWall2->render();
	topWall->render();
	blockMap->render();
	paddle->render();
	ball->render();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;

		paddle->handleEvents(event);
		ball->handleEvents(event);
	}
}