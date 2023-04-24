#pragma once


#include "BombermanClientMgr.h"
//#include "byteconverter.h"

#include "Actor.h"
#include "IAttack.h"
#include <vector>
#include <functional>

#include "OnlinePlayer.h"
#include <array>
#include "RigidBody.h"

namespace Bomberman
{

    class Player : public Actor, public IAttack
    {
    public:
        //NETWORK OPERATIONS DEFINED FURTHER DOWN THE FILE

        int ID;

        //Vector2 position;
        float  secondAccumulator,TimerDropEggbomb;
        //const float timer_reset_value = 6;
        unsigned int numberOfLives;
        //unsigned int number_of_bombs;
        unsigned int score;
        float speed;
        float speedX = 1;
        float speedY = 1;
        float speedXnegative = 1;
        float speedYnegative = 1;

        const Uint8* keys;
        
        //SDL_Object* SDL_Obj;
       


        Player()=delete;

        Player(const SDL_Object* SDL_O);

        ~Player();
        void Manage_Input();
        void Update() override;
        void InstantiateEgg(const Vector2 pos) override ;


        //NETWORKING

        std::shared_ptr<SerialData> GetPacketTransform() const;
        //void ManageNetworkOperations();
        //NetworkManager* NM;
        //unsigned char message[50];
        //OnlinePlayer* OnlinePlayers[3];
        //
        //
        //void ProcessMessage     (const unsigned char* message,const int msg_length) ;
        //
        //
        ////THIS IS SIMILAR TO DECLARING A DELEGATE IN C#
        //
        //typedef void(Player::* NetworkOp)(const unsigned char*,int);
        //std::vector<NetworkOp> NetworkOps;
        //void UpdateOnlinePlayer (const unsigned char* message, int playerID ) ;
        //void InstantiateEgg     (const unsigned char* message, int playerID ) ;
        //void InstantiatePlayer  (const unsigned char* message, int playerID ) ;
        //void KillOnlinePlayer   (const unsigned char* message, int playerID ) ;
        ////void OnCollide(Collision* collisionInfo) override;

    };
}