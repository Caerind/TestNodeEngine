#include "LayerComponent.hpp"
#include "Core/World.hpp"
#include "Utils/Math.hpp"
#include "Utils/Compression.hpp"

NLayerComponent::NLayerComponent() : mTexture("")
{
    mIsometric = false;
}

NLayerComponent::NLayerComponent(std::string const& textureName, sf::Vector2i mapSize, sf::Vector2i tileSize, bool isometric) : mTexture(textureName)
{
    mIsometric = isometric;

    create(mapSize,tileSize);
    setTexture(textureName);

    // TODO : Better structure, here : call texture before create = no texture because no sprite atm
}

void NLayerComponent::create(sf::Vector2i mapSize, sf::Vector2i tileSize)
{
    mMapSize = mapSize;
    mTileSize = tileSize;

    mTiles.resize(mMapSize.x * mMapSize.y);

    for (int i = 0; i < mMapSize.x; ++i)
    {
        for (int j = 0; j < mMapSize.y; ++j)
        {
            sf::Sprite& tile = mTiles[i + j * mMapSize.x];

            if (mIsometric)
            {
                if (j % 2 == 0)
                {
                    tile.setPosition(i * mTileSize.x, j * mTileSize.y * 0.5f);
                }
                else
                {
                    tile.setPosition((i + 0.5f) * mTileSize.x, j * mTileSize.y * 0.5f);
                }
            }
            else
            {
                tile.setPosition(i * mTileSize.x, j * mTileSize.y);
            }
        }
    }
}

void NLayerComponent::setTexture(std::string const& textureName)
{
    mTexture = textureName;
    sf::Texture& texture = NWorld::getResources().getTexture(textureName);
    for (std::size_t i = 0; i < mTiles.size(); i++)
    {
        mTiles[i].setTexture(texture);
    }
}

void NLayerComponent::render(sf::RenderTarget& target)
{
    sf::RenderStates states;
    states.transform *= getFinalTransform();
    for (std::size_t i = 0; i < mTiles.size(); i++)
    {
        target.draw(mTiles[i],states);
    }
}

sf::FloatRect NLayerComponent::getBounds() const
{
    return getFinalTransform().transformRect(sf::FloatRect(0,0,mTileSize.x * mMapSize.x,mTileSize.y * mMapSize.y));
}

bool NLayerComponent::contains(NVector const& position) const
{
    return getBounds().contains(NVector::NToSFML2F(position));
}

void NLayerComponent::setIsometric(bool isometric)
{
    mIsometric = isometric;
}

bool NLayerComponent::isIsometric() const
{
    return mIsometric;
}

void NLayerComponent::setTileId(sf::Vector2i const& coords, int id)
{
    if (coords.x >= 0 && coords.x < mMapSize.x && coords.y >= 0 && coords.y < mMapSize.y)
    {
        mTiles[coords.x + coords.y * mMapSize.x].setTextureRect(idToRect(id));
    }
}

int NLayerComponent::getTileId(sf::Vector2i const& coords)
{
    if (coords.x >= 0 && coords.x < mMapSize.x && coords.y >= 0 && coords.y < mMapSize.y)
    {
        return rectToId(mTiles[coords.x + coords.y * mMapSize.x].getTextureRect());
    }
    return 0;
}

sf::IntRect NLayerComponent::idToRect(int id)
{
    if (mTexture != "")
    {
        int tilePerLine = NWorld::getResources().getTexture(mTexture).getSize().x / mTileSize.x;
        int x = id % tilePerLine;
        int y = id / tilePerLine;
        return sf::IntRect(x * mTileSize.x,y * mTileSize.y, mTileSize.x, mTileSize.y);
    }
    return sf::IntRect();
}

int NLayerComponent::rectToId(sf::IntRect const& rect)
{
    if (mTexture != "")
    {
        int x = rect.left / mTileSize.x;
        int y = rect.top / mTileSize.y;
        int tilePerLine = NWorld::getResources().getTexture(mTexture).getSize().x / mTileSize.x;
        int id = x + y * tilePerLine;
        return id;
    }
    return 0;
}

void NLayerComponent::load(pugi::xml_node& node, std::string const& name)
{
    pugi::xml_node n = node.child(name.c_str());
    pugi::xml_attribute texture = n.attribute("texture");
    if (texture)
    {
        setTexture(texture.value());
    }
    mMapSize = NVector::NToSFML2I(NString::toVector(n.attribute("msize").value()));
    mTileSize = NVector::NToSFML2I(NString::toVector(n.attribute("tsize").value()));
    mIsometric = n.attribute("iso").as_bool();
    setPosition(NString::toVector(n.attribute("pos").value()));
    setScale(NString::toVector(n.attribute("sca").value()));
    setRotation(n.attribute("rot").as_float());

    create(mMapSize,mTileSize);

    // Load Tile Data
    std::string data = n.attribute("data").value();
    sf::Vector2i coords;

    std::stringstream ss;
    ss << data;
    ss >> data;

    if (!NCompression::decompress(data))
    {
        return;
    }
    std::vector<unsigned char> byteVector; // hold decompressed data as bytes
    byteVector.reserve(mMapSize.x * mMapSize.y * 4); // number of tiles * 4 bytes = 32bits/tile

    for (std::string::iterator i = data.begin(); i != data.end(); ++i)
    {
        byteVector.push_back(*i);
    }
    for (std::size_t i = 0; i < byteVector.size() - 3; i += 4)
    {
        int id = byteVector[i] | byteVector[i+1] << 8 | byteVector[i+2] << 16 | byteVector[i+3] << 24;
        setTileId(coords,id);

        coords.x = (coords.x + 1) % mMapSize.x;
        if (coords.x == 0)
        {
            coords.y++;
        }
    }
}

void NLayerComponent::save(pugi::xml_node& node, std::string const& name)
{
    pugi::xml_node n = node.append_child(name.c_str());
    if (mTexture != "")
    {
        n.append_attribute("texture") = mTexture.c_str();
    }
    n.append_attribute("msize") = NString::toString(mMapSize).c_str();
    n.append_attribute("tsize") = NString::toString(mTileSize).c_str();
    n.append_attribute("iso") = mIsometric;
    n.append_attribute("pos") = NString::toString(getPosition()).c_str();
    n.append_attribute("sca") = NString::toString(getScale()).c_str();
    n.append_attribute("rot") = getRotation();

    // Save Tile Data
    std::string data;
    data.reserve(mMapSize.x * mMapSize.y * 4);
    sf::Vector2i coords;
    for (coords.y = 0; coords.y < mMapSize.y; coords.y++)
    {
        for (coords.x = 0; coords.x < mMapSize.x; coords.x++)
        {
            const int id = getTileId(coords);
            data.push_back((char)(id));
            data.push_back((char)(id >> 8));
            data.push_back((char)(id >> 16));
            data.push_back((char)(id >> 24));
        }
    }
    if (NCompression::compress(data))
    {
        n.append_attribute("data") = data.c_str();
    }
}
