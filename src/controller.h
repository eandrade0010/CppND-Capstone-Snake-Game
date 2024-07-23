#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:

  void HandleInput(bool &running, Snake *snake) const;

 // Added method
  void Track(bool &running, Hunter &hunter, SDL_Point &food) const;


 private:
 // Added method
  void Hunt(Hunter &hunter) const;

  void ChangeDirection(Snake *snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif