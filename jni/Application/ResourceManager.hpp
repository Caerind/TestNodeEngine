#ifndef AH_RESOURCEMANAGER_HPP
#define AH_RESOURCEMANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "../Utils/Assume.hpp"
#include "../Utils/Map.hpp"

namespace ah
{

class ResourceManager
{
    public:
        ResourceManager();
        ~ResourceManager();

        void loadTexture(std::string const& id, std::string const& filename);
        void loadImage(std::string const& id, std::string const& filename);
        void loadFont(std::string const& id, std::string const& filename);
        void loadSoundBuffer(std::string const& id, std::string const& filename);

        bool isLoadedTexture(std::string const& id);
        bool isLoadedImage(std::string const& id);
        bool isLoadedFont(std::string const& id);
        bool isLoadedSoundBuffer(std::string const& id);

        sf::Texture& getTexture(std::string const& id, std::string const& filename = "");
        sf::Image& getImage(std::string const& id, std::string const& filename = "");
        sf::Font& getFont(std::string const& id, std::string const& filename = "");
        sf::SoundBuffer& getSoundBuffer(std::string const& id, std::string const& filename = "");

        void releaseTexture(std::string const& id);
        void releaseImage(std::string const& id);
        void releaseFont(std::string const& id);
        void releaseSoundBuffer(std::string const& id);

    protected:
        NMap<std::string,sf::Texture> mTextures;
        NMap<std::string,sf::Image> mImages;
        NMap<std::string,sf::Font> mFonts;
        NMap<std::string,sf::SoundBuffer> mSoundBuffers;
};

} // namespace ah

#endif // AH_RESOURCEMANAGER_HPP
