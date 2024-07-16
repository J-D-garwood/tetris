#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "block.h"
#include <string>
#include <stdlib.h>
#include <algorithm>
using std::cout;
using std::endl;

const int WIDTH = 600, HEIGHT = 550;
const int BOARD_HEIGHT = 392+28*4;
const int BOARD_WIDTH = 280; 

//int rightHoldMoveCount = 0;
//int leftHoldMoveCount = 0;

bool gameOn =  true;
bool start = true;

const Uint8* keystate;
using spaces =  int[10][18];
int stoppingFlag = 0;
int GameOverFlag = 0;
int checkTopLvl(spaces& array) {
    for (int i = 0; i<10; ++i) {
        if (array[i][18]==1) {
            return 1;
        }
    }
    return 0;
}
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

void printSpaces(spaces& array) {
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << array[j][i];
        }
        cout << endl;
    }
}


int checkblockpos(spaces& array, block b) {
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
                            return 1;
                        }
                    }
                    if (i==x2_Update) {
                        if (j-1==y2_Update) {
                            return 1;
                        }
                    }
                    if (i==x3_Update) {
                        if (j-1==y3_Update) {
                            return 1;
                        }
                    }
                    if (i==x4_Update) {
                        if (j-1==y4_Update) {
                            return 1;
                        }
                    }
                }   
            }
        }
    }
    return 0;
}
Uint32 initial_MI = 200;
Uint32 MOVE_INTERVAL = initial_MI;
Uint32 SHIFT_INTERVAL = MOVE_INTERVAL/2;
bool movetime = true;

int randomBlockSelect() {
    srand (time(NULL));
    int num = rand() % 7 + 1;
    return num;
}
int currentBlock = randomBlockSelect();
int nextBlock = randomBlockSelect();

//blocks
std::vector<block> all_blocks;

//LL blocks
std::vector<LLblock> all_LL_blocks;

//LR blocks
std::vector<LRblock> all_LR_blocks;

//T blocks
std::vector<Tblock> all_T_blocks;

//S blocks
std::vector<Sblock> all_S_blocks;

//Z blocks 
std::vector<Zblock> all_Z_blocks;

//I blocks
std::vector<Iblock> all_I_blocks;

//O blocks
std::vector<Oblock> all_O_blocks;


void addToActiveBlocks(int nextblock) {
    switch (nextblock) {
        case 1:
            {
                LRblock Lblock = LRblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
                Lblock.Establish();
                all_LR_blocks.push_back(Lblock);
            break;
            }
        case 2:
            {
            LLblock Lblock_2 = LLblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
            Lblock_2.Establish();
            all_LL_blocks.push_back(Lblock_2);
            break;
            }
        case 3:
            {
            Sblock S_block = Sblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
            S_block.Establish();
            all_S_blocks.push_back(S_block);
            break;
            }
        case 4:
            {
            Zblock Z_block = Zblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
            Z_block.Establish();
            all_Z_blocks.push_back(Z_block);
            break;
            }   
        case 5:
            {
            Oblock O_block = Oblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
            O_block.Establish();
            all_O_blocks.push_back(O_block);
            break; 
            }      
        case 6:
            {
            Iblock I_block = Iblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
            I_block.Establish();
            all_I_blocks.push_back(I_block);
            break;
            }   
        case 7:
            {
            Tblock T_block = Tblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
            T_block.Establish();
            all_T_blocks.push_back(T_block);
            break;
            }    
            
    }
}
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

int checkOneLine(spaces& array, int line) {
    int count = 0;
    for (int i = 0; i<10; ++i) {
        if (array[i][line]==1) {
            ++count;
        }
    }
    if (count==10) {
        //SOMETHING NEEDS TO GO HERE??
        return 1;
    } else {
        return 0;
    }
}

bool blockToBeRemoved(block b, int Yval) {
    return b.y1==Yval;
}

void checkAllLines(spaces& array) {

    for (int i = 0; i<18; ++i) {
        int lineFull = checkOneLine(array, i);
        if (lineFull) {
            //printSpaces(array);
            //cout<<""<<endl;
            for (int l = 0; l<10; ++l) {
                array[l][i] = 0;
            }
            int del = i-1;
            while (del>1) {
                for (int x = 0; x<10; ++x) {
                    int sq = array[x][del];
                    if (sq==1) {
                        array[x][del] = 0;
                        if (del<18) {
                        array[x][del+1] = 1;
                        }
                    }
                }
                --del;
            }
            int yEquiv = (i*28)+10;
            auto condition = [yEquiv](block b) {
                return b.y1 == yEquiv;
            };
            auto new_end = std::remove_if(all_blocks.begin(), all_blocks.end(), condition);
            all_blocks.erase(new_end, all_blocks.end());
            std::vector<block> new_all_blocks;
            for (block b: all_blocks) {
                if (b.y1<yEquiv) {
                    block b2 = b;
                    b2.moveSingle();
                    new_all_blocks.push_back(b2);
                } else {
                    new_all_blocks.push_back(b);
                }
            }
            all_blocks = new_all_blocks;
            //printSpaces(array);

        }
        }
    }
int drawActiveBlock(int currentblock ,SDL_Renderer *rend) {
    switch (currentblock) {
        case 1:
            all_LR_blocks[all_LR_blocks.size()-1].draw(rend);
            break;
        case 2:
            all_LL_blocks[all_LL_blocks.size()-1].draw(rend);
            break;
        case 3:
            all_S_blocks[all_S_blocks.size()-1].draw(rend);
            break;
        case 4:
            all_Z_blocks[all_Z_blocks.size()-1].draw(rend);
            break;
        case 5:
            all_O_blocks[all_O_blocks.size()-1].draw(rend);
            break;
        case 6: 
            all_I_blocks[all_I_blocks.size()-1].draw(rend);
            break;
        case 7:
            all_T_blocks[all_T_blocks.size()-1].draw(rend);
            break;
        ;
    }
    return 0;
}
void activeToStop(spaces& array, block b) {
    BLOCKtoblock(b);
    setSpaces(array, b.x1, b.y1);
    setSpaces(array, b.x2, b.y2);
    setSpaces(array, b.x3, b.y3);
    setSpaces(array, b.x4, b.y4);
}//std::vector<std::array<int, 2>> taken_spaces;
int moveActiveBlock(int currentblock) {
    switch (currentblock) {
        case 1:
            all_LR_blocks[all_LR_blocks.size()-1].moveDown();
            break;
        case 2:
            all_LL_blocks[all_LL_blocks.size()-1].moveDown();
            break;
        case 3:
            all_S_blocks[all_S_blocks.size()-1].moveDown();
            break;
        case 4:
            all_Z_blocks[all_Z_blocks.size()-1].moveDown();
            break;
        case 5:
            all_O_blocks[all_O_blocks.size()-1].moveDown();
            break;
        case 6: 
            all_I_blocks[all_I_blocks.size()-1].moveDown();
            break;
        case 7:
            all_T_blocks[all_T_blocks.size()-1].moveDown();
            break;
        ;
    }
    return 0;
}
int LeftActiveBlock(spaces& array, int currentblock) {
    switch (currentblock) {
        case 1:
            all_LR_blocks[all_LR_blocks.size()-1].moveToLeft(array);
            break;
        case 2:
            all_LL_blocks[all_LL_blocks.size()-1].moveToLeft(array);
            break;
        case 3:
            all_S_blocks[all_S_blocks.size()-1].moveToLeft(array);
            break;
        case 4:
            all_Z_blocks[all_Z_blocks.size()-1].moveToLeft(array);
            break;
        case 5:
            all_O_blocks[all_O_blocks.size()-1].moveToLeft(array);
            break;
        case 6: 
            all_I_blocks[all_I_blocks.size()-1].moveToLeft(array);
            break;
        case 7:
            all_T_blocks[all_T_blocks.size()-1].moveToLeft(array);
            break;
        ;
    }
    return 0;
}
int RightActiveBlock(spaces& array, int currentblock) {
    switch (currentblock) {
        case 1:
            all_LR_blocks[all_LR_blocks.size()-1].moveToRight(array);
            break;
        case 2:
            all_LL_blocks[all_LL_blocks.size()-1].moveToRight(array);
            break;
        case 3:
            all_S_blocks[all_S_blocks.size()-1].moveToRight(array);
            break;
        case 4:
            all_Z_blocks[all_Z_blocks.size()-1].moveToRight(array);
            break;
        case 5:
            all_O_blocks[all_O_blocks.size()-1].moveToRight(array);
            break;
        case 6: 
            all_I_blocks[all_I_blocks.size()-1].moveToRight(array);
            break;
        case 7:
            all_T_blocks[all_T_blocks.size()-1].moveToRight(array);
            break;
        ;
    }
    return 0;
}

int rotateActiveBlock(spaces& array, int currentblock) {
    switch (currentblock) {
        case 1:
            all_LR_blocks[all_LR_blocks.size()-1].rotate();
            break;
        case 2:
            all_LL_blocks[all_LL_blocks.size()-1].rotate();
            break;
        case 3:
            all_S_blocks[all_S_blocks.size()-1].rotate();
            break;
        case 4:
            all_Z_blocks[all_Z_blocks.size()-1].rotate();
            break;
        case 5:
            all_O_blocks[all_O_blocks.size()-1].rotate();
            break;
        case 6: 
            all_I_blocks[all_I_blocks.size()-1].rotate();
            break;
        case 7:
            all_T_blocks[all_T_blocks.size()-1].rotate();
            break;
        ;
    }
    return 0;
}

int checkActiveBlock(spaces& array, int currentblock) {
    int stopFlag = 0;
    switch (currentblock) {
        case 1:
            stopFlag = checkblockpos(array, all_LR_blocks[all_LR_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_LR_blocks[all_LR_blocks.size()-1].checkpos();
                if (stopFlag) {
                    all_LR_blocks[all_LR_blocks.size()-1].stopblock();
                    activeToStop(array, all_LR_blocks[all_LR_blocks.size()-1]);
                }
            } else {
                activeToStop(array, all_LR_blocks[all_LR_blocks.size()-1]);
            }
            break;
        case 2:
            stopFlag = checkblockpos(array, all_LL_blocks[all_LL_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_LL_blocks[all_LL_blocks.size()-1].checkpos();
                if (stopFlag) {all_LL_blocks[all_LL_blocks.size()-1].stopblock();
                    activeToStop(array, all_LL_blocks[all_LL_blocks.size()-1]);
                }
            } else {
                activeToStop(array, all_LL_blocks[all_LL_blocks.size()-1]);
            }

            break;
        case 3:
            stopFlag = checkblockpos(array, all_S_blocks[all_S_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_S_blocks[all_S_blocks.size()-1].checkpos();
                if (stopFlag) {
                    all_S_blocks[all_S_blocks.size()-1].stopblock();
                    activeToStop(array, all_S_blocks[all_S_blocks.size()-1]);
                }
            } else {
                activeToStop(array, all_S_blocks[all_S_blocks.size()-1]);
            }
            break;
        case 4:
            stopFlag = checkblockpos(array, all_Z_blocks[all_Z_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_Z_blocks[all_Z_blocks.size()-1].checkpos();
                if (stopFlag) {
                    all_Z_blocks[all_Z_blocks.size()-1].stopblock();
                    activeToStop(array, all_Z_blocks[all_Z_blocks.size()-1]);
                }
            } else {
                activeToStop(array, all_Z_blocks[all_Z_blocks.size()-1]);
            }
            break;
        case 5:
            stopFlag = checkblockpos(array, all_O_blocks[all_O_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_O_blocks[all_O_blocks.size()-1].checkpos();
                if (stopFlag) {
                    all_O_blocks[all_O_blocks.size()-1].stopblock();
                    activeToStop(array, all_O_blocks[all_O_blocks.size()-1]);
                }
            } else {
                activeToStop(array, all_O_blocks[all_O_blocks.size()-1]);
            }
            break;
        case 6: 
            stopFlag = checkblockpos(array, all_I_blocks[all_I_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_I_blocks[all_I_blocks.size()-1].checkpos();
                if (stopFlag) {
                    all_I_blocks[all_I_blocks.size()-1].stopblock();
                    activeToStop(array, all_I_blocks[all_I_blocks.size()-1]);
                }
            } else {
                activeToStop(array, all_I_blocks[all_I_blocks.size()-1]);
            }
            break;
        case 7:
            stopFlag = checkblockpos(array, all_T_blocks[all_T_blocks.size()-1]);
            if (!stopFlag) {
                stopFlag = all_T_blocks[all_T_blocks.size()-1].checkpos();
                if (stopFlag) {
                    all_T_blocks[all_T_blocks.size()-1].stopblock();
                    activeToStop(array, all_T_blocks[all_T_blocks.size()-1]);}
            } else {
                activeToStop(array, all_T_blocks[all_T_blocks.size()-1]);
            }
            break;
        ;
    }
    return stopFlag;
}
void drawAllblocks(SDL_Renderer *rend) {
    for (block b : all_blocks) {
        b.drawSingle(rend);
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
    //Iblock first = Iblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);
    //Sblock second = Sblock((WIDTH / 2 - BOARD_WIDTH / 2), 10);

    //first.EstablishNS();
    //first.EstablishNorth();
    //second.EstablishWest();
    //second.EstablishEast();
    //second.EstablishWest();
    //firstL.EstablishSouth();

    SDL_Rect board = { (WIDTH / 2 - BOARD_WIDTH / 2), 10, BOARD_WIDTH, BOARD_HEIGHT };
    Uint32 lastMoveTime = 0;
    Uint32 lastMoveTime2 = 0;



    SDL_Event windowEvent;

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type)
            {
                break;
            }

    //const Uint8* keystate = SDL_GetKeyboardState(NULL);
    //more work to be done on this^^^
    //continuous-response keys
            
            if (windowEvent.type == SDL_KEYDOWN)
            {
                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        //second.moveToLeft(SPACES);
                        LeftActiveBlock(SPACES, currentBlock);
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_UP:
                         rotateActiveBlock(SPACES, currentBlock);
                        break;
                    case SDLK_RIGHT:
                        //second.moveToRight(SPACES);
                        RightActiveBlock(SPACES, currentBlock);
                        break;
                }
            }
            
        }
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_DOWN]) {
            //std::cout << "Down arrow key is pressed" << std::endl;
            MOVE_INTERVAL = 50;
            SHIFT_INTERVAL = MOVE_INTERVAL/2;
        } else {
            MOVE_INTERVAL = initial_MI;
            SHIFT_INTERVAL = MOVE_INTERVAL/2;
        }
        Uint32 currentTime = SDL_GetTicks();
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

        if (movetime) {
            if (start) {
                if (!GameOverFlag) {
                    nextBlock = randomBlockSelect();
                    addToActiveBlocks(nextBlock);
                    currentBlock = nextBlock;
                    start = false;
                }
            } else {
                stoppingFlag = checkActiveBlock(SPACES, currentBlock);
                GameOverFlag = checkTopLvl(SPACES);
                if (stoppingFlag) {
                    start = true;
                }
        }
        if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
            moveActiveBlock(currentBlock);
            lastMoveTime = currentTime;
            lastMoveTime2 = lastMoveTime;
            movetime = false;
            }
        
        } else {
            if (currentTime - lastMoveTime2 >= SHIFT_INTERVAL) {
            lastMoveTime2 = currentTime;
            lastMoveTime = lastMoveTime2;
            movetime = true;
            }
        }
        checkAllLines(SPACES);
        drawActiveBlock(currentBlock, renderer);
        drawAllblocks(renderer);
        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //
        /*
       if (start) {
                if (!GameOverFlag) {
                    nextBlock = randomBlockSelect();
                    addToActiveBlocks(nextBlock);
                    currentBlock = nextBlock;
                    start = false;
                    drawActiveBlock(currentBlock, renderer);
                }
            } else {
                drawActiveBlock(currentBlock, renderer);
                stoppingFlag = checkActiveBlock(SPACES, currentBlock);
                GameOverFlag = checkTopLvl(SPACES);
                if (stoppingFlag) {
                    start = true;
                }
        }
        if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
            moveActiveBlock(currentBlock);
            lastMoveTime = currentTime;
        }

        checkAllLines(SPACES);
        drawAllblocks(renderer);
        */
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}