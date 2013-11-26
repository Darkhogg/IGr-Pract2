/**
 * @author Daniel Escoz Solana
 */
#include "Ball.hpp"

#include <cmath>
#include <iostream>

Ball Ball::withRandSpeed (Vect pos, int rad) {
  auto dir = (rand() / (double) RAND_MAX) * M_PI * 2;
  auto mod = (rand() / (double) RAND_MAX) * 150 + 50;
  return Ball(pos, Vect(mod*cos(dir), mod*sin(dir), 0), rad);
}

void Ball::update (float delta) {
  _pos += _dir * delta;
  _dir += _acc * delta;
}

void Ball::draw () const {
  auto radius = std::max((double) MIN_PARTICLE_RADIUS, _rad);
  int points = std::max(6, (int)(radius * 2));
  auto step = 2 * M_PI / points;

  glColor3f(1, 1 ,1);
  glBegin(GL_POLYGON);
  for (int i = 0; i < points; i++) {
    glVertex2f(
      _pos.x() + (radius * cos(i * step)),
      _pos.y() + (radius * sin(i * step))
    );
  }
  glEnd();
}