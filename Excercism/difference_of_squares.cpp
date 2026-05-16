#include "difference_of_squares.h"

namespace difference_of_squares
{

    // TODO: add your solution here
    int square_of_sum(int number)
    {
        int square_sum{0};

        for (int i{0}; i <= number; i++)
        {
            square_sum = square_sum + i;
        }

        square_sum = square_sum * square_sum;

        return square_sum;
    }

    int sum_of_squares(int number)
    {

        int sum_square{0};

        for (int i{0}; i <= number; i++)
        {
            sum_square = sum_square + i * i;
        }

        return sum_square;
    }
    int difference(int number)
    {
        return square_of_sum(number) - sum_of_squares(number);
    }
}
