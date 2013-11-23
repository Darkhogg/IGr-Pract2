#include "SceneObstacle.hpp"

#include <iostream>

bool SceneObstacle::collide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta
) {
  auto dest = pos + spd * delta;

  auto left = _left + rad;
  auto right = _right - rad;
  auto bottom = _bottom + rad;
  auto top = _top - rad;

  bool outLeft = dest.x() < left;
  bool outRight = dest.x() > right;
  bool outBottom = dest.y() < bottom;
  bool outTop = dest.y() > top;

  if (!(outLeft | outRight | outTop | outBottom)) {
    return false;
  }

  float dltLeft = delta * (pos.x() - left) / (pos.x() - dest.x());
  float dltRight = delta * (pos.x() - right) / (pos.x() - dest.x());
  float dltBottom = delta * (pos.y() - bottom) / (pos.y() - dest.y());
  float dltTop = delta * (pos.y() - top) / (pos.y() - dest.y());

  bool hor = outLeft | outRight;
  bool ver = outTop | outBottom;

  if (hor & ver) {
    // Decide which bounces earlier
    float dltHor = std::min(dltLeft, dltRight);
    float dltVer = std::min(dltTop, dltBottom);

    if (dltHor < dltVer) {
      outTop = outBottom = false;
    } else {
      outLeft = outRight = false;
    }
  }

  if (outLeft) {
    outDelta = delta - dltLeft;
    outPos = pos + spd * dltLeft;
    outSpd = Vect(-spd.x(), spd.y());
    return true;

  } else if (outRight) {
    outDelta = delta - dltRight;
    outPos = pos + spd * dltRight;
    outSpd = Vect(-spd.x(), spd.y());
    return true;

  } else if (outTop) {
    outDelta = delta - dltTop;
    outPos = pos + spd * dltTop;
    outSpd = Vect(spd.x(), -spd.y());
    return true;

  } else/* if (outBottom) */{
    outDelta = delta - dltBottom;
    outPos = pos + spd * dltBottom;
    outSpd = Vect(spd.x(), -spd.y());
    return true;
  }
}

void SceneObstacle::draw () {

}