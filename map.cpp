/*
  Abdirahman Ahmed Osman
  Date: 6.11.2016
  Version: 1.0.0
*/

#include<iostream>
#include<fstream>
#include<ncurses.h>

bool validate(const int y, const int x, const int max_y, const int max_x, char const*const*map);
bool victory(const int y, const int x, char const*const*map);
int main()
{
  std::ifstream fin;
  int map_hight, map_width,step, x,y;
  char **map;
  
  fin.open("map.txt");
  
  //Gets map dimensions
  fin>>map_width>>map_hight;
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
          y = k;
          x = i;
          map[k][i] = 'O';
        }
      }
    fin.ignore();
  }
  fin.close();

  //initializing curses mode
  initscr();  
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_CYAN);
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
        else
        {
          attron(COLOR_PAIR(2));
          mvprintw(k,i,"%c",map[k][i]);
          attroff(COLOR_PAIR(2));
        }
      } 
  }

  mvprintw(map_hight,0,"You are the O, move with the arrow keys, \nand hit q to quit. White are walls and \nyou are a snail so you'll leave a trail");
  move(y,x);
  refresh();

  while((step = getch()) != 'q')
  {
    //movement
    switch(step)
    {
      case KEY_UP:
        y--;

        if(victory(y,x,map)==true)
        {
          clear();
          mvprintw(LINES/2-3,COLS/2,"VICORY");
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
          mvprintw(LINES/2-3,COLS/2,"VICORY");
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
          mvprintw(LINES/2-3,COLS/2,"VICORY");
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
          mvprintw(LINES/2-3,COLS/2,"VICORY");
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
  //stop from just closeing right away
  //getch();
  //exiting curses mode
  endwin();

  //deleting map
  for(int k = 0; k < map_width; k++)
    delete[]map[k];
  
  delete[]map;

  return 0;
}


bool validate(const int y, const int x, const int max_y, const int max_x, char const* const*map)
{
  if(map[y][x] == ' ' && max_y > y && max_x > x && x>0 && y>0)
    return true;
  return false;
}
bool victory(const int y, const int x, char const*const*map)
{
  if(map[y][x]=='E')
    return true;
  return false;
}
