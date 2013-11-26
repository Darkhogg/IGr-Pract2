/**
 * @author Daniel Escoz Solana
 */
#ifndef __SCENE_OBSTACLE__H__
#define __SCENE_OBSTACLE__H__

#include "skel/skel.h"

#include "Obstacle.hpp"

class SceneObstacle : public Obstacle {
  private:
    Vect::Component _left, _right, _top, _bottom;

  public:
    SceneObstacle (Vect bl, Vect tr)
      : _left(bl.x()), _bottom(bl.y()), _top(tr.y()), _right(tr.x()) {}

    bool collide (
      Vect pos, Vect::Component rad, Vect spd, float delta,
      Vect& outPos, Vect& outSpd, float& outDelta);
    void draw ();
};

#endif