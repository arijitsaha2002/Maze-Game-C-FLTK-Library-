#ifndef MOVES_H
#define MOVES_H

#ifndef BALL_H
# include"Ball.h"
#endif

#ifndef ARROW_H
# include"Arrow.h"
#endif

/**
 * @brief    class to guide movement of the Balls
 */
class Move {
	double u;  /// friction coefficient
	double g;  /// gravity
public:
	/**
	 * @brief      Constructs a new instance.
	 *
	 * @param[in]  u     friction coef
	 * @param[in]  g     gravity
	 */
	Move(double u = frictionCoef, double g = gravity) {
		this->u = u;
		this->g = g;
	}

	/**
	 * @brief      find next angular velocity of a Ball
	 *
	 * @param      B     Ball
	 * @param      A     Arrow
	 *
	 * @return     angular velocity
	 */
	double nextPosition(Ball *B, Arrow *A) {
		double angle = B->angleDiff(A->getP());
		if (angle < ERROR && abs(B->getW()) < ERROR) return 0;
		double gsin = g * sin(degreeToRadian * angle);
		if (!B->isLessThan(A->getP())) gsin *= -1;
		double alphaG = gsin / B->getRadius();
		double alphaF = u * g * (abs(B->getW()) > ERROR) / B->getRadius();
		alphaF = alphaF * (2 * signbit(B->getW()) - 1);
		double alpha = alphaG + alphaF;
		return B->getW() + alpha * STEPS;
	}

	/**
	 * @brief      Move the ball if possible
	 *
	 * @param      B1    Ball 1
	 * @param      B2    Ball 2
	 * @param      B3    Ball 3
	 * @param      A     Arrow
	 */
	void Mover(Ball *B1 , Ball *B2 , Ball *B3 , Arrow *A) {
		if (canMove(B1, B2, A) and canMove(B1, B3, A)) nextMove(B1, A);
		if (canMove(B2, B1, A) and canMove(B2, B3, A)) nextMove(B2, A);
		if (canMove(B3, B2, A) and canMove(B3, B1, A)) nextMove(B3, A);
	}

	/**
	 * @brief      move the ball
	 *
	 * @param      B     Ball
	 * @param      A     Arrow
	 */
	void nextMove(Ball *B, Arrow *A) {
		B->setW(nextPosition(B, A));
		B->setAngle(B->getW()*STEPS + B->getAngle());
		changeRadius(B, A);
	}

	/**
	 * @brief      if collision happens then exchanges the velocities of balls
	 *
	 * @param      B1    Ball 1
	 * @param      B2    Ball 2
	 */
	void Exchange(Ball *B1, Ball *B2) {
		double temp = B1->getW();
		B1->setW(B2->getW());
		B2->setW(temp);
	}

	/**
	 * @brief      Determines ability to move.
	 *
	 * @param      B1    Ball 1
	 * @param      B2    Ball 2
	 * @param      A     Arrow
	 *
	 * @return     True if able to move, False otherwise.
	 */
	bool canMove(Ball *B1, Ball *B2, Arrow *A) {
		Polar P1 = Polar(nextPosition(B1, A) * STEPS + B1->getAngle(), B1->getRadius());
		Polar P2 = Polar(nextPosition(B2, A) * STEPS + B2->getAngle(), B2->getRadius());
		if (P1.distance(&P2) <= 2 * ballRadius) {
			if (!B1->isLessThan(*B2)) {
				B1->setAngle(B1->getAngle() + .5);
				B2->setAngle(B2->getAngle() - .5);
			}
			else {
				B1->setAngle(B1->getAngle() - .5);
				B2->setAngle(B2->getAngle() + .5);
			}
			Exchange(B1, B2);
			return false;
		}
		return true;
	}

	/**
	 * @brief      moves the ball in or out of maze
	 *
	 * @param      B     Ball
	 * @param      A     Arrow
	 */
	void changeRadius(Ball *B, Arrow *A) {
		if (B->getR() == R3) {
			if (B->angleDiff(angle2) < permissibleAngleDiff and B->angleDiff(A->getP()) > permissibleAngleI) {
				B->changeRadius(R2);
			}
		}
		else if (B->getR() == R2) {
			if (B->angleDiff(angle1) < permissibleAngleDiff and B->angleDiff(A->getP()) > permissibleAngleI) {
				B->changeRadius(R1);
			}
			else if (B->angleDiff(angle2) < permissibleAngleDiff and B->angleDiff(A->getP()) < permissibleAngleO) {
				B->changeRadius(R3);
			}
		}
		else if (B->getR() == R1) {
			if (B->angleDiff(angle0) < permissibleAngleDiff and B->angleDiff(A->getP()) > permissibleAngleI) {
				B->changeRadius(R0);
			}
			else if (B->angleDiff(angle1) < permissibleAngleDiff and B->angleDiff(A->getP()) < permissibleAngleO) {
				B->changeRadius(R2);
			}
		}
		else if (B->getR() == R0) {
			if (B->angleDiff(angle0) < permissibleAngleDiff and B->angleDiff(A->getP()) < permissibleAngleO) {
				B->changeRadius(R1);
			}
		}
	}
};
#endif