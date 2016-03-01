#ifndef SGUI_JOYSTICK_HPP
#define SGUI_JOYSTICK_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../Application/Application.hpp"

#include "Widget.hpp"

namespace SGUI
{

class Joystick : public Widget
{
    public:
        Joystick();

        void setButtonTexture(std::string const& id);
        void setButtonRect(sf::IntRect const& rect);

        void setBackgroundTexture(std::string const& id);
        void setBackgroundRect(sf::IntRect const& rect);

        sf::Vector2f getDelta() const;
        bool isHeld() const;

        void setDeltaMax(float dMax);

        sf::FloatRect getBounds() const;
        bool contains(sf::Vector2f const& pos) const;

        virtual void handleEvent(sf::Event const& event, ah::Window& window);
        virtual void update(sf::Time dt);
        virtual void render(sf::RenderTarget& target, sf::RenderStates states);

    protected:
        sf::Sprite mButton;
        sf::Sprite mBackground;
        bool mHeld;
        unsigned int mFingerId;
        float mDeltaMax;
        bool mMouse;
};

} // namespace SGUI

#endif // SGUI_JOYSTICK_HPP
