#pragma once


#include "BombermanCore.h"
#include "Vector2.h"
#include "Delegates.h"
#include <thread>

Player* player;
SDL_Object* SDL_Obj;

Uint64 currentTime, previousTime;
float deltaTime, FPS;


float DeltaTimeUpdate()
{

    currentTime = SDL_GetPerformanceCounter();
    deltaTime = (float)(currentTime - previousTime) / (float)SDL_GetPerformanceFrequency();
    BombermanTime::DeltaTime = deltaTime;
    previousTime = currentTime;
    //timer_drop_eggbomb += deltaTime;
    
    float fps = (1.f / deltaTime);
    FPS = fps;
    
    char windowTitle[50];
    sprintf_s(windowTitle, "DeltaTime : %f  FPS: %f", deltaTime, fps);
    SDL_SetWindowTitle(SDL_Object::window, windowTitle);
    return fps;
}

MulticastDelegate<int, int, int> testing;

void test()
{

}
int main(int argc, char** argv)
{

    testing.AddLambda([](int a, int b, int c)
        {
            std::cout << a << " " << b << " " << c << "\n";
        });
    SDL_Obj = new SDL_Object();
    TextureFactory::LoadTexture("materials\\eggsplosion.png");
    TextureFactory::LoadTexture("materials\\EGGOLD.png");
    TextureFactory::LoadTexture("materials\\paperella.png");

    MapManager::Initialize("..\\BombermanCore\\Include\\Maps");

    std::cout << "SDL Object created" << std::endl;
    BombermanTime::BombermanTime(deltaTime);


    player = new Player(SDL_Obj);

    BombermanClientMgr::ServerConnectionEstablished.AddLambda([](int localPlayerID, int mapID, Vector2 pos, Vector2 dim)
        {
            player->ID = localPlayerID;
           player->transform.SetDimensions(dim);
            //std::cout <<"POSIZIONI "<< dim.x << " : " << dim.y << "\n";
           player->transform.SetPosition(pos);
            MapManager::LoadMap(mapID);

        });
    BombermanClientMgr::Initialize("127.0.0.1", 8888);

    

    int  running = 1;

      // std::thread drawerThread(&SDL_Object::EndFrameUpdate,SDL_Obj);
    while (running)
    {

       
        
       BombermanTime::DeltaTimeUpdate();
         
         SDL_Obj->StartFrameUpdate();
       
        UpdateMgr::Update();
        BombermanClientMgr::Update();
       
       // BombermanClientMgr::TransformsToSync[0]->SetPosition({ -1,0 });
       // BombermanClientMgr::TransformsToSync[1]->SetPosition({ 1011,512 });
       // BombermanClientMgr::TransformsToSync[2]->SetPosition({ 0,-1 });
       //
       //
        //BombermanClientMgr::TransformsToSync[5]->SetPosition({ 64,64 });
       // BombermanClientMgr::TransformsToSync[0x1c]->SetPosition({ 32,32 });

        SDL_Obj->EndFrameUpdate();
        
       //drawerThread.join();
    }
    
    //closesocket(Server_socket);
     WSACleanup();
    return 0;
}
