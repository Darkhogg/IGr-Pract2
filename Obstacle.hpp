/**
 * @author Daniel Escoz Solana
 */
#ifndef __OBSTACLE__H__
#define __OBSTACLE__H__

#include "skel/skel.h"
#include "Ball.hpp"

class Ball;

class Obstacle {
  public:
    virtual void draw () = 0;
    virtual bool collide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta) = 0;
};

#endif