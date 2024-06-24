class block{
public:
    bool stopped;
    int dim = 28;
    int x;
    int y;
    block(int x_pos, int y_pos, bool stop = false) {
        x = x_pos;
        y = y_pos;
        stopped = stop;
    }
    void stopblock() {
        stopped = true;
    }
};

class Lblock: public block {
  public:
    int highest_y;
    int x_b2;
    int y_b2;
    int x_b3;
    int y_b3;
    int x_b4;
    int y_b4;
    Lblock(int x, int y) : block(x, y) {}
    void EstablishWest() {
        x = x+28*3;
        y = 10;
        x_b2 = x+28;
        y_b2 = y;
        x_b3 = x+56;
        y_b3 = y;
        x_b4 = x_b3;
        y_b4 = y+28;
        highest_y = y+28;
    }
    void EstablishEast() {
        x = x+28*4;
        y = 10;
        x_b2 = x+28;
        y_b2 = y;
        x_b3 = x+56;
        y_b3 = y;
        x_b4 = x;
        y_b4 = y-28;
        highest_y = y_b4+28;
    }
    void EstablishNorth() {
        x = x+28*4;
        y = 10;
        x_b2 = x+28;
        y_b2 = y;
        x_b3 = x+28;
        y_b3 = y-28;
        x_b4 = x+28;
        y_b4 = y-56;
        highest_y = y+28;
    }
    void EstablishSouth() {
        x = x+28*4;
        y = 10;
        x_b2 = x+28;
        y_b2 = y;
        x_b3 = x;
        y_b3 = y+28;
        x_b4 = x;
        y_b4 = y+56;
        highest_y = y_b4+28;
    }
    /*
    //You could probably combine
    // the below functions by establishing 
    // a boolean param passed in (8 to 4 methods)
    void EasttoSouthArrange() {
        x = 
        y = 
        x_b2 =
        y_b2 =
        x_b3 =
        y_b3 =
        x_b4 =
        y_b4 =
    }
    void NorthtoEastArrange() {
        x = 
        y = 
        x_b2 =
        y_b2 =
        x_b3 =
        y_b3 =
        x_b4 =
        y_b4 =
    }
    void WesttoNorthArrange() {
        x = 
        y = 
        x_b2 =
        y_b2 =
        x_b3 =
        y_b3 =
        x_b4 =
        y_b4 =
    }
    void SouthtoWestArrange() {
        x = 
        y = 
        x_b2 =
        y_b2 =
        x_b3 =
        y_b3 =
        x_b4 =
        y_b4 =
    }
    */
};