#include "main.h"

#define MAXIMUM_FRAME_RATE 120
#define MINIMUM_FRAME_RATE 15
#define UPDATE_INTERVAL (1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)


float fps = 0;
float Createtime = 0;
float dtime = 0;
float newtime;
float accumulator;
int main ( int argc, char** argv )
{
	LogOpen();
    SDL_Surface*  screen;
    gfx_tileset*  font;
    gfx_tileset*  tiles;
    gam_world*	  world;
    gfx_viewport* vp;
    gfx_tilemap* tm = AllocMem(sizeof(tm));
	SDL_Event ev;
	int mx, my;
	int xoff = 0, yoff = 0;
	srand(time(NULL));

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(320, 240, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);


    font    = gfxTilesetCreate(gfxLoadFile("font.bmp"),8, 8);
    tiles   = gfxTilesetCreate(gfxLoadFile("tiles.bmp"),16, 16);
    tm->tileset = tiles;
    tm->w = 25;
    tm->h = 20;
 	world   = gamWorldCreate(tm, NULL);
	vp      = gfxViewportCreate(320, 240, world);

	SDL_Rect testrect = {42, 26, 186, 123};
	float currenttime = SDL_GetTicks();
    while(1) {
		newtime = SDL_GetTicks();
		dtime = (newtime - currenttime);
		currenttime = newtime;
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 30, 30, 30));
        SDL_PollEvent(&ev);
		switch(ev.type) {
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mx, &my);
			break;
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
			break;
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym) {
					case SDLK_LEFT:
						xoff+=10;
					break;
					case SDLK_RIGHT:
						xoff-=10;
					break;
					case SDLK_UP:
						yoff+=10;
					break;
					case SDLK_DOWN:
						yoff-=10;
					break;
					default:
					break;
				}
			break;
		}

		vp->metrics.x = -xoff;
		vp->metrics.y = yoff;
		gfxViewportUpdate(vp);
		gfxViewportDraw(vp, screen, 0, 0);
		SDL_Delay(10);
		SDL_Flip(screen);
	};
    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

