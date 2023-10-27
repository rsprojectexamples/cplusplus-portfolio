#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "inputHandler.h"
#include "operationNumberRepresentation.h"

namespace InputHandler
{
    std::istream &operator>>(std::istream &inputStream, const char *format)
    {
        char c;
        for (int i = 0; i < strlen(format); i++)
        {
            if (!inputStream.get(c) || c != format[i])
            {
                inputStream.setstate(std::ios::failbit);
                return inputStream;
            }
        }
        return inputStream;
    }

    // An overload for reading comma separated integers into a int vector
    std::istream &operator>>(std::istream &inputStream, std::vector<int> &integers)
    {
        int item;
        while (inputStream >> item >> ",")
        {
            integers.push_back(item);
        }
        inputStream.clear(); // The last item won't have ',' which will set failbit, need to clear here
        integers.push_back(item);
        return inputStream;
    }

    Monkey readMonkeyIStream(std::istream &inputStream)
    {
        int monkeyInteger;
        // as per input "Monkey 111:"
        inputStream >> "Monkey" >> monkeyInteger >> ":\n";

        // as per input "Starting items: 1, 2, 3"
        std::vector<int> itemItegers{};

        inputStream >> "  Starting items:" >> itemItegers;
        ItemContainer monkeyItems;
        std::transform(itemItegers.begin(), itemItegers.end(), std::back_inserter(monkeyItems),
                       [](int i)
                       { return OperationNumberRepresentation(i); });

        // as per input "Operation: new = old + 111" (in this case the 111)
        std::string monkeyOperator;
        std::string monkeyOperand;

        inputStream >> "  Operation: new = old" >> monkeyOperator >> monkeyOperand >> "\n";
        // as per input "Test: divisible by 112"
        int divisionTest;
        inputStream >> "  Test: divisible by" >> divisionTest >> "\n";

        // as per input "If true: throw to monkey 113"
        int trueTarget;
        inputStream >> "    If true: throw to monkey" >> trueTarget >> "\n";
        // as per input "If false: throw to monkey 114"
        int falseTarget;
        inputStream >> "    If false: throw to monkey" >> falseTarget >> "\n";

        return Monkey(monkeyInteger,
                      monkeyItems,
                      monkeyOperator == "*" ? OperationNumberRepresentation::multiply : OperationNumberRepresentation::add,
                      (monkeyOperand != "old") ? stoi(monkeyOperand) : std::optional<int>{},
                      divisionTest,
                      trueTarget,
                      falseTarget);
    }
}
