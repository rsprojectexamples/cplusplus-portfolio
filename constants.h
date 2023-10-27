#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string_view>
using namespace std::literals;

enum class Round
{
    One,
    Two
};

namespace Round1
{
    inline constexpr int numOfRounds{20};
    inline constexpr int worryDivisor{3};
}

namespace Round2
{
    inline constexpr int numOfRounds{10000};
    inline constexpr int worryDivisor{1};
}

namespace RunConfig
{
    inline constexpr Round round{Round::One}; // Set One or Two here for each part of the task
    inline constexpr auto numOfRounds = RunConfig::round == Round::One ? Round1::numOfRounds : Round2::numOfRounds;
    inline constexpr auto inputFilePath{"input/input"sv};
    inline int worryDivisor = RunConfig::round == Round::One ? Round1::worryDivisor : Round2::worryDivisor;
    inline bool reduceModulo = RunConfig::round == Round::Two; // Can't reduce modulo for part 1 since multiplicative rule of modular arithmetic doesn't extend to division
}

#endif
