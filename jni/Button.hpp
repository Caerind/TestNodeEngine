#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics/Sprite.hpp>


#include "Application/Application.hpp"

class Button
{
    public:
        Button();

        void setTexture(std::string const& id);
        void setPosition(NVector const& position);

        sf::FloatRect getBounds() const;
        bool contains(NVector const& position);

        void setCallback(std::function<void()> callback);

        void handleEvent(sf::Event const& event, NVector const& position);
        void render(sf::RenderTarget& target, sf::RenderStates states);

    private:
        sf::Sprite mSprite;
        std::function<void()> mCallback;
};

#endif // BUTTON_HPP
