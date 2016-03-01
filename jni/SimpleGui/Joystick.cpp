#include "Joystick.hpp"

namespace SGUI
{

Joystick::Joystick() : Widget()
{
    mHeld = false;
}

void Joystick::setButtonTexture(std::string const& id)
{
    mButton.setTexture(ah::Application::getResources().getTexture(id));
    mButton.setOrigin(mButton.getGlobalBounds().width /2, mButton.getGlobalBounds().height /2);
}

void Joystick::setButtonRect(sf::IntRect const& rect)
{
    mButton.setTextureRect(rect);
    mButton.setOrigin(mButton.getGlobalBounds().width /2, mButton.getGlobalBounds().height /2);
}

void Joystick::setBackgroundTexture(std::string const& id)
{
    mBackground.setTexture(ah::Application::getResources().getTexture(id));
    mBackground.setOrigin(mBackground.getGlobalBounds().width /2, mBackground.getGlobalBounds().height /2);
}

void Joystick::setBackgroundRect(sf::IntRect const& rect)
{
    mBackground.setTextureRect(rect);
    mBackground.setOrigin(mBackground.getGlobalBounds().width /2, mBackground.getGlobalBounds().height /2);
}

sf::Vector2f Joystick::getDelta() const
{
    sf::Vector2f p = mButton.getPosition();
    float r = std::sqrt(p.x*p.x + p.y*p.y);
    if (r == 0.f)
    {
        return sf::Vector2f();
    }
    return sf::Vector2f(p.x/r,p.y/r) * (r / mDeltaMax);
}

bool Joystick::isHeld() const
{
    return mHeld;
}

void Joystick::setDeltaMax(float dMax)
{
    mDeltaMax = dMax;
}

sf::FloatRect Joystick::getBounds() const
{
    sf::FloatRect r = mButton.getGlobalBounds();
    r.left += getPosition().x;
    r.top += getPosition().y;
    return r;
}

bool Joystick::contains(sf::Vector2f const& pos) const
{
    return Joystick::getBounds().contains(pos);
}

void Joystick::update(sf::Time dt)
{
    if (mHeld)
    {
        sf::Vector2f p = ah::Application::getWindow().getPointerPosition(mFingerId) - getPosition();
        float r = std::sqrt(p.x*p.x + p.y*p.y);
        if (r >= mDeltaMax)
        {
            mButton.setPosition(mDeltaMax * sf::Vector2f(p.x/r,p.y/r));
        }
        else
        {
            mButton.setPosition(p);
        }
    }
}

void Joystick::handleEvent(sf::Event const& event, ah::Window& window)
{
    #ifdef WINDOWS
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && Joystick::contains(window.getPointerPosition()))
    {
        mHeld = true;
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        mHeld = false;
        mButton.setPosition(0,0);
    }
    #else
    if (event.type == sf::Event::TouchBegan && Joystick::contains(window.getPointerPosition(event.touch.finger)))
    {
        mHeld = true;
        mFingerId = event.touch.finger;
    }
    if (event.type == sf::Event::TouchEnded && event.touch.finger == mFingerId)
    {
        mHeld = false;
        mButton.setPosition(0,0);
    }
    #endif
}

void Joystick::render(sf::RenderTarget& target, sf::RenderStates states)
{
	states.transform *= getTransform();
    target.draw(mBackground,states);
    target.draw(mButton,states);
}

} // namespace SGUI
