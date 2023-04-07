#include<algorithm>
#include<ctime>
#include<iostream>
#include<cstdlib>
#include<vector>
#include <stdio.h>

#include<string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>


using namespace std;
#undef main

int arr[24] = {1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12};

int tablevalue[8][6];

const string game_title = "Animal Match";

const string background_path = "background.png";
const string start_image_path = "start_image.png";
const string spritesheet_path = "spritesheet.png";
const string game_win_path = "game_win_background.png";


static Mix_Music* g_sound_music = NULL;
static Mix_Chunk* g_chunk_click = NULL;
static Mix_Chunk* g_chunk_clicktrue = NULL;
static Mix_Chunk* g_chunk_gamewin = NULL;

enum AnimalType{
    animal_hidden,
    animal_one,
    animal_two,
    animal_three,
    animal_four,
    animal_five,
    animal_six,
    animal_seven,
    animal_eight,
    animal_nine,
    animal_ten,
    animal_eleven,
    animal_twelve,
    animal_shown,
    animal_total,
};

struct Cellpos {                        // vị trí của một ô
	int row;
	int col;
};

struct Graphic{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* start_image;
    SDL_Texture* background;
    SDL_Texture* spritesheet;
    SDL_Texture* gamewin;
    SDL_Texture* gameover;
    TTF_Font *font;
    SDL_Surface *surface;
    vector <SDL_Rect> AnimalRects;
};



bool initGraphic(Graphic &g);

bool initMusic();

bool initFont();

void destroyGraphic(Graphic &g);

void initAnimalRects(vector<SDL_Rect> &rects);

void TableValue(int tablevalue[8][6]);

void displayGame(const Graphic &graphic);

SDL_Texture* createTexture(SDL_Renderer *renderer, const string &path);

void ClickMouse(SDL_Event &event,Graphic &graphic);

bool GameWin (int tablevalue[4][6]);

void err(const string &m);


int main()
{
    Graphic g;
    initGraphic(g);
    TableValue(tablevalue);

    if(initMusic() == false)
        return -1;
    Mix_PlayMusic(g_sound_music, -1);
    bool win=false;
    bool quit = false;
    while (!quit) {
        displayGame(g);

        if (GameWin(tablevalue)&&!win) {
            Mix_PlayChannel(-1,g_chunk_gamewin,0);
            win = true;
        }
        SDL_Event event;
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                        break;
                    }
                    if (!GameWin(tablevalue))
                        ClickMouse(event, g);

                }
    }
}

SDL_Texture* createTexture(SDL_Renderer *renderer, const string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        err("Unable to load image " + path + "!");
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void err(const string &m) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", m.c_str(), NULL);
}

void destroyGraphic(Graphic &g) {
	SDL_DestroyTexture(g.background);
	SDL_DestroyTexture(g.start_image);
	SDL_DestroyTexture(g.spritesheet);
	SDL_DestroyTexture(g.gamewin);
	SDL_DestroyRenderer(g.renderer);
	SDL_DestroyWindow(g.window);
	IMG_Quit();
	SDL_Quit();
}

bool initMusic()
{

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }
    else
    {
        g_sound_music = Mix_LoadMUS("background_sound.mp3");
        g_chunk_click = Mix_LoadWAV("click.wav");
        g_chunk_clicktrue = Mix_LoadWAV("matchclick.wav");
        g_chunk_gamewin = Mix_LoadWAV("winsound.wav");
    return true;
    }
}

bool initGraphic(Graphic &g) {
    g.window = NULL;
    g.renderer = NULL;
    g.background = NULL;
    g.spritesheet = NULL;

    int sdlFlags = SDL_INIT_VIDEO;  // Dùng SDL để hiển thị hình ảnh
    if (SDL_Init(sdlFlags) != 0) {
        err("SDL could not initialize!");
        return false;
    }

    int imgFlags = IMG_INIT_PNG;    // Dùng SDL_Image để load ảnh png
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        err("SDL_Image could not initialize!");
        return false;
    }

    g.window = SDL_CreateWindow(game_title.c_str(), // tiêu đề
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                1000, // chiều rộng window
                                600, //chiều dài window
                                SDL_WINDOW_SHOWN); // hiện

    if (g.window == NULL) {
        err("Window could not be created!");
        return false;
    }

    g.renderer = SDL_CreateRenderer(g.window, -1, SDL_RENDERER_ACCELERATED);
    if (g.renderer == NULL) {
        err("Renderer could not be created!");
        return false;
    }

    g.background = createTexture(g.renderer, background_path);
    if (g.background == NULL) {
        err("Unable to create texture from " + background_path + "!");
        return false;
    }
    g.spritesheet = createTexture(g.renderer, spritesheet_path);
    if (g.spritesheet == NULL) {
        err("Unable to create texture from " + spritesheet_path + "!");
        return false;
    }

    g.gamewin = createTexture(g.renderer, game_win_path);
    if (g.gamewin == NULL) {
        err("Unable to create texture from " + game_win_path + "!");
        return false;
    }

    initAnimalRects(g.AnimalRects);
    return true;
}

void initAnimalRects(vector<SDL_Rect> &rects)
{
	for (int i = 0; i < animal_total; i++) {
		SDL_Rect rect = { 0,0, 100, 100 };
			rect.x = i*100;
		rects.push_back(rect);
	}
}

void TableValue(int tablevalue[8][6])
{
    srand(time(0));
    int cnt=0;
    random_shuffle(arr,arr+23);
    for(int i=0;i<4;i++)
        for(int j=0;j<6;j++)
        {
            tablevalue[i][j]=0;
        }

    for(int i=4;i<8;i++)
        for(int j=0;j<6;j++)
            if(cnt<24)
    {
        tablevalue[i][j]=arr[cnt];
        cnt++;
    }
}

SDL_Rect getAnimalRects(const Cellpos &pos,const vector<SDL_Rect> &AnimalRects) {
	switch (tablevalue[pos.row][pos.col]) {
	case 0:
		return AnimalRects[animal_hidden];
	case 1:
		return AnimalRects[animal_one];
	case 2:
		return AnimalRects[animal_two];
	case 3:
		return AnimalRects[animal_three];
	case 4:
		return AnimalRects[animal_four];
	case 5:
		return AnimalRects[animal_five];
	case 6:
		return AnimalRects[animal_six];
	case 7:
		return AnimalRects[animal_seven];
	case 8:
		return AnimalRects[animal_eight];
	case 9:
		return AnimalRects[animal_nine];
	case 10:
		return AnimalRects[animal_ten];
	case 11:
		return AnimalRects[animal_eleven];
    case 12:
		return AnimalRects[animal_twelve];
    case 13:
        return AnimalRects[animal_shown];
	}
}

void displayGame(const Graphic &graphic) {
	SDL_RenderClear(graphic.renderer);

	SDL_Rect desRect = { 0,0,1000,600 };
	SDL_RenderCopy(graphic.renderer, graphic.background, NULL, &desRect);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			SDL_Rect desRect = {
				j*100+300,
				i*100+100 ,
				100,
				100,
			};

			Cellpos pos = { i, j };
			SDL_Rect srcRect = getAnimalRects(pos, graphic.AnimalRects);
			SDL_RenderCopy(graphic.renderer, graphic.spritesheet, &srcRect, &desRect);
		}
	}

	if (GameWin(tablevalue)) {
        SDL_Rect desRect = { 0,0,1000,600 };
        SDL_RenderCopy(graphic.renderer, graphic.gamewin, NULL, &desRect);
	}

	SDL_RenderPresent(graphic.renderer); // hiện những gì vừa vẽ
	//SDL_Delay(5000);
}
static bool choose[4][6];
static int similar[2];
int open = 0;
void ClickMouse (SDL_Event &event,Graphic &graphic) {
    int xm, ym;
    int row1, col1;// row2, col2;
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        xm = event.button.x;
        ym = event.button.y;
        if(xm >= 300 && xm <= 890 && ym >= 100 && ym <= 490)
        {
            col1 = (xm-300)/100;
            row1 = (ym-100)/100;
            if(choose[row1][col1] == false)
            {
                open++;
                swap(tablevalue[row1][col1],tablevalue[row1+4][col1]);
                similar[open] = tablevalue[row1][col1];
                choose[row1][col1] = true;

                Mix_PlayChannel(-1,g_chunk_click,0);
            }
            if(open >= 2)
            {
                displayGame(graphic);
                SDL_Delay(300);
                open = 0;

                for(int i = 0;i < 4; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        if(choose[i][j] == true && tablevalue[i][j] != 13)
                        {
                            swap(tablevalue[i][j],tablevalue[i+4][j]);
                            choose[i][j] = false;
                        }
                    }
                }
                if(similar[1] == similar[2])
                {
                   for(int i = 0;i < 4; i++)
                    {
                        for (int j = 0; j < 6; j++)
                        {
                            if(tablevalue[i+4][j] == similar[1])
                            {
                                tablevalue[i][j] = 13;
                                tablevalue[i+4][j] = 13;
                                choose[i][j] = true;
                            }
                        }
                    }

                    Mix_PlayChannel(-1, g_chunk_clicktrue,0);
                }
            }

        }
    }
}


bool GameWin (int tablevalue[4][6]) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (tablevalue[i][j] == 13)
                count++;
        }
    }
    if (count == 24)
        return true;
    return false;
}

