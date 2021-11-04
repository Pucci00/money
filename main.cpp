#include "person.h"
#include <chrono>
#include <thread>

int main(){
  int populationSize = 1000;
  int money = 6000;
  Person::setDim(35);
  int iteration = 10000;

  std::vector<Person> population(populationSize);

  //set money uniformely
  for (int i = 0; i < money; i++) {
    population[i%populationSize].changeMoney();
  }

  std::cout << "In progress: ";
  for (int it = 0; it < iteration; it++) {
    if (it*100%iteration == 0)
      std::cout << '#';
    /*using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
    system("cls");

    Person::print(population);*/

    for (int i = 0; i < populationSize; i++) {
      population[i].move();
    }

    for (int i = 0; i < populationSize; i++) {
      for (int j = i+1; j < populationSize; j++) {
        population[i].gamble(population[j]);
      }
    }
  }
  std::cout << '\n';

  std::vector<int> moneyVec;
  for (int i = 0; i < populationSize; i++) {
    while (moneyVec.size() < population[i].money()+1) {
      moneyVec.push_back(0);
    }
    moneyVec[population[i].money()]++;
  }

  int sizeM = moneyVec.size();
  for (int i = 0; i< sizeM; i++) {
    std::cout << i << ' ' << moneyVec[i] << '\n';
  }
  
  return 0;
}