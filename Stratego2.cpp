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
  int DeadRed[40];
  int numberofdeadred;
  int DeadBlue[40];
  int numberofdeadblue;
  int numofmoves;
  int *possiblex1;
  int *possibley1;
  int *possiblex2;
  int *possibley2;
  int moves;
public:
  Game();
  ~Game();
  void Initialize();
  void ShowBoard(bool a, bool b);
  void SetupBoard(bool a, bool b);
  void Play();
  bool checkifmoveislegal(int cx1,int cy1,int cx2,int cy2) const;
  void movepiece();
  int CheckforMoves();
  void AskUsertomove();
  void AskComptomove();
  void SaveGame();
}; 
Game::Game(){}
Game::~Game(){
  cout<<"Cleaning up memory"<<endl;
  cout<<"Ended Game Cleanly"<<endl;
}
void Game::Initialize(){
  Pieces[0]=10;Pieces[10]=6;Pieces[20]=3;Pieces[30]=2;
  Pieces[1]=9; Pieces[11]=5;Pieces[21]=3;Pieces[31]=2;
  Pieces[2]=8; Pieces[12]=5;Pieces[22]=3;Pieces[32]=1; //Spy
  Pieces[3]=8; Pieces[13]=5;Pieces[23]=3;Pieces[33]=11;//11 are bombs
  Pieces[4]=7; Pieces[14]=5;Pieces[24]=2;Pieces[34]=11;
  Pieces[5]=7; Pieces[15]=4;Pieces[25]=2;Pieces[35]=11;
  Pieces[6]=7; Pieces[16]=4;Pieces[26]=2;Pieces[36]=11;
  Pieces[7]=6; Pieces[17]=4;Pieces[27]=2;Pieces[37]=11;
  Pieces[8]=6; Pieces[18]=4;Pieces[28]=2;Pieces[38]=11;
  Pieces[9]=6; Pieces[19]=3;Pieces[29]=2;Pieces[39]=12;//12 is the flag
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
  for(int i=0;i<40;i++){
    DeadRed[i]=DeadBlue[i]=0;
  }
  moves=0;
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
	else if (b==0 && Board[i][j]==3){
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
  int p=0;
  numberofdeadred=numberofdeadblue=0;
  printf("0 for premade set up  1 for manual");
  scanf("%d",&p);
  if ((bool)p){
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
	Board[x][y]=2;
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
	  printf("stick to the bottom half\n");
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
	Board[x][y]=3;
	ShowBoard(0,1);
	i++;
      }
    }
  }
  else {
    if (a){
      RedPiece[0][0]=2;RedPiece[0][1]=3;RedPiece[0][2]=11;RedPiece[0][3]=2;
      RedPiece[0][4]=3;RedPiece[0][5]=11;RedPiece[0][6]=12;RedPiece[0][7]=11;
      RedPiece[0][8]=3;RedPiece[0][9]=3;RedPiece[1][0]=4;RedPiece[1][1]=11;
      RedPiece[1][2]=4;RedPiece[1][3]=7;RedPiece[1][4]=8;RedPiece[1][5]=5;
      RedPiece[1][6]=11;RedPiece[1][7]=5;RedPiece[1][8]=6;RedPiece[1][9]=4;
      RedPiece[2][0]=5;RedPiece[2][1]=4;RedPiece[2][2]=11;RedPiece[2][3]=1;
      RedPiece[2][4]=9;RedPiece[2][5]=2;RedPiece[2][6]=7;RedPiece[2][7]=7;
      RedPiece[2][8]=8;RedPiece[2][9]=2;RedPiece[3][0]=6;RedPiece[3][1]=2;
      RedPiece[3][2]=2;RedPiece[3][3]=5;RedPiece[3][4]=2;RedPiece[3][5]=6;
      RedPiece[3][6]=3;RedPiece[3][7]=10;RedPiece[3][8]=2;RedPiece[3][9]=6;
      for (int i=0;i<10;i++){ //just to put pieces on the board
	for (int j=0;j<10;j++){
	  if (i<4){
	    //RedPiece[i][j]=Pieces[j+(i*10)];
	    Board[i][j]=2;
	  }
	}
      }
      ShowBoard(1,0);
    }
    if (b){
      BluePiece[9][0]=12;BluePiece[9][1]=11;BluePiece[9][2]=3;BluePiece[9][3]=3;
      BluePiece[9][4]=3;BluePiece[9][5]=6;BluePiece[9][6]=2;BluePiece[9][7]=2;
      BluePiece[9][8]=6;BluePiece[9][9]=2;BluePiece[8][0]=11;BluePiece[8][1]=7;
      BluePiece[8][2]=3;BluePiece[8][3]=3;BluePiece[8][4]=8;BluePiece[8][5]=7;
      BluePiece[8][6]=2;BluePiece[8][7]=7;BluePiece[8][8]=4;BluePiece[8][9]=2;
      BluePiece[7][0]=8;BluePiece[7][1]=1;BluePiece[7][2]=11;BluePiece[7][3]=6;
      BluePiece[7][4]=4;BluePiece[7][5]=2;BluePiece[7][6]=2;BluePiece[7][7]=11;
      BluePiece[7][8]=5;BluePiece[7][9]=6;BluePiece[6][0]=11;BluePiece[6][1]=9;
      BluePiece[6][2]=10;BluePiece[6][3]=2;BluePiece[6][4]=4;BluePiece[6][5]=5;
      BluePiece[6][6]=4;BluePiece[6][7]=5;BluePiece[6][8]=5;BluePiece[6][9]=11;
      for (int i=0;i<10;i++){ //just to put pieces on the board
	for (int j=0;j<10;j++){
	  if (i>5){
	    //BluePiece[i][j]=Pieces[j+((i-6)*10)];
	    Board[i][j]=3;
	  }
	}
      }
      ShowBoard(0,1);
    }
  }
}
void Game::Play(){
  x1=y1=x2=y2=end=0;
  whoseturn=1;
  FILE * pFileW;
  pFileW = fopen ("/home/o/Stratego/Stratego.text", "a");
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      if(RedPiece[i][j]==0&&BluePiece[i][j]==0){
	fprintf(pFileW,"0,");
      }
      else if(RedPiece[i][j]!=0){
	fprintf(pFileW,"%d,",RedPiece[i][j]);
      }
      else if(BluePiece[i][j]!=0){
	fprintf(pFileW,"%d,",BluePiece[i][j]);
      }
    }
  }
  fclose (pFileW);
  while(!end){
    printf("Dead Red Pieces\n");
    for (int i=0;i<numberofdeadred+1;i++){
      printf("%d,",DeadRed[i]);
    }
    printf("\nDead Blue Pieces\n");
    for (int i=0;i<numberofdeadblue+1;i++){
      printf("%d,",DeadBlue[i]);
    }
    printf("\n");
    numofmoves=CheckforMoves();
    printf("Number of moves: %d\n",numofmoves);
    if(numofmoves==0){
      end=1;
      free(possiblex1);
      free(possibley1);
      free(possiblex2);
      free(possibley2);
      continue;
    }
    if(whoseturn==1){
      //ShowBoard(1,0);
      printf("\nRed Moves\n");
      //AskUsertomove();
      AskComptomove();
    }
    if(whoseturn==2){
      //ShowBoard(0,1);
      printf("\nBlue Moves\n");
      AskComptomove();
    }
    if(checkifmoveislegal(x1,y1,x2,y2)){
      printf("Not Legal\n");
      continue;
    }
    movepiece();
    free(possiblex1);
    free(possibley1);
    free(possiblex2);
    free(possibley2);
    moves++;
    SaveGame();
  }
  printf("game over\n");
  if (whoseturn==1){
    printf("Blue Wins\n");
    FILE * pFileW;
    pFileW = fopen ("/home/o/Stratego/Stratego.text", "a");
    fprintf(pFileW,"Blue Wins\n");
    fclose (pFileW);
  }
  else{
    printf("Red Wins\n");
    FILE * pFileW;
    pFileW = fopen ("/home/o/Stratego/Stratego.text", "a");
    fprintf(pFileW,"Red Wins\n");
    fclose (pFileW);
  }
}
void Game::AskUsertomove(){
  bool going=1;
  while(going){
    printf("Which Piece to move?\nWhich Row: ");
    scanf("%d",&x1);
    if (x1<0||x1>9){
      printf("Bad move\n");
      continue;
    }
    printf("Which Column: ");
    scanf("%d",&y1);
    if (y1<0||y1>9){
      printf("Bad move\n");
      continue;
    }
    printf("To Where?\nWhich Row: ");
    scanf("%d",&x2);
    if (x2<0||x2>9){
      printf("Bad move\n");
      continue;
    }
    printf("Which Column: ");
    scanf("%d",&y2);
    if (y2<0||y2>9){
      printf("Bad move\n");
      continue;
    }
    going=0;
  }
}
void Game::AskComptomove(){
  int t=0;
  srand (time(NULL));//random choice
  t =rand() % numofmoves;
  x1=possiblex1[t];
  y1=possibley1[t];
  x2=possiblex2[t];
  y2=possibley2[t];
}
bool Game::checkifmoveislegal(int cx1,int cy1,int cx2,int cy2) const{
  if (whoseturn==1){//red turn
    if(Board[cx1][cy1]!=0&&Board[cx2][cy2]!=0){//neither choice was water
      if (RedPiece[cx1][cy1]!=0&&RedPiece[cx1][cy1]!=11&&RedPiece[cx1][cy1]!=12&&RedPiece[cx2][cy2]==0){//cant move if space is empty, bomb or flag
	if (RedPiece[cx1][cy1]!=2){
	  if (cx2==cx1+1||cx2==cx1-1||cy2==cy1+1||cy2==y1-1){//
	    return 0;
	  }
	} 
	else if (RedPiece[cx1][cy1]==2){//need to make sure nothing is in the way
	  int diffx=0;
	  int diffy=0;
	  diffx=abs(cx2-cx1);
	  diffy=abs(cy2-cy1);
	  if(cx2-cx1>0){
	    for (int i=1;i<diffx;i++){
	      if (Board[cx1+i][cy1]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(cx2-cx1<0){
	    for (int i=1;i<diffx;i++){
	      if (Board[cx1-i][cy1]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(cy2-cy1>0){
	    for (int i=1;i<diffy;i++){
	      if (Board[cx1][cy1+i]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(cy2-cy1<0){
	    for (int i=1;i<diffy;i++){
	      if (Board[cx1][cy1-i]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(diffx==0&&diffy==0){
	    return 1;
	  }
	  return 0;
	}
      }
    }
  }
  else if(whoseturn==2){//blue turn
    if(Board[cx1][cy1]!=0&&Board[cx2][cy2]!=0){//neither choice was water
      if (BluePiece[cx1][cy1]!=0&&BluePiece[cx1][cy1]!=11&&BluePiece[cx1][cy1]!=12&&BluePiece[cx2][cy2]==0){//cant move if space is empty, bomb or flag
	if (BluePiece[cx1][cy1]!=2){
	  if (cx2==cx1+1||cx2==cx1-1||cy2==cy1+1||cy2==cy1-1){//
	    return 0;
	  }
	} 
	else if (BluePiece[cx1][cy1]==2){
	  int diffx=0;
	  int diffy=0;
	  diffx=abs(cx2-cx1);
	  diffy=abs(y2-y1);
	  if(cx2-cx1>0){
	    for (int i=1;i<diffx;i++){
	      if (Board[cx1+i][cy1]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(cx2-cx1<0){
	    for (int i=1;i<diffx;i++){
	      if (Board[cx1-i][cy1]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(cy2-cy1>0){
	    for (int i=1;i<diffy;i++){
	      if (Board[cx1][cy1+i]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(cy2-cy1<0){
	    for (int i=1;i<diffy;i++){
	      if (Board[cx1][cy1-i]!=1){//
		return 1;
	      }
	    }
	  }
	  else if(diffx==0&&diffy==0){
	    return 1;
	  }
	  return 0;
	}
      }
    }
  }
  return 1;
}
void Game::movepiece(){
  int movedpiece=0;
  if (whoseturn==1){
    movedpiece=RedPiece[x1][y1];
    RedPiece[x1][y1]=0;
    Board[x1][y1]=1;
    if (BluePiece[x2][y2]==12){//flag captured
      end=1;
    }
    if (movedpiece==3&&BluePiece[x2][y2]==11){//bomb defused by 3
      //DeadBlue[numberofdeadblue]=BluePiece[x2][y2];
      //numberofdeadblue++;
      BluePiece[x2][y2]=0;
      Board[x2][y2]=2;
      printf("Bomb Defused by 3");
    }
    if (movedpiece==1&&BluePiece[x2][y2]==10){//Spy kills 10
      //DeadBlue[numberofdeadblue]=BluePiece[x2][y2];
      //numberofdeadblue++;
      BluePiece[x2][y2]=0;
      Board[x2][y2]=2;
      printf("Spy kills 10");
    }
    if (BluePiece[x2][y2]!=0){
      if(movedpiece<=BluePiece[x2][y2]){
	DeadRed[numberofdeadred]=movedpiece;
	numberofdeadred++;
	printf("Blue %d kills Red %d",BluePiece[x2][y2],movedpiece);
	//redpiece dies
      }
      if(movedpiece>BluePiece[x2][y2]){
	DeadBlue[numberofdeadblue]=BluePiece[x2][y2];
	numberofdeadblue++;
	printf("Red %d kills Blue %d",movedpiece,BluePiece[x2][y2]);
	BluePiece[x2][y2]=0;
	Board[x2][y2]=2;
      }
    }  
    else{
      RedPiece[x2][y2]=movedpiece;
      Board[x2][y2]=2;
    }
    whoseturn=2;
  }
  else{
    movedpiece=BluePiece[x1][y1];
    BluePiece[x1][y1]=0;
    Board[x1][y1]=1;
    if (RedPiece[x2][y2]==12){//flag captured
      end=1;
    }
    if (movedpiece==3&&RedPiece[x2][y2]==11){//bomb defused by 3
      //DeadBlue[numberofdeadblue]=BluePiece[x2][y2];
      //numberofdeadblue++;
      RedPiece[x2][y2]=0;
      Board[x2][y2]=3;
      printf("Bomb defused by 3");
    }
    if (movedpiece==1&&RedPiece[x2][y2]==10){//Spy kills 10
      //DeadBlue[numberofdeadblue]=BluePiece[x2][y2];
      //numberofdeadblue++;
      RedPiece[x2][y2]=0;
      Board[x2][y2]=3;
      printf("Spy kills 10");
    }
    if (RedPiece[x2][y2]!=0){
      if(movedpiece<=RedPiece[x2][y2]){
	DeadBlue[numberofdeadblue]=movedpiece;
	numberofdeadblue++;
	//bluepiece dies
	printf("Red %d kills Blue %d",RedPiece[x2][y2],movedpiece);
      }
      if(movedpiece>RedPiece[x2][y2]){
	DeadRed[numberofdeadred]=RedPiece[x2][y2];
	numberofdeadred++;
	printf("Blue %d kills Red %d",movedpiece,RedPiece[x2][y2]);
	RedPiece[x2][y2]=0;
      	Board[x2][y2]=3;
      }
    }  
    else{
      BluePiece[x2][y2]=movedpiece;
      Board[x2][y2]=3;
    }
    whoseturn=1;
  }
}
int Game::CheckforMoves(){
  int numberofmoves=0;
  possiblex1 = (int*)malloc(sizeof(int));
  possibley1 = (int*)malloc(sizeof(int));
  possiblex2 = (int*)malloc(sizeof(int));
  possibley2 = (int*)malloc(sizeof(int));
  if (whoseturn==1){
    for (int i=0;i<10;i++){
      for (int j=0;j<10;j++){
	if (RedPiece[i][j]!=0){
	  if(RedPiece[i][j]!=2){
	    if(i<9){
	      if(!checkifmoveislegal(i,j,i+1,j)){
		//printf("%d %d to %d %d\n",i,j,i+1,j);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i+1;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j;
	      }
	    }
	    if(j<9){
	      if(!checkifmoveislegal(i,j,i,j+1)){
		//printf("%d %d to %d %d\n",i,j,i,j+1);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j+1;
	      }
	    }
	    if(i>0){
	      if(!checkifmoveislegal(i,j,i-1,j)){
		//printf("%d %d to %d %d\n",i,j,i-1,j);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i-1;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j;
	      }
	    }
	    if(j>0){
	      if(!checkifmoveislegal(i,j,i,j-1)){
		//printf("%d %d to %d %d\n",i,j,i,j-1);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j-1;
	      }
	    }
	  }
	  if(RedPiece[i][j]==2){
	    if(i<9){
	      for(int k=1;k<10-i;k++){
		if(!checkifmoveislegal(i,j,i+k,j)){
		  //printf("%d %d to %d %d\n",i,j,i+k,j);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i+k;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j;
		}
	      }
	    }
	    if(j<9){
	      for(int k=1;k<10-j;k++){
		if(!checkifmoveislegal(i,j,i,j+k)){
		  //printf("%d %d to %d %d\n",i,j,i,j+k);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j+k;
		}
	      }
	    }
	    if(i>0){
	      for(int k=1;k<i+1;k++){
		if(!checkifmoveislegal(i,j,i-k,j)){
		  //printf("%d %d to %d %d\n",i,j,i-k,j);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i-k;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j;
		}
	      }
	    }
	    if(j>0){
	      for(int k=1;k<j+1;k++){
		if(!checkifmoveislegal(i,j,i,j-k)){
		  //printf("%d %d to %d %d\n",i,j,i,j-k);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j-k;
		}
	      }
	    }
	  }
	}
      }
    }
  }
  else if (whoseturn==2){
    for (int i=0;i<10;i++){
      for (int j=0;j<10;j++){
	if (BluePiece[i][j]!=0){
	  if(BluePiece[i][j]!=2){
	    if(i<9){
	      if(!checkifmoveislegal(i,j,i+1,j)){
		//printf("%d %d to %d %d\n",i,j,i+1,j);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i+1;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j;
	      }
	    }
	    if(j<9){
	      if(!checkifmoveislegal(i,j,i,j+1)){
		//printf("%d %d to %d %d\n",i,j,i,j+1);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j+1;
	      }
	    }
	    if(i>0){
	      if(!checkifmoveislegal(i,j,i-1,j)){
		//printf("%d %d to %d %d\n",i,j,i-1,j);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i-1;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j;
	      }
	    }
	    if(j>0){
	      if(!checkifmoveislegal(i,j,i,j-1)){
		//printf("%d %d to %d %d\n",i,j,i,j-1);
		numberofmoves++;
		possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		possiblex1[numberofmoves-1]=i;
		possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		possibley1[numberofmoves-1]=j;
		possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		possiblex2[numberofmoves-1]=i;
		possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		possibley2[numberofmoves-1]=j-1;
	      }
	    }
	  }
	  if(BluePiece[i][j]==2){
	    if(i<9){
	      for(int k=1;k<10-i;k++){
		if(!checkifmoveislegal(i,j,i+k,j)){
		  //printf("%d %d to %d %d\n",i,j,i+k,j);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i+k;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j;
		}
	      }
	    }
	    if(j<9){
	      for(int k=1;k<10-j;k++){
		if(!checkifmoveislegal(i,j,i,j+k)){
		  //printf("%d %d to %d %d\n",i,j,i,j+k);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j+k;
		}
	      }
	    }
	    if(i>0){
	      for(int k=1;k<i+1;k++){
		if(!checkifmoveislegal(i,j,i-k,j)){
		  //printf("%d %d to %d %d\n",i,j,i-k,j);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i-k;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j;
		}
	      }
	    }
	    if(j>0){
	      for(int k=1;k<j+1;k++){
		if(!checkifmoveislegal(i,j,i,j-k)){
		  //printf("%d %d to %d %d\n",i,j,i,j-k);
		  numberofmoves++;
		  possiblex1 = (int*)realloc(possiblex1,numberofmoves*sizeof(int));
		  possiblex1[numberofmoves-1]=i;
		  possibley1 = (int*)realloc(possibley1,numberofmoves*sizeof(int));
		  possibley1[numberofmoves-1]=j;
		  possiblex2 = (int*)realloc(possiblex2,numberofmoves*sizeof(int));
		  possiblex2[numberofmoves-1]=i;
		  possibley2 = (int*)realloc(possibley2,numberofmoves*sizeof(int));
		  possibley2[numberofmoves-1]=j-k;
		}
	      }
	    }
	  }
	}
      }
    }
  }
  return numberofmoves;
}
void Game::SaveGame(){//each game is about 80 kb
  FILE * pFileW;
  pFileW = fopen ("/home/o/Stratego/Stratego.text", "a");
  fprintf(pFileW,"%d%d%d%d,",x1,y1,x2,y2);
  fclose (pFileW);
}
  /*  FILE * pFileR;
  pFileR = fopen ("/home/o/Parse/Stratego.text", "r");
  for(int k=0;k<moves;k++){
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
	fscanf(pFileR,"%d",&RedPiece[i][j]);
	fscanf(pFileR,"%d",&BluePiece[i][j]);
      }
    }
  }
  fclose (pFileR);*/
int main(){
  int gamess=0;
  printf("How many games to play?(80kb per game)");
  scanf("%d",&gamess);
  for(int g=0;g<gamess;g++){
    Game *GO= new Game();
    GO->Initialize();
    GO->ShowBoard(1,1);
    GO->SetupBoard(1,0);
    GO->SetupBoard(0,1);
    GO->Play();
    delete GO;
  }
}
