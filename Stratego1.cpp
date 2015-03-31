#include <stdio.h>
#include <iostream>
#include <stdlib.h>    
#include <time.h>  
#include <string.h>
using namespace std;

class Game{
  int Board[10][10];//0 is water 1 is empty space and 2 is space with unknown red piece 3 is space with unknown blue piece
  int Pieces[40];
  int RedPiece[10][10];
  int BluePiece[10][10];
  int x1;
  int y1;
  int x2;
  int y2;
  int whoseturn;//1 for red 2 for blue
  bool end;
public:
  Game();
  ~Game();
  void Initialize();
  void ShowBoard(bool a, bool b);
  void SetupBoard(bool a, bool b);
  void Play();
  void checkifmoveislegal();
  void movepiece();
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
      if (i==0 && j==0){
	printf("\tCol0\tCol1\tCol2\tCol3\tCol4\tCol5\tCol6\tCol7\tCol8\tCol9\n");
      }
      if (j==0){
	printf("Row %d\t",i);
      }

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
  int x=0;
  int y=0;
  int i=0;
  if (a){
    while(i<40){
      printf("Which Row to put %d:", Pieces[i]);
      scanf("%d",&x);
      printf("Which Column to put %d:", Pieces[i]);
      scanf("%d",&y);
      //check if its legal
      if (x>3){
	printf("stick to the top half\n");
	continue;
      }
      if (Board[x][y]!=1){
	printf("Something is in the way\n");
	continue;
      }
      if (x<0 || x>9 ||y<0||y>9){
	printf("Off of board\n");
	continue;
      }
      RedPiece[x][y]=Pieces[i];
      Board[x][y]=3;
      ShowBoard(1,0);
      i++;
    }
  }
  x=y=i=0;
  if (b){
    while(i<40){
      printf("Which Row to put %d:", Pieces[i]);
      scanf("%d",&x);
      printf("Which Column to put %d:", Pieces[i]);
      scanf("%d",&y);
      //check if its legal
      if (x<6){
	printf("stick to the top half\n");
	continue;
      }
      if (Board[x][y]!=1){
	printf("Something is in the way\n");
	continue;
      }
      if (x<0 || x>9 ||y<0||y>9){
	printf("Off of board\n");
	continue;
      }
      BluePiece[x][y]=Pieces[i];
      Board[x][y]=4;
      ShowBoard(0,1);
      i++;
    }
  }
}
void Game::Play(){
  x1=y1=x2=y2=end=0;
  whoseturn=1;
  while(end==0){
    if(whoseturn==1)
      printf("Red Moves");
    if(whoseturn==2)
      printf("Blue Moves");
    printf("Which Piece to move?\nWhich Row: ");
    scanf("%d",&x1);
    printf("Which Column: ");
    scanf("%d",&y1);
    printf("To Where?\nWhich Row: ");
    scanf("%d",&x2);
    printf("Which Column: ");
    scanf("%d",&y2);
    checkifmoveislegal();
    movepiece();
  }
}
void Game::checkifmoveislegal(){

}
void Game::movepiece(){
}
int main(){
  Game *GO= new Game();
  GO->Initialize();
  GO->ShowBoard(1,1);
  GO->SetupBoard(1,0);
  GO->SetupBoard(0,1);
  delete GO;
}
