#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>

const int width = 20;
const int height = 20;


enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct SnakeSegment {
  int x;
  int y;
};

std::vector<SnakeSegment> snake;
Direction direction = RIGHT;
bool gameOver = false;

void drawBoard() {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      bool isSnake = false;
      for (const auto& segment : snake) {
        if (segment.x == x && segment.y == y) {
          isSnake = true;
          break;
        }
      }
      if (isSnake) {
        std::cout << "x";
      } else if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
        std::cout << "#";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

void updateSnake() {
  int newX = snake[0].x;
  int newY = snake[0].y;
  switch (direction) {
    case UP:
      newY--;
      break;
    case DOWN:
      newY++;
      break;
    case LEFT:
      newX--;
      break;
    case RIGHT:
      newX++;
      break;
  }

  // Check for collisions
  if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
    gameOver = true;
    return;
  }

  // Check for self-collision
  for (int i = 1; i < snake.size(); ++i) {
    if (snake[i].x == newX && snake[i].y == newY) {
      gameOver = true;
      return;
    }
  }

  // Update snake head
  snake[0].x = newX;
  snake[0].y = newY;

  // Grow snake if needed
  if (snake.size() == 2) {
    SnakeSegment newSegment;
    newSegment.x = snake[1].x;
    newSegment.y = snake[1].y;
    snake.push_back(newSegment);
  } else {
    // Move tail
    snake[1].x = snake[0].x;
    snake[1].y = snake[0].y;
  }
}

void handleInput() {
  if (_kbhit()) {
    char c = _getch();
    switch (c) {
      case 'w':
        if (direction != DOWN) {
          direction = UP;
        }
        break;
      case 's':
        if (direction != UP) {
          direction = DOWN;
        }
        break;
      case 'a':
        if (direction != RIGHT) {
          direction = LEFT;
        }
        break;
      case 'd':
        if (direction != LEFT) {
          direction = RIGHT;
        }
        break;
    }
  }
}

int main() {
  // Initialize snake
  snake.push_back({5, 5});
  snake.push_back({5, 6});

  while (!gameOver) {
    drawBoard();
    handleInput();
    updateSnake();
    Sleep(100); 
  }

  std::cout << "Game Over!" << std::endl;

  return 0;
}
