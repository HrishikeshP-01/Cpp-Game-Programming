// Simple blue background in the game loop
#include  <SDL.h>;

class BlueBackground {
public:
	BlueBackground();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
};

BlueBackground::BlueBackground() {
	isRunning = true;
	window = nullptr;
	renderer = nullptr;
}

bool BlueBackground::Initialize() {
	// initialize SDL library
	// for now we just initialize video system
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL %s", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Blue Background", // title
		100, // x co-ordinate
		100, // y co-ordinate
		1024, // width
		786, // height
		0 // flags
	);
	if (!window) {
		SDL_Log("Unable to create window %s", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(
		window, // ptr to window
		-1, // which graphics driver to use, useful when game has multiple windows as we use only 1 window here pass -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // initialization flags to choose renderer
		// here we use an accelerated renderer with vertical synchronization
	);
	if (!renderer) {
		SDL_Log("Renderer intialization failed %s", SDL_GetError());
		return false;
	}
	return true;
}

void BlueBackground::RunLoop() {
	while (isRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void BlueBackground::Shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void BlueBackground::ProcessInput() {
	SDL_Event event;
	// while there are still events in the queue
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// get current state of keyboard and check if Esc key has been pressed
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// query a specific key by indexing the array with the SDL_SCANCODE value of the key
	if (state[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
}

void BlueBackground::UpdateGame() {

}

void BlueBackground::GenerateOutput() {
	// to clear back buffer and display a color we first need to specify a color with SDL_SetRenderDrawColor
	SDL_SetRenderDrawColor(
		renderer, // ptr to renderer
		0, // R
		0, // G
		255, // B
		255 //A
		);
	// Call SDL_RenderClear to clear and set the back buffer to current draw color
	SDL_RenderClear(renderer);
	// the next step is to draw the game scene but I won't be doing that now
	// finally swap the front and back buffers
	SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
	BlueBackground game;
	bool result = game.Initialize();
	if (!result)
		return 1;
	game.RunLoop();
	game.Shutdown();
	return 0;
}
