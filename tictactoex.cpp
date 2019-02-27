// Author Name: Amanda Zheng
// File name: tictactoe.cpp
// Date: 2019-02-7
// Purpose: Implementation for game Tictactoe described in tictactoe.h

#include "tictactoex.h"
#include <iostream>

TicTacToe::TicTacToe(int boardSize)
{
  board_ = new char*[boardSize];  // initialize gameboard
  for (int i = 0; i < boardSize; ++i) {
    board_[i] = new char[boardSize];
  }
  boardSize_ = boardSize;
  clear();
}

TicTacToe::~TicTacToe()  // deallocate array memory for gameboard
{
  for (int i = 0; i < boardSize_; ++i) {
    delete[] board_[i];
  }
  delete[] board_;
}

void TicTacToe::clear()
{
  for (int y = 0; y < boardSize_; ++y) {
    for (int x = 0; x < boardSize_; ++x) {
      board_[y][x] = PIECE_BLANK;
    }
  }
}

// an prototype of 5 x 5 board is below:
//     A   B   C   D   E
//    --- --- --- --- ---
// 5 | O | X |   |   | X | 5
//     --- --- --- --- ---
// 4 | X | X |   | X | O | 4
//     --- --- --- --- ---
// 3 |   | O | O |   |   | 3
//     --- --- --- --- ---
// 2 |   | X |   |   | O | 2
//     --- --- --- --- ---
// 1 | O | X |   |   | O | 1
//    --- --- --- --- ---
//     A   B   C   D   E
// currently, display function handles board size up to 26 * 26, which fits
// into terminal well. x label range from A to Z, and y label range from 1-26.

void TicTacToe::display()
{
  // display x-axis at top
  std::cout << "   ";
  for (int x = 0; x < boardSize_; ++x) {
    std::cout << "  " << xAxisIndexToLabel(x) << " ";
  }
  std::cout << std::endl;

  // display each board row
  for (int y = 0; y < boardSize_; ++y) {
    std::cout << "   ";
    for (int x = 0; x < boardSize_; ++x) {
      std::cout << " "
                << "---";
    }
    std::cout << std::endl;

    // since y label can be both single digit(1) and double digit(11), we
    // prepend a space to y label if it's single digit to align the board.
    int yLabel = yAxisIndexToLabel(y);
    if (yLabel < 10) {
      std::cout << " " << yLabel << " ";
    } else {
      std::cout << yLabel << " ";
    }

    for (int x = 0; x < boardSize_; ++x) {
      std::cout << "|"
                << " " << board_[y][x] << " ";
    }

    std::cout << "|"
              << " " << yAxisIndexToLabel(y) << std::endl;
  }

  std::cout << "   ";
  for (int x = 0; x < boardSize_; ++x) {
    std::cout << " "
              << "---";
  }
  std::cout << std::endl;
  // display x-axis at bottom
  std::cout << "   ";
  for (int x = 0; x < boardSize_; ++x) {
    std::cout << "  " << xAxisIndexToLabel(x) << " ";
  }
  std::cout << std::endl;
}

bool TicTacToe::place(char xLabel, int yLabel, char piece)
{
  if (!isXAxisLabelValid(xLabel)) {
    std::cerr << xLabel << "isn't valid x axis label" << std::endl;
    return false;
  }
  if (!isYAxisLabelValid(yLabel)) {
    std::cerr << yLabel << "isn't valid y axis label" << std::endl;
    return false;
  }
  int xIndex = xAxisLabelToIndex(xLabel);
  int yIndex = yAxisLabelToIndex(yLabel);
  if (board_[yIndex][xIndex] != PIECE_BLANK) {
    std::cerr << "location " << xLabel << yLabel << " is already oocupied"
              << std::endl;
    return false;
  }

  board_[yIndex][xIndex] = piece;
  return true;
}

bool TicTacToe::isWinner(int xLabel, int yLabel, char piece)
{
  int xIndex = xAxisLabelToIndex(xLabel);
  int yIndex = yAxisLabelToIndex(yLabel);

  // check row
  bool checkFailed = false;
  for (int i = 0; !checkFailed && i < boardSize_; ++i) {
    if (board_[yIndex][i] != piece) {
      checkFailed = true;
    }
  }
  if (!checkFailed) {
    return true;
  }

  // check column
  checkFailed = false;
  for (int i = 0; !checkFailed && i < boardSize_; ++i) {
    if (board_[i][xIndex] != piece) {
      checkFailed = true;
    }
  }
  if (!checkFailed) {
    return true;
  }

  // check top left -> bottom right diagonal
  if (xIndex == yIndex) {
    checkFailed = false;
    for (int i = 0; !checkFailed && i < boardSize_; ++i) {
      if (board_[i][i] != piece) {
        checkFailed = true;
      }
    }
    if (!checkFailed) {
      return true;
    }
  }

  // check bottom left -> top right diagonal
  if (xIndex + yIndex + 1 == boardSize_) {
    checkFailed = false;
    for (int i = 0; !checkFailed && i < boardSize_; ++i) {
      if (board_[boardSize_ - 1 - i][i] != piece) {
        checkFailed = true;
      }
    }
    if (!checkFailed) {
      return true;
    }
  }
  return false;
}

char TicTacToe::xAxisIndexToLabel(int xIndex)
{
  return 'A' + xIndex;
}
int TicTacToe::xAxisLabelToIndex(char xLabel)
{
  return xLabel - 'A';
}
bool TicTacToe::isXAxisLabelValid(char xLabel)
{
  char maxXLabel = xAxisIndexToLabel(boardSize_ - 1);
  return xLabel >= 'A' && xLabel <= maxXLabel;
}

int TicTacToe::yAxisIndexToLabel(int yIndex)
{
  return boardSize_ - yIndex;
}
int TicTacToe::yAxisLabelToIndex(int yLabel)
{
  return boardSize_ - yLabel;
}
bool TicTacToe::isYAxisLabelValid(int yLabel)
{
  return yLabel >= 1 && yLabel <= boardSize_;
}
