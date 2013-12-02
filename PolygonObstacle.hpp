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
    
    PolygonObstacle inflate (Vect::Component size);
    
  public:
    PolygonObstacle (const std::vector<Vect>& points) : _points(points) {
      bb_clear();
      for (auto it = _points.begin(); it != _points.end(); ++it) {
        bb_add_point(*it);
      }
    }

    void draw ();
    bool performCollide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
};

#endif