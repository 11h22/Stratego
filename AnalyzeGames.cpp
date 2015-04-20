#include <stdio.h>
#include <iostream>
#include <stdlib.h>   
using namespace std;

int RedPiece[10][10]={0};
int BluePiece[10][10]={0};
int m[10]={0};
int x1[10]={0};
int y1[10]={0};
int x2[10]={0};
int y2[10]={0};
char b=' ';
int main(){
  FILE * pFileR;
  pFileR = fopen ("/home/o/Stratego/Stratego.text", "r");
  for(int i=0;i<4;i++){//read in game data
    for(int j=0;j<10;j++){
      fscanf(pFileR,"%d",&RedPiece[i][j]);
      fscanf(pFileR,"%c",&b);
      }
    }
  for(int i=4;i<10;i++){
    for(int j=0;j<10;j++){
      fscanf(pFileR,"%d",&BluePiece[i][j]);
      fscanf(pFileR,"%c",&b);
    }
  }
  for(int i=0;i<10;i++){
    fscanf(pFileR,"%d",&m[i]);
    fscanf(pFileR,"%c",&b);
  }
  fclose (pFileR);
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      printf("%d,",RedPiece[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      printf("%d,",BluePiece[i][j]);
    }
    printf("\n");
  }
  for(int i=0;i<10;i++){
    x1[i]=m[i]/1000;
    y1[i]=(m[i]-(x1[i]*1000))/100;
    x2[i]=((m[i]-(x1[i]*1000))-(y1[i]*100))/10;
    y2[i]=(((m[i]-(x1[i]*1000))-(y1[i]*100))-(x2[i]*10));
    printf("MOVE %d %d,%d,%d,%d\n",m[i],x1[i],y1[i],x2[i],y2[i]);
    }
  //char * pEndGame;
  //pEndGame=strstr(str,"\n");
  char * str;
  char c=' ';
  char d=' ';
  int i=0;
  int counter=0;
  str = (char*)malloc(sizeof(char));
  pFileR = fopen ("/home/o/Stratego/Stratego.text", "r");
  if (pFileR==NULL) {
    perror ("Error opening file");
  }
  while(c!=EOF) {//search for end of games
    c = getc(pFileR);
    counter++;
    if (c=='\n'){
      while(d!='\n'){
	d=getc(pFileR);
	str = (char*)realloc(str,(i+1)*sizeof(char));
	str[i]=d;
	i++;
	counter++;
      }
      c=' ';
      d=' ';
    }
  }
  fclose (pFileR);
  printf("%s",str);
  printf("%d\n",counter);
}
