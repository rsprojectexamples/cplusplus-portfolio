# Problem statement
For detailed problem statement see advent of code 2022 problem 11
## Summary:
There are X number of monkeys read from input example:
```
Monkey 0:
  Starting items: 111, 222
  Operation: new = old * 17
  Test: divisible by 21
    If true: throw to monkey 4
    If false: throw to monkey 5
```
The monkeys take turns performing operation from row 3 on each item they are currently holding. After that they perform the test in row 4, and depending on outcome transfer the item to monkey with respective id with the new value for the item as per the operation.

There are two parts to the problem
* In part 1: 20 rounds are performed and after each inspection but before the test the item integer is divided by 3
* In part 2: 10000 rounds are performed and the integer is no longer divided by 3

Note therefore there is nothing keeping the numbers from growing very large in part 2

# Solution
The naive solution is quite simple. Simply read the input and then for loop the monkeys while performing their operations and testing divisibility after each operation. 

The same solution does not work in part 2, as due to the number of rounds and no mechanism for keeping the numbers small the numbers quickly start overflowing even the largest integer types.

Since the problem basically boils down to modular arithmetic (since we don't care about the actual integer, simply its divisibilty), the common solution found around the web to this problem is to use the chinese remainder theorem. Acknowledging this is the most efficient solution, the solution presented here is a different solution as a proof of concept.

The solution presented here is to simply not keep track of each number integer as an integer, but rather a series of operations that made up the current item integer.

So when Monkey 0 performs its operation (old * 17), instead of multiplying 111*17, we store the operation and the operand in this format 
```
std::pair<int (*)(int, int), std::optional<int>>>
```
The first part of the pair stores the operation, which is either addition or multiplication. The operation is expressed as a closure, and implemented by passing a static method:
```
    static int multiply(int a, int b) { return a * b; }
    static int add(int a, int b) { return a + b; }
```

Since all operations the monkeys perform always involve the previous item integer (ex: old * 17), we only need to store the second operand (in this case 17). Note some monkey operations (ex old * old) simply multiply the existing integer value, thus the operand is made optional and its absence assumed to mean squaring the current value.

Then whenever a monkey is performing its operation, we simply represent that by adding a new operation to the following structure
```
std::vector<std::pair<int (*)(int, int), std::optional<int>>>;
```

To facilitate this there is a convenient wrapper struct `OperationNumberRepresentation` which accepts the usual mathematical operators of addition, multiplication and division. So you can add to the number by simply doing:
```
auto number = OperationNumberRepresentation{1}; // Initialize with 1
number += 5;    // Add 5
number *= 3;    // Multiply by 3
std::cout << number.numberModulateBy(4) << std::endl; // Prints 2
```

And when testing for divisibility, instead of calculating the original number from the series of operations, something that would overflow integer types, we simply perform one operation at a time, while performing a modulo using the monkeys divisibility test. This is allowed as per the multiplicative rule of modular arithmetic. 

```
a * b (mod n) == a (mod n) * b (mod n) 
```

Note this behaviour is disabled for part 1, since each sub-result is divided by 3 (see problem statement for part 1) and since the multiplicative rule of modular arithmetic does not apply to division, the same logic can't be applied in part 1.

# Optimization
Since this solution isn't as efficient as the chinese remainder theorem solution, a number of optimizations is employed here so that it would complete part 2 in less than a couple hours.

## Turning on compiler optimizations
The final computation time for the full 10000 rounds seemed to be around a couple of hours (extrapolated from timed runs on 100, 1000 and 2000 rounds). Since the complexity of this algorithm is quadratic the final time for 10000 rounds extrapolated seemed to be around an hour.

Rounds | 100 | 1000 | 2000 | 10000
-------- | -------- | -------- | -------- | --------
Time | 0.3 | 33 | 136 | 3486

However after turning on compiler optimization to `-O3` the final time for 10000 rounds reduced to just 120 seconds


## Avoid reconstructing original number
The main optimization is avoiding having to reconstruct the original number multiple times during inspection as that is the most time intesive task. Therefore during inspection, the integer number is only calculated once and then subsequent operations are performed on integer directly (while also recorded in the operations series log).

On 5000 rounds this takes down the time from 42 seconds to 26 seconds.

Note that further optimizations such as keeping track of last reconstructed (reduced mod number) between rounds is not possible, since the reconstructed number is only valid in the context of that monkey and its divisibility test. Passing such a number to a monkey with a different divisibility test would result in incorrect results.

## Avoid copying the monkeys items

Originally the `performTurn` method would return type
```
    std::vector<std::pair<OperationNumberRepresentation, int>> performTurn();
```
Which would indicate for each item which monkey to throw it to. This involved unnecessary copying of the `OperationNumberRepresentation` objects on return which added about 10 extra seconds to the total run time. 

Instead we just return a vector of throw targets for each monkey, and then access the monkey item list directly to avoid making a copy.
