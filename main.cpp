/**
 * @author Daniel Escoz Solana
 */
#include <memory>

#include "skel/skel.h"
#include "BounceScene.hpp"

int main (int argc, char** argv) {
    std::unique_ptr<Scene> scene (new BounceScene());
    return scene->run();
}