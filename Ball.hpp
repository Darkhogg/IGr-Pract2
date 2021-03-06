/**
 * @author Daniel Escoz Solana
 */
#ifndef __BALL__H__
#define __BALL__H__

#include "skel/skel.h"
#include "Obstacle.hpp"
#include <memory>

class Ball {
  private:

    Vect _pos, _dir, _acc;
    Vect::Component _rad;
    Vect::Component _ang, _angspd;

  public:
    static const int MIN_PARTICLE_RADIUS = 2; 

    Ball (Vect pos, Vect dir, Vect::Component rad)
        : _pos(pos), _dir(dir), _rad(rad), _ang(0), _angspd(90) {}
    virtual ~Ball () {}

    void collided () {
        _angspd = -_angspd;
    }

    void update (float delta);
    void draw () const;

    Vect pos () const { return _pos; }
    Vect speed () const { return _dir; }
    Vect acc () const { return _acc; }
    Vect::Component radius () const { return _rad; }

    void pos (const Vect& pos) { _pos = pos; }
    void speed (const Vect& spd) { _dir = spd; }
    void acc (const Vect& acc) { _acc = acc; }

    static Ball withRandSpeed (Vect pos, int rad);
};

#endif