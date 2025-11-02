//
// Created by  Liu on 10/27/25.
//

#include "functions.h"
#include <iostream>
#include <vector>

int main() {
    coffeeFunctions object;
    std::vector<temporaryCoffee> testData = object.testCoffeeData();
    object.calculateQualityScore(testData);
    std::cout << "Quality Scores" << std::endl;
    for (auto& coffee : testData) {
        std::cout << coffee.qualityScore << std::endl;
    }
    return 0;
}


