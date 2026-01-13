#include <SFML/Graphics/RenderWindow.hpp>
#include "ParticleSystem.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML_Window");
    window.setFramerateLimit(60);

    ParticleSystem particles;
    particles.init(window.getSize());

    // run the program as long as the window is open
    while (window.isOpen())
    {   
        // check all the window's events that were triggered since the last iteration of the loop
        while (auto event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        //update particle system
        particles.update();

        window.clear(sf::Color::Black);
        
        //draw particles
        particles.draw(window);

        window.display();
    }

    return 0;
}