#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Texture.h"
#include "Wall.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Ball.h"

typedef unsigned int uint;

enum TextureName {
	BallText, BrickText, PaddleText, SideText, TopText
};

struct TextureAttributes {
	string filename;
	uint rows;
	uint cols;
};

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 20;
//Walls
const int WALL_OFFSET = 5;
const uint WALL_WIDTH = 16 + WALL_OFFSET;
//TEXTURAS
const uint NUM_TEXTURES = 5;
const TextureAttributes TEXTURE_ATRIBS[NUM_TEXTURES] = {
	{"ball.png", 1, 1},
	{"bricks.png", 2, 3},
	{"paddle.png", 1, 1},
	{"side.png", 1, 1},
	{"topside.png", 1, 1},
};
//BlocksMap
const uint MAP_X = WALL_WIDTH + WALL_OFFSET;
const uint MAP_Y = WALL_WIDTH + WALL_OFFSET;
const uint MAP_WIDTH = WIN_WIDTH - 2 * WALL_WIDTH - WALL_OFFSET - 3;
const uint MAP_HEIGHT = WIN_HEIGHT / 2;//3; 
const string MAP_FILENAME = "level01.ark";
//Paddle
const uint PADDLE_WIDTH = 100;
const uint PADDLE_HEIGHT = 20;
const double PADDLE_X_INI = WIN_WIDTH / 2 - PADDLE_WIDTH / 2;
const double PADDLE_Y_INI = WIN_HEIGHT - PADDLE_HEIGHT - 50;
const double PADDLE_SPEED = 10;
//Ball
const uint BALL_RADIUS = 15;
const double BALL_X_INI = WIN_WIDTH / 2 - BALL_RADIUS / 2;
const double BALL_Y_INI = WIN_HEIGHT - BALL_RADIUS - 100;
const double BALL_SPEED = 3;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
		
	//Punteros a los objetos
	Wall* topWall = nullptr;
	Wall* leftSideWall = nullptr;
	Wall* rightSideWall = nullptr;
	BlocksMap* map = nullptr;
	Paddle* paddle = nullptr;
	Ball* ball = nullptr;

	//booleanos de control
	bool exit = false;
	bool gameover = false;
	bool win = false;

	Texture* textures[NUM_TEXTURES];
	SDL_Rect allRect{ 0, 0, WIN_WIDTH, WIN_HEIGHT }; //Rect. Completo


public:
	Game();
	~Game();
	void createObjects();
	void destroyObjects();
	void run();
	void render() const;
	void handleEvents();
	void update();
	bool collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);
	void restart();
};
