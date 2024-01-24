#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

class MeditationTimer
{
public:
  MeditationTimer(sf::RenderWindow &window);

  void run();

private:
  sf::RenderWindow &window;
  sf::Font font;
  sf::Text text;
  sf::Text inputText;
  sf::Text startButton;

  std::string inputString;
  bool timerRunning;
  sf::Clock timer;

  void handleEvents();
  void handleTextInput(const sf::Event &event);
  void handleMouseButton(const sf::Event &event);
  void startTimer();
  void render();
};
