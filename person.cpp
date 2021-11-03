#include "person.h"
#include <iostream>
#include <random>
#include <algorithm>

int Person::_dim = -1;

Person::Person(int money, int position, int dim) : _money{money}, _position{position} {
  if (_dim == -1) {
    std::cerr << "WARN (11): Dim value not set: using default value. Use Person::setDim static function if you want to set it manually\n";
    setDefaultDim();
  }
  else if (dim != -1) {
    std::cerr << "WARN (12): Static parameter dim already set: ignoring parameter dim = " << dim 
              << ".\nUse Person::setDim static function to change the parameter dim";
  }

  if (_position == -1) {  //setRandPosition()
    std::random_device gen;
    std::uniform_int_distribution<int> dist(0, _dim*_dim);
    _position = dist(gen);
  }
}

void Person::move() {
  std::random_device gen;
  std::uniform_int_distribution<int> dist(0, 3); //4 possibility
  int direction = dist(gen);

  switch (direction)
  {
  case 0:     //left
    if (_position % _dim != 0) {
        _position--;
    }
    break;
  case 1:     //right
    if (_position % _dim != _dim-1) {
        _position++;
    }
    break;
  case 2:     //up
    if (_position / _dim != 0) {
      _position -= _dim;
    }
    break;
  case 3:     //down
    if (_position / _dim != _dim-1) {
      _position += _dim;
    }
    break;
  default:
    std::cerr << "AAAAAAAA\n";
  }

  //_history.push_back(_money);
}

void Person::gamble(Person second) {
  if (_position == second.position()) {
    std::random_device gen;
    std::uniform_int_distribution<int> dist(0, 1);
    int rand = dist(gen);
    if (rand == 0) {
      if (_money > 0) {
        _money--;
        second.changeMoney(1);
      }
    }
    else {
      if (second.money() > 0) {
        _money++;
        second.changeMoney(-1);
      }
    }
  }
}

void Person::print(std::vector<Person> population) {
  std::sort(population.begin(), population.end());
  
  for (int n = 0; n < _dim*_dim; n++) {
    if (n % _dim == 0) {
      if (n == 0)
        std::cout << '\n';
      else
        std::cout << "|\n";
      
      for (int i = 0; i < _dim; i++)
        std::cout << "----";
      std::cout << '\n';
    }

    std::cout << "| ";
    
    int max = -1; 
    for(int i = 0; i < population.size(); i++) {
      if (population[i].position() == n) {
        max = population[i].money();
        population.erase(population.begin()+i);
      }
    }
    if (max == -1)
      std::cout << "  ";
    else
      std::cout << max << ' ';

  }

  std::cout << "|\n";
  for (int i = 0; i < _dim; i++) {
    std::cout << "----";
  }
}

bool operator<(Person lhs, Person rhs) {
  if (lhs.position() < rhs.position())
    return true;
  return false;
}