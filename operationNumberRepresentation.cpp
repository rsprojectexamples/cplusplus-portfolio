#include "operationNumberRepresentation.h"

OperationNumberRepresentation::OperationNumberRepresentation(int value) : number{{OperationNumberRepresentation::add, value}} {}

OperationNumberRepresentation &OperationNumberRepresentation::operator+=(std::optional<int> value)
{
    this->number.push_back({OperationNumberRepresentation::add, value});
    return *this;
}

OperationNumberRepresentation &OperationNumberRepresentation::operator*=(std::optional<int> value)
{
    this->number.push_back({OperationNumberRepresentation::multiply, value});
    return *this;
}

OperationNumberRepresentation &OperationNumberRepresentation::operator/=(std::optional<int> value)
{
    this->number.push_back({OperationNumberRepresentation::divide, value});
    return *this;
}

int OperationNumberRepresentation::numberModulateBy(int modulator) const
{
    int finalNum = 0;
    for (auto &opPair : this->number)
    {
        auto secondOperand = opPair.second.has_value() ? opPair.second.value() : finalNum;
        finalNum = opPair.first(finalNum, secondOperand) % modulator;
    }
    return finalNum;
}
