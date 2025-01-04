#include <string>
#include "../GameObject.h"

class Player : public GameObject
{
public:
  Player(long x, long y) : GameObject(x, y, "O") {}

  void update() override {}
};