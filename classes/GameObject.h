#include <string>

class GameObject
{
public:
  long x = 0;
  long y = 0;

  std::string sprite;

  GameObject(long x, long y, std::string sprite)
  {
    this->x = x;
    this->y = y;
    this->sprite = sprite;
  };

  virtual void update() = 0;
  virtual ~GameObject() {}
};