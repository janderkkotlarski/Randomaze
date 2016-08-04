#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class tile
{
    const sf::Vector2i m_posit;

    const std::string m_tile_name{"Tile.png"};

    const sf::Color m_dark{63, 63, 63};
    const sf::Color m_grey{127, 127, 127};
    const sf::Color m_light{191, 191, 191};

    int m_type{1};

    sf::Color m_color{m_dark};

    void color_tile()
    {
        const int a_type{abs(m_type)};

        switch (a_type)
        {
            case 0:
                m_color = m_light;
            case 1:
                m_color = m_dark;
            case 2:
                m_color = m_grey;
            default:
                m_color = m_dark;
                m_type = 1;
        }
    }

    void change_tile()
    {
        if (m_type == -1)
        {
            m_type = -3;
        }

        if (m_type == -3)
        {
            m_type = -1;
        }

        color_tile();
    }



    public:



    tile(const sf::Vector2i& posit, const int type)
        : m_posit(posit), m_type(type)
    {

    }

    ~tile()
    {

    }


};

int main()
{
    const std::string program_name{"Randomaze V0.1"};
    return 0;
}

