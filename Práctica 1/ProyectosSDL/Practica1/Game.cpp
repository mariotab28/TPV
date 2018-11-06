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
	createObjects();
}

//Destructora de Game
Game::~Game() {
	destroyObjects();

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Crea los objetos del juego
void Game::createObjects() {
	topWall = new Wall(-WALL_OFFSET, 0, WIN_WIDTH + WALL_OFFSET * 2, WALL_WIDTH, textures[TopText]);
	leftSideWall = new Wall(0, 0, WALL_WIDTH, WIN_HEIGHT, textures[SideText]);
	rightSideWall = new Wall(WIN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, WIN_HEIGHT, textures[SideText]);
	map = new BlocksMap(MAP_X, MAP_Y, MAP_FILENAME, MAP_WIDTH, MAP_HEIGHT, textures[BrickText]);
	paddle = new Paddle(PADDLE_X_INI, PADDLE_Y_INI, PADDLE_WIDTH, PADDLE_HEIGHT, textures[PaddleText]);
	ball = new Ball(BALL_X_INI, BALL_Y_INI, BALL_RADIUS, BALL_RADIUS, textures[BallText], this);
}


//Destruye los objetos en orden inverso a su creación
void Game::destroyObjects() {
	delete ball;
	delete paddle;
	delete map;
	delete rightSideWall;
	delete leftSideWall;
	delete topWall;
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
	}
}


void Game::update() {
	paddle->update();
	ball->update();

	//Comprueba si el jugador ha ganado
	if (win)
		std::cout << "¡YOU WON!";
}


void Game::render() const {
	SDL_RenderClear(renderer);

	leftSideWall->render();
	rightSideWall->render();
	topWall->render();
	map->render();
	paddle->render();
	ball->render();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		paddle->handleEvents(event);
	}
}

//Devuelve true si ballRect colisiona con un objeto, devolviendo en ese caso también el vector de colisión collVector
bool Game::collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D &collVector) {
	if (ball != nullptr) { //Si la bola está en el mapa (TEMPORAL)

		bool col = false;

		//colisión con BLOQUE
		if (rect.y <= MAP_Y + MAP_HEIGHT && rect.y >= MAP_Y) { //Comprueba que la pelota está dentro del espacio del mapa de bloques
			Block* block = map->collides(rect, vel, collVector);
			if (block != nullptr) {
				map->ballHitsBlock(block);
				if (map->getNumBlocks() == 0)
					win = true;

				col = true;
				//return true;
			}
		}

		//colisión con MUROS
		if (rect.y <= WALL_WIDTH) //TOP WALL
		{
			collVector = { 0,1 };
			col = true;
			//return true;
		}
		else if (rect.x <= WALL_WIDTH) //LEFT WALL
		{
			collVector = { 1,0 };
			col = true;
			//return true;
		}
		else if (rect.x + rect.w >= WIN_WIDTH - WALL_WIDTH) //RIGHT WALL
		{
			collVector = { -1,0 };
			col = true;
			//return true;
		}
		
		/*if (topWall->collides(rect)) //TOP WALL
		{
			collVector = { 0,1 };
			return true;
		}
		else if (leftSideWall->collides(rect)) //LEFT WALL
		{
			collVector = { 1,0 };
			return true;
		}
		else if (rightSideWall->collides(rect)) //RIGHT WALL
		{
			collVector = { -1,0 };
			return true;
		}*/

		//colisión con PADDLE
		if (rect.y + rect.h >= PADDLE_Y_INI - rect.h) {
			if (paddle->collides(rect, vel, collVector)) {
				//collVector = { 0,-1 };
				col = true;
				//return true;
			}
		}

		return col;
	}
}


void Game::restart() {
	destroyObjects();
	createObjects();
}