#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class pattern
{
    const std::string m_filename{"Tile.png"};

    sf::Color m_color;

    sf::Vector2f m_posit;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    void set_filename()
    {
        assert(m_filename != "");

        if (!m_texture.loadFromFile(m_filename))
        {
            std::cout << m_filename << " not found!\n";
        }
    }

    void set_texture()
    {
        m_sprite.setTexture(m_texture);
    }

    void set_color()
    {
        m_sprite.setColor(m_color);
    }

    void set_posit()
    {
        m_sprite.setPosition(m_posit);
    }

    public:

    void reposit(const sf::Vector2f& posit)
    {
        m_posit = posit;
    }

    void recolor(const sf::Color& color)
    {
        m_color = color;
        set_color();
    }

    void display(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }
};

class tile
{
    const sf::Vector2i m_posit;



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
        color_tile();
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

