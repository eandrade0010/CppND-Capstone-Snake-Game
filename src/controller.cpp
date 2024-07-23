#include "controller.h"
#include <SDL2/SDL.h>

void Controller::ChangeDirection(Snake *snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) {
    snake->direction = input;
  }
  return;
}

void Controller::HandleInput(bool &running, Snake *snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;
        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;
        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;
        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

// Track method surveys the distance between the hunter and the food, then invoking the hunt method to control the hunter's movements
void Controller::Track(bool &running, Hunter &hunter, SDL_Point &food) const {
  if (running) {
    int x = static_cast<int>(hunter.head_x);
    hunter.distance_x = food.x - x;

    Hunt(hunter);
  }
  return;
}

// Called once the hunter surveys the distance from the food. Very inefficient method for moving the hunter
void Controller::Hunt(Hunter &hunter) const {
  if (hunter.distance_x > 0) {
    hunter.direction = Hunter::Direction::kRight;
  } else if (hunter.distance_x < 0) {
    hunter.direction = Hunter::Direction::kLeft;
  } else {
    hunter.direction = Hunter::Direction::kUp;
  }
  return;
}
