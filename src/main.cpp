#include <Arduino.h>
#include <FastLED.h>
#include <limits.h>

#include "moveGenerator.hpp"

struct Gamestate{
  uint8_t whiteKingPosition = WHITE_KING_START_POS;
  uint8_t blackKingPosition = BLACK_KING_START_POS;
  int8_t board1D[BOARD_SIZE] = {
    r, n, b, q, k, b, n, r,
    p, p, p, p, p, p, p, p,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    P, P, P, P, P, P, P, P,
    R, N, B, Q, K, B, N, R
  };


};

Gamestate currentState;


int64_t moves = 0LL;

void setup() 
{
    


  Serial.begin(9600);

  int8_t row = 3;
  int8_t col = 4;
  int8_t testpos = row*8 + col;
  currentState.board1D[currentState.whiteKingPosition] = EMPTY;
  currentState.whiteKingPosition = (4*8) +2;
  currentState.board1D[currentState.whiteKingPosition] = K;
  currentState.board1D[testpos] = R;

  moves = generateRookMoves(currentState.board1D,testpos);
  
  Serial.print("\n");
  moves = moveLegalizer(currentState.board1D,testpos,moves,currentState.blackKingPosition ,currentState.whiteKingPosition);

  printLongLong(moves);
  Serial.print("\n");

  // Serial.println("\n");
  // moves = generateKingMoves(board1D,whiteKingPosition);
  // moves = generateKingMoves(board1D,blackKingPosition);

}
void loop() 
{

}
