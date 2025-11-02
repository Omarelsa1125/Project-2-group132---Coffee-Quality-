#include "functions.h"
#include <iostream>

std::vector<temporaryCoffee> coffeeFunctions::testCoffeeData() {
    std::vector<temporaryCoffee> testData;
    testData.push_back({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 0.0});
    testData.push_back({7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0});
    testData.push_back({1.0, 2.0, 3.0, 4.0, 4.0, 3.0, 2.0, 0.0});
    testData.push_back({10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 0.0});
    testData.push_back({6.0, 7.0, 8.0, 9.0, 10.0, 1.0, 2.0, 0.0});
    return testData;
};

void coffeeFunctions::calculateQualityScore(std::vector<temporaryCoffee>& testData) {
    for (auto& coffee : testData) {
        double qualityScoreSum = coffee.coffeeAroma + coffee.coffeeFlavor + coffee.coffeeAfterTaste +
            coffee.coffeeAcidity + coffee.coffeeBody + coffee.coffeeBalance + coffee.coffeeOverall;
        coffee.qualityScore = qualityScoreSum/7;
    }
}












