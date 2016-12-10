#ifndef WALL_H
#define WALL_H

struct wall
{
  const int y;
  const int x;
  wall(const int Y, const int X) : y(Y), x(X) {}
  wall(const wall* a_wall) : y(a_wall->y), x(a_wall->x) {}
};

class wall_array
{
private:
  wall** m_data;
  int m_size, m_max;

public:
  /*
   *Purpose: create a wall_array with 
   *
   *Pre: None 
   *
   *Post: Max size set to 10 and current size set to 0 and data set to an array
   *    
   */
  wall_array();
  /*
   *Purpose: Empty dealocated wall_arrays
   *
   *Pre: None
   *
   *Post: m_data emptied then deleted
   */
  ~wall_array();
  /*
   *Purpose:  Retruns wall at element index-1
   *
   *Pre: index a nonnegative number
   *
   *Post: Returns wall pointer
   */
  wall* get_wall(int index);
  /*
   *Purpose: Gets random wall from m_data 
   *
   *Pre: m_size > 0
   *
   *Post: returns
   */
  wall* rand_wall();
  /*
   *Purpose: 
   *
   *Pre: 
   *
   *Post:
   */
  void add_wall(wall* a_wall);
  /*
   *Purpose:
   *
   *Pre: 
   *
   *Post:
   */
  void remove_wall(int index);
  /*
   *Purpose:
   *
   *Pre: 
   *
   *Post:
   */
  void remove_wall(wall* a_wall);
  /*
   *Purpose:
   *
   *Pre: 
   *
   *Post:
   */
  int get_size();
  /*
   *Purpose:
   *
   *Pre: 
   *
   *Post:
   */
  void add_neighbors(wall* a_wall, char** map, int y_max, int x_max);
  /*
   *Purpose:
   *
   *Pre: 
   *
   *Post:
   */
  void rec_add(wall* a_wall, char** map, int y_max, int x_max);
  /*
   *Purpose:
   *
   *Pre: 
   *
   *Post:
   */
  void print();
};

#endif
