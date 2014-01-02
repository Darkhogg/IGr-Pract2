/**
 * @author Daniel Escoz Solana
 */
#include "BounceScene.hpp"

#include "SceneObstacle.hpp"
#include "CircleObstacle.hpp"
#include "PolygonObstacle.hpp"
#include "TriangleObstacle.hpp"
#include "EllipseObstacle.hpp"

#include <iostream>
#include <memory>
#include <array>

void BounceScene::onInitialize () {
  setTitle("Bouncing Balls");
  generateObstacles();

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  mode = M_BALLS;
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

          itb->collided();

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

  if (mode == M_OBSTACLE && points.size() > 0) {
    glLineWidth(3);
    glColor3f(.8f, .8f, .8f);
    glBegin(GL_LINE_STRIP);
    for (auto it = points.begin(); it != points.end(); it++) {
      glVertex2f(it->x(), it->y());
    }
    glEnd();

    auto mv = getMouseWorldPosition();
    auto fst = points.front();
    auto lst = points.back();

    if (points.size() > 1) {

      // Check validity
      if (checkPolyValidity()) {
        glColor3f(.2f, .6f, .2f);
      } else {
        glColor3f(.6f, .2f, .2f);
      }

      glLineWidth(2);
      glBegin(GL_LINE_STRIP);
      glVertex2f(fst.x(), fst.y());
      glVertex2f(mv.x(), mv.y());
      glVertex2f(lst.x(), lst.y());
      glEnd();

    } else {
      glLineWidth(2);
      glColor3f(.2f, .6f, .2f);
      glBegin(GL_LINE_STRIP);
      glVertex2f(fst.x(), fst.y());
      glVertex2f(mv.x(), mv.y());
      glEnd();

      auto center = (points[0] + mv) / 2;
      auto radius = (points[0] - center).mod();
      int pnum = std::max(6, (int)(radius * 3));
      auto step = 2 * M_PI / pnum;

      glColor3f(.3f, .3f, .3f);
      glBegin(GL_LINE_LOOP);
        for (int i = 0; i < pnum; i++) {
          glVertex2f(
            center.x() + (radius * cos(i * step)),
            center.y() + (radius * sin(i * step))
          );
        }
      glEnd();
    }
  }
}

void BounceScene::onMouseDown (int button) {

  switch (button) {

    /* Left click */
    case MOUSE_LEFT: {
      /* Generate 8 particles moving at random directions and speeds */
      if (mode == M_BALLS) {  
        for (auto i = 0; i < 24; i++) {
          balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 0));
        }
      } else {
        if (checkPolyValidity()) {
          points.push_back(getMouseWorldPosition());
        }
      }
    } break;

    /* Left click */
    case MOUSE_CENTER: {
      if (mode == M_BALLS) {
        balls.push_back(Ball(getMouseWorldPosition(), Vect(42, 42, 0.f), 16));
      }
    } break;

    /* Right click */
    case MOUSE_RIGHT: {
      if (mode == M_BALLS) {
        for (auto i = 0; i < 3; i++) {
          balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 4 + rand() % 8));
        }
      } else {
        if (checkPolyValidity()) {
          points.push_back(getMouseWorldPosition());
          if (points.size() == 2) {
            // Create a circle
            auto center = (points[0] + points[1]) / 2;
            auto radius = (center - points[0]).mod();
            auto circleObst = std::make_shared<CircleObstacle>(center, radius);
            obstacles.push_back(circleObst);

          } else if (points.size() == 3) {
            // Create a triangle
            auto triObst = std::make_shared<TriangleObstacle>(points[0], points[1], points[2]);
            obstacles.push_back(triObst);

          } else if (points.size() > 3) {
            // Create a polygon
            auto polyObst = std::make_shared<PolygonObstacle>(points);
            obstacles.push_back(polyObst);
          }
          points.clear();
        }
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
    } break;

    case KEY_T: {
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
      for (auto i = 0; i < 1000; i++) {
        balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 0));
      }
    } break;

    case KEY_W: {
      for (auto i = 0; i < 1000; i++) {
        balls.push_back(Ball::withRandSpeed(getMouseWorldPosition(), 4 + rand() % 8));
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


    case KEY_RCTRL:
    case KEY_LCTRL: {
      points.clear();
      mode = M_OBSTACLE;
    } break;
  }
}

void BounceScene::onKeyUp(int code) {
  switch (code) {
    case KEY_RCTRL:
    case KEY_LCTRL: {
      mode = M_BALLS;
      points.clear();
    } break;
  }
}

void BounceScene::generateObstacles () {
  obstacles.clear();

  auto view = cam().view(width(), height());
  auto sceneObst = std::make_shared<SceneObstacle>(
    Vect(view.left, view.bottom, 1.f), Vect(view.right, view.top, 1.f));
  obstacles.push_back(sceneObst);

  auto ellipseObst = std::make_shared<EllipseObstacle>(
    Vect(20, 20, 1.f), 100, 50);
  obstacles.push_back(ellipseObst);
}

void BounceScene::onResize (int width, int height) {
  if (obstacles.size() >= 1) {
    auto view = cam().view(width, height);
    auto sceneObst = std::make_shared<SceneObstacle>(
      Vect(view.left, view.bottom, 1.f), Vect(view.right, view.top, 1.f));

    obstacles[0] = sceneObst;
  }
}

void BounceScene::onMouseMove (int x, int y) {

}

bool BounceScene::checkPolyValidity () {
  if (points.size() < 2) {
    return true;
  }

  auto mv = getMouseWorldPosition();

  auto vec = points;
  vec.push_back(mv);

  Vect pct;
  for (size_t i = 1; i < vec.size(); ++i) {
    pct += vec[i];
  }
  pct /= vec.size();

  auto p = (vec[0] - vec[1]).perp_left_z0().dot(vec[0] - vec[2]);

  for (size_t i = 1; i < vec.size(); ++i) {
    auto j = (i + 1) % vec.size();
    auto k = (j + 1) % vec.size();

    auto pp = (vec[i] - vec[j]).perp_left_z0().dot(vec[i] - vec[k]);

    if (pp <= 0) {
      return false;
    }
  }

  return true;
}