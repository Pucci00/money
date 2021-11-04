#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include <iostream>

class Person
{
  static int _dim;
  int _position;
  int _money;
  void setDefaultDim() { _dim = 10; };

 public:
  Person(int money = 0, int position = -1, int dim = -1);

  int position() { return _position; };
  int money() { return _money; };
  static void setDim(int dim) { _dim = dim; } ;
  void setPosition(int position) { if (position < _dim*_dim) _position = position; };
  void changeMoney(int change = 1) { _money += change; };

  void move();
  void gamble(Person second);
  static void print(std::vector<Person> population);
};

bool operator<(Person lhs, Person rhs);

#endif  //PERSON.H
