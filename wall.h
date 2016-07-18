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
  wall_array();
  ~wall_array();
  wall* get_wall(int index);
  wall* rand_wall();
  void add_wall(wall* a_wall);
  void remove_wall(int index);
  void remove_wall(wall* a_wall);
  int get_size();
  void add_neighbors(wall* a_wall, char** map, int y_max, int x_max);
  void rec_add(wall* a_wall, char** map, int y_max, int x_max);
  void print();
};

#endif
