#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once
#include <string>
#include <vector>
using namespace std;

struct Coffee {
  string country;
  string region;
  string owner;
  double aroma;
  double flavor;
  double aftertaste;
  double acidity;
  double body;
  double balance;
  double uniformity;
  double sweet;
  double moisture;
  double total;
};

class CoffeeManager {
private:
  vector<Coffee> data;
  int quickSortHelper(std::vector<Coffee>& data, int low, int high);
  void merge(vector<Coffee>& arr, int left, int mid, int right);
  void mergeSort(vector<Coffee>& arr, int left, int right);

public:
  std::vector<Coffee>& getData();
  void generate(int n);
  std::vector<Coffee> testCoffeeData();
  void quickSort(std::vector<Coffee>& data, int low, int high);
  vector<Coffee> getTopN(int n);
  vector<Coffee> getBottomN(int n);
  std::string calculateQualityScore(std::vector<Coffee>& data);
};

#endif