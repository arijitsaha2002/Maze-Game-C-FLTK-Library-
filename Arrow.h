#ifndef ARROW_H
#define ARROW_H

#ifndef POLAR_H
#include "Polar.h"
#endif

/**
 * @brief      This class describes an arrow for gravity.
 */
class Arrow : public Fl_Widget {
	Polar P; /// gravity vector
	double length; /// length of the arrow
public:

	/**
	 * @brief      Constructs a new instance.
	 *
	 * @param[in]  angle  default position
	 */
	Arrow(double angle = -90) : Fl_Widget(0, 0, Window_W, Window_H) {
		this->P.setAngle(angle);
		this->length = ArrowLenght;
	}

	/**
	 * @brief      Draws a line.
	 *
	 * @param[in]  color  color of the line
	 */
	void drawLine(int color) {
		P.setRadius(length+R3);
		double x = P.getX(), y = P.getY();
		P.setRadius(R3);
		double x_ = P.getX(), y_ = P.getY();
        fl_color(color);
        fl_line(x,y,x_, y_);
	}

	/**
	 * @brief      draw the arrow
	 */
	void draw() {
		drawLine(lineColor);
	}
	
	/**
	 * @brief      Sets the angle and redraw the arrow
	 *
	 * @param[in]  angle  new angle
	 */
	void setAngle(double angle){
		drawLine(backgroundColor);
		P.setAngle(angle);
		redraw();
	}

	/**
	 * @brief      Gets the gravity vector.
	 *
	 * @return     Polar of arrow
	 */
	Polar getP(){
		return P;
	}
	
	/**
	 * @brief      Sets the angle and redraw the arrow
	 *
	 * @param[in]  x     The new value
	 * @param[in]  y     The new value
	 */
	void setAngle(double x, double y){
		drawLine(backgroundColor);
		P.setFromPoint(x, y);
		redraw();
	}
};
#endif
