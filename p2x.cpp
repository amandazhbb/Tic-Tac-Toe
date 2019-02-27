// Author Name: Amanda Zheng
// File name: p2.cpp
// Date: 2019-02-7
// Purpose: drives the whole application.
// Input: size of the game board, name for each player and where to place
// pieces. Process: relies on tictactoe class to proceed. Output: it will output
// information for player's action.

#include <iostream>
#include "tictactoex.h"

static const int PLAYER_COUNT = 2;
static const int FLUSH_SCREEN_LINES = 25;

int startGameLoop(TicTacToe& board, char playerPieces[PLAYER_COUNT],
                  std::string playerNames[PLAYER_COUNT]);
// start a new game round
// return the which player wins this game, 0 for playerX, 1 for playerO.

void flushScreen();
// flush the screen.

int main()
{
  int boardSize = 0;
  char playerPieces[PLAYER_COUNT] = {'X', 'O'};
  std::string playerNames[PLAYER_COUNT];
  int playerScores[PLAYER_COUNT] = {};

  flushScreen();
  std::cout << "Welcome to play Tic-Tac-Toe by Silly Little Games!"
            << std::endl;
  while (boardSize < 1 || boardSize > 26) {
    std::cout << "Please input desired boardSize within [1-26]:";
    std::cin >> boardSize;
  }

  for (int i = 0; i < PLAYER_COUNT; ++i) {
    std::cout << "Please input name for Player with piece " << playerPieces[i]
              << ":";
    std::cin >> playerNames[i];
  }

  TicTacToe board = TicTacToe(boardSize);
  char continueGame = 'Y';
  while (continueGame == 'Y') {
    int wonPlayerIndex = startGameLoop(board, playerPieces, playerNames);
    playerScores[wonPlayerIndex] += 1;
    std::cout << "score board:" << std::endl;
    for (int i = 0; i < PLAYER_COUNT; ++i) {
      std::cout << playerNames[i] << ": " << playerScores[i] << " scores"
                << std::endl;
    }
    std::cout << "continue? Y / N:";
    std::cin >> continueGame;
  }
  std::cout << "Hope you enjoyed our game, Good bye!" << std::endl;
}

int startGameLoop(TicTacToe& board, char playerPieces[PLAYER_COUNT],
                  std::string playerNames[PLAYER_COUNT])
{
  bool gameEnded = false;
  char xLabel;
  int yLabel;

  std::string curPlayerName;
  char curPlayerPiece;
  int curPlayerIndex;
  bool placeSucceed = false;

  int nextPlayerIndex = -1;
  std::string firstPlayerName;
  while (nextPlayerIndex < 0) {
    std::cout << "which player goes first,";
    for (int i = 0; i != PLAYER_COUNT; ++i) {
      std::cout << playerNames[i] << " ? ";
    }
    std::cout << ":";
    std::cin >> firstPlayerName;

    for (int i = 0; i != PLAYER_COUNT; ++i) {
      if (playerNames[i] == firstPlayerName) {
        nextPlayerIndex = i;
      }
    }
  }

  board.clear();
  flushScreen();
  board.display();
  while (!gameEnded) {
    curPlayerIndex = nextPlayerIndex;
    nextPlayerIndex = (curPlayerIndex + 1) % PLAYER_COUNT;
    curPlayerName = playerNames[curPlayerIndex];
    curPlayerPiece = playerPieces[curPlayerIndex];

    placeSucceed = false;
    while (!placeSucceed) {
      std::cout << curPlayerName << ", please choose where to place piece "
                << curPlayerPiece << ":";
      std::cin >> xLabel >> yLabel;
      placeSucceed = board.place(xLabel, yLabel, curPlayerPiece);
    }
    flushScreen();
    board.display();
    gameEnded = board.isWinner(xLabel, yLabel, curPlayerPiece);
  }
  std::cout << curPlayerName << " won this round! congratulations!"
            << std::endl;
  return curPlayerIndex;
}

void flushScreen()
{
  for (int i = 0; i < FLUSH_SCREEN_LINES; ++i) {
    std::cout << std::endl;
  }
}
