#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>

#include "hunters.h"

class Snake : public Hunters {
 public:

  using Hunters::Hunters;
  /*Snake(int grid_width, int grid_height, int offset)
      : Hunters(grid_width, grid_height, offset) {}*/

  // Destructor added
  ~Snake() { std::cout << "Snake object destroyed"; }

  void Update () override;

  void GrowBody();
  bool HunterCell(int x, int y) override;

  Direction direction = Direction::kUp;

  int size{1};
  std::vector<SDL_Point> body;

 private:
  void UpdateHead() override;
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
};

#endif