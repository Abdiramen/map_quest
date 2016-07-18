#include <iostream>
#include <fstream>
#include "wall.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

bool validate(const int y, const int x, const int max_y, const int max_x, char const*const*map);
bool victory(const int y, const int x, char const*const*map);


int main()
{
  srand(time(NULL));
  std::ifstream fin;
  int map_hight, map_width, y_start=1, x_start=1, step, x, y;
  char **map;
  
  fin.open("maptest.txt");
  
  //Gets map dimensions
  fin>>map_width>>map_hight;
  y_start= rand()%(map_width-2)+1;
  y=y_start;
  x_start= rand()%(map_hight-2)+1;
  x=x_start;
  //-----------------------------//
  //building map
  map = new char*[map_hight];

  for(int k = 0; k < map_hight; k++)
    map[k] = new char[map_width];
  //-----------------------------//
  fin.ignore();
  //Putting map file into map
  for(int k = 0; k < map_hight ; k++)
  {
    for(int i = 0; i < map_width ; i++)
      {
        fin.get(map[k][i]);
        if(map[k][i]=='B')
        {
          //y = k;
          //x = i;
          //map[k][i] = 'O';
        }
      }
    fin.ignore();
  }
  fin.close();

  initscr();  
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_CYAN);
  init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(4, COLOR_CYAN, COLOR_CYAN);
  cbreak();
  noecho();
  keypad(stdscr,true);
 

  for(int k = 0; k < map_hight ; k++)
  {
    for(int i = 0; i < map_width ; i++)
      {
        //note: try and add color here later
        if(map[k][i]=='#')
        {
          attron(COLOR_PAIR(1));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(1));
        }
        else if(/*map[k][i]=='V'||*/map[k][i]=='S')
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
//testing myprims algorithm
  wall* a_wall = new wall(y_start,x_start);
  wall_array wall_list;
  bool stop = false;
  wall_list.add_wall(a_wall);

  do
  {
    if(wall_list.get_size()==0)
    {
      stop=true;
      map[a_wall->y][a_wall->x]='E';
mvprintw(a_wall->y,a_wall->x,"#"/*,map[a_wall->y][a_wall->x]*/);
refresh();
      delete a_wall;
    }
    else
    {
      delete a_wall;
      a_wall = new wall(wall_list.rand_wall());
wall_list.remove_wall(a_wall);
      map[a_wall->y][a_wall->x]='V';

      wall_list.add_neighbors(a_wall,map,map_hight,map_width);
attron(COLOR_PAIR(3));
mvprintw(a_wall->y,a_wall->x,"%c",map[a_wall->y][a_wall->x]);
attroff(COLOR_PAIR(3));

mvprintw(0,COLS/2,"%3d",wall_list.get_size());
wall_list.print();
refresh();
    }
//getch();
  }
  while(!stop);

map[y][x]='O';
clear();

  for(int k = 0; k < map_hight ; k++)
  {
    for(int i = 0; i < map_width ; i++)
      {
        //note: try and add color here later
        if(map[k][i]=='#')
        {
          attron(COLOR_PAIR(1));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(1));
        }
        else if(map[k][i]=='V'||map[k][i]=='S')
        {
          attron(COLOR_PAIR(3));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(3));
        }
        else
        {
          attron(COLOR_PAIR(2));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(2));
        }
      } 
  }
  refresh();

//---------------------------------------------------------------//
  mvprintw(map_hight,0,"You are the O, move with the arrow keys, \nand hit q to quit. White are walls and \nyou are a snail so you'll leave a trail");
  move(y,x);
  refresh();

  while( step !='q' && ((step = getch()) != 'q'))
  {
    //movement
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
          mvprintw(y, x, "%c",map[y][x]);
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
          mvprintw(y, x, "%c",map[y][x]);
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
          mvprintw(y, x, "%c",map[y][x]);
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
          mvprintw(y, x, "%c",map[y][x]);
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
