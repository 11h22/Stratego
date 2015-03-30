#include <stdio.h>
#include <iostream>
#include <stdlib.h>    
#include <time.h>  
#include <string.h>
using namespace std;

class Game{

public:
  Game();
  ~Game();
  void Initialize();

}; 
Game::Game(){}
Game::~Game(){
  cout<<"Cleaning up memory"<<endl;
  cout<<"Ended Game Cleanly"<<endl;
}
void Game::Initialize(){

int main(){
  Game *GO= new Game();

  delete GO;
}
  /*fgets(word1, 100, stdin);*/
