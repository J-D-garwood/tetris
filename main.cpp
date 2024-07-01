#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <SDL2/SDL.h>
#include "block.h"
#include <string>

const int WIDTH = 600, HEIGHT = 550;
const int BOARD_HEIGHT = 392+28*4;
const int BOARD_WIDTH = 280; 
bool gameOn =  true;

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
                    if (i==x1_Update) {
                        if (j-1==y1_Update) {
                            return true;
                        }
                    }
                    if (i==x2_Update) {
                        if (j-1==y2_Update) {
                            return true;
                        }
                    }
                    if (i==x3_Update) {
                        if (j-1==y3_Update) {
                            return true;
                        }
                    }
                    if (i==x4_Update) {
                        if (j-1==y4_Update) {
                            return true;
                        }
                    }
                }   
            }
        }
    }
    return false;
}
// Move block sprite every 100 milliseconds
const Uint32 MOVE_INTERVAL = 200;

//taken positions [x, y]
//std::vector<std::array<int, 2>> taken_spaces;
//blocks
std::vector<block> all_blocks;

//LL blocks
std::vector<LLblock> all_LL_blocks;

//LR blocks
std::vector<LRblock> all_LR_blocks;

//T blocks
std::vector<Tblock> all_T_blocks;

//S blocks

//Z blocks 

//I blocks

//O blocks


int BLOCKtoblock(block b) {
        block A = block(b.x1, b.y1, true, b.type);
        block B = block(b.x2, b.y2, true, b.type);
        block C = block(b.x3, b.y3, true, b.type);
        block D = block(b.x4, b.y4, true, b.type);
        all_blocks.push_back(A);
        all_blocks.push_back(B);
        all_blocks.push_back(C);
        all_blocks.push_back(D);
        return 0;
}
void drawAllblocks(SDL_Renderer *rend) {
    for (int i = 0; i<all_blocks.size(); i++) {
        block b = all_blocks[i];
        b.draw(rend);
    }
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
    Iblock first = Iblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
    Sblock second = Sblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
    first.EstablishNS();
    //first.EstablishNorth();
    //second.EstablishWest();
    second.EstablishEast();
    //second.EstablishWest();
    //firstL.EstablishSouth();

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
            
            if (windowEvent.type == SDL_KEYDOWN)
            {
                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        second.moveToLeft(SPACES);
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_UP:
                        break;
                    case SDLK_RIGHT:
                        second.moveToRight(SPACES);
                        break;
                }
            }
            
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
            stoppingFlag = first.checkpos();
            second.checkpos();
            stoppingFlag2 = checkblockpos(SPACES, second);
            if (stoppingFlag2) {
                second.stopblock();
                BLOCKtoblock(second);
            }
            if (stoppingFlag) {
                BLOCKtoblock(first);
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                second.moveDown();
                setSpaces(SPACES, first.x1, first.y1);
                setSpaces(SPACES, first.x2, first.y2);
                setSpaces(SPACES, first.x3, first.y3);
                setSpaces(SPACES, first.x4, first.y4);
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
            first.moveDown();
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

        if (stoppingFlag && !stoppingFlag2) {
            second.draw(renderer);
        }
        if (!stoppingFlag) {
            first.draw(renderer);
        }
        drawAllblocks(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}