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

enum Mode {
    M_BALLS, M_OBSTACLE
};

class BounceScene : public Scene {

  private:
    std::vector<Ball> balls;
    std::vector< std::shared_ptr<Obstacle> > obstacles;

    Mode mode;
    std::vector<Vect> points;

    void generateObstacles ();
    bool checkPolyValidity ();

  public:
    void onInitialize ();
    void onUpdate (float time);
    void onDraw ();
    void onMouseDown (int button);
    void onMouseMove (int x, int y);
    void onKeyDown (int code);
    void onKeyUp (int code);
    void onResize (int width, int height);
};

#endif