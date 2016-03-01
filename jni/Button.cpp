#include "Button.hpp"

Button::Button()
{
    mCallback = [](){};
}

void Button::setTexture(std::string const& id)
{
    mSprite.setTexture(ah::Application::getResources().getTexture(id));
}

void Button::setPosition(NVector const& position)
{
    mSprite.setPosition(NVector::NToSFML2F(position));
}

sf::FloatRect Button::getBounds() const
{
    return mSprite.getGlobalBounds();
}

bool Button::contains(NVector const& position)
{
    return getBounds().contains(NVector::NToSFML2F(position));
}

void Button::setCallback(std::function<void()> callback)
{
    mCallback = callback;
}

void Button::handleEvent(sf::Event const& event, NVector const& position)
{
    if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    || (event.type == sf::Event::TouchBegan))
    {
        if (mCallback && contains(position))
        {
            mCallback();
        }
    }
}

void Button::render(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(mSprite);
}
