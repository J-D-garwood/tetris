#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <SDL2/SDL.h>
#include "block.h"
#include <string>
//#include "Lblock.h"

const int WIDTH = 600, HEIGHT = 550;
const int BOARD_HEIGHT = 392+28*4;
const int BOARD_WIDTH = 280; 

using spaces =  int[10][18];
int stoppingFlag = 0;
int stoppingFlag2 = 0;
void setSpaces(spaces& array, int x, int y) {
    // Update the array with your data
    int xUpdate = (x-160)/28;
    int yUpdate = (y-10)/28;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 18; ++j) {
            if (i==xUpdate && j==yUpdate) {
                array[i][j] = 1;
            }
        }
    }
}

bool checkblockpos(spaces& array, block b) {
    int x1_Update = (b.x1-160)/28;
    int y1_Update = (b.y1-10)/28;
    int x2_Update = (b.x2-160)/28;
    int y2_Update = (b.y2-10)/28;
    int x3_Update = (b.x3-160)/28;
    int y3_Update = (b.y3-10)/28;
    int x4_Update = (b.x4-160)/28;
    int y4_Update = (b.y4-10)/28;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 18; ++j) {
            if (array[i][j]==1) {
                if (i==x1_Update || i==x2_Update || i==x3_Update || i==x4_Update) {
                    if (j-1==y1_Update || j-1==y2_Update || j-1==y3_Update || j-1==y4_Update) {
                        return true;
                    }
                }   
            }
        }
    }
    return false;
}
// Move block sprite every 100 milliseconds
const Uint32 MOVE_INTERVAL = 300;

//taken positions [x, y]
//std::vector<std::array<int, 2>> taken_spaces;
//rectangles 
std::vector<SDL_Rect> all_rects;
//blocks
std::vector<block> all_blocks;

//L blocks
std::vector<Lblock> all_L_blocks;

//T blocks

//SL blocks

//SR blocks 

//I blocks

//O blocks
void updateSpaces(spaces& array) {
        
}

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "poop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }
    int SPACES[10][18] = {0};
    //L blocks
    Lblock firstL = Lblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
    Lblock secondL = Lblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
    //firstL.EstablishEast();
    //firstL.EstablishNorth();
    secondL.EstablishNorth();
    //firstL.EstablishWest();
    firstL.EstablishSouth();

    SDL_Rect board = { (WIDTH / 2 - BOARD_WIDTH / 2), 10, BOARD_WIDTH, BOARD_HEIGHT };
    Uint32 lastMoveTime = 0;


    SDL_Event windowEvent;

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type)
            {
                break;
            }
            /*
            if (windowEvent.type == SDL_KEYDOWN)
            {
                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_UP:
                        rect.y -= SPEED;
                        break;
                    case SDLK_DOWN:
                        rect.y += SPEED;
                        break;
                    case SDLK_LEFT:
                        rect.x -= SPEED;
                        break;
                    case SDLK_RIGHT:
                        rect.x += SPEED;
                        break;
                }
            }
            */
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
            stoppingFlag = firstL.checkpos();
            stoppingFlag2 = checkblockpos(SPACES, secondL);
            if (stoppingFlag2) {
                secondL.stopblock();
            }
            if (stoppingFlag) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                secondL.moveDown();
                setSpaces(SPACES, firstL.x1, firstL.y1);
                setSpaces(SPACES, firstL.x2, firstL.y2);
                setSpaces(SPACES, firstL.x3, firstL.y3);
                setSpaces(SPACES, firstL.x4, firstL.y4);
                /*cout << firstL.x1 << " " << firstL.y1 << endl;
                //cout << 5*28+160 << " " << 1*28+10 << endl;
                cout << firstL.x2 << " " << firstL.y2 << endl;
                //cout << 5*28+160 << " " << firstL.y1 << endl;
                cout << firstL.x3 << " " << firstL.y3 << endl;
                //cout << 5*28+160 << " " << firstL.y1 << endl;
                cout << firstL.x4 << " " << firstL.y4 << endl;
                //cout << 4*28+160 << " " << firstL.y1 << endl;
                for(int a = 0; a < 10; a++)
                {
                    for(int b = 0; b < 18; b++)
                    {
                    cout << SPACES[a][b] << " ";
                    }
                    cout << endl;
                }
                */
            }
            firstL.moveDown();
            lastMoveTime = currentTime;  
        }

        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 198, 198, 198, 255);
        SDL_RenderFillRect(renderer, &board);
    
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        for (int i = 0; i<9; i++)
        {
            SDL_RenderDrawLine(renderer, (WIDTH / 2 - BOARD_WIDTH / 2)+28+28*i, 10, (WIDTH / 2 - BOARD_WIDTH / 2)+28+28*i, 10+BOARD_HEIGHT);
        }
        for (int i = 0; i<17; i++)      
        {
            SDL_RenderDrawLine(renderer, (WIDTH / 2 - BOARD_WIDTH / 2), 38+28*i, (WIDTH / 2 - BOARD_WIDTH / 2)+BOARD_WIDTH, 38+28*i);
        }  

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //
        //Drawing all L blocks

        if (stoppingFlag) {
            secondL.draw(renderer);
        }
        firstL.draw(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}