/**
 * @author Daniel Escoz Solana
 */
#include "BounceScene.hpp"

#include "SceneObstacle.hpp"
#include "CircleObstacle.hpp"
#include "PolygonObstacle.hpp"
#include "TriangleObstacle.hpp"

#include <iostream>
#include <memory>
#include <array>

void BounceScene::onInitialize () {
  setTitle("Bouncing Balls");
  generateObstacles();
}

void BounceScene::onUpdate (float delta) {
  for (auto itb = balls.begin(); itb != balls.end(); ++itb) {
    float rest = delta;
    bool coll = true;

    while (coll) {
      coll = false;
      for (auto ito = obstacles.begin(); ito != obstacles.end(); ++ito) {
        auto pos = itb->pos();
        auto spd = itb->speed();
        auto dlt = rest;

        if ((*ito)->collide(pos, itb->radius(), spd, rest, pos, spd, rest)) {
          itb->update(dlt - rest);
          itb->pos(pos);
          itb->speed(spd);

          coll = (dlt - rest > 0.001f); // Break same-point collisions
        }
      }
    }

    itb->update(rest);
  }
}

void BounceScene::onDraw () {
  for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
    (*it)->draw();
  }
  for (auto it = balls.begin(); it != balls.end(); ++it) {
    it->draw();
  }
}

void BounceScene::onMouseDown (int button) {
  switch (button) {

    /* Left click */
    case MOUSE_LEFT: {
      /* Generate 8 particles moving at random directions and speeds */
      for (auto i = 0; i < 24; i++) {
        balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 0));
      }
    } break;

    /* Left click */
    case MOUSE_CENTER: {
      balls.push_back(Ball(getMouseWorldPosition(), Vect(42, 42), 0));
    } break;

    /* Right click */
    case MOUSE_RIGHT: {
      /** NO BALLS RIGHT NOW */break;
      for (auto i = 0; i < 3; i++) {
        balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 8 + rand() % 8));
      }
    }
  }
}

void BounceScene::onKeyDown (int code) {
  switch (code) {
    case KEY_SPACE: {
      if (isPaused()) {
        resume();
      } else {
        pause();
      }
    } break;

    case KEY_R: {
      balls.clear();
      obstacles.clear();
      generateObstacles();
    } break;



    case KEY_1: {
      tick(0.010f);
    } break;

    case KEY_2: {
      tick(0.050f);
    } break;

    case KEY_3: {
      tick(0.100f);
    } break;

    case KEY_4: {
      tick(0.250f);
    } break;



    case KEY_Q: {
      for (auto i = 0; i < 10000; i++) {
        balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 0));
      }
    } break;

    case KEY_W: {
      for (auto i = 0; i < 000; i++) {
        balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 10));
      }
    } break;



    case KEY_Z: {
      for (auto it = balls.begin(); it != balls.end(); ++it) {
        it->acc(Vect(0, -200, 0));
      }
    } break;

    case KEY_X: {
      for (auto it = balls.begin(); it != balls.end(); ++it) {
        it->acc(Vect(0, 0, 0));
      }
    } break;
  }
}

void BounceScene::generateObstacles () {
  obstacles.clear();

  auto view = cam().view(width(), height());
  auto sceneObst = std::make_shared<SceneObstacle>(
    Vect(view.left, view.bottom), Vect(view.right, view.top));
  obstacles.push_back(sceneObst);

  /* Polygons */
  auto rMin = M_PI/8;
  auto rMax = M_PI/2;
  for (int i = 0; i < 0; i++) {
    auto r = 20 + (rand() % 60);
    auto x = view.left + r + (rand() % (width() - 2*r));
    auto y = view.bottom + r + (rand() % (height() - 2*r));

    auto aMin = rand() / (double) RAND_MAX * rMin;
    auto ang = aMin;

    std::vector<Vect> points;
    while (ang < 2*M_PI - rMin + aMin) {
      points.push_back(Vect(x + r * cos(ang), y + r * sin(ang)));
      ang += rMin + ((rand() / (double) RAND_MAX) * (rMax-rMin));
    }

    auto polyObst = std::make_shared<PolygonObstacle>(points);
    obstacles.push_back(polyObst);
  }

  /* Circles */
  for (int i = 0; i < 3; i++) {
    auto r = (rand() % 30) + 20;
    auto x = view.left + r + (rand() % (width() - 2*r));
    auto y = view.bottom + r + (rand() % (height() - 2*r));
    auto circleObst = std::make_shared<CircleObstacle>(Vect(x, y), r);
    obstacles.push_back(circleObst);
  }

  /* Triangles */
  for (int i = 0; i < 3; i++) {
    auto r = (rand() % 50) + 40;
    auto x = view.left + r + (rand() % (width() - 2*r));
    auto y = view.bottom + r + (rand() % (height() - 2*r));

    std::array<Vect, 3> pts;

    std::vector<Vect> points;
    auto ai = (2*M_PI/3) * (rand() / (double) RAND_MAX);
    for (auto i = 0; i < 3; i++) {
      auto ang = ai + i * (2*M_PI/3)
        + 0.5 + ((2*M_PI/3 - 1) * (rand() / (double) RAND_MAX));
      pts[i] = Vect(x + r * cos(ang), y + r * sin(ang));
    }

    auto triObst = std::make_shared<TriangleObstacle>(pts[0], pts[1], pts[2]);
    obstacles.push_back(triObst);
  }

}

void BounceScene::onResize (int width, int height) {
  if (obstacles.size() >= 1) {
    auto view = cam().view(width, height);
    auto sceneObst = std::make_shared<SceneObstacle>(
      Vect(view.left, view.bottom), Vect(view.right, view.top));

    obstacles[0] = sceneObst;
  }
}