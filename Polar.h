#ifndef POLAR_H
#define POLAR_H

#ifndef STD_HEADER_H
#include "std_headers.h"
#endif

/**
 * @brief      Describes Polar coordinate representation of a Point.
 */
class Polar {
	double angle; /// angle
	double radius; /// radius
	double centerX; /// center x
	double centerY; /// center y
public:
	/**
	 * @brief      Constructs a new instance.
	 *
	 * @param[in]  angle    The angle
	 * @param[in]  radius   The radius
	 * @param[in]  centerX  The center x
	 * @param[in]  centerY  The center y
	 */
	Polar(double angle = 270, double radius = R0, double centerX = Window_W / 2, double centerY = Window_H / 2) {
		this->angle = makeStandard(angle);
		this->radius = radius;
		this->centerX = centerX;
		this->centerY = centerY;
	}
	/**
	 * @brief      validates the angle
	 *
	 * @param[in]  a     angle
	 *
	 * @return     valid angle
	 */
	double makeStandard(double a) {
		if (a < 0) return 360 - fmod(-a, 360);
		return fmod(a, 360);
	}

	/**
	 * @brief      Calculate difference between Angles
	 *
	 * @param[in]  P     Second Polar argument
	 *
	 * @return     difference ( >= 0 and <= 180 )
	 */
	double angleDiff(Polar P) {
		double a = makeStandard(angle - P.angle);
		if (a > 180) return 360 - a;
		return a;
	}

	/**
	 * @brief      Calculate difference between Angles
	 *
	 * @param[in]  angle second angle
	 *
	 * @return     difference ( >= 0 and <= 180 )
	 */
	double angleDiff(double angle) {
		double a = makeStandard(this->angle - angle);
		if (a > 180) return 360 - a;
		return a;
	}

	/**
	 * @brief      Gets the x coordinate.
	 *
	 * @return     x.
	 */
	double getX() {
		return (centerX + radius * cos(degreeToRadian * angle));
	}

	/**
	 * @brief      Gets the y coordinate.
	 *
	 * @return     y.
	 */
	double getY() {
		return (centerY - radius * sin(degreeToRadian * angle));
	}

	/**
	 * @brief      Gets the angle.
	 *
	 * @return     angle
	 */
	double getAngle() {
		return angle;
	}

	/**
	 * @brief      Gets the radius.
	 *
	 * @return     radius.
	 */
	double getRadius() {
		return radius;
	}

	/**
	 * @brief      Sets the angle.
	 *
	 * @param[in]  a     The new value
	 */
	void setAngle(double a) {
		angle = makeStandard(a);
	}

	/**
	 * @brief      Sets the radius.
	 *
	 * @param[in]  radius  new radius
	 */
	void setRadius(double radius) {
		this->radius = radius;
	}

	/**
	 * @brief      Creates a circle at it's position
	 *
	 * @param[in]  color  color of the circle
	 */
	void createCircle(int color) {
		circle(getX(), getY(), ballRadius, color);
	}

	/**
	 * @brief      distance between two Polar
	 *
	 * @param      P     second Polar
	 *
	 * @return     { description_of_the_return_value }
	 */
	double distance(Polar *P) {
		double dX = (getX() - P->getX());
		double dY = (getY() - P->getY());
		return sqrt(dX * dX + dY * dY);
	}

	/**
	 * @brief      Sets the from point.
	 *
	 * @param[in]  x     x
	 * @param[in]  y     y
	 */	
	void setFromPoint(double x, double y) {
		setAngle(atan2(centerY - y, x - centerX) * radianToDegree);
	}

	/**
	 * @brief      Determines whether the specified p is less than this.
	 *
	 * @param[in]  P    argument
	 *
	 * @return     True if the specified p is less than, False otherwise.
	 */
	bool isLessThan(Polar P) {
		P.setAngle(P.getAngle() - getAngle());
		return P.getAngle() <= 180;
	}
};

#endif