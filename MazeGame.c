#include "stdio.h"
#include "SDL.h"

typedef struct
{
	int xPos, yPos, width, height, startX,startY;
	short life;
	char *name;
	int speed = 7;
} Player;

typedef struct
{
	Player player;
}stateOfGame;

typedef struct {
	int xPos, yPos, width, height;
}Walls;

typedef struct {
	int xPos, yPos, width, height, speed;
}Enemies;

typedef struct {
	int xPos, yPos, width, height, speed;
	bool visible;
}Coins;

bool collision(Player obj1, Walls obj2)
{
	if (obj1.xPos + obj1.width >= obj2.xPos &&
		obj1.xPos <= obj2.xPos + obj2.width &&
		obj1.yPos + obj1.height >= obj2.yPos &&
		obj1.yPos <= obj2.yPos + obj2.height)
	{ return true; }
	else { return false; }
};

bool collision(Enemies obj1, Walls obj2)
{
	if (obj1.xPos + obj1.width >= obj2.xPos &&
		obj1.xPos <= obj2.xPos + obj2.width &&
		obj1.yPos + obj1.height >= obj2.yPos &&
		obj1.yPos <= obj2.yPos + obj2.height)
	{
		return true;
	}
	else { return false; }
};

bool collision(Player obj1, Coins obj2)
{
	if (obj1.xPos + obj1.width >= obj2.xPos &&
		obj1.xPos <= obj2.xPos + obj2.width &&
		obj1.yPos + obj1.height >= obj2.yPos &&
		obj1.yPos <= obj2.yPos + obj2.height)
	{
		return true;
	}
	else { return false; }
};

bool collision(Player obj1, Enemies obj2)
{
	if (obj1.xPos + obj1.width >= obj2.xPos &&
		obj1.xPos <= obj2.xPos + obj2.width &&
		obj1.yPos + obj1.height >= obj2.yPos &&
		obj1.yPos <= obj2.yPos + obj2.height)
	{
		return true;
	}
	else { return false; }
};

int processEvents(SDL_Window *window, Player *player, Walls *wall5, Enemies *enemy1)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event))
	{
		// CREATE WAYS TO QUIT GAME
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
		{
			if (window)
			{
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;
			}
		}
		break;
		case SDL_QUIT:
			done = 1;
			break;
		}
	}
	// STATE OF KEYBOARD TO MOVE PLAYER
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		// MOVE PLAYER LEFT ON X AXIS
		player->xPos -= player->speed;
		while (collision(*player, *wall5))
		{
			player->xPos += 1;
		}
		// KEEP PLAYER IN LEFT BOUNDRY
		if (player->xPos < 51)
		{
			player->xPos = 50;
		}
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		// MOVE PLAYER OVER RIGHT ON X AXIS
		player->xPos += player->speed;
		while (collision(*player, *wall5))
		{
			player->xPos += -1;
		}
		
		// KEEP PLAYER IN RIGHT BOUNDRY
		if (player->xPos > 400)
		{
			player->xPos = 400;
		}
	}
	if (state[SDL_SCANCODE_UP])
	{
		// MOVE PLAYER UP Y AXIS
		player->yPos -= player->speed;
		while (collision(*player, *wall5))
		{
			player->yPos += 1;
		}
		// KEEP PLAYER IN UPPER BOUNDRY
		if (player->yPos < 51)
		{
			player->yPos = 50;
		}
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		// MOVE PLAYER DOWN Y AXIS
		player->yPos += player->speed;
		// KEEP PLAYER IN BOTTOM BOUNDRY
		if (player->yPos > 400)
		{
			player->yPos = 400;
		}
	}
	return done;
}

void draw(SDL_Renderer *renderer, Player *player, Walls *wall1, Walls *wall2, Walls *wall3, Walls *wall4, Walls *wall5, Enemies *enemy1, Enemies *enemy2, Enemies *enemy3, Coins *coin1, Coins *coin2, Coins *coin3)
{
	// set drawing color to blue
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	// clear the screen to blue
	SDL_RenderClear(renderer);
	// Set Drawing color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//------------------- CREATE GAME OBJECTS ---------------------------------------------------------------------
	SDL_Rect rectPlayer = { player->xPos,player->yPos,player->width,player->height };

	SDL_Rect rectWall1 = { wall1->xPos,wall1->yPos,wall1->width,wall1->height };
	SDL_Rect rectWall2 = { wall2->xPos,wall2->yPos,wall2->width,wall2->height };
	SDL_Rect rectWall3 = { wall3->xPos,wall3->yPos,wall3->width,wall3->height };
	SDL_Rect rectWall4 = { wall4->xPos,wall4->yPos,wall4->width,wall4->height };
	SDL_Rect rectWall5 = { wall5->xPos,wall5->yPos,wall5->width,wall5->height };

	SDL_Rect rectEnemy1 = { enemy1->xPos,enemy1->yPos,enemy1->width,enemy1->height };
	SDL_Rect rectEnemy2 = { enemy2->xPos,enemy2->yPos,enemy2->width,enemy2->height };
	SDL_Rect rectEnemy3 = { enemy3->xPos,enemy3->yPos,enemy3->width,enemy3->height };

	SDL_Rect rectCoin1 = { coin1->xPos,coin1->yPos,coin1->width,coin1->height };
	SDL_Rect rectCoin2 = { coin2->xPos,coin2->yPos,coin2->width,coin2->height };
	SDL_Rect rectCoin3 = { coin3->xPos,coin3->yPos,coin3->width,coin3->height };

	SDL_RenderFillRect(renderer, &rectPlayer);

	SDL_SetRenderDrawColor(renderer, 158, 107, 25, 255);
	SDL_RenderFillRect(renderer, &rectWall1);
	SDL_RenderFillRect(renderer, &rectWall2);
	SDL_RenderFillRect(renderer, &rectWall3);
	SDL_RenderFillRect(renderer, &rectWall4);
	SDL_RenderFillRect(renderer, &rectWall5);

	SDL_SetRenderDrawColor(renderer, 89, 89, 89, 255);
	SDL_RenderFillRect(renderer, &rectEnemy1);
	SDL_RenderFillRect(renderer, &rectEnemy2);
	SDL_RenderFillRect(renderer, &rectEnemy3);

	// -----------------------RENDERS COINS IF VISIBLE ----------------------------------------------------------
	SDL_SetRenderDrawColor(renderer, 240, 109, 89, 255);
	if (coin1->visible)
	{
		SDL_RenderFillRect(renderer, &rectCoin1);
	}
	if (coin2->visible)
	{
		SDL_RenderFillRect(renderer, &rectCoin2);
	}
	if (coin3->visible)
	{
		SDL_RenderFillRect(renderer, &rectCoin3);
	}
	//---------------------- IF COLLISION WITH PLAYER AND COIN, COIN INVISIBLE---------------------------------
	if (collision(*player,*coin1))
	{
		coin1->visible = false;
	}
	if (collision(*player, *coin2))
	{
		coin2->visible = false;
	}
	if (collision(*player, *coin3))
	{
		coin3->visible = false;
	}
	// ----------------- MOVE ENEMIES ------------------------------------------------------------------------------
	enemy1->xPos += enemy1->speed;
	if (collision(*enemy1,*wall5))
	{
		enemy1->speed = enemy1->speed * -1;
	}
	if (collision(*enemy1, *wall1))
	{
		enemy1->speed = enemy1->speed * -1;
	}

	enemy2->xPos += enemy2->speed;
	if (collision(*enemy2, *wall5))
	{
		enemy2->speed = enemy2->speed * -1;
	}
	if (collision(*enemy2, *wall1))
	{
		enemy2->speed = enemy2->speed * -1;
	}

	enemy3->yPos -= enemy3->speed;
	if (collision(*enemy3, *wall5))
	{
		enemy3->speed = enemy3->speed * -1;
	}
	if (collision(*enemy3, *wall3))
	{
		enemy3->speed = enemy3->speed * -1;
	}

	// RESTART GAME IF COLLISION WITH ENEMY
	if (collision(*player, *enemy1) || collision(*player,*enemy2) || collision(*player,*enemy3))
	{
		player->xPos = player->startX;
		player->yPos = player->startY;

		coin1->visible = true;
		coin2->visible = true;
		coin3->visible = true;
	}

	// show drawing
	SDL_RenderPresent(renderer);
}


int main(int argc, char *argv[])
{
	
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	Player player;
	player.xPos = 375;
	player.yPos = 50;
	player.height = 50;
	player.width = 50;
	player.startX = 375;
	player.startY = 50;

	Walls wall1 = { 0,0,50,500 };
	Walls wall2 = { 0,0,500,50 };
	Walls wall3 = { 0,450,500,50 };
	Walls wall4 = { 450,0,50,500 };
	Walls wall5 = { 275,0,50,275 };

	Enemies enemy1 = { 200,225,50,50,2 };
	Enemies enemy2 = { 50,100,50,50,3 };
	Enemies enemy3 = { 275,400,50,50,4 };

	Coins coin1 = { 200,200,30,30 };
	coin1.visible = true;
	Coins coin2 = { 100,275,30,30 };
	coin2.visible = true;
	Coins coin3 = { 400,300,30,30 };
	coin3.visible = true;

	//walls wallsArray[4] = { wall1 = {0,0,50,50 } };

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int done = 0;
	while (!done)
	{
		// Check for events
		if (processEvents(window, &player, &wall5, &enemy1) == 1)
		{ 
			done = 1;
		}

		// Draw Display
		draw(renderer, &player, &wall1, &wall2, &wall3, &wall4, &wall5, &enemy1, &enemy2, &enemy3, &coin1, &coin2, &coin3);	

		//SDL_Delay(10);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
	return EXIT_SUCCESS;
}
