#ifndef NLAYERCOMPONENT_HPP
#define NLAYERCOMPONENT_HPP

#include <vector>

#include <SFML/Graphics/Sprite.hpp>

#include "Core/SceneComponent.hpp"

class NLayerComponent : public NSceneComponent
{
    public:
        NLayerComponent();
        NLayerComponent(std::string const& textureName, sf::Vector2i mapSize, sf::Vector2i tileSize, bool isometric = false);

        void create(sf::Vector2i mapSize, sf::Vector2i tileSize);

        void setTexture(std::string const& textureName);

        void render(sf::RenderTarget& target);

        sf::FloatRect getBounds() const;
        bool contains(NVector const& position) const;

        void setIsometric(bool isometric);
        bool isIsometric() const;

        void setTileId(sf::Vector2i const& coords, int id);
        int getTileId(sf::Vector2i const& coords);

        sf::IntRect idToRect(int id);
        int rectToId(sf::IntRect const& rect);

        virtual void load(pugi::xml_node& node, std::string const& name = "LayerComponent");
        virtual void save(pugi::xml_node& node, std::string const& name = "LayerComponent");

    private:
        std::vector<sf::Sprite> mTiles;
        sf::Vector2i mMapSize;
        sf::Vector2i mTileSize;
        std::string mTexture;
        bool mIsometric;
};

#endif // NLAYERCOMPONENT_HPP
