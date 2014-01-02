/**
 * @author Daniel Escoz Solana
 */
#include <memory>
#include <iostream>

#include "skel/skel.h"
#include "BounceScene.hpp"
#include "Matr.hpp"

int main (int argc, char** argv) {
    std::unique_ptr<Scene> scene (new BounceScene());
    return scene->run();
}