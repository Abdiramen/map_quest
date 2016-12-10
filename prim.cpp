#include "wall.h"
#include <ncurses.h>

void Prims(char** map, int map_hight, int map_width, int y_start, int x_start, int y, int x){
  //Implimentation of prims algorithm.
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
      mvprintw(a_wall->y,a_wall->x,"#");
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
      refresh();
    }
  }
  while(!stop);

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
}  
