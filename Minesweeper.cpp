#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
char table[30][30];
int flag;

class Minesweeper{
  
  private:
     int table_length;
     int table_width;
     int mines;
  public:
     char table_coord[16][16];
     char minesmap[16][16];
     void setting(int set_length, int set_width, int set_mines){
         table_length = set_length;
         table_width = set_width;
         mines = set_mines;
     }
     int GetMines(){
         int MinesTemp = mines;
         return MinesTemp;
     }
     int GetWidth(){
         int WidthTemp = table_width;
         return WidthTemp;
     }
     int GetLength(){
         int LengthTemp = table_length;
         return LengthTemp;
     }
  
};

void print_fail(Minesweeper* game){
  
  int i,j;
  char coll = 'a';
  
  cout << endl << "0-uncover 1-mark mine" << endl;
  cout << "  a b c d e f g h i j k l m n o p" << endl;
  cout << "  -------------------------------" << endl;
  cout << coll;
  for(i=0;i<16;i++){
    for(j=0;j<16;j++){
      cout << ' ' << (*game).minesmap[i][j];
    }
    cout << endl;
    coll++;
    if(coll != 'q'){
      cout << coll;
    }
  }
  cout << "  -------------------------------" << endl;
  cout << "You Fail!" << endl;
  
}

void mine_initial(Minesweeper* game){
    
    int i,j,mines_index,x,y,a,b;
    char mines_count = '0';
    int set_mines[16][16]={0};
    char temp[16][16];
    mines_index = 0;
    srand(time(0));
    
    do{
        do{
            i = rand()%16;
            j = rand()%16;
        }while(set_mines[i][j]!=0);
        set_mines[i][j] = 1;
        mines_index++;
    }while(mines_index!=(*game).GetMines());
    
    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            if(set_mines[i][j] == 0){
                (*game).table_coord[i][j] = '-';
            }
            if(set_mines[i][j] == 1){
                (*game).table_coord[i][j] = '*';
            }
        }
    }
    
    for(i=0;i<16;i++){
      for(j=0;j<16;j++){
        x=i;y=j;
        if((*game).table_coord[x][y]!='*'){
          //if(temp[x][y] == 0){
            for(a=x-1;a<=x+1;a++){
              for(b=y-1;b<=y+1;b++){
                if((a!=x)|(b!=y)){
                  if((a>=0)&(a<=15)&(b>=0)&(b<=15)){
                    if((*game).table_coord[a][b]=='*'){
                      mines_count+=1;
                    }
                  }
                }
              }
            }
         // }
        }
        temp[x][y] = mines_count;
        mines_count = '0';
      }
    }
    
    for(i=0;i<16;i++){
      for(j=0;j<16;j++){
        if((*game).table_coord[i][j] == '-'){
          (*game).minesmap[i][j] = temp[i][j];
        }else{
          (*game).minesmap[i][j] = (*game).table_coord[i][j];
        }
      }
    }
    
    
}

void table_initial(int width,int length){
  
  int i,j;
  for(i=0;i<width;i++){
    for(j=0;j<length;j++){
      table[i][j] = '-';
    }
  }
}

void print_table(int width,int length){
  
  int i,j;
  char coll='a';
  
  cout << endl << "0-uncover 1-mark mine" << endl;
  cout << "  a b c d e f g h i j k l m n o p" << endl;
  cout << "  -------------------------------" << endl;
  cout << coll;
  for(i=0;i<width;i++){
    for(j=0;j<length;j++){
      cout  << " " << table[i][j];
    }
    cout << endl;
    coll++;
    if(coll != 'q'){
      cout << coll;
    }
  }
  
}

void game_initial(Minesweeper* game){
    
    int i,j,remain_mines=(*game).GetMines();
    int width = (*game).GetWidth();
    int length = (*game).GetLength();
    
    flag = 1;
    
    
    mine_initial(game);
    table_initial(width,length);
    cout << "Height:16 Witdh:16 Mines:40"<< endl;
    print_table(width,length);
    
}

int check_input(int x,int y,int operate,int width,int length){
  
  int c;
  if(x<0|x>=width|y<0|y>=length|operate<0|operate>1){
     c = 0;
  }else{
    c = 1;
  }
  return c;
  
}

bool check_mine(int x,int y,int width,int length,Minesweeper* game){
  
  bool c_mine;
  if((*game).table_coord[x][y] == '*' ){
     cout<< (*game).table_coord[x][y] << endl;
     c_mine = 1;
  }else{
     c_mine = 0;
  }
  return c_mine;
  
}

void uncover(int x,int y,Minesweeper* game);

void operation(int x,int y,int operate,Minesweeper* game){
 
  int width = (*game).GetWidth();
  int length = (*game).GetLength();
  
  bool c_mine = check_mine(x,y,width,length,game); 
  if(operate){
    
    if(table[x][y] == '-'){
      table[x][y] = '#';
    }
    print_table(width,length);
    
  }else{
    
    if(c_mine){
      flag = 0;
    }else{
      uncover(x,y,game);
      print_table(width,length);
    }
    
  }
  cout << endl;
  
}

int uncover_check(int c ,Minesweeper* game){
  
  int i,j,a,b,t=0;
  
  for(i=0;i<16;i++){
    for(j=0;j<16;j++){
      if(table[i][j]=='0'){
        for(a=i-1;a<=i+1;a++){
          for(b=j-1;b<=j+1;b++){
            if(table[a][b] == '-'){
              if((*game).minesmap[a][b]!='*'){
                table[a][b] = (*game).minesmap[a][b];
                t = 1;
              }
            }
          }
        }
      }
    }
  }
  
  if(t == 1){
    c = 1;
  }else{
    c = 0;
  }
  
  return c;
}

void uncover(int x,int y,Minesweeper* game){
  
  int i,j,a,b,c;
  int width = (*game).GetWidth();
  int length = (*game).GetLength();
  
  if((*game).minesmap[x][y]=='*'){
    flag = 0;
  }else{
    if((*game).minesmap[x][y]!='0'){
        table[x][y] = (*game).minesmap[x][y];
    }else{
      c = 1;
      table[x][y] = (*game).minesmap[x][y];
      for(i=x-1;i<=x+1;i++){
        for(j=y-1;j<=y+1;j++){
          if((i>=0)&(i<=15)&(j>=0)&(j<=15)){
            if((*game).minesmap[i][j]!='*'){
                table[i][j] = (*game).minesmap[i][j];
            }
          }
        }
      }
    }
  }
  
  while(c == 1){
    c = uncover_check(c,game);
  }
  
}

void check_win(Minesweeper* game){
  
  int i,j,c = 0;
  
  for(i=0;i<16;i++){
    for(j=0;j<16;j++){
      if((*game).minesmap[i][j]!='*'){
        if(table[i][j] == '-'){
          c++;
        }
      }
    }
  }
  
  while(c == 0){
    cout<<endl<< "YOU WIN!"<<endl;
    game_initial(game);
  }
  
}

int main(){
    
    Minesweeper game;
    game.setting(16,16,40);
    int width = game.GetWidth();
    int length = game.GetLength();
    int mines = game.GetMines();
    int cover_mine=0;
    
    game_initial(&game);
    while(flag){
      
     cout << "enter (x y 0/1): ";
     char x_coll,y_coll;
     int x,y,operate,c=3;
     cin >> x_coll >> y_coll>>operate;
     x = x_coll - 96;
     y = y_coll - 96;
     
     x=x-1;
     y=y-1;
     c = check_input(x,y,operate,width,length);
     
     
     if(c==1){
       operation(x,y,operate,&game);
       check_win(&game);
     }else{
       cout << "Illegal Input! " << endl;
     }
      
    }
    print_fail(&game);
    
    return 0;
}