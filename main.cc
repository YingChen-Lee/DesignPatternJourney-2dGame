#include <iostream>
#include "time.h"

#include "domain/game.h"

int main() {
    srand(time(0));
    Game game(10, 10);
    game.StartRandomGame();

    return 0;
}