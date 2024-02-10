#include "map_object/treasure.h"

// static
std::unique_ptr<Treasure> Treasure::Create(Position position) {
  return std::make_unique<Treasure>(position);
}