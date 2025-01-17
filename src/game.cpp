#include "game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>

#include <memory>
#include <thread>
#include <future>
#include <mutex>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      hunter(grid_width, grid_height, 4) { // Hunter competes with the snake for the food while also acting as a predator for the player
  // Initialize snared pointer to snake object, with an offset of half the grid_width and height (center)
  snake = std::make_shared<Snake>(grid_width, grid_height, 2);
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Task is launched to read high score from text file while user is playing
  std::future<int> future = std::async(&Game::ReadHighScore, this);
  highScore = future.get();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake.get());
    controller.Track(running, hunter, food);
    Update();
    renderer.Render(snake.get(), food, hunter);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  return;
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->HunterCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::WriteScores() {
  // Once game terminates, uses enters name which is appended to the scores file with score
  std::string name;

  while (name.empty()) {
    std::cout << "Please enter an alphanumeric name: ";
    std::cin >> name;
  }

  // locking access to score .txt file
  std::lock_guard<std::mutex> lck(_mutex);

  // writing name and score to file
  std::ofstream myfile;
  myfile.open(filePath, std::ios::app);
  myfile << name << " " << score << std::endl;
  myfile.close();
}

int Game::ReadHighScore() {
  // locking access to score .txt file
  std::lock_guard<std::mutex> lck(_mutex);

  int high_score{0};
  std::string person, score;
  std::string line;
  std::ifstream filestream(filePath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> person >> score;
      if (std::stoi(score) >= high_score) {
        high_score = std::stoi(score);
      }
    }
  }
  std::cout << "Current High Score is " << high_score << std::endl;
  return high_score;
}

void Game::Update() {
  if (!snake->alive) return;

  snake->Update();
  hunter.Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
  }

  // Check if hunter has caught snake
  SDL_Point hunter_cell{
    static_cast<int>(hunter.head_x),
    static_cast<int>(
        hunter.head_y)};

  for (auto const &item : snake->body) {
    if (hunter_cell.x == item.x && hunter_cell.y == item.y) {
      snake->alive = false;
    }
  }

  // Replace food if hunter has ate it
  if (food.x == hunter_cell.x && food.y == hunter_cell.y) {
    PlaceFood();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }