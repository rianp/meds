#include "MeditationTimer.hpp"

int main()
{
  sf::RenderWindow window;
  MeditationTimer meditationTimer(window);
  meditationTimer.run();

  return 0;
}
