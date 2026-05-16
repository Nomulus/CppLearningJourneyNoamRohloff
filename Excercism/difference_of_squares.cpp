#include "difference_of_squares.h"

namespace difference_of_squares
{

    // TODO: add your solution here
    constexpr int square_of_sum(int number)
    {

        int square_sum{(number * (number + 1)) / 2}; // Gaußsche Summenformel

        return square_sum * square_sum; // es läuft so schneller als mit cmath pow()
    }

    constexpr int sum_of_squares(int number)
    {

        int sum_square{(number * (number + 1) * (2 * number + 1)) / 6};

        return sum_square;
    }
    constexpr int difference(int number)
    {
        return square_of_sum(number) - sum_of_squares(number);
    }
}
