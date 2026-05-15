namespace targets
{
    // TODO: Insert the code for the alien class here
    class Alien
    {
    public:
        int x_coordinate{};
        int y_coordinate{};

        Alien(int x, int y)
        {
            x_coordinate = x;
            y_coordinate = y;
        }

        bool teleport(int x_new, int y_new)
        {
            x_coordinate = x_new;
            y_coordinate = y_new;
            return true;
        }

        bool collision_detection(const Alien &other_Alien)
        {
            if (other_Alien.get_x_coordinate() == x_coordinate && other_Alien.get_y_coordinate() == y_coordinate)
            {
                return true;
            }
            return false;
        }

        int get_x_coordinate() const
        {
            return x_coordinate;
        }

        int get_y_coordinate() const
        {
            return y_coordinate;
        }

        int get_health()
        {
            return health;
        }

        bool hit()
        {
            if (health == 0)
            {
                return true;
            }
            else
            {
                health--;
            }
            return true;
        }

        bool is_alive()
        {
            if (health == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

    private:
        int health{3};
    };
}
