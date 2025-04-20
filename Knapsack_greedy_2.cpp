#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>

using namespace std;

void enableUTF8() {
    SetConsoleOutputCP(65001);
}

struct Result {
    int totalWeight;
    int totalValue;

    Result(int weight, int value) : totalWeight(weight), totalValue(value) {}
};


struct Item {
    int index;       // номер предмета
    int value;       // ценность
    int weight;      // вес
    double priority; // эвристика: value / weight
};


bool compareByPriority(const Item& a, const Item& b) {
    return a.priority > b.priority;
}

Result solveKnapsack(int maxWeight, vector<Item>& items) {
    int currentWeight = 0;
    int totalValue = 0;

    sort(items.begin(), items.end(), compareByPriority);

    for (const auto& item : items) {
        if (currentWeight + item.weight <= maxWeight) {
            currentWeight += item.weight;
            totalValue += item.value;
        }
    }

    return Result(currentWeight, totalValue);
}

int main() {
    enableUTF8();

    ifstream inputFile("../ks_200_0");
    if (!inputFile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    int itemCount, knapsackCapacity;
    inputFile >> itemCount >> knapsackCapacity;

    vector<Item> items(itemCount);

    for (int i = 0; i < itemCount; ++i) {
        inputFile >> items[i].value >> items[i].weight;
        items[i].index = i + 1;
        items[i].priority = static_cast<double>(items[i].value) / items[i].weight;
    }

    inputFile.close();

    Result result = solveKnapsack(knapsackCapacity, items);

    cout << "Max value: " << result.totalValue << endl;
    cout << "Total weight " << result.totalWeight << " of " << knapsackCapacity << endl;

    return 0;
}
