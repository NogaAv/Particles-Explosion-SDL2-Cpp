#pragma once
#include <iostream>
#include <SDL.h>

using namespace std;

namespace CaveOfProgramming {

	class Screen
	{

	 public:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;

	 private:
		 SDL_Window* m_window;
		 SDL_Renderer *m_renderer;
		 SDL_Texture *m_texture;
		 SDL_Event m_event;

		 Uint32 *m_buffer1;
		 Uint32* m_buffer2;

	 public:
		 Screen();
		 ~Screen();
		 bool Init();
		 void update();
		 void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		 bool processEvents();
		 void close();
		 void boxBlur();

	};

}

/*
Uint32 m_buffer[SCREEN_WIDTH * SCREEN_HEIGHT]  => Each Uint32 (4 bytes) in this buffer represents 4 pixels. byte for a pixel.
												 pixels are: Red, Green, Blue, Apoque (RGBA)
*/

