#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "Mathf.h"

#undef main

const float PI = 3.14159265;
const float TO_RAD = PI / 180;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SCALE = 4;
const int RENDER_WIDTH = WINDOW_WIDTH / SCALE;
const int RENDER_HEIGHT = RENDER_WIDTH * (WINDOW_HEIGHT / (float)WINDOW_WIDTH);

const int gridSize = 10;
const int gridHight = 10;

int g_seed = 0;

const float moveSpeed = 0.1;
const float rotSpeed = 0.1;
const float fov = 60;
const float distanceProjectionPlane = (RENDER_WIDTH / 2) / tan((fov / 2) * TO_RAD);

vec2 playerPos{15,15};
vec2 playerDir{15,0};
float playerRot = 0;

//TODO::Create a better system for the Inputs
bool KEYS[322];


#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

inline int fastrand() {
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

inline uint32_t ARGB(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void UpdateLogic()
{
	if (KEYS[SDLK_w])
	{
		playerPos.y -= moveSpeed;
	}

	if (KEYS[SDLK_s])
	{
		playerPos.y += moveSpeed;
	}

	if (KEYS[SDLK_a])
	{
		playerPos.x -= moveSpeed;
	}

	if (KEYS[SDLK_d])
	{
		playerPos.x += moveSpeed;
	}

	if (KEYS[SDLK_q])
	{
		playerRot -= rotSpeed * TO_RAD;
	}

	if (KEYS[SDLK_e])
	{
		playerRot += rotSpeed * TO_RAD;
	}
}

void Render()
{

}

int main()
{
	playerRot = 60 * TO_RAD;

	SDL_Window* window = nullptr;
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);

	std::vector<unsigned char> pixels(RENDER_WIDTH * RENDER_HEIGHT * 4, 0);

	//Inizializing KeyEvents to false
	for (int i = 0; i < 322; i++)
		KEYS[i] = false;

	bool isRunning = true;
	
	SDL_Event e;

	Uint64 oldTime = SDL_GetPerformanceCounter();

	while (isRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				isRunning = false;

			//KeyPressSystem
			switch (e.type)
			{
			case SDL_KEYDOWN:
				KEYS[e.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				KEYS[e.key.keysym.sym] = false;
				break;
			default:
				break;
			}
		}

		int32_t pitch = 0;
		uint32_t* pixelBuffer = nullptr;

		UpdateLogic();


		//TODO:: BETTER CLEAR
		if (!SDL_LockTexture(texture, NULL, (void**)&pixelBuffer, &pitch))
		{
			pitch /= sizeof(uint32_t);

			for (int x = 0; x < RENDER_WIDTH; x++)
			{
				for (int y = 0; y < RENDER_HEIGHT; y++)
				{
					pixelBuffer[x + y * RENDER_WIDTH] = ARGB(0,0, 0, 255);
				}
			}

			SDL_UnlockTexture(texture);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		//RenderMap
		for (int x = 0; x < mapWidth; x++)
		{
			for (int y = 0; y < mapWidth; y++)
			{
				if (worldMap[x][y])
				{
					SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
					SDL_Rect fillRect = { x * gridSize,y * gridSize,gridSize,gridSize };
					SDL_RenderFillRect(renderer, &fillRect);
				}
			}
		}

		//Raycasting

		//calculating the direction
		float halfFov = fov / 2.0f;
		float segment = fov / RENDER_WIDTH;
		vec2 currentDir = Rotate2DVector(playerDir, playerRot);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, playerPos.x, playerPos.y, playerPos.x + currentDir.x, playerPos.y + currentDir.y);

		//FirstRay
		vec2 rayDir = Rotate2DVector(playerDir, (playerRot * TO_RAD) - halfFov * TO_RAD);
		vec2 horizontalRayStart;
		vec2 verticalRayStart;

		if (playerRot < 0)
		{
			playerRot += PI * 2;
		}
		else if (playerRot > PI * 2)
		{
			playerRot -= PI * 2;
		}

		for (int x = 0; x < RENDER_WIDTH; x++)
		{
			float rayRot(((playerRot)-halfFov * TO_RAD) + x * segment * TO_RAD);
			float yHorizontalOffset;
			float xHorizontalOffset = gridSize / tan(rayRot);

			float yVerticalOffset = gridSize * tan(rayRot);
			float xVerticalOffset;

			if (rayRot < 0)
			{
				rayRot += PI * 2;
			}
			else if (rayRot > PI * 2)
			{
				rayRot -= PI * 2;
			}


			//Horizontal
			if (rayRot > PI)
			{
				yHorizontalOffset = -gridSize;
				xHorizontalOffset = -gridSize / tan(rayRot);
				horizontalRayStart.y = (floor(playerPos.y / gridSize) * gridSize - 0.0001);
			}
			else
			{
				yHorizontalOffset = gridSize;
				xHorizontalOffset = gridSize / tan(rayRot);
				horizontalRayStart.y = (floor(playerPos.y / gridSize) * gridSize + gridSize);
			}
			horizontalRayStart.x = playerPos.x + (playerPos.y - horizontalRayStart.y) / tan(-rayRot);


			//Vertical
			if (rayRot > PI - 90.0 * TO_RAD && rayRot < PI + 90.0 * TO_RAD)
			{
				xVerticalOffset = -gridSize;
				yVerticalOffset = -gridSize * tan(rayRot);
				verticalRayStart.x = (floor(playerPos.x / gridSize) * gridSize - 0.0001);
			}
			else
			{
				xVerticalOffset = gridSize;
				yVerticalOffset = gridSize * tan(rayRot);
				verticalRayStart.x = (floor(playerPos.x / gridSize) * gridSize + gridSize);
			}
			verticalRayStart.y = playerPos.y + (playerPos.x - verticalRayStart.x) * tan(-rayRot);


			int h = 0;
			int v = 0;

			while (h < 50)
			{
			
				int mapX = horizontalRayStart.x / gridSize;
				int mapY = horizontalRayStart.y / gridSize;

				if (mapX >= 0 && mapX < mapWidth && mapY >= 0 && mapY < mapHeight)
				{
					if (worldMap[mapX][mapY] > 0)
					{
						break;
					}
				}

				horizontalRayStart.x += xHorizontalOffset;
				horizontalRayStart.y += yHorizontalOffset;
				h++;
			}


			while (v < 50)
			{

				int mapX = verticalRayStart.x / gridSize;
				int mapY = verticalRayStart.y / gridSize;

				if (mapX >= 0 && mapX < mapWidth && mapY >= 0 && mapY < mapHeight)
				{
					if (worldMap[mapX][mapY] > 0)
					{
						break;
					}
				}

				verticalRayStart.x += xVerticalOffset;
				verticalRayStart.y += yVerticalOffset;
				v++;
			}

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

			float hLenght = Vector2DLenght(vec2{ playerPos.x - horizontalRayStart.x , playerPos.y - horizontalRayStart.y }) * cos(x*segment * TO_RAD - halfFov * TO_RAD);
			float vLenght = Vector2DLenght(vec2{ playerPos.x - verticalRayStart.x , playerPos.y - verticalRayStart.y })  * cos(x*segment * TO_RAD - halfFov * TO_RAD);

			if (hLenght < vLenght)
			{
				int pixelLineHeight = (gridHight / hLenght * distanceProjectionPlane);


				if (!SDL_LockTexture(texture, NULL, (void**)&pixelBuffer, &pitch))
				{
					pitch /= sizeof(uint32_t);

					for (int y = (RENDER_HEIGHT / 2) - pixelLineHeight / 2; y < pixelLineHeight; y++)
					{
						if(x >= 0 && x < RENDER_WIDTH && y >=0 && y < RENDER_HEIGHT)
							pixelBuffer[x + y * RENDER_WIDTH] = ARGB(255, 0, 0, 255);
					}

					SDL_UnlockTexture(texture);
				}
				SDL_RenderDrawLine(renderer, playerPos.x, playerPos.y, horizontalRayStart.x, horizontalRayStart.y);
			}
			else
			{
				int pixelLineHeight = ((gridHight / vLenght) * distanceProjectionPlane);

				if (!SDL_LockTexture(texture, NULL, (void**)&pixelBuffer, &pitch))
				{
					pitch /= sizeof(uint32_t);



					for (int y = (RENDER_HEIGHT / 2) - pixelLineHeight / 2; y < pixelLineHeight; y++)
					{
						if (x >= 0 && x < RENDER_WIDTH && y >= 0 && y < RENDER_HEIGHT)
							pixelBuffer[x + y * RENDER_WIDTH] = ARGB(255, 0, 0, 255);
					}

					SDL_UnlockTexture(texture);
				}
				SDL_RenderDrawLine(renderer, playerPos.x, playerPos.y, verticalRayStart.x, verticalRayStart.y);
			}

		/*	if (Vector2DLenght(vec2{ playerPos.x - verticalRayStart.x , playerPos.y - verticalRayStart.y }) < 150)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, playerPos.x, playerPos.y, verticalRayStart.x, verticalRayStart.y);
			}*/
		}

		SDL_RenderCopy(renderer, texture, NULL, NULL);

		//std::cout << "Px: " << playerPos.x << " Py" << playerPos.y << "\n";
		//std::cout << "Ay: " << rayStart.y << " Ax" << rayStart.x << "\n";

		SDL_RenderPresent(renderer);
		Uint64 currentTime = SDL_GetPerformanceCounter();
		//std::cout << SDL_GetPerformanceFrequency() / (currentTime - oldTime) << "\n";
		oldTime = currentTime;

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}