#include "wall.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

bool validate(const int y, const int x, const int max_y, const int max_x, char const*const*map);
bool victory(const int y, const int x, char const*const*map);
void Prims(char** map, int map_hight, int map_width, int y_start, int x_start, int y, int x);

int main()
{
  srand(time(NULL));
  int map_hight, map_width, y_start=1, x_start=1, step, x, y;
  char **map;
  bool go=true;
  

  initscr();  
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_CYAN);
  init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(4, COLOR_CYAN, COLOR_CYAN);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  keypad(stdscr,true);
  cbreak();
  //Geting hight and width from user.
  while(go)
  {
    mvprintw(LINES/2,(COLS-31)/2,"Please enter a hight in (6,%d).  ",LINES);
    refresh();
    scanw("%d",&map_hight);
    clear();
    if(map_hight > LINES || map_hight < 6)
    {
      clear();
      mvprintw(LINES/2,(COLS-31)/2,"Size not supported by Terminal.");
      refresh();
      getch();
      clear();
    }
    else
      {
        mvprintw(LINES/2,(COLS-31)/2,"Please enter a width in (6,%d).  ",COLS);
        refresh();
	scanw("%d",&map_width);
        clear();
        if(map_width > COLS || map_width < 6)
        {
          mvprintw(LINES/2,(COLS-31)/2,"Size not supported by Terminal.");
          refresh();
          getch();
          clear();
        }
        else
          go = false;
      }
    clear();
  }
  cbreak();
  noecho();

  //Building map.
  map = new char*[map_hight];
  for(int k=0; k<map_hight; k++)
    map[k]=new char[map_width];

  for(int k= 0; k<map_hight;k++)
  {
    for(int j= 0; j<map_width; j++)
    {
      if(k%2==0)
        if(j%2==0)
          map[k][j]='#';
        else
          map[k][j]='S';
      else if(j%2==0)
        map[k][j]='S';
      else
        map[k][j]=' ';

      if(k==0||k==map_hight-1)
        map[k][j]='#';
      if(j==0 || j==map_width-1)
        map[k][j]='#';
    }
  }
  //-----------------------------//
  //Picking random start points.
  y_start= rand()%(map_hight-2)+1;
  y=y_start;
  x_start= rand()%(map_width-2)+1;
  x=x_start;
  //-----------------------------//

  for(int k = 0; k < map_hight ; k++)
  {
    for(int i = 0; i < map_width ; i++)
      {
        if(map[k][i]=='#')
        {
          attron(COLOR_PAIR(1));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(1));
        }
        else if(map[k][i]=='S')
        {
          attron(COLOR_PAIR(4));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(4));
        }
        else
        {
          attron(COLOR_PAIR(2));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(2));
        }
      } 
  }
  getch();

  Prims(map, map_hight, map_width, y_start, x_start, y, x);
  refresh();
//----------------User inputs to game starts here----------------//
  mvprintw(map_hight,0,"You are the green snail, move with the arrow keys, \nhit q to quit. White are walls and the path is purple.");
  move(y,x);
  refresh();

  while( step !='q' && ((step = getch()) != 'q'))
  {
    switch(step)
    {
      case KEY_UP:
        y--;

        if(victory(y,x,map)==true)
        {
          clear();
          mvprintw(LINES/2-3,COLS/2,"VICTORY");
          step='q';
        }
        if(validate(y, x, map_hight, map_width,map)==false)
          y++;
        else
        {
          map[y+1][x] = ' ';
          mvprintw(y+1, x, "%c",map[y+1][x]);
          map[y][x] = 'O';

          attron(COLOR_PAIR(5));
          mvprintw(y, x, "%c",map[y][x]);
          attroff(COLOR_PAIR(5));
          move(y,x);
        }
        break;

      case KEY_DOWN:
        y++;
        if(victory(y,x,map)==true)
        {
          clear();
          mvprintw(LINES/2-3,COLS/2,"VICTORY");
          step='q';
        }
        if(validate(y, x, map_hight, map_width,map)==false)
          y--;
        else
        {
          map[y-1][x] = ' ';
          mvprintw(y-1, x, "%c",map[y-1][x]);
          map[y][x] = 'O';
          attron(COLOR_PAIR(5));
          mvprintw(y, x, "%c",map[y][x]);
          attroff(COLOR_PAIR(5));
  
          move(y,x);
        }
        break;

      case KEY_LEFT:
        x--;
        if(victory(y,x,map)==true)
        {
          clear();
          mvprintw(LINES/2-3,COLS/2,"VICTORY");
          step='q';
        }
        if(validate(y, x, map_hight, map_width,map)==false)
          x++;
        else
        {
          map[y][x+1] = ' ';
          mvprintw(y, x+1, "%c",map[y][x+1]);
          map[y][x] = 'O';
          attron(COLOR_PAIR(5));
          mvprintw(y, x, "%c",map[y][x]);
          attroff(COLOR_PAIR(5));

          move(y,x);
        }
        break;

      case KEY_RIGHT:
        x++;
        if(victory(y,x,map)==true)
        {
          clear();
          mvprintw(LINES/2-3,COLS/2,"VICTORY");
          step='q';
        }
        if(validate(y, x, map_hight, map_width,map)==false)
          x--;
        else
        {
          map[y][x-1] = ' ';
          mvprintw(y, x-1, "%c",map[y][x-1]);
          map[y][x] = 'O';
          attron(COLOR_PAIR(5));
          mvprintw(y, x, "%c",map[y][x]);
          attroff(COLOR_PAIR(5));

          move(y,x);
        }
        break;
    }
    refresh();
  }

  for(int k = 0; k < map_hight; k++)
    delete[]map[k];
  
  delete[]map;

  getch();
  endwin();
  return 0;
}

bool validate(const int y, const int x, const int max_y, const int max_x, char const* const*map)
{
  if((map[y][x] == ' ' || map[y][x] == 'V' ) && max_y > y && max_x > x && x>0 && y>0)
    return true;
  return false;
}
bool victory(const int y, const int x, char const*const*map)
{
  if(map[y][x]=='E')
    return true;
  return false;
}
