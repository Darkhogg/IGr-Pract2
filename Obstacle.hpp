/**
 * @author Daniel Escoz Solana
 */
#ifndef __OBSTACLE__H__
#define __OBSTACLE__H__

#include "skel/skel.h"
#include "Ball.hpp"

#include <iostream>

class Ball;

class Obstacle {
  private:
    Vect::Component _top;
    Vect::Component _left;
    Vect::Component _right;
    Vect::Component _bottom;

  protected:
    Obstacle () : _left(1), _right(-1) {}

    void bb_clear();
    void bb_add_point(Vect point);
    bool bb_inside(Vect pos, Vect::Component padding);
    void bb_draw();

  public:
    virtual void draw () { /*bb_draw();*/ }
    virtual bool performCollide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta) = 0;

    virtual bool collide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
};

#endif