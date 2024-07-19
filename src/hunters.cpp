#include "hunters.h"

void Hunters::Update() {
    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(
            head_y)};  // We first capture the head's cell before updating.
    UpdateHead();
}

void Hunters::UpdateHead() {
    switch (direction) {
        case Direction::kUp:
            head_y -= speed;
        break;

        case Direction::kDown:
            head_y += speed;
        break;

        case Direction::kLeft:
            head_x -= speed;
        break;

        case Direction::kRight:
            head_x += speed;
        break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

bool Hunters::HunterCell(int x, int y) {
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
    }
    return false;
}