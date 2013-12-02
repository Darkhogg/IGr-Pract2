/**
 * @author Daniel Escoz Solana
 */
#ifndef __Circle_OBSTACLE__H__
#define __Circle_OBSTACLE__H__

#include "skel/skel.h"
#include "Obstacle.hpp"

class CircleObstacle : public Obstacle {
  private:
    Vect _center;
    Vect::Component _rad;
  
  public:
    CircleObstacle (Vect center, Vect::Component radius) : _center(center), _rad(radius) {
      bb_clear();
      bb_add_point(Vect(center.x() - radius, center.y() - radius));
      bb_add_point(Vect(center.x() + radius, center.y() + radius));
    }

    void draw ();
    bool performCollide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
};

#endif