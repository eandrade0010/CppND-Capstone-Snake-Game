#ifndef HUNTERS_H
#define HUNTERS_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>

class Hunters {
public:
    enum class Direction { kUp, kDown, kLeft, kRight };

    // Hunters class is constructed using offset as a scaled offset from the x-y origin
    Hunters(int grid_width, int grid_height, int offset)
        : grid_width(grid_width),
          grid_height(grid_height),
          head_x(grid_width /offset),
          head_y(grid_height /offset) {}

    virtual void Update();
    virtual bool HunterCell(int x, int y);

    Direction direction = Direction::kUp;

    bool alive{true};
    float speed{0.1f};
    float head_x;
    float head_y;

protected:
    virtual void UpdateHead();

    int grid_width;
    int grid_height;
};

class Hunter : public Hunters {
public:
    using Hunters::Hunters;

    void Update() override;
    bool HunterCell(int x, int y) override;

    float speed{0.8f};

private:
    void UpdateHead() override;

};

#endif //HUNTERS_H