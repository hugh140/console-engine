#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

class Key
{
public:
  static void setInputMode()
  {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
  }

  static void resetInputMode()
  {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }
};

int main()
{
  Key::setInputMode();

  const short fps = 60;
  const short frameDuration = 1000 / fps;
  int counter = 0;

  while (true)
  {
    char key = getchar();
    if (key == 27) break;

    auto frameStart = std::chrono::high_resolution_clock::now();
    struct winsize win;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1)
    {
      std::cerr << "Failed to get terminal size." << std::endl;
      return 1;
    }

    std::cout << "\033[H\033[0J";

    std::string str_separator = "";
    for (int width = 0; width < win.ws_row; width++)
      for (int height = 0; height < win.ws_col; height++)
        str_separator += key;
    std::cout << str_separator << std::endl;

    std::cout << "Counter: " << counter++ << std::endl;

    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

    if (frameElapsed < frameDuration)
      std::this_thread::sleep_for(std::chrono::milliseconds(frameDuration - frameElapsed));
  }

  Key::resetInputMode();
  return 0;
}
