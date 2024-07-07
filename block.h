#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
using namespace std;
using std::cout;
using std::endl;


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
    int rotation;// 1 = north, 2 = east, 3 = south, 4 = west
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
    int randest() {
        srand (time(NULL));
        int dir = rand() % 4 + 1;
        return dir;
    }

    void setType(int t) {
        type = t;
    }
    void setRot(int r) {
        rotation = r;
    }
    void innerBoxCol(SDL_Renderer *rend, int type) {
        switch (type) {
            case 1:
                 SDL_SetRenderDrawColor(rend, 153, 76, 0, 255);
                 break;
            case 2:
                SDL_SetRenderDrawColor(rend, 0, 204, 204, 255);
                break;
            case 3:
                SDL_SetRenderDrawColor(rend, 178, 255, 102, 255);
                break;
            case 4:
                 SDL_SetRenderDrawColor(rend, 255, 51, 255, 255);
                 break;
            case 5:
                 SDL_SetRenderDrawColor(rend, 255, 51, 51, 255);
                 break;
            case 6:
                SDL_SetRenderDrawColor(rend, 255, 153, 51, 255);
                break;
            case 7:
                 SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
                 break;
        }
    }
    int* findLeftX() {
        static int result[2];
        result[0] = x1;
        result[1] = y1;
        if (x2 < result[0]) 
        {
            result[0] = x2;
            result[1] = y2;
        }
        if (x3 < result[0]) 
        {
            result[0] = x3;
            result[1] = y3;
        }
        if (x4 < result[0]) {
            {
            result[0] = x4;
            result[1] = y4;
        }
        }
        return result;
    };
    int* findRightX()  {
        static int result[2];
        result[0] = x1;
        result[1] = y1;
        if (x2 > result[0]) 
        {
            result[0] = x2;
            result[1] = y2;
        }
        if (x3 > result[0]) 
        {
            result[0] = x3;
            result[1] = y3;
        }
        if (x4 > result[0]) {
            {
            result[0] = x4;
            result[1] = y4;
        }
        }
        return result;
    };
//Needs to updated for complex blocks
    void moveToRight(spaces& array) {
        int rightX = ((findRightX()[0]-160)/28);
        int rightY = ((findRightX()[1]-10)/28);
        if (array[rightX+1][rightY]!=1) {
            if (rightX<9) {
                x1+=dim;
                x2+=dim;
                x3+=dim;
                x4+=dim;
            }
        }
    }
//Needs to updated for complex blocks
    void moveToLeft(spaces& array) {
        int leftX = (findLeftX()[0]-160)/28;
        int leftY = ((findLeftX()[1]-10)/28);
        if (array[leftX-1][leftY]!=1) {
            if (leftX>0) {
                x1-=dim;
                x2-=dim;
                x3-=dim;
                x4-=dim;
            }
        }
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
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        if (y1>=10) {
        SDL_Rect A = {x1, y1, dim, dim};
        SDL_Rect E = {x1+1, y1+1, 26, 26};
        SDL_RenderFillRect(rend, &A);
        innerBoxCol(rend, type);
        SDL_RenderFillRect(rend, &E);
        } 
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        if (y2>=10) {
        SDL_Rect B = {x2, y2, dim, dim};
        SDL_Rect F = {x2+1, y2+1, 26, 26};
        SDL_RenderFillRect(rend, &B);
        innerBoxCol(rend, type);
        SDL_RenderFillRect(rend, &F);
        } 
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        if (y3>=10) {
        SDL_Rect C = {x3, y3, dim, dim};
        SDL_Rect G = {x3+1, y3+1, 26, 26};
        SDL_RenderFillRect(rend, &C);
        innerBoxCol(rend, type);
        SDL_RenderFillRect(rend, &G);
        } 
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        if (y4>=10) {
        SDL_Rect D = {x4, y4, dim, dim};
        SDL_Rect H = {x4+1, y4+1, 26, 26};
        SDL_RenderFillRect(rend, &D);
        innerBoxCol(rend, type);
        SDL_RenderFillRect(rend, &H);
        } 
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
        setRot(1);
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
        setRot(2);
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
        setRot(4);
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
        setRot(3);
    }
    void Establish() {
        int dir = randest();
        switch (dir) {
            case 1:
                EstablishNorth();
                break;
            case 2:
                EstablishEast();
                break;
            case 3:
                EstablishSouth();
                break;
            case 4:
                EstablishWest();
                break;
        }
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
    void Establish() {
        int dir = randest();
        switch (dir) {
            case 1:
                EstablishNorth();
                break;
            case 2:
                EstablishEast();
                break;
            case 3:
                EstablishSouth();
                break;
            case 4:
                EstablishWest();
                break;
        }
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
        setRot(4);
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
        setRot(2);
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
        setRot(1);
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
        setRot(3);
    }

    void Establish() {
        int dir = randest();
        switch (dir) {
            case 1:
                EstablishNorth();
                break;
            case 2:
                EstablishEast();
                break;
            case 3:
                EstablishSouth();
                break;
            case 4:
                EstablishWest();
                break;
        }
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
        setRot(4);
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
        setRot(2);
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
        setRot(1);
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
        setRot(3);
    }
    void Establish() {
        int dir = randest();
        switch (dir) {
            case 1:
                EstablishNorth();
                break;
            case 2:
                EstablishEast();
                break;
            case 3:
                EstablishSouth();
                break;
            case 4:
                EstablishWest();
                break;
        }
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
        setRot(4);
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
        setRot(2);
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
        setRot(1);
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
        setRot(3);
    }

    void Establish() {
        int dir = randest();
        switch (dir) {
            case 1:
                EstablishNorth();
                break;
            case 2:
                EstablishEast();
                break;
            case 3:
                EstablishSouth();
                break;
            case 4:
                EstablishWest();
                break;
        }
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
        setRot(1);

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
        setRot(2);
    }

     void Establish() {
        int dir = randest();
        switch (dir) {
            case 1:
                EstablishNS();
                break;
            case 2:
                EstablishEW();
                break;
            case 3:
                EstablishNS();
                break;
            case 4:
                EstablishEW();
                break;
        }
    }
};