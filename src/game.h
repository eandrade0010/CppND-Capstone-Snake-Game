#ifndef GAME_H
#define GAME_H

#include <mutex>
#include <random>
#include <SDL2/SDL.h>
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "hunters.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void WriteScores(); // writes score to .txt file in higher directory

  bool running;
  int highScore{0};   // default initialized high score

 private:
  std::shared_ptr<Snake> snake;
  Hunter hunter;
  SDL_Point food;

  std::string filePath{"../scores.txt"}; // path to score txt file

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  int ReadHighScore(); // reads highest score from .txt file

  std::mutex _mutex;   // mutex is to lock the score .txt file when reading and writing
};

#endif