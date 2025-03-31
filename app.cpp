#include <chrono>
#include <iostream>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "classes/Key.h"
#include "classes/Window.h"
#include "classes/game-objects/Player.h"

int loop() {
  const short fps = 60;
  const short frameDuration = 1000 / fps;

  std::vector<GameObject *> gameObjects(0);

  Player player(0, 0);
  gameObjects.push_back(&player);
  std::cout << player.sprite << std::endl;

  Window window = Window(0, 0);

  while (true) {
    char key = getchar();

    // Close if pressed ESC
    if (key == Key::ESC)
      break;

    // Get terminal screen size
    auto frameStart = std::chrono::high_resolution_clock::now();
    struct winsize win;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1) {
      std::cerr << "Failed to get terminal size." << std::endl;
      return 1;
    }

    window.updateSize(win.ws_col, win.ws_row);
    window.setCellValue(10, 1, 'A');

    std::cout << "\033[H\033[0J";

    window.draw();

    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                            frameEnd - frameStart)
                            .count();

    if (frameElapsed < frameDuration)
      std::this_thread::sleep_for(
          std::chrono::milliseconds(frameDuration - frameElapsed));
  }

  return 0;
}

int main() {
  Key::setInputMode();
  int status = loop();
  Key::resetInputMode();

  return status;
}
