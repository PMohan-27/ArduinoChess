#ifndef MOVE_GEN_HPP
#define MOVE_GEN_HPP
#include <Arduino.h>
#include "constants.hpp"



inline bool isWhitePiece(int8_t piece) {
    return piece > 0 ? WHITE : BLACK;
}


void printGrid1D(const int8_t board[BOARD_SIZE]) {
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            Serial.print(board[row * BOARD_COLS + col]);
            Serial.print(" ");
        }
        Serial.println();
    }
}

void printLongLong(int64_t move){
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if (i%BOARD_COLS == 0)
        {
        Serial.print("\n");
        }
        Serial.print(int((move >> i) & 1LL));
    }
}
int64_t generateKingMoves(const int8_t board[BOARD_SIZE], int8_t position)
{
    int8_t baseRow = position / BOARD_COLS;
    int8_t baseCol = position % BOARD_COLS;
    bool isWhite = isWhitePiece(board[position]); // true (1) = white, false (0) = black 
    
    static constexpr int8_t directions[8][2] = 
    {
        {  1,  0 }, {  1,  1 }, {  0,  1 }, { -1,  1 }, 
        { -1,  0 }, { -1, -1 }, {  0, -1 }, {  1, -1 }  
    }; 
    int64_t moves = 0LL;

    for(auto& pos: directions)
    {
        
        int8_t row = baseRow + pos[0];
        int8_t col = baseCol + pos[1];

        int8_t pos1D = row*BOARD_COLS + col;
        
        // 2 checks here
        // 1. within bounds of the board
        // 2. checks if the space to move to is either empty OR the enemy matches colours
        if (row >= BOARD_MIN_ROW && row <= BOARD_MAX_ROW_INDEX&& col >= BOARD_MIN_COL && col <= BOARD_MAX_COL_INDEX)
        {            
            if((board[pos1D] == EMPTY || (board[pos1D] > 0) != isWhite)){
            //bitwise or to update the move int64
            moves |= 1LL << pos1D;
            }
        }
    }
    
    return moves;
}
//TAKES AN ATTACK ONLY BOOL DUE TO PAWNS NOT ATTACKING WHERE THEY MOVE
int64_t generatePawnMoves(const int8_t board[BOARD_SIZE], int8_t position, bool attackingOnly) 
{
    int8_t baseRow = position / BOARD_COLS;
    int8_t baseCol = position % BOARD_COLS;
    bool isWhite = isWhitePiece(board[position]); // true (1) = white, false (0) = black 

    int8_t forward = isWhite ? -1 : 1;
    int8_t startRow = isWhite ? PAWN_WHITE_START_ROW : PAWN_BLACK_START_ROW;

    int64_t moves = 0LL;
    int8_t updatedRow = baseRow+forward;
    if (!attackingOnly) 
    {
        if (updatedRow >= BOARD_MIN_ROW && updatedRow <= BOARD_MAX_ROW_INDEX)
        {
            int8_t nextPos1D = (baseRow+forward)*BOARD_COLS + baseCol;

            if(board[nextPos1D] == EMPTY)
            {
                moves |= 1LL << nextPos1D;
                if (baseRow == startRow)
                {
                    int8_t doubleMovePos1D = (baseRow+(forward*2))*BOARD_COLS + baseCol;
                    updatedRow = doubleMovePos1D / BOARD_COLS;
                    if (updatedRow >= BOARD_MIN_ROW && updatedRow <= BOARD_MAX_ROW_INDEX)
                    {
                        if(board[doubleMovePos1D] == EMPTY){
                            moves |= 1LL << doubleMovePos1D;
                        }
                    }
                }
            }
        }
    }
    
    
    constexpr int8_t dc[2] = {1,-1};
    for(int8_t change : dc){
        updatedRow = baseRow+forward;
        int8_t updatedCol = baseCol+change;
        int8_t nextPos1D = updatedRow*BOARD_COLS + updatedCol;

        if(updatedRow >= BOARD_MIN_ROW && updatedRow <= BOARD_MAX_ROW_INDEX && updatedCol >= BOARD_MIN_COL && updatedCol <= BOARD_MAX_COL_INDEX){
            if ((board[nextPos1D] > 0) != isWhite && board[nextPos1D] != EMPTY)
            {
                moves |= 1LL << nextPos1D;
            }
        }
    }
    return moves;
}

int64_t generateRookMoves(const int8_t board[BOARD_SIZE], int8_t position)
{
    int8_t row = position / BOARD_COLS;
    int8_t col = position % BOARD_COLS;
    bool isWhite = isWhitePiece(board[position]); // true (1) = white, false (0) = black 
    int64_t moves = 0LL;
    auto scan = [&](int8_t dRow, int8_t dCol){
        int8_t r = row + dRow;
        int8_t c = col + dCol;

        while (r >= BOARD_MIN_ROW && r <= BOARD_MAX_ROW_INDEX 
            && c >= BOARD_MIN_COL && c <= BOARD_MAX_COL_INDEX)
        {
            int8_t pos1D = r*BOARD_COLS + c;
            if(board[pos1D] == EMPTY)
            {
                moves |= 1LL << pos1D;
            }else{
                if ((board[pos1D] > 0) != isWhite){
                    moves |= 1LL << pos1D;
                }
                break;
            }
            r+= dRow;
            c+=dCol;
        }
    };
    scan(1,0);
    scan(0,1);
    scan(-1,0);
    scan(0,-1);
    return moves;
}

int64_t generateBishopMoves(const int8_t board[BOARD_SIZE], int8_t position)
{
    int8_t row = position / BOARD_COLS;
    int8_t col = position % BOARD_COLS;
    bool isWhite = isWhitePiece(board[position]); // true (1) = white, false (0) = black 
    int64_t moves = 0LL;
    auto scan = [&](int8_t dRow, int8_t dCol){
        int8_t r = row + dRow;
        int8_t c = col + dCol;

        while (r >= BOARD_MIN_ROW && r <= BOARD_MAX_ROW_INDEX 
            && c >= BOARD_MIN_COL && c <= BOARD_MAX_COL_INDEX)
        {
            int8_t pos1D = r*BOARD_COLS + c;
            if(board[pos1D] == EMPTY)
            {
                moves |= 1LL << pos1D;
            }else{
                if ((board[pos1D] > 0) != isWhite){
                    moves |= 1LL << pos1D;
                }
                break;
            }
            r+= dRow;
            c+= dCol;
        }
    };
    scan(1,1);
    scan(-1,1);
    scan(1,-1);
    scan(-1,-1);
    return moves;
}

int64_t generateQueenMoves(const int8_t board[BOARD_SIZE], int8_t position){
    int64_t moves = 0LL;
    moves |= generateBishopMoves(board,position);
    moves |= generateRookMoves(board,position);
    return moves;
}

int64_t generateKnightMoves(const int8_t board[BOARD_SIZE], int8_t position)
{
    int8_t baseRow = position / BOARD_COLS;
    int8_t baseCol = position % BOARD_COLS;
    bool isWhite = isWhitePiece(board[position]); // true (1) = white, false (0) = black 
    
    static constexpr int8_t directions[8][2] =
    {
        {  2,  1 }, {  1,  2 },
        { -1,  2 }, { -2,  1 },
        { -2, -1 }, { -1, -2 },
        {  1, -2 }, {  2, -1 }
    };

    int64_t moves = 0LL;

    for(auto& pos: directions)
    {
        
        int8_t row = baseRow + pos[0];
        int8_t col = baseCol + pos[1];

        int8_t pos1D = row*BOARD_COLS + col;

        if (row >= BOARD_MIN_ROW && row <= BOARD_MAX_ROW_INDEX&& col >= BOARD_MIN_COL && col <= BOARD_MAX_COL_INDEX)
        {            
            if((board[pos1D] == EMPTY || (board[pos1D] > 0) != isWhite)){
            moves |= 1LL << pos1D;
            }
        }
    }
    
    return moves;
}


int64_t generateEnemyAttacks(const int8_t board[BOARD_SIZE], bool isWhite){
    int64_t moves = 0LL;
    for(int8_t i = 0; i < BOARD_SIZE; i++){
        int8_t piece = board[i];
        if((piece>0) == isWhite || piece == EMPTY){continue;};
        switch (abs(piece))
        {
            case(P):
                moves |= generatePawnMoves(board,i,true);
                break;
            case(R):
                moves |= generateRookMoves(board,i);
                break;
            case(N):
                moves |= generateKnightMoves(board,i);
                break;
            case(B):
                moves |= generateBishopMoves(board,i);
                break;
            case(Q):
                moves |= generateQueenMoves(board,i);
                break;
            case(K):
                moves |= generateKingMoves(board,i);
                break;
            default:
                break;
        }
    }
    return moves;
}

int64_t moveLegalizer(int8_t board[BOARD_SIZE],int8_t from, int64_t moves, uint8_t bkPos, uint8_t wkPos){
    bool isWhite = isWhitePiece(board[from]); // white = true, black = false
    int8_t boardCopy[BOARD_SIZE];
    memcpy(boardCopy,board,sizeof(boardCopy));

    int64_t enemyMoves = 0LL;
\

    for(int8_t i = 0; i < BOARD_SIZE; i++)
    {
        bool bit = (moves >> i) & 1LL;
        // Serial.print(bit);
        if(bit){
            if (boardCopy[from] == K) {
                wkPos = i;
            } else if (boardCopy[from] == k) {
                bkPos = i;
            }
            int8_t initial_to = boardCopy[i];
            int8_t initial_from = boardCopy[from];
            
            boardCopy[i] = boardCopy[from];
            boardCopy[from] = EMPTY;

            enemyMoves = generateEnemyAttacks(boardCopy,isWhite);

            if(isWhite == WHITE){
                if((enemyMoves >> wkPos) & 1LL){
                    moves &= ~(1LL << i);
                }
            }
            if(isWhite == BLACK){
                if((enemyMoves >> bkPos) & 1LL){
                    moves &= ~(1LL << i);
                }
            }

            boardCopy[i] = initial_to;
            boardCopy[from] = initial_from;
        }
    }
    return moves;
}



#endif