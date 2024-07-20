#include "controller.h"
#include <iostream>
#include <SDL2/SDL.h>

void Controller::ChangeDirection(Snake *snake, Hunter &hunter, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) {
    snake->direction = input;
    hunter.direction = input;
  }
  return;
}


void Controller::HandleInput(bool &running, Snake *snake, Hunter &hunter) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, hunter, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, hunter, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, hunter, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, hunter, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}