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

bool ResourceManager::isLoadedTexture(std::string const& id)
{
    return mTextures.contains(id);
}

bool ResourceManager::isLoadedImage(std::string const& id)
{
    return mImages.contains(id);
}

bool ResourceManager::isLoadedFont(std::string const& id)
{
    return mFonts.contains(id);
}

bool ResourceManager::isLoadedSoundBuffer(std::string const& id)
{
    return mSoundBuffers.contains(id);
}

sf::Texture& ResourceManager::getTexture(std::string const& id, std::string const& filename)
{
    if (!isLoadedTexture(id) && filename != "")
    {
        loadTexture(id,filename);
    }
    Assume((isLoadedTexture(id) == true));
    return mTextures[id];
}

sf::Image& ResourceManager::getImage(std::string const& id, std::string const& filename)
{
    if (!isLoadedImage(id) && filename != "")
    {
        loadImage(id,filename);
    }
    Assume((isLoadedImage(id) == true));
    return mImages[id];
}

sf::Font& ResourceManager::getFont(std::string const& id, std::string const& filename)
{
    if (!isLoadedFont(id) && filename != "")
    {
        loadFont(id,filename);
    }
    Assume((isLoadedFont(id) == true));
    return mFonts[id];
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string const& id, std::string const& filename)
{
    if (!isLoadedSoundBuffer(id) && filename != "")
    {
        loadSoundBuffer(id,filename);
    }
    Assume((isLoadedSoundBuffer(id) == true));
    return mSoundBuffers[id];
}

void ResourceManager::releaseTexture(std::string const& id)
{
    mTextures.remove(id);
}

void ResourceManager::releaseImage(std::string const& id)
{
    mImages.remove(id);
}

void ResourceManager::releaseFont(std::string const& id)
{
    mFonts.remove(id);
}

void ResourceManager::releaseSoundBuffer(std::string const& id)
{
    mSoundBuffers.remove(id);
}

} // namespace ah
