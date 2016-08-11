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

    void set_sprite()
    {
        set_texture();
        set_color();
        set_posit();
    }

    public:

    void reposit(const sf::Vector2f& posit)
    {
        m_posit = posit;
        set_posit();
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

    pattern(const std::string& filename, const sf::Color& color,
            const sf::Vector2f& posit)
        : m_filename(filename), m_color(color), m_posit(posit),
          m_texture(), m_sprite()
    {
        set_sprite();
    }

    ~pattern()
    {
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


int window_maker(const std::string& program_name, const float windim)
{
    sf::Color black{0, 0, 0};

    sf::RenderWindow window(sf::VideoMode(windim, windim), program_name, sf::Style::Default);

    while (window.isOpen())
    {
        sf::Event event;

        window.clear(black);
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            return 0;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
        }
    }

    return 1;
}

int main()
{
    const std::string program_name{"Randomaze V0.1"};

    const float windim{512.0f};

    return window_maker(program_name, windim);
}

