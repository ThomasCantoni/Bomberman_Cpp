#pragma once
#include "BombermanClientMgr.h"
#include "Actor.h"
#include "IAttack.h"
#include <vector>
#include <functional>
#include "OnlinePlayer.h"
#include <array>


namespace Bomberman
{
   #define DEFAULT_POS Vector2(64,64)
   #define DEFAULT_DIM Vector2(64,64)

    class Player : public Actor, public IAttack
    {
    private:
        static Player* LocalPlayer;
    public:
        static  Player* const GetLocalPlayer() 
        { 
            return LocalPlayer; 
        } 
        unsigned int numberOfLives;
        unsigned int score;
        float secondAccumulator;
        float TimerDropEggbomb;
        float speed;
        float speedX = 1;
        float speedY = 1;
        float speedXnegative = 1;
        float speedYnegative = 1;
        Vector2 velocity;
        const Uint8* keys;
        
        Player()=delete;
        Player(const SDL_Object* SDL_O);
        ~Player();
        const Uint8* GetInput();
        void Update() override;
        void InstantiateEgg(const Vector2 pos) override ;
        std::shared_ptr<NetworkPacket> GetPacketTransform() const override;
        std::shared_ptr<NetworkPacket> GetPacketMovement() const;

        
    };
}