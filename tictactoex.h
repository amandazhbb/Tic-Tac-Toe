// Author Name: Amanda Zheng
// File name: tictactoe.h
// Date: 2019-02-4
// Purpose: practice two demensional array.

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <cstring>

class TicTacToe
{
 public:
  TicTacToe(int boardSize);
  // constructor

  ~TicTacToe();
  // destructor

  void clear();
  // resets the game board status.

  void display();
  // display the game board to terminal.

  bool place(char xLabel, int yLabel, char piece);
  // place an piece at board location specified by xLabel and yLabel.
  // return whether the piece placed successfully.
  // place will return false when the xLabel or yLabel is invalid or there is
  // already an piece at specified location.

  bool isWinner(int xLabel, int yLabel, char piece);
  // return whether game has winner after placed an piece at xLabel and yLabel.
  // pre: xLabel and yLabel must be valid location.
 private:
  char xAxisIndexToLabel(int xIndex);
  // return label on x axis from 0-based index.
  // pre: xIndex must be a valid index on x axis, i.e, within [0, boardSize_)

  int xAxisLabelToIndex(char xLabel);
  // return 0-based index on x axis from label.
  // pre: xLabel must be a valid label on x axis.

  bool isXAxisLabelValid(char xLabel);
  // return whether x axis label is valid.

  int yAxisIndexToLabel(int yIndex);
  // return label on y axis from 0-based index.
  // pre: yIndex must be a valid index on y axis, i.e, within [0, boardSize_)

  int yAxisLabelToIndex(int yLabel);
  // return 0-based index on y axis from label.
  // pre: yLabel must be a valid label on y axis.

  bool isYAxisLabelValid(int yLabel);
  // return whether y axis label is valid.

 private:
  int boardSize_;
  char** board_;

  const static char PIECE_X = 'X';
  const static char PIECE_O = 'O';
  const static char PIECE_BLANK = ' ';
};

#endif
