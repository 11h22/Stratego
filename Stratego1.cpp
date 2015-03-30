#include <stdio.h>
#include <iostream>
#include <stdlib.h>    
#include <time.h>  
#include <string.h>
using namespace std;

class Game{
  int Board[10][10];//0 is water 1 is empty space and 2 is space with unknown piece
  int Pieces[40];
  int RedPiece[10][10];
  int BluePiece[10][10];
public:
  Game();
  ~Game();
  void Initialize();
  void ShowBoard(bool a, bool b);
  void SetupBoard(bool a, bool b);
}; 
Game::Game(){}
Game::~Game(){
  cout<<"Cleaning up memory"<<endl;
  cout<<"Ended Game Cleanly"<<endl;
}
void Game::Initialize(){
  Pieces[0]=10;Pieces[10]=6;Pieces[20]=3;Pieces[30]=2;
  Pieces[1]=9; Pieces[11]=5;Pieces[21]=3;Pieces[31]=2;
  Pieces[2]=8; Pieces[12]=5;Pieces[22]=3;Pieces[32]=1;
  Pieces[3]=8; Pieces[13]=5;Pieces[23]=3;Pieces[33]=11;
  Pieces[4]=7; Pieces[14]=5;Pieces[24]=2;Pieces[34]=11;
  Pieces[5]=7; Pieces[15]=4;Pieces[25]=2;Pieces[35]=11;
  Pieces[6]=7; Pieces[16]=4;Pieces[26]=2;Pieces[36]=11;
  Pieces[7]=6; Pieces[17]=4;Pieces[27]=2;Pieces[37]=11;
  Pieces[8]=6; Pieces[18]=4;Pieces[28]=2;Pieces[38]=11;
  Pieces[9]=6; Pieces[19]=3;Pieces[29]=2;Pieces[39]=12; 
  for (int i=0;i<10;i++){
    for (int j=0;j<10;j++){
      Board[i][j]=1;
      RedPiece[i][j]=0;
      BluePiece[i][j]=0;
      if (i==4 || i==5){
	if (j==2||j==3||j==6||j==7){
	  Board[i][j]=0;
	}
      }
    }
  }
  /*for (int i=0;i<10;i++){ //just to put pieces on the board
    for (int j=0;j<10;j++){
      if (i<4){
        RedPiece[i][j]=Pieces[j+(i*10)];
	Board[i][j]=2;
      }
      if (i>5){
	BluePiece[i][j]=Pieces[j+((i-6)*10)];
	Board[i][j]=2;
      }
    }
   }*/
}
void Game::ShowBoard(bool a, bool b){
  for (int i=0;i<10;i++){
    for (int j=0;j<10;j++){
      if (Board[i][j]==0){
	printf("W\t");
      }
      if (Board[i][j]==1){
	printf("_\t");
      }
      if(a){
	if (RedPiece[i][j]!=0){
	  printf("%d\t",RedPiece[i][j]);
	}
        else if (b==0 && Board[i][j]==2){
	  printf("D\t");
	}
      }
      if (b){
	if (BluePiece[i][j]!=0){
	  printf("%d\t",BluePiece[i][j]);
	}
        else if (a==0 && Board[i][j]==2){
	  printf("D\t");	
	}
      }
    }   
    printf("\n");
  }
  printf("\n");
}
void Game::SetupBoard(bool a, bool b){
  
}
int main(){
  Game *GO= new Game();
  GO->Initialize();
  GO->ShowBoard(1,1);
  delete GO;
}
