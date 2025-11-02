#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>

//These are placeholder variables until Jiahao creates the random generate function for
//the coffee samples.

struct temporaryCoffee {
  double coffeeAroma;
  double coffeeFlavor;
  double coffeeAfterTaste;
  double coffeeAcidity;
  double coffeeBody;
  double coffeeBalance;
  double coffeeOverall;
  double qualityScore;
 };

 class coffeeFunctions {
   private:
     int quickSortHelper(int array[], int low, int high);
   public:
     std::vector<temporaryCoffee> testCoffeeData();
     void calculateQualityScore(std::vector<temporaryCoffee>& coffeeData);
     void quickSort(int array[], int low, int high);
 };

#endif