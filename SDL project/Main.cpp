
#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace CaveOfProgramming;

int main(int argc, char* argv[])
{
	srand(time(0));

	bool quit = false;

	Screen screen;
	if (!screen.Init()) {
		cout << "SDL Init returned false" << endl;
		return 1;
	}

	Swarm swarm;

	int elapsed = 0;
	unsigned char green = 0;
	unsigned char red = 0;
	unsigned char blue = 0;

	while (!quit) {
		swarm.update(elapsed);

		elapsed = SDL_GetTicks();
		green = (unsigned char)((1+ sin(elapsed * 0.0001)) * 128);
		red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);
		
		const Particle* const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; ++i) {

			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH / 2);

			//SCREEN_HEIGHT here will result in oval explosion
			int y = (particle.m_y * Screen::SCREEN_WIDTH / 2) + Screen::SCREEN_HEIGHT/2; 

			screen.setPixel(x, y, green, red, blue);

		}

		screen.boxBlur();

		//Draws the screen
		screen.update();

		//check for messeges/events (events queue)
		if (!screen.processEvents()){
			quit = true;
			break;
		}
	}

	return 0;
}