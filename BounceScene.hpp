/**
 * @author Daniel Escoz Solana
 */
#ifndef __BOUNCE_SCENE__H__
#define __BOUNCE_SCENE__H__

#include "skel/skel.h"

#include "Ball.hpp"
#include "Obstacle.hpp"

#include <cmath>
#include <vector>

class BounceScene : public Scene {

  private:
    std::vector<Ball> balls;
    std::vector< std::shared_ptr<Obstacle> > obstacles;

    void generateObstacles ();

  public:
    void onInitialize ();
    void onUpdate (float time);
    void onDraw ();
    void onMouseDown (int button);
    void onKeyDown (int code);
    void onResize (int width, int height);
};

#endif