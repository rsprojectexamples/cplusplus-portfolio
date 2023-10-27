#include "monkey.h"
#include "constants.h"

Monkey::Monkey(int id, ItemContainer items, int (*operation)(int, int), std::optional<int> multiplier, int divisionTest, int trueTarget, int falseTarget) : id{id}, items{items}, operation{operation}, operand{multiplier}, divisionTest{divisionTest}, trueTarget{trueTarget}, falseTarget{falseTarget}
{
    this->inspectionCount = 0;
}

int Monkey::determineThrowTarget(OperationNumberRepresentation &item, int optimizer)
{
    auto itemInteger = item.numberModulateBy(optimizer);

    if (operation == OperationNumberRepresentation::add)
    {
        item += operand;
    }
    else if (operation == OperationNumberRepresentation::multiply)
    {
        item *= operand;
    }

    int secondOperand = operand.has_value() ? operand.value() : itemInteger;
    auto preDivWorry = operation(itemInteger, secondOperand);
    item /= RunConfig::worryDivisor;
    auto newWorryLevel = OperationNumberRepresentation::divide(preDivWorry, RunConfig::worryDivisor);

    auto isDivisible = newWorryLevel % divisionTest == 0;

    auto finalTarget = isDivisible ? trueTarget : falseTarget;
    inspectionCount += 1;
    return finalTarget;
}

std::vector<int> Monkey::performTurn()
{
    std::vector<int> directions{};
    auto optimizer = RunConfig::reduceModulo ? divisionTest : std::numeric_limits<int>::max();
    for (auto &item : items)
    {
        directions.push_back(determineThrowTarget(item, optimizer));
    }
    return directions;
}
