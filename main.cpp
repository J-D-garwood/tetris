#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "block.h"
//#include "Lblock.h"

const int WIDTH = 600, HEIGHT = 550;
const int BOARD_HEIGHT = 392+28*4;
const int BOARD_WIDTH = 280; 
//const int SPEED = 5;

// Move block sprite every 100 milliseconds
const Uint32 MOVE_INTERVAL = 1000;

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

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    //L blocks
    Lblock firstL = Lblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
    firstL.EstablishSouth();
    all_L_blocks.push_back(firstL);


    SDL_Rect board = { (WIDTH / 2 - BOARD_WIDTH / 2), 10, BOARD_WIDTH, BOARD_HEIGHT };

/*
        for (int i = 0; i<all_L_blocks.size(); i++) {
            if (all_blocks.size()>=all_L_blocks.size()*4) {
                break;
            }
            Lblock thisL = all_L_blocks[i];
            block A = block(thisL.x, thisL.y, thisL.stopped);
            block B = block(thisL.x_b2, thisL.y_b2, thisL.stopped);
            block C = block(thisL.x_b3, thisL.y_b3, thisL.stopped);
            block D = block(thisL.x_b4, thisL.y_b4, thisL.stopped);
            all_blocks.push_back(A);
            all_blocks.push_back(B);                    
            all_blocks.push_back(C);            
            all_blocks.push_back(D);            
        }   */
/*
        for (int i = 0; i<all_blocks.size(); i++) {
        block Block = all_blocks[i];
        SDL_Rect rect = {Block.x, Block.y, Block.dim, Block.dim};
        all_rects.push_back(rect);
        }
*/
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
            // Move the L rectangles
            for (int i = 0; i<all_rects.size(); i++) {
                if(all_rects[i].y+28!=BOARD_HEIGHT+10) {
                    for (int k = 0; k<all_blocks.size(); k++) {
                        if(all_rects[i].x == all_blocks[k].x && all_rects[i].y == all_blocks[k].y) {
                            if (all_blocks[k].stopped) {
                                all_rects[i].y+=28;
                            }
                        }
                    }
                } else {
                }
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
        for (int i = 0; i<all_rects.size(); i++) {
            SDL_Rect rect = all_rects[i];
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}