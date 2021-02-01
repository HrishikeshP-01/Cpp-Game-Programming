#include <SDL.h>

class SimpleGameLoop {
public:
	SimpleGameLoop();
	// Initialize the game loop
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	bool isRunning;
	SDL_Window* window;
	// functions for the 3 main components of game loops
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
};

SimpleGameLoop::SimpleGameLoop() {
	isRunning = true;
	window = nullptr;
}

bool SimpleGameLoop::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Error during initialization: %s", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow(
		"A simple game loop", //Window title
		100, // x co-ordinate position
		100, // y co-ordinate position
		1024, // width
		786, // height
		0 // Additional flags. 0 for no flags 
	);
	if (!window) {
		SDL_Log("Error during window creation: %s", SDL_GetError());
		return false;
	}
	return true;
}

void SimpleGameLoop::Shutdown() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SimpleGameLoop::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		// check if close button has been pressed
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// get the state of the keyboard it's a pointer to an array
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// query a specific key by indexing into the array using the SDL_SCANCODE value of the key
	// here we check if escape key is present in the array
	if (state[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
}

void SimpleGameLoop::RunLoop() {
	while (isRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void SimpleGameLoop::UpdateGame(){
}

void SimpleGameLoop::GenerateOutput(){}

int main(int argc, char** argv) {
	// the int argc and char** argv are necessary 
	SimpleGameLoop game;
	bool success = game.Initialize();
	if (!success) {
		return 1;
	}
	game.RunLoop();
	game.Shutdown();
	return 0;
}
