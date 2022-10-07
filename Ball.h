#ifndef BALL_H
#define BALL_H

#ifndef POLAR_H
#include "Polar.h"
#endif

/**
 * @brief      This class describes a ball.
 *          this is child of Polar and Fl_Widget
 */
class Ball : public Fl_Widget , public Polar {
    double  radius; /// radius of the Ball
    double R;       /// Radius of Outer Circle
    double W;       /// angular velocity of Ball
    int Color;      /// color of Ball
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  R      Radius of Outer Circle 
     * @param[in]  angle  angle of position vector 
     * @param[in]  Color  color of the Ball
     */
    Ball(double R = R0, double angle = 0, int Color = ballColor) : Fl_Widget(0, 0, Window_W, Window_H),
        Polar(angle, R - GAP / 2) {
        this->radius = ballRadius;
        this->W = 0;
        this->R = R;
        this->Color = Color;
    }

    /**
     * @brief      draw a Ball on canvas
     */
    void draw() {
        createCircle(Color);
    }

    /**
     * @brief      remove the Ball from canvas
     */
    void wipe() {
        createCircle(backgroundColor);
    }

    /**
     * @brief      changes the Radius of Outer Circle 
     *
     * @param[in]  R    
     */
    void changeRadius(double R) {
        this->R = R;
        setRadius(R - GAP / 2);
    }

    /**
     * @brief      Determines whether the specified b is collide.
     *
     * @param      B     Ball
     *
     * @return     True if the specified b is collide, False otherwise.
     */
    bool isCollide(Ball *B) {
        return (distance(B) < (2 * ballRadius));
    }

    /**
     * @brief      Sets the w.
     *
     * @param[in]  W     The new value
     */
    void setW(double W) {
        this->W = W;
    }

    /**
     * @brief      Sets the angle and draw ball at new position     *           
     *
     * @param[in]  a     The new value
     */
    void setAngle(double a) {
        wipe();
        Polar::setAngle(a);
        redraw();
    }

    /**
     * @brief      Gets the angular velocity.
     *
     * @return     angular velocity.
     */
    double getW() {
        return W;
    }

    /**
     * @brief      Gets the Radius of outer Circle.
     *
     * @return     Radius
     */
    double getR() {
        return R;
    }
};
#endif