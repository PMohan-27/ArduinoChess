#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <Arduino.h>

constexpr int8_t BOARD_ROWS = 8;
constexpr int8_t BOARD_COLS = 8;
constexpr int8_t BOARD_SIZE = BOARD_ROWS * BOARD_COLS;


constexpr int8_t BOARD_MIN_ROW = 0;
constexpr int8_t BOARD_MIN_COL = 0;
constexpr int8_t BOARD_MAX_ROW_INDEX = BOARD_ROWS - 1;
constexpr int8_t BOARD_MAX_COL_INDEX = BOARD_COLS - 1;


constexpr int8_t PAWN_WHITE_START_ROW = 6; 
constexpr int8_t PAWN_BLACK_START_ROW = 1;  

constexpr int8_t EMPTY = 0;

constexpr int8_t P = 1;
constexpr int8_t B = 2;
constexpr int8_t N = 3;
constexpr int8_t R = 4;
constexpr int8_t Q = 5;
constexpr int8_t K = 6;

constexpr int8_t p = -1;
constexpr int8_t b = -2;
constexpr int8_t n = -3;
constexpr int8_t r = -4;
constexpr int8_t q = -5;
constexpr int8_t k = -6;

constexpr uint8_t WHITE_KING_START_POS = 60;  // e1
constexpr uint8_t BLACK_KING_START_POS = 4;   // e8

constexpr bool WHITE  = true;
constexpr bool BLACK = false;

#endif