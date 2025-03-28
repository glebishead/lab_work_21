#include <SFML/Graphics.hpp>
#include <iostream>

void reset_coords(sf::CircleShape& circle) {
    double x0 = rand() % 550;
    double y0 = rand() % 550;
    std::cout << x0 << " " << y0 << std::endl;
    circle.setPosition(sf::Vector2f(x0, y0));
}

void edit_text(sf::Text& some_text, sf::Font& font) {
    some_text.setFont(font);
    some_text.setCharacterSize(24);
    some_text.setStyle(sf::Text::Bold);
    
}

int main()
{
    long long misses;
    long score;
    double precision;
    score = 0;
    misses = 0;
    precision = 100;

    std::string score_str = std::to_string(score);
    std::string precision_str = std::to_string(precision);

    sf::Font font;
    if (!font.loadFromFile("ALGER.ttf"))
    {
        // error
    }

    sf::Text score_text;
    edit_text(score_text, font);
    score_text.setString(score_str);
    score_text.setPosition(sf::Vector2f(130, 20));
    

    sf::Text precision_text;
    precision_text.setString(precision_str);
    edit_text(precision_text, font);
    precision_text.setPosition(sf::Vector2f(160, 60));

    sf::Text strikes_message_text;
    std::string strikes_str = "Points:";
    strikes_message_text.setString(strikes_str);
    edit_text(strikes_message_text, font);
    strikes_message_text.setPosition(sf::Vector2f(20, 20));

    sf::Text precision_message_text;
    std::string precision_message_str = "Precision:";
    precision_message_text.setString(precision_message_str);
    edit_text(precision_message_text, font);
    precision_message_text.setPosition(sf::Vector2f(20, 60));

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
                    score_str = std::to_string(score);
                    score_text.setString(score_str);
                    reset_coords(circle);
                }
                else {
                    misses += 1;
                }
                precision = round((1.0 * score) / (score + misses) * 100 * 100) / 100;
                precision_str = std::to_string(precision);
                precision_text.setString(precision_str);
            }
        }

        window.clear();
        window.draw(circle);
        window.draw(precision_text);
        window.draw(score_text);
        window.draw(strikes_message_text);
        window.draw(precision_message_text);
        window.display();
    }

    return 0;
}
