#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

class MeditationTimer
{
public:
  MeditationTimer(sf::RenderWindow &window) : window(window)
  {
    window.create(sf::VideoMode(400, 200), "Meds :)");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("arial.ttf"))
    {
      std::cerr << "Error loading font file." << std::endl;
      std::exit(1);
    }

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 50);
    text.setString("Hi friend :)\nHow many minutes would you like to meditate?");

    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(10, 100);
    inputText.setString("");

    startButton.setFont(font);
    startButton.setCharacterSize(24);
    startButton.setPosition(10, 150);
    startButton.setString("Start");

    timerRunning = false;
  }

  void run()
  {
    while (window.isOpen())
    {
      handleEvents();
      render();
    }
  }

private:
  sf::RenderWindow &window;
  sf::Font font;
  sf::Text text;
  sf::Text inputText;
  sf::Text startButton;

  std::string inputString;
  bool timerRunning;
  sf::Sound finishSound;
  int durationInMinutes;
  sf::Clock timer;

  void handleEvents()
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (event.type == sf::Event::TextEntered)
      {
        handleTextInput(event);
      }
      else if (event.type == sf::Event::MouseButtonPressed)
      {
        handleMouseButton(event);
      }
    }
  }

  void handleTextInput(const sf::Event &event)
  {
    if (event.text.unicode >= 48 && event.text.unicode <= 57)
    {
      inputString += static_cast<char>(event.text.unicode);
      inputText.setString(inputString);
    }
    else if (event.text.unicode == 8 && inputString.size() > 0)
    {
      inputString.pop_back();
      inputText.setString(inputString);
    }
  }

  void handleMouseButton(const sf::Event &event)
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = startButton.getGlobalBounds();

    if (buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
      startTimer();
    }
  }

  void startTimer()
  {
    if (!timerRunning)
    {
      int durationInMinutes = std::stoi(inputString);

      sf::SoundBuffer startBuffer, finishBuffer;
      if (!startBuffer.loadFromFile("bell.wav") || !finishBuffer.loadFromFile("bell.wav"))
      {
        std::cerr << "Error loading sound files." << std::endl;
        std::exit(1);
      }

      sf::Sound startSound(startBuffer);
      finishSound.setBuffer(finishBuffer);

      std::cout << "Timer started for " << durationInMinutes << " minutes :)" << std::endl;
      startSound.play();
      timer.restart();
      timerRunning = true;

      while (timerRunning)
      {
        updateTimer();
      }
    }
  }

  void updateTimer()
  {
    sf::Time elapsed = timer.getElapsedTime();
    int remainingMinutes = durationInMinutes - static_cast<int>(elapsed.asSeconds() / 60);

    if (remainingMinutes <= 0)
    {
      finishTimer();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  void finishTimer()
  {
    finishSound.play();
    timerRunning = false;
    std::cout << "Timer finished!" << std::endl;
  }

  void render()
  {
    window.clear();
    window.draw(text);
    window.draw(inputText);
    window.draw(startButton);
    window.display();
  }
};

int main()
{
  sf::RenderWindow window;
  MeditationTimer meditationTimer(window);
  meditationTimer.run();

  return 0;
}
