#include <SFML/Graphics.hpp>
#include <iostream>

void reset_coords(sf::CircleShape& circle) {
    double x0 = rand() % 550;
    double y0 = rand() % 550;
    std::cout << x0 << " " << y0 << std::endl;
    circle.setPosition(sf::Vector2f(x0, y0));
}

int main()
{
    long long misses;
    long score;
    score = 0;
    misses = 0;
    std::string score_str = std::to_string(score);
    std::string misses_str = std::to_string(misses);

    sf::Font font;
    if (!font.loadFromFile("ALGER.ttf"))
    {
        // error
    }
    sf::Text text;
    text.setFont(font);
    text.setString(score_str);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(20, 20));

    sf::Text text1;
    text1.setFont(font);
    text1.setString(misses_str);
    text1.setCharacterSize(24);
    text1.setStyle(sf::Text::Bold);
    text1.setPosition(sf::Vector2f(20, 60));

    sf::RenderWindow window(sf::VideoMode(600, 600), "aim trainer");

    sf::CircleShape circle(10.f);
    circle.setFillColor(sf::Color::Green);
    reset_coords(circle);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {

                misses += 1;
                std::string misses_str = std::to_string(misses);
                text1.setString(misses_str);

                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                double mouse_x = mouse_position.x;
                double mouse_y = mouse_position.y;

                sf::Vector2f circle_position = circle.getPosition();
                double circle_x = circle_position.x;
                double circle_y = circle_position.y;

                std::cout << "MOUSE: " << mouse_x << " " << mouse_y << std::endl;
                std::cout << "CIRCLE LEFT UP: " << circle_x << " " << circle_y << std::endl;
                std::cout << "CIRCLE RIGHT DOWN: " << circle_x + 2 * circle.getRadius() << " " << circle_y + 2 * circle.getRadius() << std::endl << std::endl;

                if ((circle_x < mouse_x && mouse_x < (circle_x + 2 * circle.getRadius()) &&
                    (circle_y < mouse_y && mouse_y < (circle_y + 2 * circle.getRadius())))) {
                    score += 1;
                    std::string score_str = std::to_string(score);
                    text.setString(score_str);
                    reset_coords(circle);
                }

            }
        }

        window.clear();
        window.draw(circle);
        window.draw(text);
        window.draw(text1);
        window.display();
    }

    return 0;
}