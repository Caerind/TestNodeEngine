#ifndef SGUI_SPRITE_H
#define SGUI_SPRITE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <map>

#include "../Application/Application.hpp"

namespace SGUI
{

class Sprite
{
    public:
        Sprite();

        void setTexture(sf::Texture& texture);
        void setTexture(std::string const& texture);

        void setTextureRect(int type, sf::IntRect textureRect);
        void useTextureRect(int type);
        bool hasTextureRect(int type);

        sf::Vector2f getSize() const;
        void setSize(sf::Vector2f newSize);
        void setSize(float x, float y);

		sf::FloatRect getBounds() const;
		bool contains(sf::Vector2f const& pos) const;

		void render(sf::RenderTarget& target, sf::RenderStates states);

    protected:
        sf::Sprite mSprite;
        std::map<int,sf::IntRect> mRects;
};

}

#endif // SGUI_SPRITE_H
