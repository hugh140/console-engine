#include <iostream>

class Window {
public:
  int width, height;
  char **screen;

  Window(int width, int height) {
    this->width = width;
    this->height = height;
    setScreen();
  }

  void updateSize(int width, int height) {
    if (width == this->width && height == this->height)
      return;

    this->width = width;
    this->height = height;

    delete[] screen;
    setScreen();
  }

  void setCellValue(int x, int y, char value) {
    if (x <= this->width && y <= this->height - 1)
      screen[y - 1][x - 1] = value;
  }

  void draw() {
    for (int h = 0; h <= this->height - 2; h++) {
      for (int w = 0; w < this->width; w++)
        std::cout << screen[h][w];
      std::cout << std::endl;
    }
  }

  ~Window() {
    for (int i = 0; i < height; i++)
      delete[] screen[i];
    delete[] screen;
  }

private:
  void setScreen() {
    screen = new char *[this->height];
    for (int i = 0; i < this->height; i++)
      screen[i] = new char[this->width]();

    for (int i = 0; i < this->height; i++)
      for (int j = 0; j < this->width; j++)
        screen[i][j] = ' ';
  }
};
