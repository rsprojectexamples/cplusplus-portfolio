#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "monkey.h"
#include "constants.h"
#include "inputHandler.h"

int main(int argc, char const *argv[])
{
    std::ifstream fileStream(RunConfig::inputFilePath.data());

    std::vector<Monkey> monkeyList{};

    while (!fileStream.fail())
    {
        Monkey monkey = InputHandler::readMonkeyIStream(fileStream);
        monkeyList.push_back(monkey);
        fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip line after each Monkey
    }

    for (int i = 0; i < RunConfig::numOfRounds; i++)
    {
        for (Monkey &monkey : monkeyList)
        {
            auto results = monkey.performTurn();
            for (int i = 0; i < monkey.items.size(); i++)
            {
                monkeyList[results[i]].items.push_back(monkey.items[i]);
            }
            monkey.items.clear();
        }
    }

    std::vector<int> sorted{};
    for (auto &monkey : monkeyList)
    {
        sorted.push_back(monkey.inspectionCount);
    }
    std::sort(sorted.begin(), sorted.end(), std::greater<int>());
    std::cout << (long long int)sorted[0] * sorted[1] << std::endl;

    return 0;
}
