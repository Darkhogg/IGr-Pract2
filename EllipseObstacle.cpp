/**
 * @author Daniel Escoz Solana
 */
#include "EllipseObstacle.hpp"
#include "CircleObstacle.hpp"
#include "Matr.hpp"

#include <iostream>
#include <cmath>

void EllipseObstacle::draw () {
  Obstacle::draw();

  auto r = std::max(_rx, _ry);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated(_center.x(), _center.y(), 0.d);
  glRotated(_ang * 180.d / M_PI, 0.d, 0.d, 1.d);
  glScaled(_rx/r, _ry/r, 1.d);

  CircleObstacle co {Vect(0.f, 0.f, 1.f), r};
  co.draw();

  glPopMatrix();
}

bool EllipseObstacle::performCollide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta, Vect& norm
) {
  if (rad > Ball::MIN_PARTICLE_RADIUS) {
    EllipseObstacle el {_center, _rx+rad, _ry+rad, _ang};
    return el.collide(pos, 0, spd, delta, outPos, outSpd, outDelta);
  }

  Matr mScale = Matr::scale(1.f/_rx, 1.f/_ry);
  Matr mTrans = Matr::translate(-_center.x(), -_center.y());
  Matr mRot = Matr::rotate(_ang);

  Vect tPos = pos * mTrans * mRot * mScale;
  Vect tSpd = spd * mRot * mScale;

  CircleObstacle co {Vect(0.f, 0.f, 1.f), 1.f};

  Vect tOutPos, tOutSpd;
  bool coll = co.performCollide(
    tPos, rad, tSpd, delta,
    tOutPos, tOutSpd, outDelta,
    norm
  );

  if (!coll) {
    return false;
  }

  norm = (mScale * mRot).transposed() * norm;

  Matr muScale = Matr::scale(_rx, _ry);
  Matr muTrans = Matr::translate(_center.x(), _center.y());
  Matr muRot = Matr::rotate(-_ang);

  outPos = tOutPos * muScale * muRot * muTrans;
  outSpd = spd - norm.project(spd) * 2;

  return true;
}