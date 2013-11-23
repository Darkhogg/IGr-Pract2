#ifndef __Circle_OBSTACLE__H__
#define __Circle_OBSTACLE__H__

#include "skel/skel.h"
#include "Obstacle.hpp"

class CircleObstacle : public Obstacle {
  private:
    Vect _center;
    Vect::Component _rad;
  
  public:
    CircleObstacle (Vect center, Vect::Component radius) : _center(center), _rad(radius) {}

    void draw ();
    bool collide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
};

#endif