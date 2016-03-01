#include <iostream>

#include "Application/Application.hpp"

#include "Core/World.hpp"
#include "Core/SpriteComponent.hpp"
#include "Core/InputComponent.hpp"
#include "Core/CameraComponent.hpp"
#include "Core/PointComponent.hpp"

#include "Button.hpp"
#include "LayerComponent.hpp"

#include "SimpleGui/Joystick.hpp"
#include "SimpleGui/Button.hpp"

class MapActor : public NActor
{
    public:
        MapActor()
        : mMapComponent("tileset",{20,20},{32,32})
        , mIsoMapComponent("iso-tileset",{20,20},{64,32},true)
        {
            sf::Vector2i coords;
            for (coords.x = 0; coords.x < 20; coords.x++)
            {
                for (coords.y = 0; coords.y < 20; coords.y++)
                {
                    mMapComponent.setTileId(coords,NMath::random(2,5));
                    mIsoMapComponent.setTileId(coords,NMath::random(2,5));
                }
            }
            mMapComponent.setPosition(0,0);
            mIsoMapComponent.setPosition(400,0);
            setPosition(0,0);
        }

    private:
        NLayerComponent mMapComponent;
        NLayerComponent mIsoMapComponent;
};

class EActor : public NActor
{
    public:
        EActor()
        {
            attachComponent(&mSpriteComponent);

            mSpriteComponent.setTexture("icon");
            mSpriteComponent.setOrigin(64,64);
        }

        NSpriteComponent mSpriteComponent;
};

class Player : public NActor
{
    public:
        Player()
        {
            attachComponent(&mSpriteComponent);
            attachComponent(&mCameraComponent);

            mSpriteComponent.setTexture("icon");
            mSpriteComponent.setOrigin(64,64);
        }

        NSpriteComponent mSpriteComponent;
        NCameraComponent mCameraComponent;
};

class EState : public ah::State
{
    public:
        EState(ah::StateManager& manager) : ah::State(manager)
        {
            mRight.setTexture("icon");
            mRight.setPosition(NWorld::getWindow().getSize().x-128,0);
            mRight.setCallback(SGUI::Button::Pressed,[&]()
            {
                ah::Application::close();
            });

            mLeft.setTexture("icon");
            mLeft.setPosition(0,NWorld::getWindow().getSize().y-128);
            mLeft.setCallback(SGUI::Button::Pressed,[&]()
            {
                auto e = NWorld::createActor<EActor>();
                std::string id;
                if (e != nullptr)
                {
                    e->setPosition(NVector(NMath::random(0.f,(float)NWorld::getWindow().getSize().x),NMath::random(0.f,(float)NWorld::getWindow().getSize().y)));
                    id = e->getId();
                }
                NWorld::setTimer(sf::seconds(2.f),[id](){NWorld::removeActor(id);});
            });

            mJoystick.setButtonTexture("joyButton");
            mJoystick.setBackgroundTexture("joyBackground");
            mJoystick.setPosition(sf::Vector2f(NWorld::getWindow().getSize().x - 150, NWorld::getWindow().getSize().y - 150));
            mJoystick.setDeltaMax(50);

            NWorld::createActor<MapActor>();

            mPlayer = NWorld::createActor<Player>();
            mPlayer->setPosition(100,100,100);

            #ifdef WINDOWS
            NWorld::save("t.xml");
            #else
            NWorld::save("/sdcard/t.xml");
            #endif
        }

        bool handleEvent(sf::Event const& event)
        {
            NWorld::addEvent(event);
            mLeft.handleEvent(event,NWorld::getWindow());
            mRight.handleEvent(event,NWorld::getWindow());
            mJoystick.handleEvent(event,NWorld::getWindow());
            return true;
        }

        bool update(sf::Time dt)
        {
            NWorld::tick(dt);

            mJoystick.update(dt);
            sf::Vector2f m = mJoystick.getDelta();
            if (m != sf::Vector2f() && mPlayer != nullptr)
            {
                mPlayer->setPosition(mPlayer->getPosition() + NVector::SFML2FToN(m * 300.f * dt.asSeconds()));
            }

            NWorld::update();

            ah::Application::getWindow().setDebugInfo("Actors",std::to_string(NWorld::getActorCount()));
            ah::Application::getWindow().setDebugInfo("Tickables",std::to_string(NWorld::getTickableCount()));
            ah::Application::getWindow().setDebugInfo("Renderables",std::to_string(NWorld::getRenderableCount()));
            ah::Application::getWindow().setDebugInfo("PPos",std::to_string(NWorld::getPointerPositionView(0).x) + " " + std::to_string(NWorld::getPointerPositionView(0).y));
            ah::Application::getWindow().setDebugInfo("SPos",std::to_string(NWorld::getPointerPositionScreen(0).x) + " " + std::to_string(NWorld::getPointerPositionScreen(0).y));

            return true;
        }

        void render(sf::RenderTarget& target, sf::RenderStates states)
        {
            NWorld::render(target);
            mLeft.render(target,states);
            mRight.render(target,states);
            mJoystick.render(target,states);
        }

    private:
        NActionTarget mController;
        SGUI::Button mLeft;
        SGUI::Button mRight;
        SGUI::Joystick mJoystick;
        Player::Ptr mPlayer;
};

int main()
{
    ah::Application::getResources().loadTexture("icon","icon.png");
    ah::Application::getResources().loadTexture("iso-tileset","iso-tileset.png");
    ah::Application::getResources().loadTexture("tileset","tileset.png");
    ah::Application::getResources().loadTexture("joyButton","joyButton.png");
    ah::Application::getResources().loadTexture("joyBackground","joyBackground.png");
    ah::Application::getWindow().create(sf::VideoMode::getDesktopMode(),"NodeEngine",sf::Style::Fullscreen);
    ah::Application::getWindow().showDebugInfo(true);
    ah::Application::getWindow().setDebugInfoFont("sansation.ttf");
    ah::Application::getWindow().setDebugInfoColor(sf::Color::White);
    ah::Application::getWindow().setKeyRepeatEnabled(false);

    ah::Application::getStates().registerState<EState>("EState");
    ah::Application::getStates().pushState("EState");

    ah::Application::run();

    return 0;
}
