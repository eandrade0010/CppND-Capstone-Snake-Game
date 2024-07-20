#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake *snake, Hunter &hunter) const;

 private:
  void ChangeDirection(Snake *snake, Hunter &hunter, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif