#ifndef __TRIANGLE_OBSTACLE__H__
#define __TRIANGLE_OBSTACLE__H__

#include "skel/skel.h"
#include "Obstacle.hpp"

class TriangleObstacle : public Obstacle {
  public:
    void draw ();
    bool collide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
};

#endif