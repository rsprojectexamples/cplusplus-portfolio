#ifndef OPERATIONNUMBERREPRESENTATION_H
#define OPERATIONNUMBERREPRESENTATION_H
#include <vector>
#include <optional>
#include <cmath>
#include <limits>

struct OperationNumberRepresentation
{
    // Each number is represented
    using OperationNumber = std::vector<std::pair<int (*)(int, int), std::optional<int>>>;

    // Monkey item operations
    static int multiply(int a, int b) { return a * b; }
    static int add(int a, int b) { return a + b; }
    static int divide(int a, int b) { return (int)std::floor(a / b); }

public:
    OperationNumber number;
    OperationNumberRepresentation(int value);
    OperationNumberRepresentation &operator+=(std::optional<int> value);
    OperationNumberRepresentation &operator*=(std::optional<int> value);
    OperationNumberRepresentation &operator/=(std::optional<int> value);
    int numberModulateBy(int modulator = std::numeric_limits<int>::max()) const;
};

#endif
