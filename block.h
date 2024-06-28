#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class block{
public:
    bool stopped;
    int dim = 28;
    int x1;
    int y1;
    //unused atts
    int highest_y;
    int x2;
    int y2;
    int x3;
    int y3;
    int x4;
    int y4;
    int type;
    using spaces =  int[10][18];
    block(int x_pos, int y_pos, bool stop = false, int t = 0) {
        x1 = x_pos;
        y1 = y_pos;
        x2 = x_pos;
        y2 = y_pos;
        x3 = x_pos;
        y3 = y_pos;
        x4 = x_pos;
        y4 = y_pos;
        stopped = stop;
        type = t;
    }
    void setType(int t) {
        type = t;
    }
    void stopblock() {
        stopped = true;
    }
    int checkpos() {
        if (highest_y+28==392+28*4+10) {
            stopped = true;
            return 1;
        }
        return 0;
    }
    void moveDown() {
        if (!stopped) {
            y1 +=dim;        
            y2 +=dim;
            y3 +=dim;
            y4 +=dim;
            highest_y+=dim;
        }      
    }
    void drawSingle(SDL_Renderer *rend ) {
        SDL_Rect A = {x1, y1, dim, dim};
        SDL_Rect E = {x1+1, y1+1, 26, 26};
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderFillRect(rend, &A);
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderFillRect(rend, &E);
    }

    void draw(SDL_Renderer *rend ) {
        SDL_Rect A = {x1, y1, dim, dim};
        SDL_Rect B = {x2, y2, dim, dim};
        SDL_Rect C = {x3, y3, dim, dim};
        SDL_Rect D = {x4, y4, dim, dim};
        SDL_Rect E = {x1+1, y1+1, 26, 26};
        SDL_Rect F = {x2+1, y2+1, 26, 26};
        SDL_Rect G = {x3+1, y3+1, 26, 26};
        SDL_Rect H = {x4+1, y4+1, 26, 26};
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderFillRect(rend, &A);
        SDL_RenderFillRect(rend, &B);
        SDL_RenderFillRect(rend, &C);
        SDL_RenderFillRect(rend, &D);
        if (type == 1) { //LR Block - Brown
            SDL_SetRenderDrawColor(rend, 153, 76, 0, 255);
        } else if (type == 2) { //LL Block - Blue
            SDL_SetRenderDrawColor(rend, 0, 204, 204, 255);
        } else if (type == 3) { //S Block - Green
            SDL_SetRenderDrawColor(rend, 178, 255, 102, 255);
        } else if (type == 4) { //Z Block - Pink
            SDL_SetRenderDrawColor(rend, 255, 51, 255, 255);
        } else if (type == 5) { //O Block - Red
            SDL_SetRenderDrawColor(rend, 255, 51, 51, 255);
        } else if (type == 6) { //I Block - Orange
            SDL_SetRenderDrawColor(rend, 255, 153, 51, 255);
        } else if (type == 7) { //T Block - White
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        }
        SDL_RenderFillRect(rend, &E);
        SDL_RenderFillRect(rend, &F);
        SDL_RenderFillRect(rend, &G);
        SDL_RenderFillRect(rend, &H);
    }
};

class Tblock: public block {
  public:
    Tblock(int x, int y) : block(x, y) {}
    void EstablishNorth() {
        x1 = x1+dim*5;
        y1 = 10;
        x2 = x1-dim;
        y2 = 10+dim;
        x3 = x1;
        y3 = 10+dim;
        x4 = x3+dim;
        y4 = 10+dim;
        highest_y = y4;
        setType(7);
    }
    void EstablishEast() {
        x1 = x1+dim*6;
        y1 = 10;
        x2 = x1-dim;
        y2 = 10-dim;
        x3 = x2;
        y3 = 10;
        x4 = x3;
        y4 = 10+dim;
        highest_y = y4;
        setType(7);
    }
    void EstablishWest() {
        x1 = x1+dim*6;
        y1 = 10;
        x2 = x1+dim;
        y2 = 10-dim;
        x3 = x2;
        y3 = 10;
        x4 = x3;
        y4 = 10+dim;
        highest_y = y2;
        setType(7);
    }
    void EstablishSouth() {
        x1 = x1+dim*5;
        y1 = 10+dim;
        x2 = x1+dim;
        y2 = 10;
        x3 = x1;
        y3 = 10;
        x4 = x3-dim;
        y4 = 10;
        highest_y = y1;
        setType(7);
    }

    //You could probably combine
    // the below functions by establishing 
    // a boolean param passed in (8 to 4 methods)
    void EasttoSouthArrange(bool clockwise) {
        // south to east
        if(clockwise) {
            x1-=dim;
            y1+=dim; 
            x2 = x2;
            y2 = y2;
            x3 += dim;
            y3 -= dim;
            x4 += 2*dim; 
            y4 = y4;
            highest_y = y1;
        } 
        //south to east
        else {
            x1+=dim;
            y1-=dim; 
            x2 = x2;
            y2 = y2;
            x3 -= dim;
            y3 += dim;
            x4 -= 2*dim; 
            y4 = y4;
            highest_y = y1;
        }
    }
    void NorthtoEastArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1=x1;
            y1+=2*dim; 
            x2 -= dim;
            y2 += dim;
            x3 -= 2*dim;
            y3 = y3;
            x4 -= dim; 
            y4 -= dim;
            highest_y = y1;
        } 
        //east to north
        else {
            x1=x1;
            y1-=2*dim; 
            x2 += dim;
            y2 -= dim;
            x3 += 2*dim;
            y3 = y3;
            x4 += dim; 
            y4 += dim;
            highest_y = y4;
        }
    }
    void WesttoNorthArrange(bool clockwise) {
        // north to east
        if(clockwise) {
            x1+=2*dim;
            y1-=dim; 
            x2 += dim;
            y2 = y2;
            x3 = x3;
            y3 += dim;
            x4 -= dim; 
            y4 = y4;
            highest_y = y4;
        } 
        //east to north
        else {
            x1-=2*dim;
            y1+=dim; 
            x2 -= dim;
            y2 = y2;
            x3 = x3;
            y3 -= dim;
            x4 += dim; 
            y4 = y4;
            highest_y = y4;
        }
    }
    void SouthtoWestArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1-=dim;
            y1-=2*dim; 
            x2 = x2;
            y2 -= dim;
            x3 += dim;
            y3 = y3;
            x4 = x4; 
            y4 += dim;
            highest_y = y4;
        } 
        //east to north
        else {
            x1+=dim;
            y1+=2*dim; 
            x2 = x2;
            y2 += dim;
            x3 -= dim;
            y3 = y3;
            x4 = x4; 
            y4 -= dim;
            highest_y = y1;
        }
    }
};

class LRblock: public block {
  public:
    LRblock(int x, int y) : block(x, y) {}
    void EstablishWest() {
        x1 = x1+dim*4;
        y1 = 10;
        x2 = x1+dim;
        y2 = 10;
        x3 = x2+dim;
        y3 = 10;
        x4 = x3;
        y4 = y3-dim;
        highest_y = y3;
        setType(1);
    }
    void EstablishEast() {
        x1 = x1+dim*6;
        y1 = 10;
        x2 = x1-dim;
        y2 = 10;
        x3 = x2-dim;
        y3 = 10;
        x4 = x3;
        y4 = y3+dim;
        highest_y = y4;
        setType(1);
    }
    void EstablishNorth() {
        x1 = x1+dim*5;
        y1 = 10-2*dim;
        x2 = x1;
        y2 = 10-1*dim;
        x3 = x2;
        y3 = 10;
        x4 = x3+dim;
        y4 = 10;
        highest_y = y4;
        setType(1);
    }
    void EstablishSouth() {
        x1 = x1+dim*4;
        y1 = 10;
        x2 = x1;
        y2 = 10-dim;
        x3 = x2;
        y3 = 10-2*dim;
        x4 = x3-dim;
        y4 = y3;
        highest_y = y1;
        setType(1);
    }

    //You could probably combine
    // the below functions by establishing 
    // a boolean param passed in (8 to 4 methods)
    void EasttoSouthArrange(bool clockwise) {
        // south to east
        if(clockwise) {
            x1-=dim;
            y1+=dim; 
            x2 = x2;
            y2 = y2;
            x3 += dim;
            y3 -= dim;
            x4 += 2*dim; 
            y4 = y4;
            highest_y = y1;
        } 
        //south to east
        else {
            x1+=dim;
            y1-=dim; 
            x2 = x2;
            y2 = y2;
            x3 -= dim;
            y3 += dim;
            x4 -= 2*dim; 
            y4 = y4;
            highest_y = y1;
        }
    }
    void NorthtoEastArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1=x1;
            y1+=2*dim; 
            x2 -= dim;
            y2 += dim;
            x3 -= 2*dim;
            y3 = y3;
            x4 -= dim; 
            y4 -= dim;
            highest_y = y1;
        } 
        //east to north
        else {
            x1=x1;
            y1-=2*dim; 
            x2 += dim;
            y2 -= dim;
            x3 += 2*dim;
            y3 = y3;
            x4 += dim; 
            y4 += dim;
            highest_y = y4;
        }
    }
    void WesttoNorthArrange(bool clockwise) {
        // north to east
        if(clockwise) {
            x1+=2*dim;
            y1-=dim; 
            x2 += dim;
            y2 = y2;
            x3 = x3;
            y3 += dim;
            x4 -= dim; 
            y4 = y4;
            highest_y = y4;
        } 
        //east to north
        else {
            x1-=2*dim;
            y1+=dim; 
            x2 -= dim;
            y2 = y2;
            x3 = x3;
            y3 -= dim;
            x4 += dim; 
            y4 = y4;
            highest_y = y4;
        }
    }
    void SouthtoWestArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1-=dim;
            y1-=2*dim; 
            x2 = x2;
            y2 -= dim;
            x3 += dim;
            y3 = y3;
            x4 = x4; 
            y4 += dim;
            highest_y = y4;
        } 
        //east to north
        else {
            x1+=dim;
            y1+=2*dim; 
            x2 = x2;
            y2 += dim;
            x3 -= dim;
            y3 = y3;
            x4 = x4; 
            y4 -= dim;
            highest_y = y1;
        }
    }
};

class LLblock: public block {

  public:
    LLblock(int x, int y) : block(x, y) {}
    void EstablishWest() {
        x1 = x1+dim*4;
        y1 = 10;
        x2 = x1+dim;
        y2 = 10;
        x3 = x2+dim;
        y3 = 10;
        x4 = x3;
        y4 = y3+dim;
        highest_y = y4;
        setType(2);
    }
    void EstablishEast() {
        x1 = x1+dim*6;
        y1 = 10;
        x2 = x1-dim;
        y2 = 10;
        x3 = x2-dim;
        y3 = 10;
        x4 = x3;
        y4 = y3-dim;
        highest_y = y1;
        setType(2);
    }
    void EstablishNorth() {
        x1 = x1+dim*5;
        y1 = 10-2*dim;
        x2 = x1;
        y2 = 10-1*dim;
        x3 = x2;
        y3 = 10;
        x4 = x3-dim;
        y4 = 10;
        highest_y = y4;
        setType(2);
    }
    void EstablishSouth() {
        x1 = x1+dim*4;
        y1 = 10;
        x2 = x1;
        y2 = 10-dim;
        x3 = x2;
        y3 = 10-2*dim;
        x4 = x3+dim;
        y4 = y3;
        highest_y = y1;
        setType(2);
    }

    //You could probably combine
    // the below functions by establishing 
    // a boolean param passed in (8 to 4 methods)
    void EasttoSouthArrange(bool clockwise) {
        // south to east
        if(clockwise) {
            x1-=dim;
            y1+=dim; 
            x2 = x2;
            y2 = y2;
            x3 += dim;
            y3 -= dim;
            x4 += 2*dim; 
            y4 = y4;
            highest_y = y1;
        } 
        //south to east
        else {
            x1+=dim;
            y1-=dim; 
            x2 = x2;
            y2 = y2;
            x3 -= dim;
            y3 += dim;
            x4 -= 2*dim; 
            y4 = y4;
            highest_y = y1;
        }
    }
    void NorthtoEastArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1=x1;
            y1+=2*dim; 
            x2 -= dim;
            y2 += dim;
            x3 -= 2*dim;
            y3 = y3;
            x4 -= dim; 
            y4 -= dim;
            highest_y = y1;
        } 
        //east to north
        else {
            x1=x1;
            y1-=2*dim; 
            x2 += dim;
            y2 -= dim;
            x3 += 2*dim;
            y3 = y3;
            x4 += dim; 
            y4 += dim;
            highest_y = y4;
        }
    }
    void WesttoNorthArrange(bool clockwise) {
        // north to east
        if(clockwise) {
            x1+=2*dim;
            y1-=dim; 
            x2 += dim;
            y2 = y2;
            x3 = x3;
            y3 += dim;
            x4 -= dim; 
            y4 = y4;
            highest_y = y4;
        } 
        //east to north
        else {
            x1-=2*dim;
            y1+=dim; 
            x2 -= dim;
            y2 = y2;
            x3 = x3;
            y3 -= dim;
            x4 += dim; 
            y4 = y4;
            highest_y = y4;
        }
    }
    void SouthtoWestArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1-=dim;
            y1-=2*dim; 
            x2 = x2;
            y2 -= dim;
            x3 += dim;
            y3 = y3;
            x4 = x4; 
            y4 += dim;
            highest_y = y4;
        } 
        //east to north
        else {
            x1+=dim;
            y1+=2*dim; 
            x2 = x2;
            y2 += dim;
            x3 -= dim;
            y3 = y3;
            x4 = x4; 
            y4 -= dim;
            highest_y = y1;
        }
    }
};

class Sblock: public block {

  public:
    Sblock(int x, int y) : block(x, y) {}
    void EstablishWest() {
        x1 = x1+dim*5;
        y1 = 10;
        x2 = x1+dim;
        y2 = 10;
        x3 = x2;
        y3 = 10-dim;
        x4 = x2+dim;
        y4 = y3;
        highest_y = y1;
        setType(3);
    }
    void EstablishEast() {
        x1 = x1+dim*6;
        y1 = 10-dim;
        x2 = x1-dim;
        y2 = 10-dim;
        x3 = x2;
        y3 = 10;
        x4 = x3-dim;
        y4 = 10;
        highest_y = y4;
        setType(3);
    }
    void EstablishNorth() {
        x1 = x1+dim*4;
        y1 = 10-dim;
        x2 = x1;
        y2 = 10;
        x3 = x2+dim;
        y3 = 10;
        x4 = x3;
        y4 = 10+dim;
        highest_y = y4;
        setType(3);
    }
    void EstablishSouth() {
        x1 = x1+dim*6;
        y1 = 10+dim;
        x2 = x1;
        y2 = 10;
        x3 = x2-dim;
        y3 = 10;
        x4 = x3;
        y4 = y3-dim;
        highest_y = y1;
        setType(3);
    }

    //You could probably combine
    // the below functions by establishing 
    // a boolean param passed in (8 to 4 methods)
    void EasttoSouthArrange(bool clockwise) {
        // south to east
        if(clockwise) {
            x1-=dim;
            y1+=dim; 
            x2 = x2;
            y2 = y2;
            x3 += dim;
            y3 -= dim;
            x4 += 2*dim; 
            y4 = y4;
            highest_y = y1;
        } 
        //south to east
        else {
            x1+=dim;
            y1-=dim; 
            x2 = x2;
            y2 = y2;
            x3 -= dim;
            y3 += dim;
            x4 -= 2*dim; 
            y4 = y4;
            highest_y = y1;
        }
    }
    void NorthtoEastArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1=x1;
            y1+=2*dim; 
            x2 -= dim;
            y2 += dim;
            x3 -= 2*dim;
            y3 = y3;
            x4 -= dim; 
            y4 -= dim;
            highest_y = y1;
        } 
        //east to north
        else {
            x1=x1;
            y1-=2*dim; 
            x2 += dim;
            y2 -= dim;
            x3 += 2*dim;
            y3 = y3;
            x4 += dim; 
            y4 += dim;
            highest_y = y4;
        }
    }
    void WesttoNorthArrange(bool clockwise) {
        // north to east
        if(clockwise) {
            x1+=2*dim;
            y1-=dim; 
            x2 += dim;
            y2 = y2;
            x3 = x3;
            y3 += dim;
            x4 -= dim; 
            y4 = y4;
            highest_y = y4;
        } 
        //east to north
        else {
            x1-=2*dim;
            y1+=dim; 
            x2 -= dim;
            y2 = y2;
            x3 = x3;
            y3 -= dim;
            x4 += dim; 
            y4 = y4;
            highest_y = y4;
        }
    }
    void SouthtoWestArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1-=dim;
            y1-=2*dim; 
            x2 = x2;
            y2 -= dim;
            x3 += dim;
            y3 = y3;
            x4 = x4; 
            y4 += dim;
            highest_y = y4;
        } 
        //east to north
        else {
            x1+=dim;
            y1+=2*dim; 
            x2 = x2;
            y2 += dim;
            x3 -= dim;
            y3 = y3;
            x4 = x4; 
            y4 -= dim;
            highest_y = y1;
        }
    }
};

class Zblock: public block {

  public:
    Zblock(int x, int y) : block(x, y) {}
    void EstablishWest() {
        x1 = x1+dim*5;
        y1 = 10-dim;
        x2 = x1+dim;
        y2 = y1;
        x3 = x2;
        y3 = 10;
        x4 = x3+dim;
        y4 = 10;
        highest_y = y4;
        setType(4);
    }
    void EstablishEast() {
        x1 = x1+dim*6;
        y1 = 10;
        x2 = x1-dim;
        y2 = y1;
        x3 = x2;
        y3 = 10-dim;
        x4 = x3-dim;
        y4 = y3;
        highest_y = y1;
        setType(4);
    }
    void EstablishNorth() {
        x1 = x1+dim*5;
        y1 = 10-dim;
        x2 = x1;
        y2 = 10;
        x3 = x2-dim;
        y3 = 10;
        x4 = x3;
        y4 = 10+dim;
        highest_y = y4;
        setType(4);
    }
    void EstablishSouth() {
        x1 = x1+dim*5;
        y1 = 10+dim;
        x2 = x1;
        y2 = 10;
        x3 = x2+dim;
        y3 = 10;
        x4 = x3;
        y4 = y3-dim;
        highest_y = y1;
        setType(4);
    }

    //You could probably combine
    // the below functions by establishing 
    // a boolean param passed in (8 to 4 methods)
    void EasttoSouthArrange(bool clockwise) {
        // south to east
        if(clockwise) {
            x1-=dim;
            y1+=dim; 
            x2 = x2;
            y2 = y2;
            x3 += dim;
            y3 -= dim;
            x4 += 2*dim; 
            y4 = y4;
            highest_y = y1;
        } 
        //south to east
        else {
            x1+=dim;
            y1-=dim; 
            x2 = x2;
            y2 = y2;
            x3 -= dim;
            y3 += dim;
            x4 -= 2*dim; 
            y4 = y4;
            highest_y = y1;
        }
    }
    void NorthtoEastArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1=x1;
            y1+=2*dim; 
            x2 -= dim;
            y2 += dim;
            x3 -= 2*dim;
            y3 = y3;
            x4 -= dim; 
            y4 -= dim;
            highest_y = y1;
        } 
        //east to north
        else {
            x1=x1;
            y1-=2*dim; 
            x2 += dim;
            y2 -= dim;
            x3 += 2*dim;
            y3 = y3;
            x4 += dim; 
            y4 += dim;
            highest_y = y4;
        }
    }
    void WesttoNorthArrange(bool clockwise) {
        // north to east
        if(clockwise) {
            x1+=2*dim;
            y1-=dim; 
            x2 += dim;
            y2 = y2;
            x3 = x3;
            y3 += dim;
            x4 -= dim; 
            y4 = y4;
            highest_y = y4;
        } 
        //east to north
        else {
            x1-=2*dim;
            y1+=dim; 
            x2 -= dim;
            y2 = y2;
            x3 = x3;
            y3 -= dim;
            x4 += dim; 
            y4 = y4;
            highest_y = y4;
        }
    }
    void SouthtoWestArrange(bool clockwise) {
        // north to east
        if(!clockwise) {
            x1-=dim;
            y1-=2*dim; 
            x2 = x2;
            y2 -= dim;
            x3 += dim;
            y3 = y3;
            x4 = x4; 
            y4 += dim;
            highest_y = y4;
        } 
        //east to north
        else {
            x1+=dim;
            y1+=2*dim; 
            x2 = x2;
            y2 += dim;
            x3 -= dim;
            y3 = y3;
            x4 = x4; 
            y4 -= dim;
            highest_y = y1;
        }
    }
};

class Oblock: public block {

  public:
    Oblock(int x, int y) : block(x, y) {}
    void Establish() {
        x1 = x1+dim*5;
        y1 = 10-dim;
        x2 = x1+dim;
        y2 = y1;
        x3 = x2;
        y3 = 10;
        x4 = x1;
        y4 = 10;
        highest_y = y4;
        setType(5);
    }
};

class Iblock: public block {
    public:
    Iblock(int x, int y) : block(x, y) {}
    void EstablishNS() {
        x1 = x1+dim*5;
        y1 = 10-2*dim;
        x2 = x1;
        y2 = 10-dim;
        x3 = x2;
        y3 = 10;
        x4 = x3;
        y4 = 10+dim;
        highest_y = y4;
        setType(6);
    }
    void EstablishEW() {
        x1 = x1+dim*3;
        y1 = 10;
        x2 = x1+dim;
        y2 = 10;
        x3 = x2+dim;
        y3 = 10;
        x4 = x3+dim;
        y4 = 10;
        highest_y = y4;
        setType(6);
    }
};