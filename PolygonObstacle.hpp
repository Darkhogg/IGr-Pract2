/**
 * @author Daniel Escoz Solana
 */
#ifndef __POLYGON_OBSTACLE__H__
#define __POLYGON_OBSTACLE__H__

#include "skel/skel.h"
#include "Obstacle.hpp"

class PolygonObstacle : public Obstacle {
  private:
    std::vector<Vect> _points;
    
  public:
    PolygonObstacle (const std::vector<Vect>& points) : _points(points) {}

    void draw ();
    bool collide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
};

#endif