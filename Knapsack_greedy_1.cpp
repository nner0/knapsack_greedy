#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>

using namespace std;

void enableUTF8Console() {
    SetConsoleOutputCP(65001);
}

struct Result {
    int totalWeight;
    int totalValue;

    Result(int weight, int value) : totalWeight(weight), totalValue(value) {}
};

struct Item {
    int index;      // порядковый номер 
    int value;      // ценность
    int weight;     // вес
    double priority; // ценность на единицу веса

    Item() : index(0), value(0), weight(0), priority(0.0) {}
};

bool greedyComparator(const Item& a, const Item& b) {
    return a.priority > b.priority;
}

Result greedyKnapsack(int max_capacity, vector<Item>& items) {
    int totalWeight = 0;
    int totalValue = 0;

    sort(items.begin(), items.end(), greedyComparator);

    for (size_t i = 0; i < items.size(); ++i) {
        const Item& item = items[i];
        if (totalWeight + item.weight <= max_capacity) {
            totalValue  += item.value;
            totalWeight += item.weight;
        }
    }

    return Result(totalWeight, totalValue);
}


int main() {
    enableUTF8Console();

    ifstream inputFile("../ks_200_0");
    if (!inputFile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    int itemCount, maxKnapsackWeight;
    inputFile >> itemCount >> maxKnapsackWeight;

    vector<Item> items(itemCount);

    for (int i = 0; i < itemCount; ++i) {
        inputFile >> items[i].value >> items[i].weight;
        items[i].index = i + 1;
        items[i].priority = static_cast<double>(items[i].value) / items[i].weight;
    }

    inputFile.close();

    Result result = greedyKnapsack(maxKnapsackWeight, items);

    cout << "\nTotal value: " << result.totalValue << endl;
    cout << "Total weight: " << result.totalWeight << " of " << maxKnapsackWeight << endl;

    return 0;
}
