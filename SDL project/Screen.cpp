
#include "Screen.h"
#include <cstring>

namespace NogaAvrProj {


	Screen::Screen():
		
			m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL){
	}

	Screen::~Screen() {
		close();
	}

	bool Screen::Init() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			string err = SDL_GetError();
			cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
			return false;
		}

		m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, /*SDL_WINDOW_FULLSCREEN*/SDL_WINDOW_SHOWN);

		if (m_window == NULL)
		{
			SDL_QUIT;
			return false;
		}


		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == NULL) {
			cout << SDL_GetError << endl;
			SDL_DestroyWindow(m_window);
			SDL_QUIT;
			return false;
		}

		//SDL_PIXELFORMAT_RGBA8888 -> every pixel on the window will have 4 byte of data to describe it: a byte for Red (0-255 shades of red), a byte for Green, a byte for Bleu, and a byte for 'A' which stands for transperracy. 
		//SDL_TEXTUREACCESS_STATIC -> every computer refreshes the screen every x time-spane, and refreshing occures from the upper-left most pixel of the screen
		//							 to the right, and down line by line. so if the rendering of text (drawing to our windows) occures when the refreshing occures, the collisoin of refreshing pixel with draw pixel will be displayed as shiny undesired pixel. 
		//							  so to prevent that, a sync must be configured, so that the rendering will not occure when screen refreshing occures.

		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (m_texture == NULL) {
			cout << SDL_GetError << endl;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_QUIT;
			return false;
		}

		m_buffer1 = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH]; // buffer that contains all the information for the pixels
		m_buffer2 = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH]; // buffer that contains all the information for the pixels

		//Clearing memory
		memset(m_buffer1, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
		memset(m_buffer2, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));

		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) //prevent crashing if given out of bounderies values.
			return;

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		m_buffer1[(SCREEN_WIDTH * y) + x] = color;

	}


	void Screen::update() {

		SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	bool Screen::processEvents() {
		
			while(SDL_PollEvent(&m_event))
			{
				if (m_event.type == SDL_QUIT)
					return false;
			}
			return true;
	}

	void Screen::close() {

		delete[] m_buffer1;
		delete[] m_buffer2;

		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_QUIT;
	}

	/*void Screen::clear() {
		memset(m_buffer1, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
		memset(m_buffer2, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));

	}*/

	void Screen::boxBlur() {

		//Swap the buffers, so pixels are in m_buffer1 and we are drawing to m_buffer2

		Uint32* tmp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = tmp;

		/* Blure affect-> deviding all 3 pixel colors in the current member in buffer, between all adjust members
		* 
		*	0 0 0
		*	0 1 0
		*	0 0 0
		* 
		*/

		for (int y = 0; y < Screen::SCREEN_HEIGHT; ++y) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; ++x) {
							
				Uint32 redTotal = 0;
				Uint32 greenTotal = 0;
				Uint32 bleuTotal = 0;

				for (int row = -1; row <= 1; ++row) {
					for (int col = -1; col <= 1; ++col) {
						
						Uint32 currentX = x + col;
						Uint32 currentY = y + row;

						//Check bounderies
						if (currentX >= 0 && currentX < Screen::SCREEN_WIDTH && currentY >= 0 && currentY < Screen::SCREEN_HEIGHT) {
							Uint32 color = m_buffer2[currentY * Screen::SCREEN_WIDTH + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 bleu = color >> 8;

							redTotal += red;
							greenTotal += green;
							bleuTotal += bleu;

							/*redTotal += (Uint8)(color >> 24);
							greenTotal += (Uint8)(color >> 16);
							bleuTotal += (Uint8)(color >> 8);*/

						}
					}
				}
				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 bleu = bleuTotal / 9;

				setPixel(x, y, red, green, bleu);

			}

        }
	}
}
