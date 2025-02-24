#include <Arduino.h>
#include <FastLED.h>


#define P 1
#define N 2
#define B 3
#define R 4
#define Q 5
#define K 6
#define p -1
#define n -2
#define b -3
#define r -4
#define q -5
#define k -6


void getRookMoves(int8_t rank, int8_t file, bool BOARD[8][8],int8_t pieceBoard[8][8]);
void getBishopMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]);
void getQueenMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]);
void getKingMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]);
void getPawnMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]);
void getKnightMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]);
void movePiece(int8_t startRank, int8_t startFile, int8_t endRank, int8_t endFile, int8_t pieceBoard[8][8], bool BOARD[8][8]);
bool checkAttackers(int8_t rank, int8_t file, int8_t pieceBoard[8][8], bool colour);

void resetBoard(bool BOARD[8][8]);
void resetBoard(int8_t BOARD[8][8]);
void printBoard(bool BOARD[8][8]);
void printBoard(int8_t BOARD[8][8]);

int8_t whiteKingPos[2] = {7,4};
int8_t blackKingPos[2] = {0,4};
bool whiteCheck = true;
bool blackCheck = false;

void setup() {
  int8_t board[8][8]{
                  {r,n,b,q,k,b,n,r},
                  {p,p,p,p,p,p,p,p},
                  {0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,n},
                  {0,0,0,0,0,0,0,0},
                  {P,P,P,P,P,P,P,P},
                  {R,N,B,Q,K,B,N,R}};

  

  
  bool moveBoard[8][8] = {0};
  Serial.begin(9600);
  Serial.print('\n');
  resetBoard(moveBoard);
  whiteCheck = checkAttackers(whiteKingPos[0],whiteKingPos[1],board,true);
  blackCheck = checkAttackers(blackKingPos[0],blackKingPos[1],board,false);

  //printBoard(board);
  
  getKnightMoves(4,7,moveBoard,board);
  
  printBoard(moveBoard);
  printBoard(board);
  
  if(whiteCheck){
    Serial.println("white check");
  }
  if(blackCheck){
    Serial.println("black check");
  }

}
void loop() {

}
bool checkAttackers(int8_t rank, int8_t file, int8_t pieceBoard [8][8], bool colour){
  bool BOARD[8][8] = {0};
  bool attacked = false;
  int8_t piece = pieceBoard[rank][file];
  pieceBoard[rank][file] = (colour) ? 1 : -1;

  auto check = [&attacked,colour,pieceBoard](int8_t piece, bool attack[8][8]){
    for(int8_t i = 0; i < 8; i++){
      for(int8_t j = 0; j < 8; j++){
        if(attack[i][j]){
          if(colour){
            if(pieceBoard[i][j] == -piece){
              attacked = true;
            }
          }else{
            if(pieceBoard[i][j] == piece){
              attacked = true;
            }
          }
        }
      }
    }
  };
  // ----------------------
  //BISHOP MOVE CHECK
  // ----------------------
  BOARD[rank][file] = true;
  for(int8_t i = 1; (i < 8 - rank) && (i < 8- file); i++){
    if(pieceBoard[rank+i][file+i] == 0){
      BOARD[rank+i][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file+i] < 0){
        BOARD[rank+i][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file+i] > 0){
        BOARD[rank+i][file+i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i <= rank) && (i <= file); i++){
    if(pieceBoard[rank-i][file-i] == 0){
      BOARD[rank-i][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file-i] < 0){
        BOARD[rank-i][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file-i] > 0){
        BOARD[rank-i][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i < 8 - rank) && (i <= file); i++){
    if(pieceBoard[rank+i][file-i] == 0){
      BOARD[rank+i][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file-i] < 0){
        BOARD[rank+i][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file-i] > 0){
        BOARD[rank+i][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i <= rank) && (i < 8 - file); i++){
    if(pieceBoard[rank-i][file+i] == 0){
      BOARD[rank-i][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file+i] < 0){
        BOARD[rank-i][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file+i] > 0){
        BOARD[rank-i][file+i] = true;
      }
      break;
    }
  }
  check(B,BOARD);
  resetBoard(BOARD);
  // ----------------------
  //KNIGHT MOVE CHECK
  // ----------------------
  BOARD[rank][file] = true;
  auto knightMove = [pieceBoard,&BOARD](int8_t addR, int8_t addF, int8_t rank, int8_t file){
    if(addR + rank <= 8 && addF + file <=8 && addR + rank >= 0 && addF + file >= 0){
      if(pieceBoard[rank + addR][file + addF] == 0){
      BOARD[rank + addR][file + addF] = true;
      }else{
        if(pieceBoard[rank][file] > 0 && pieceBoard[rank+addR][file + addF] < 0){
            BOARD[rank+addR][file + addF] = true;
          }
          if(pieceBoard[rank][file] < 0 && pieceBoard[rank+addR][file + addF] > 0){
            BOARD[rank+addR][file + addF] = true;
          }
      }
    }
  };
  knightMove(2,1,rank,file);
  knightMove(-2,1,rank,file);
  knightMove(1,2,rank,file);
  knightMove(1,-2,rank,file);
  knightMove(-1,-2,rank,file);
  knightMove(-1,2,rank,file);
  knightMove(-2,-1,rank,file);
  knightMove(2,-1,rank,file);
  check(N,BOARD);
  resetBoard(BOARD);
  // ----------------------
  //QUEEN MOVE CHECK
  // ----------------------
  BOARD[rank][file] = true;
  for(int8_t i = 1; i < 8 - rank; i++){
    if(pieceBoard[rank+i][file] == 0){
      BOARD[rank+i][file] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file] < 0){
        BOARD[rank+i][file] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file] > 0){
        BOARD[rank+i][file] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i <= rank; i++){
    if(pieceBoard[rank-i][file] == 0){
      BOARD[rank-i][file] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file] < 0){
        BOARD[rank-i][file] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file] > 0){
        BOARD[rank-i][file] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i <= file; i++){
    if(pieceBoard[rank][file-i] == 0){
      BOARD[rank][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank][file-i] < 0){
        BOARD[rank][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank][file-i] > 0){
        BOARD[rank][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i < 8 - file; i++){
    if(pieceBoard[rank][file+i] == 0){
      BOARD[rank][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank][file+i] < 0){
        BOARD[rank][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank][file+i] > 0){
        BOARD[rank][file+i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i < 8 - rank) && (i < 8- file); i++){
    if(pieceBoard[rank+i][file+i] == 0){
      BOARD[rank+i][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file+i] < 0){
        BOARD[rank+i][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file+i] > 0){
        BOARD[rank+i][file+i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i <= rank) && (i <= file); i++){
    if(pieceBoard[rank-i][file-i] == 0){
      BOARD[rank-i][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file-i] < 0){
        BOARD[rank-i][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file-i] > 0){
        BOARD[rank-i][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i < 8 - rank) && (i <= file); i++){
    if(pieceBoard[rank+i][file-i] == 0){
      BOARD[rank+i][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file-i] < 0){
        BOARD[rank+i][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file-i] > 0){
        BOARD[rank+i][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i <= rank) && (i < 8 - file); i++){
    if(pieceBoard[rank-i][file+i] == 0){ 
      BOARD[rank-i][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file+i] < 0){
        BOARD[rank-i][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file+i] > 0){
        BOARD[rank-i][file+i] = true;
      }
      break;
    }
  }
  check(Q,BOARD);
  resetBoard(BOARD);

  // ----------------------
  //ROOK MOVE CHECK
  // ----------------------
  BOARD[rank][file] = true;
  for(int8_t i = 1; i < 8 - rank; i++){
    if(pieceBoard[rank+i][file] == 0){
      BOARD[rank+i][file] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file] < 0){
        BOARD[rank+i][file] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file] > 0){
        BOARD[rank+i][file] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i <= rank; i++){
    if(pieceBoard[rank-i][file] == 0){
      BOARD[rank-i][file] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file] < 0){
        BOARD[rank-i][file] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file] > 0){
        BOARD[rank-i][file] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i <= file; i++){
    if(pieceBoard[rank][file-i] == 0){
      BOARD[rank][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank][file-i] < 0){
        BOARD[rank][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank][file-i] > 0){
        BOARD[rank][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i < 8 - file; i++){
    if(pieceBoard[rank][file+i] == 0){
      BOARD[rank][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank][file+i] < 0){
        BOARD[rank][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank][file+i] > 0){
        BOARD[rank][file+i] = true;
      }
      break;
    }
  }
  check(R,BOARD);
  resetBoard(BOARD);

  // ----------------------
  //PAWN MOVE CHECK
  // ----------------------
  BOARD[rank][file] = true;
  if (pieceBoard[rank][file] > 0){
     if((pieceBoard[rank - 1][file] == 0)){
      BOARD[rank - 1][file] = true;
      if(pieceBoard[rank - 2][file] == 0 && rank == 6){
        BOARD[rank - 2][file] = true;
      }  
    }
    if (pieceBoard[rank-1][file+1] < 0){
        BOARD[rank - 1][file+1] = true;
    }
    if (pieceBoard[rank-1][file-1] < 0){
        BOARD[rank - 1][file-1] = true;
    }
  }
  if (pieceBoard[rank][file] < 0){
     if((pieceBoard[rank + 1][file] == 0) ){
      BOARD[rank + 1][file] = true;
      if(pieceBoard[rank + 2][file] == 0 && rank == 1){
        BOARD[rank + 2][file] = true;
      }  
    }
    if (pieceBoard[rank+1][file+1] > 0){
        BOARD[rank + 1][file+1] = true;
    }
    if (pieceBoard[rank+1][file-1] > 0){
        BOARD[rank + 1][file-1] = true;
    }
  }
  BOARD[rank + 1][file] = false;
  BOARD[rank + 2][file] = false;
  BOARD[rank - 1][file] = false;
  BOARD[rank - 2][file] = false;
  check(P,BOARD);
  resetBoard(BOARD);

  // ----------------------
  //KING MOVE CHECK
  // ----------------------

  auto Move = [pieceBoard,&BOARD](int8_t addR, int8_t addF, int8_t rank, int8_t file){
    if(addR + rank <= 7 && addF + file <=7 && addR + rank >= 0 && addF + file >= 0){
          if(pieceBoard[rank + addR][file + addF] == 0){
            BOARD[rank + addR][file + addF] = true;
          }else{
            if(pieceBoard[rank][file] > 0 && pieceBoard[rank+addR][file + addF] < 0){
                BOARD[rank+addR][file + addF] = true;
            }
            if(pieceBoard[rank][file] < 0 && pieceBoard[rank+addR][file + addF] > 0){
              BOARD[rank+addR][file + addF] = true;
            }
          }
      }
    };
  Move(0,0,rank,file);
  Move(1,0,rank,file);
  Move(1,1,rank,file);
  Move(0,1, rank,file);
  Move(-1,1,rank,file);
  Move(1,-1,rank,file);
  Move(-1,-1,rank,file);
  Move(0,-1,rank,file);
  Move(-1,0,rank,file);
  check(K,BOARD);
  resetBoard(BOARD);
  pieceBoard[rank][file] = piece;
  return attacked;
}
void movePiece(int8_t startRank, int8_t startFile, int8_t endRank, int8_t endFile, int8_t pieceBoard[8][8], bool BOARD[8][8]){
 resetBoard(BOARD);
  switch(abs(pieceBoard[startRank][startFile])){
      case 1:
        getPawnMoves(startRank,startFile,BOARD,pieceBoard);
        if(endRank == 0 && pieceBoard[startRank][startFile] > 0){
          pieceBoard[startRank][startFile] = Q;
        }
        if(endRank == 7 && pieceBoard[startRank][startFile] < 0){
          pieceBoard[startRank][startFile] = q;
        }
        break;
      case 2:
        getKnightMoves(startRank,startFile,BOARD,pieceBoard);
        break;
      case 3:
        getBishopMoves(startRank,startFile,BOARD,pieceBoard);
        break;
      case 4:
        getRookMoves(startRank,startFile,BOARD,pieceBoard);
        break;
      case 5:
        getQueenMoves(startRank,startFile,BOARD,pieceBoard);
        break;
      case 6:
        getKingMoves(startRank,startFile,BOARD,pieceBoard);
        break;
  }
  if(BOARD[endRank][endFile]){
    pieceBoard[endRank][endFile] = pieceBoard[startRank][startFile];
    pieceBoard[startRank][startFile] = 0;
  }else{
    Serial.println("thats not gonna work");
  }
  
}
void getRookMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]){
  BOARD[rank][file] = true;
  bool colour = pieceBoard[rank][file] > 0;
  for(int8_t i = 1; i < 8 - rank; i++){
   if(whiteCheck){//white
      if(colour){
        int8_t piece = pieceBoard[rank + i][file];
        pieceBoard[rank + i][file] = R; 
        if(!checkAttackers(whiteKingPos[0],whiteKingPos[1],pieceBoard,colour)){
          BOARD[rank + i][file] = true;
        }
        pieceBoard[rank + i][file ] = piece; 
      }
    }else if(blackCheck){
      if(!colour){
        int8_t piece = pieceBoard[rank + i][file];
        pieceBoard[rank + i][file] = r; 
        if(!checkAttackers(blackKingPos[0],blackKingPos[1],pieceBoard,colour)){
          BOARD[rank + i][file] = true;
        }
        pieceBoard[rank + i][file] = piece; 
      }
    }else if(pieceBoard[rank+i][file] == 0){
      BOARD[rank+i][file] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file] < 0){
        BOARD[rank+i][file] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file] > 0){
        BOARD[rank+i][file] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i <= rank; i++){
    if(whiteCheck){//white
      if(colour){
        int8_t piece = pieceBoard[rank - i][file];
        pieceBoard[rank - i][file] = R; 
        if(!checkAttackers(whiteKingPos[0],whiteKingPos[1],pieceBoard,colour)){
          BOARD[rank - i][file] = true;
        }
        pieceBoard[rank - i][file ] = piece; 
      }
    }else if(blackCheck){
      if(!colour){
        int8_t piece = pieceBoard[rank - i][file];
        pieceBoard[rank - i][file] = r; 
        if(!checkAttackers(blackKingPos[0],blackKingPos[1],pieceBoard,colour)){
          BOARD[rank - i][file] = true;
        }
        pieceBoard[rank - i][file] = piece; 
      }
    }else if(pieceBoard[rank-i][file] == 0){
      BOARD[rank-i][file] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file] < 0){
        BOARD[rank-i][file] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file] > 0){
        BOARD[rank-i][file] = true;
      }
      break;
    }
  }

  for(int8_t i = 1; i <= file; i++){
    if(whiteCheck){//white
      if(colour){
        int8_t piece = pieceBoard[rank][file-i];
        pieceBoard[rank][file-i]= R; 
        if(!checkAttackers(whiteKingPos[0],whiteKingPos[1],pieceBoard,colour)){
          BOARD[rank][file-i] = true;
        }
        pieceBoard[rank][file-i] = piece; 
      }
    }else if(blackCheck){
      if(!colour){
        int8_t piece = pieceBoard[rank][file-i];
        pieceBoard[rank][file-i] = r; 
        if(!checkAttackers(blackKingPos[0],blackKingPos[1],pieceBoard,colour)){
          BOARD[rank][file-i] = true;
        }
        pieceBoard[rank][file-i] = piece; 
      }
    }else if(pieceBoard[rank][file-i] == 0){
      BOARD[rank][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank][file-i] < 0){
        BOARD[rank][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank][file-i] > 0){
        BOARD[rank][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; i < 8 - file; i++){
    if(whiteCheck){//white
      if(colour){
        int8_t piece = pieceBoard[rank][file+i];
        pieceBoard[rank][file+i]= R; 
        if(!checkAttackers(whiteKingPos[0],whiteKingPos[1],pieceBoard,colour)){
          BOARD[rank][file+i] = true;
        }
        pieceBoard[rank][file+i] = piece; 
      }
    }else if(blackCheck){
      if(!colour){
        int8_t piece = pieceBoard[rank][file+i];
        pieceBoard[rank][file+i] = r; 
        if(!checkAttackers(blackKingPos[0],blackKingPos[1],pieceBoard,colour)){
          BOARD[rank][file+i] = true;
        }
        pieceBoard[rank][file+i] = piece; 
      }
    }else if(pieceBoard[rank][file+i] == 0){
      BOARD[rank][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank][file+i] < 0){
        BOARD[rank][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank][file+i] > 0){
        BOARD[rank][file+i] = true;
      }
      break;
    }
  }
  
}
void getBishopMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]){
  BOARD[rank][file] = true;
  for(int8_t i = 1; (i < 8 - rank) && (i < 8- file); i++){
    if(pieceBoard[rank+i][file+i] == 0){
      BOARD[rank+i][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file+i] < 0){
        BOARD[rank+i][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file+i] > 0){
        BOARD[rank+i][file+i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i <= rank) && (i <= file); i++){
    if(pieceBoard[rank-i][file-i] == 0){
      BOARD[rank-i][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file-i] < 0){
        BOARD[rank-i][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file-i] > 0){
        BOARD[rank-i][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i < 8 - rank) && (i <= file); i++){
    if(pieceBoard[rank+i][file-i] == 0){
      BOARD[rank+i][file-i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank+i][file-i] < 0){
        BOARD[rank+i][file-i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank+i][file-i] > 0){
        BOARD[rank+i][file-i] = true;
      }
      break;
    }
  }
  for(int8_t i = 1; (i <= rank) && (i < 8 - file); i++){
    if(pieceBoard[rank-i][file+i] == 0){
      BOARD[rank-i][file+i] = true;
    }else{
      if(pieceBoard[rank][file] > 0 && pieceBoard[rank-i][file+i] < 0){
        BOARD[rank-i][file+i] = true;
      }
      if(pieceBoard[rank][file] < 0 && pieceBoard[rank-i][file+i] > 0){
        BOARD[rank-i][file+i] = true;
      }
      break;
    }
  }
}
void getQueenMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]){
  BOARD[rank][file] = true;
  getRookMoves(rank,file,BOARD,pieceBoard);
  getBishopMoves(rank,file,BOARD,pieceBoard);
}
void getKingMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]){
  bool col = pieceBoard[rank][file] > 0;
  pieceBoard[rank][file] = 0;
  auto Move = [pieceBoard,&BOARD, col](int8_t addR, int8_t addF, int8_t rank, int8_t file){
    if(addR + rank <= 7 && addF + file <=7 && addR + rank >= 0 && addF + file >= 0){
      if(!checkAttackers(addR + rank, addF + file, pieceBoard,col)){
          if(pieceBoard[rank + addR][file + addF] == 0){
            BOARD[rank + addR][file + addF] = true;
          }else{
            if(pieceBoard[rank][file] > 0 && pieceBoard[rank+addR][file + addF] < 0){
                BOARD[rank+addR][file + addF] = true;
            }
            if(pieceBoard[rank][file] < 0 && pieceBoard[rank+addR][file + addF] > 0){
              BOARD[rank+addR][file + addF] = true;
            }
          }
        }
      }
    };
  Move(0,0,rank,file);
  Move(1,0,rank,file);
  Move(1,1,rank,file);
  Move(0,1,rank,file);
  Move(-1,1,rank,file);
  Move(1,-1,rank,file);
  Move(-1,-1,rank,file);
  Move(0,-1,rank,file);
  Move(-1,0,rank,file);
  pieceBoard[rank][file] = col ? K : k;

}
void getPawnMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]){
  BOARD[rank][file] = true;
  if (pieceBoard[rank][file] > 0){
     if((pieceBoard[rank - 1][file] == 0)){
      BOARD[rank - 1][file] = true;
      if(pieceBoard[rank - 2][file] == 0 && rank == 6){
        BOARD[rank - 2][file] = true;
      }  
    }
    if (pieceBoard[rank-1][file+1] < 0){
        BOARD[rank - 1][file+1] = true;
    }
    if (pieceBoard[rank-1][file-1] < 0){
        BOARD[rank - 1][file-1] = true;
    }
  }
  if (pieceBoard[rank][file] < 0){
     if((pieceBoard[rank + 1][file] == 0) ){
      BOARD[rank + 1][file] = true;
      if(pieceBoard[rank + 2][file] == 0 && rank == 1){
        BOARD[rank + 2][file] = true;
      }  
    }
    if (pieceBoard[rank+1][file+1] > 0){
        BOARD[rank + 1][file+1] = true;
    }
    if (pieceBoard[rank+1][file-1] > 0){
        BOARD[rank + 1][file-1] = true;
    }
  }
}
void getKnightMoves(int8_t rank, int8_t file,bool BOARD[8][8],int8_t pieceBoard[8][8]){
  BOARD[rank][file] = true;
  bool colour = pieceBoard[rank][file] > 0;
  auto Move = [pieceBoard,&BOARD,colour](int8_t addR, int8_t addF, int8_t rank, int8_t file){
    if(addR + rank < 8 && addF + file < 8 && addR + rank >= 0 && addF + file >= 0){
      if(whiteCheck){//white
        if(colour){
          int8_t piece = pieceBoard[rank + addR][file + addF];
          pieceBoard[rank + addR][file + addF] = N; 
          if(!checkAttackers(whiteKingPos[0],whiteKingPos[1],pieceBoard,colour)){
            BOARD[rank + addR][file + addF] = true;
          }
          pieceBoard[rank + addR][file + addF] = piece; 
        }
      }else if(blackCheck){
        if(!colour){
          int8_t piece = pieceBoard[rank + addR][file + addF];
          pieceBoard[rank + addR][file + addF] = n; 
          if(!checkAttackers(blackKingPos[0],blackKingPos[1],pieceBoard,colour)){
            BOARD[rank + addR][file + addF] = true;
          }
          pieceBoard[rank + addR][file + addF] = piece; 
        }
      }else if(pieceBoard[rank + addR][file + addF] == 0){
      BOARD[rank + addR][file + addF] = true;
      }else{
        if(pieceBoard[rank][file] > 0 && pieceBoard[rank+addR][file + addF] < 0){
            BOARD[rank+addR][file + addF] = true;
          }
          if(pieceBoard[rank][file] < 0 && pieceBoard[rank+addR][file + addF] > 0){
            BOARD[rank+addR][file + addF] = true;
          }
      }
    }
  };
  Move(2,1,rank,file);
  Move(-2,1,rank,file);
  Move(1,2,rank,file);
  Move(1,-2,rank,file);
  Move(-1,-2,rank,file);
  Move(-1,2,rank,file);
  Move(-2,-1,rank,file);
  Move(2,-1,rank,file);
}

void resetBoard(bool BOARD[8][8]){
  for(int8_t i = 0; i < 8; i++){
    for(int8_t j = 0; j < 8; j++){
      BOARD[i][j] = 0;
    }
  }
}
void resetBoard(int8_t BOARD[8][8]){
  for(int8_t i = 0; i < 8; i++){
    for(int8_t j = 0; j < 8; j++){
      BOARD[i][j] = 0;
    }
  }
}
void printBoard(bool BOARD[8][8]){
  for(int8_t i = 0; i < 8; i++){
    for(int8_t j = 0; j < 8; j++){
     Serial.print(BOARD[i][j]);
      Serial.print(" ");
    }
    Serial.print('\n');
  }
  Serial.println(" ");
}
void printBoard(int8_t BOARD[8][8]){
  for(int8_t i = 0; i < 8; i++){
    for(int8_t j = 0; j < 8; j++){
     Serial.print(BOARD[i][j]);
      Serial.print(" ");
    }
    Serial.print('\n');
  }
  Serial.println(" ");
}
