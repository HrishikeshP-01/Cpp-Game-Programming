// Demonstrates the use of Surfaces in SDL

/* Surfaces - SDL abstracts any area we can draw to which makes 
software rendering very easy. However GPU rendering DOESN'T USE SURFACES*/

// Create a surface, draw on it, use SDL_UpdateWindowSurface() to display it

#include <SDL.h>;

int main(int argc, char** argv) {
	SDL_Window* window;
	SDL_Surface* surface;
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("SDL intialization failed %s", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow("A rectangle", //title
		100, //x co-ordinate
		100, //y co-ordinate
		1024, //width
		700, //height
		0 //flag
	);
	if (!window) {
		SDL_Log("Weingow creation failed %s", SDL_GetError());
		return 1;
	}
	// Get surface from window
	surface = SDL_GetWindowSurface(window);

	// make sure it runs successfully
	if (!surface) {
		SDL_Log("Surface not obtained %s", SDL_GetError());
		return 1;
	}

	// fill window with a rectangle
	SDL_FillRect(surface,
		NULL,
		SDL_MapRGB(surface->format, 255, 0, 0)
	);
	
	// update the window display
	SDL_UpdateWindowSurface(window);

	// wait
	system("pause");

	// Destroy the window. This will also destroy the surfae
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
