#include "ResourceManager.hpp"

namespace ah
{

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadTexture(std::string const& id, std::string const& filename)
{
    std::string f = filename;
    #ifdef WINDOWS
    f = "../assets/" + filename;
    #endif // WINDOWS
    mTextures[id].loadFromFile(f);
}

void ResourceManager::loadImage(std::string const& id, std::string const& filename)
{
    std::string f = filename;
    #ifdef WINDOWS
    f = "../assets/" + filename;
    #endif // WINDOWS
    mImages[id].loadFromFile(f);
}

void ResourceManager::loadFont(std::string const& id, std::string const& filename)
{
    std::string f = filename;
    #ifdef WINDOWS
    f = "../assets/" + filename;
    #endif // WINDOWS
    mFonts[id].loadFromFile(f);
}

void ResourceManager::loadSoundBuffer(std::string const& id, std::string const& filename)
{
    std::string f = filename;
    #ifdef WINDOWS
    f = "../assets/" + filename;
    #endif // WINDOWS
    mSoundBuffers[id].loadFromFile(f);
}

sf::Texture& ResourceManager::getTexture(std::string const& id)
{
    if (mTextures.find(id) == mTextures.end())
    {
        std::cerr << "Resource : " << id << " not loaded properly" << std::endl;
        assert(false);
    }
    return mTextures[id];
}

sf::Image& ResourceManager::getImage(std::string const& id)
{
    if (mImages.find(id) == mImages.end())
    {
        std::cerr << "Resource : " << id << " not loaded properly" << std::endl;
        assert(false);
    }
    return mImages[id];
}

sf::Font& ResourceManager::getFont(std::string const& id)
{
    if (mFonts.find(id) == mFonts.end())
    {
        std::cerr << "Resource : " << id << " : not loaded properly" << std::endl;
        assert(false);
    }
    return mFonts[id];
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string const& id)
{
    if (mSoundBuffers.find(id) == mSoundBuffers.end())
    {
        std::cerr << "Resource : " << id << " : not loaded properly" << std::endl;
        assert(false);
    }
    return mSoundBuffers[id];
}

void ResourceManager::releaseTexture(std::string const& id)
{
    mTextures.erase(mTextures.find(id));
}

void ResourceManager::releaseImage(std::string const& id)
{
    mImages.erase(mImages.find(id));
}

void ResourceManager::releaseFont(std::string const& id)
{
    mFonts.erase(mFonts.find(id));
}

void ResourceManager::releaseSoundBuffer(std::string const& id)
{
    mSoundBuffers.erase(mSoundBuffers.find(id));
}

} // namespace ah
