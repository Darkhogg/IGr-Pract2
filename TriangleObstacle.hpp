/**
 * @author Daniel Escoz Solana
 */
#ifndef __TRIANGLE_OBSTACLE__H__
#define __TRIANGLE_OBSTACLE__H__

#include "skel/skel.h"
#include "Obstacle.hpp"
#include "PolygonObstacle.hpp"

#include <array>

class TriangleObstacle : public Obstacle {
  private:
    std::array<Vect, 3> _points;
    
  public:
    TriangleObstacle (Vect p1, Vect p2, Vect p3) {
      _points[0] = p1; 
      _points[1] = p2; 
      _points[2] = p3;

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