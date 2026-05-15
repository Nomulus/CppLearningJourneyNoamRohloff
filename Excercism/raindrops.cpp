#include "raindrops.h"
#include <string>

namespace raindrops
{
    // TODO: add your solution here
    std::string convert(int number)
    {
        std::string sound{""};
        if (number % 3 == 0)
        {
            sound = sound + "Pling";
        }
        if (number % 5 == 0)
        {
            sound = sound + "Plang";
        }
        if (number % 7 == 0)
        {
            sound = sound + "Plong";
        }

        if (sound == "")
        {
            sound = std::to_string(number);
        }

        return sound;
    }
} // namespace raindrops
