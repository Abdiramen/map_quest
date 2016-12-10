#include "wall.h"
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>

wall_array::wall_array()
{
  m_data = new wall*[10];
  for(int i=0; i<10; i++)
    m_data[i] = NULL;

  m_size = 0;
  m_max = 10;
}

wall_array::~wall_array()
{
  int count=0;
  while(m_data[count]!=NULL)
  {
    delete m_data[count];
    count++;
  }
  delete[] m_data;

}

wall* wall_array::get_wall(int index)
{
  
  return m_data[index-1];
}

wall* wall_array::rand_wall()
{
 return m_data[rand()%(m_size)];//get_wall(rand()%);//<--this should be better
}

//Note: add_wall is ugly try and make the if case not so bloated.
void wall_array::add_wall(wall* a_wall)
{
  m_size++;

  if(m_size==m_max+1)
  {
    wall** temp = new wall*[m_max*2];

    for(int cop=0; cop<m_max; cop++)
      temp[cop] = new wall(m_data[cop]);

    for(int i=0;i<m_max;i++)
    {
      delete m_data[i]; 
    }
    delete[] m_data;

    m_max*=2;

    for(int Nl=m_size; Nl<m_max ;Nl++)
      temp[Nl]=NULL;

    m_data = temp;
  }

  m_data[m_size-1]= new wall(a_wall);
}

//this one will never be used unless the rec_add and add_neighbors gets a major rework
void wall_array::remove_wall(int index)
{
  delete m_data[index-1];
  m_data[index-1]=NULL;

  for(int i=0;i<(m_size-index);i++)
  {
    m_data[index-1+i]=m_data[index+i];
    m_data[index+i]=NULL;
  }
  m_size--;
}

//should have used a linked list so i wouldn't need to search through an array list
void wall_array::remove_wall(wall* a_wall)                               
{ 
  int index;
  for(int i = 0; i<m_size; i++)
    if(m_data[i]->y == a_wall->y && m_data[i]->x == a_wall->x)
    {
      delete m_data[i];
      index=i;
    }

  m_data[index]=NULL;
  
  for(int i=0;i<(m_size-index);i++)
  { 
    m_data[index+i]=m_data[index+i+1];
    m_data[index+i+1]=NULL;                                             
  }                                                                   
  m_size--;                                                           
}


int wall_array::get_size()
{
  return m_size;
}

void wall_array::add_neighbors(wall* a_wall, char** map, int y_max, int x_max)
{
  refresh();
  usleep(50);

  wall* temp;

  for(int c=0; c<4; c++)
  {
    switch(c)
    {
      case 0:
        temp = new wall(a_wall->y-1,a_wall->x);
        break;
      case 1:
        temp = new wall(a_wall->y+1,a_wall->x); 
        break;
      case 2:
        temp = new wall(a_wall->y,a_wall->x+1); 
        break;
      case 3:
        temp = new wall(a_wall->y,a_wall->x-1); 
        break;
    }
    if(temp->y >0 && temp-> y < y_max)
      if(temp->x >0 && temp->x < x_max) 
        rec_add(temp, map, y_max, x_max);
    delete temp;
  }


  return;
}


void wall_array::rec_add(wall* a_wall, char** map, int y_max, int x_max)
{
  refresh();
  switch(map[a_wall->y][a_wall->x])
  {
    case 'S':
      add_wall(a_wall);
      map[a_wall->y][a_wall->x]='L';
      mvprintw(a_wall->y,a_wall->x,"%c",map[a_wall->y][a_wall->x]);
;
      break;
    case ' ':
      map[a_wall->y][a_wall->x]='V';
      add_neighbors(a_wall, map, y_max, x_max);
      attron(COLOR_PAIR(3));
      mvprintw(a_wall->y,a_wall->x,"%c",map[a_wall->y][a_wall->x]);
      attroff(COLOR_PAIR(3));

      break;
    case 'L':
      remove_wall(a_wall);
      map[a_wall->y][a_wall->x]='#';

      attron(COLOR_PAIR(1));
      mvprintw(a_wall->y,a_wall->x,"%c",map[a_wall->y][a_wall->x]);
      attroff(COLOR_PAIR(1));

     break;
  }
  refresh();
  usleep(500);
  return;
}

void wall_array::print()
{
  for(int i = 0; i< m_max ; i++)
  {
   if(i<m_size)
     mvprintw(i+1,(COLS-9)/2,"%3d , %3d", get_wall(i+1)->y,get_wall(i+1)->x);
   else
     mvprintw(i+1,(COLS-9)/2,"              ");
  }
  refresh();
  return;
}
