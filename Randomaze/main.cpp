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

    sf::Vector2f m_dims{0.0f, 0.0f};

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    void set_filename()
    {
        assert(m_filename != "");

        std::cout << m_filename << '\n';

        if (!m_texture.loadFromFile(m_filename))
        {
            std::cout << m_filename << " not found!\n";
        }
    }

    void set_texture()
    {
        m_sprite.setTexture(m_texture);
    }

    void get_dims()
    {
        const sf::FloatRect dims{m_sprite.getLocalBounds()};

        m_dims.x = dims.width;
        m_dims.y = dims.height;
    }

    void set_center()
    {
        m_sprite.setOrigin(0.5f*m_dims);
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
        set_filename();
        set_texture();
        get_dims();
        set_center();
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

    pattern(const std::string& filename,
            const sf::Color& color,
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

    const std::string m_filename{"Ripple_Square.png"};

    const sf::Vector2i m_posit;

    const sf::Color m_dark{63, 63, 63};
    const sf::Color m_grey{127, 127, 127};
    const sf::Color m_light{191, 191, 191};

    const sf::Color m_dark_red{127, 63, 63};
    const sf::Color m_dark_green{63, 127, 63};
    const sf::Color m_dark_blue{63, 63, 127};

    const sf::Color m_light_red{191, 127, 127};
    const sf::Color m_light_green{127, 191, 127};
    const sf::Color m_light_blue{127, 127, 191};

    int m_type{3};

    sf::Color m_color;

    pattern m_pattern;

    void color_tile()
    {
        switch (m_type)
        {
            case 0:
                m_color = m_dark;
            case 1:
                m_color = m_light_red;
            case 2:
                m_color = m_light_green;
            case 3:
                m_color = m_light_blue;
            case 10:
                m_color = m_light;
            case -1:
                m_color = m_dark_red;
            case -2:
                m_color = m_dark_green;
            case -3:
                m_color = m_dark_blue;
            case -10:
                m_color = m_grey;
            default:
                m_color = m_light_blue;
                // m_type = 1;
        }

        if (m_type == -2)
        {
            // m_color = m_dark_green;
        }

        m_pattern.recolor(m_color);
    }

    public:

    void display(sf::RenderWindow& window)
    {
        m_pattern.display(window);
    }

    tile(const sf::Vector2i& posit, const int type)
        : m_posit(posit), m_type(type), m_color(m_dark), m_pattern(m_filename, m_color, static_cast<sf::Vector2f>(m_posit))
    {
        std::cout << m_type << '\n';

        color_tile();
    }

    ~tile()
    {

    }


};


int window_maker(const std::string& program_name, const float windim)
{
    const float seconds{30.0f};

    sf::Clock clock;
    sf::Time time;

    sf::Color black{0, 0, 0};
    sf::Color white{255, 255, 255};

    const std::string image_name{"Ripple_Square.png"};

    const sf::Vector2f home{0.0f, 0.0f};



    pattern patchy{image_name, white, home};


    const sf::Vector2f middle{0.5f*windim, 0.5f*windim};

    const sf::Vector2f upper_left{0.25f*windim, 0.25f*windim};

    tile tily{static_cast<sf::Vector2i>(upper_left), -2};

    sf::RenderWindow window(sf::VideoMode(windim, windim), program_name, sf::Style::Default);

    while (window.isOpen())
    {
        sf::Event event;

        window.clear(black);

        patchy.display(window);

        tily.display(window);

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

        time = clock.getElapsedTime();

        if(time.asSeconds() > seconds)
        {
            window.close();
            return 0;
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

