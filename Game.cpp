# include"Moves.h"
# include"Arrow.h"

/**
 * @brief      This class describes a game.
 */
class Game : public Fl_Widget {
    Ball *B1; /// Ball 1
    Ball *B2; /// Ball 2
    Ball *B3; /// Ball 3
    Move *M;  /// mover
    Arrow *A; /// arrow

public:

    /**
     * @brief      Constructs a new instance.
     */
    Game() : Fl_Widget(0, 0, Window_W, Window_H) {
        B1 = new Ball(R1, 0, 7);
        B2 = new Ball(R2, -90, 5);
        B3 = new Ball(R3, 180, 4);
        M = new Move;
        A = new Arrow;
        double rotationSpeed = 0;
    }

    /**
     * @brief      draw all outer circles
     */
    void draw() {
        initial();
    }

    /**
     * @brief      initializes the maze
     */
    void initial() {
        circleBig(R3, 0);
        circleBig(R3, 180);
        circleBig(R2, angle2);
        circleBig(R1, angle1);
        circleBig(R0, angle0);
    }

    /**
     * @brief      takes inputs from mouse
     *
     * @param[in]  e     event
     *
     * @return     0
     */
    int handle(int e) {
        if (e == FL_PUSH) A->setAngle(Fl::event_x(), Fl::event_y());
        return 0;
    }

    /**
     * @brief      check whether the game ended or not
     *
     * @return     false if not ended and true otherwise
     */
    bool check() {
        if (B1->getR() == R0 && B2->getR() == R0 && B3->getR() == R0) {
            fl_color(colorText);
            fl_font(FL_COURIER, 50);
            fl_draw("!! CONGRATULATION !!", Window_W / 4, Window_H / 9);
            return true;
        }
        return false;
    }

    /**
     * @brief      rotate the maze and update user interface
     */
    void refresh() {
        redraw();
        angle2 = fmod((angle2 + rotationSpeed), 360);
        angle1 = fmod((angle1 + rotationSpeed), 360);
        angle0 = fmod((angle0 + rotationSpeed), 360);
        M->Mover(B1, B2, B3 , A);
    }
};


/**
 * @brief      call refresh after every .01 second 
 *             if game is not ended
 *
 * @param      a     Game object
 */
void Update(void *a) {
    if (((Game *)a)->check()) return;
    ((Game *)a)->refresh();
    Fl::repeat_timeout(.01, Update, a);
}


int main() {
    srand(time(0));
    Fl_Window w(Window_W, Window_H, "GAME"); /// create a new window
    w.color(backgroundColor); /// set background color
    Game G; /// create a game object
    Fl::repeat_timeout(.2, Update, &G);
    w.show();
    return Fl::run();
}
