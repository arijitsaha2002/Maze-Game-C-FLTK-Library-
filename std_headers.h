#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

/// parameters
const double radianToDegree = (double)180 / M_PI;
const double degreeToRadian = M_PI / (double)180;
const double ballMass = 30;
const double frictionCoef = .2;
const double ERROR = .06;
const double gravity = 2;
const double rotationSpeed = .3;
const double STEPS = 5;
const int permissibleAngleO = 50;
const int permissibleAngleI = 135;
const int permissibleAngleDiff = 10;
const int Window_W = 1000;
const int Window_H = 1000;
const int ArrowLenght = 100;
const int GAP = 80;
const int R0 = 80;
const int R1 = R0 + GAP;
const int R2 = R1 + GAP;
const int R3 = R2 + GAP;
const int thikness = 3;
const int ballColor = 5;
const int lineColor = 6;
const int backgroundColor = 0;
const int ballRadius = 30;
const int boundaryColor = 2;
const int colorText = 14;
double angle0 = 0;
double angle1 = 120;
double angle2 = 240;


/**
 * @brief      Draw the solid arc
 *
 * @param[in]  x      center x
 * @param[in]  y      center y
 * @param[in]  r      Radius
 * @param[in]  color  color
 * @param[in]  a1     angle1
 * @param[in]  a2     angle2
 */
void circle(double x, double y, double r, int color = boundaryColor, int a1 = 0, int a2 = 360) {
	fl_color(color);
	fl_pie(x - r, y - r, 2 * r, 2 * r, a1, a2);
}


/**
 * @brief      Draw the outer circle
 *
 * @param[in]  R   Radius   
 * @param[in]  angle  position of Gap
 */
void circleBig(double R, double angle = 0) {
	double t = (double)GAP / (R * 2 * degreeToRadian);
	circle(Window_W / 2, Window_H / 2, R, backgroundColor, t + angle, 360 - t + angle);
	circle(Window_W / 2, Window_H / 2, R, boundaryColor, t + angle, 360 - t + angle);
	circle(Window_W / 2, Window_H / 2, R - thikness, backgroundColor, t + angle, 360 - t + angle);
}

