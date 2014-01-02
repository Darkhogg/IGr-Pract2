/**
 * @author Daniel Escoz Solana
 */
#include "EllipseObstacle.hpp"
#include "CircleObstacle.hpp"
#include "Matr.hpp"

#include <iostream>

void EllipseObstacle::draw () {
  Obstacle::draw();

  auto r = std::max(_rx, _ry);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated(_center.x(), _center.y(), 0.f);
  glScaled(_rx/r, _ry/r, 1.f);

  CircleObstacle co {Vect(0.f, 0.f, 1.f), r};
  co.draw();

  glPopMatrix();
}

bool EllipseObstacle::performCollide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta, Vect& norm
) {
  Matr mScale = Matr::scale(1.f/_rx, 1.f/_ry);
  Matr mTrans = Matr::translate(-_center.x(), -_center.y());

  Vect tPos = pos * mTrans * mScale;
  Vect tSpd = spd * mScale;

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

  norm = mScale.transposed() * norm;

  Matr muScale = Matr::scale(_rx, _ry);
  Matr muTrans = Matr::translate(_center.x(), _center.y());

  outPos = tOutPos * muScale * muTrans;
  outSpd = spd - norm.project(spd) * 2;

  return true;
}