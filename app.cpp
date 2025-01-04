#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>

#include "classes/Key.h"
#include "classes/game-objects/Player.h"

int main()
{
  Key::setInputMode();

  const short fps = 60;
  const short frameDuration = 1000 / fps;

  std::vector<GameObject *> gameObjects(0);

  Player player(0, 0);
  gameObjects.push_back(&player);
  std::cout << player.sprite << std::endl;

  while (true)
  {
    char key = getchar();

    // Close if pressed ESC
    if (key == Key::ESC)
      break;

    // Get terminal screen size
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
    {
      for (int height = 0; height < win.ws_col; height++)
      {
        std::cout << str_separator;
      }
    }
    std::cout << str_separator << std::endl;

    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

    if (frameElapsed < frameDuration)
      std::this_thread::sleep_for(std::chrono::milliseconds(frameDuration - frameElapsed));
  }

  Key::resetInputMode();
  return 0;
}
