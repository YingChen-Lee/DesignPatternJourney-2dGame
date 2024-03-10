#include <iostream>
#include "time.h"

#include "domain/game.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/argv.h"
#include "spdlog/cfg/env.h"

int main(int argc, char *argv[]) {
    // set log level: ref: https://github.com/gabime/spdlog/blob/134f9194bb93072b72b8cfa27ac3bb30a0fb5b57/example/example.cpp
    spdlog::cfg::load_argv_levels(argc, argv);

    srand(time(0));
    Game game(10, 10);
    game.StartRandomGame();

    return 0;
}