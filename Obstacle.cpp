/**
 * @author Daniel Escoz Solana
 */
#include "Obstacle.hpp"

void Obstacle::bb_clear () {
  _left = 1;
  _right = -1;
}

void Obstacle::bb_add_point(Vect point) {
  if (_left > _right) {
    _left = _right = point.x();
    _top = _bottom = point.y();
  }

  _left = std::min(_left, point.x() - 3);
  _right = std::max(_right, point.x() + 3);
  _top = std::max(_top, point.y() + 3);
  _bottom = std::min(_bottom, point.y() - 3);
}

bool Obstacle::bb_inside (Vect pos, Vect::Component padding) {
  if (_left > _right) {
    // No bounding box defined
    return true;
  }

  return pos.x() > _left - padding
      && pos.x() < _right + padding
      && pos.y() > _bottom - padding
      && pos.y() < _top + padding;
}

void Obstacle::bb_draw () {
  if (_left < _right) {
    glLineWidth(1);
    glColor3f(.5f, .5f, .5f);
    glBegin(GL_LINE_LOOP);
      glVertex2f(_left, _bottom);
      glVertex2f(_right, _bottom);
      glVertex2f(_right, _top);
      glVertex2f(_left, _top);
    glEnd();
  }
}

bool Obstacle::collide (Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta)
{
  if (!bb_inside(pos, rad + spd.mod() * delta)) {
    return false;
  }

  return performCollide(pos, rad, spd, delta, outPos, outSpd, outDelta);
}