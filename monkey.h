#ifndef MONKEY_H
#define MONKEY_H
#include <vector>
#include <optional>
#include <deque>
#include "operationNumberRepresentation.h"

// Creating an alias here to simplify dropping in a different container
// Deque performs very slightly better here (~4% improvement) likely due to the fact that vector has worst case push_back operation being constant time complexity
// With 5000 iterations Deque avg time: 25.5        |      Vector avg time: 26.6
using ItemContainer = std::deque<OperationNumberRepresentation>; // std::vector<OperationNumber>;
struct Monkey
{
    // Id of the monkey as per input "Monkey 111:"
    int id;
    // All items that the monkey currently holds as per input "Starting items: 1, 2, 3"
    ItemContainer items;
    // Operation that the monkey performs each turn as per input "Operation: new = old + 111"
    int (*operation)(int, int);
    // Second operand for the operation as per input "Operation: new = old + 111" (in this case the 111)
    std::optional<int> operand;
    // The division test that the monkey should perform  as per input "Test: divisible by 112"
    int divisionTest;
    // Monkey to throw to if division test true as per input "If true: throw to monkey 113"
    int trueTarget;
    // Monkey to throw to if division test false true as per input "If false: throw to monkey 114"
    int falseTarget;

    // Number of items that this monkey has inspected throughout all turns - the result is to find the monkey with most inspected items
    int inspectionCount;

public:
    Monkey(int id, ItemContainer items, int (*operation)(int, int), std::optional<int> multiplier, int divisionTest, int trueTarget, int falseTarget);
    std::vector<int> performTurn();

private:
    int determineThrowTarget(OperationNumberRepresentation &item, int optimizer);
};

#endif
