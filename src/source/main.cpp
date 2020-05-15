#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(int argc, char* argv[])
{
    const char* PATH_DEFAULT_TEXTURE = "resources/default_0.png";

    sf::RenderWindow window{ sf::VideoMode(800, 600), "Control of Ground" };
    window.setFramerateLimit(60);

    sf::Texture hero_texture{ };
    if (!hero_texture.loadFromFile("resources/default_0.png"))
    {
        std::cerr << "Load texture from: " << " is failed. Used default texture." << std::endl;
        hero_texture.loadFromFile(PATH_DEFAULT_TEXTURE);
    }
    
    sf::CircleShape test{ 100.f };
    test.setTexture(&hero_texture);

    while (window.isOpen())
    {
        //Update event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Update event

        //Update state

        //Update state

        //Render
        //Clearing of frame
        window.clear(sf::Color::White);

        //Drawling of frame
        window.draw(test);
        //window.draw(shape);

        //Display in window all of has been draw
        window.display();
        //Render
    }

    return 0;
}