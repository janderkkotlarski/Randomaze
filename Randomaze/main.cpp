#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

sf::Vector2i divide(const sf::Vector2i& numerator, const int denominator)
{
    return sf::Vector2i (numerator.x/denominator, numerator.y/denominator);
}

sf::Vector2f Vect_i2f(const sf::Vector2i& vecti)
{
    return static_cast<sf::Vector2f>(vecti);
}

class pattern
{
    const std::string m_filename{"Tile.png"};

    sf::Color m_color;

    sf::Vector2i m_posit;

    sf::Vector2i m_dims{0, 0};

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

    void get_dims()
    {
        const sf::FloatRect dims{m_sprite.getLocalBounds()};

        assert(dims.width > 0);
        assert(dims.height > 0);

        m_dims.x = static_cast<int>(dims.width);
        m_dims.y = static_cast<int>(dims.height);
    }

    void set_center()
    {
        m_sprite.setOrigin(Vect_i2f(m_dims/2));
    }

    void set_color()
    {
        m_sprite.setColor(m_color);
    }

    void set_posit()
    {
        m_sprite.setPosition(Vect_i2f(m_posit));
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

    void reposit(const sf::Vector2i& posit)
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

    sf::Vector2i output_dims()
    {
        return m_dims;
    }

    pattern(const std::string& filename,
            const sf::Color& color,
            const sf::Vector2i& posit)
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

    sf::Vector2i m_posit;

    const sf::Color m_dark{63, 63, 63};
    const sf::Color m_grey{127, 127, 127};
    const sf::Color m_light{191, 191, 191};

    const sf::Color m_dark_red{127, 63, 63};
    const sf::Color m_dark_green{63, 127, 63};
    const sf::Color m_dark_blue{63, 63, 127};

    const sf::Color m_light_red{191, 127, 127};
    const sf::Color m_light_green{127, 191, 127};
    const sf::Color m_light_blue{127, 127, 191};

    sf::Vector2i m_direction{0, 0};

    int m_type{3};

    const sf::Vector2i m_stepdims;

    const int m_steps{1};

    int m_moves{0};

    sf::Color m_color;

    pattern m_pattern;

    void reposit()
    {
        m_pattern.reposit(m_posit);
    }

    void steps()
    {
        m_posit.x += m_direction.x*m_stepdims.x;
        m_posit.y += m_direction.y*m_stepdims.y;

        reposit();
    }

    void keystep()
    {
        if (m_moves == 0)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                m_direction = sf::Vector2i(1, 0);
                m_moves = m_steps;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                m_direction = sf::Vector2i(-1, 0);
                m_moves = m_steps;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                m_direction = sf::Vector2i(0, -1);
                m_moves = m_steps;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                m_direction = sf::Vector2i(0, 1);
                m_moves = m_steps;
            }
        }
    }

    void movic()
    {
        if (m_moves > 0)
        {
            steps();
            --m_moves;

            if (m_moves == 0)
            {
                m_direction = sf::Vector2i(0, 0);
            }
        }
    }

    void stepping()
    {
        if (m_type > 0)
        {
            keystep();
            movic();
        }
    }

    public:

    void type_tile(const int type)
    {
        m_type = type;
    }

    void color_tile()
    {
        switch (m_type)
        {
            case 0:
                m_color = m_dark;
                break;
            case 1:
                m_color = m_light_red;
                break;
            case 2:
                m_color = m_light_green;
                break;
            case 3:
                m_color = m_light_blue;
                break;
            case 10:
                m_color = m_light;
                break;
            case -1:
                m_color = m_dark_red;
                break;
            case -2:
                m_color = m_dark_green;
                break;
            case -3:
                m_color = m_dark_blue;
                break;
            case -10:
                m_color = m_grey;
                break;
            default:
                m_color = m_dark;
        }

        m_pattern.recolor(m_color);
    }

    void stepper()
    {
        stepping();
    }

    void display(sf::RenderWindow& window)
    {
        m_pattern.display(window);
    }

    sf::Vector2i output_dims()
    {
        return m_pattern.output_dims();
    }

    tile(const sf::Vector2i& posit, const int type, const sf::Vector2i stepdims,
         const int steps)
        : m_posit(posit), m_type(type), m_stepdims(stepdims),
          m_steps(steps), m_color(m_dark),
          m_pattern(m_filename, m_color, m_posit)
    {
        color_tile();
    }

    ~tile()
    {

    }


};


int window_maker(const std::string& program_name)
{
    const float seconds{30.0f};
    const float delta{0.025f};

    sf::Clock clock;
    sf::Time time;

    sf::Color black{0, 0, 0};
    sf::Color white{255, 255, 255};
    sf::Color invis{0, 0, 0, 0};

    const std::string image_name{"Ripple_Square.png"};

    const sf::Vector2i home{0, 0};

    const int step_div{8};

    pattern patchy{image_name, invis, home};

    const sf::Vector2i tiledims{patchy.output_dims()};
    const sf::Vector2i stepdims{tiledims/step_div};
    const sf::Vector2i windims{5*tiledims};
    const sf::Vector2i middle{windims/2};

    const sf::Vector2i upper_left{windims/4};

    tile tily{middle, 10, stepdims, step_div};

    sf::RenderWindow window(sf::VideoMode(windims.x, windims.y), program_name, sf::Style::Default);

    while (window.isOpen())
    {
        sf::Clock watch;
        sf::Time timer;

        sf::Event event;

        window.clear(black);

        tily.display(window);

        window.display();

        tily.stepper();

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

        timer = watch.getElapsedTime();

        while(timer.asSeconds() < delta)
        {
            timer = watch.getElapsedTime();
        }
    }

    return 1;
}

int main()
{
    const std::string program_name{"Randomaze V0.1"};

    return window_maker(program_name);
}

