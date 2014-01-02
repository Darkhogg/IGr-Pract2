/**
 * @author Daniel Escoz Solana
 */
#ifndef __ELLIPSE_OBSTACLE__H__
#define __ELLIPSE_OBSTACLE__H__

#include "skel/skel.h"
#include "Obstacle.hpp"

class EllipseObstacle : public Obstacle {
  private:
    Vect _center;
    Vect::Component _rx, _ry;
  
  public:
    EllipseObstacle (Vect center, Vect::Component rx, Vect::Component ry) : _center(center), _rx(rx), _ry(ry) {
      bb_clear();
      bb_add_point(Vect(center.x() - rx, center.y() - ry, 1.f));
      bb_add_point(Vect(center.x() + rx, center.y() + ry, 1.f));
    }

    void draw ();
    bool performCollide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta, Vect& norm);
};

#endif