#pragma once
//#include <stdio.h>
//#include <float.h>
//#include <stdbool.h>
namespace Bomberman {};
using namespace Bomberman;
#define SDL_MAIN_HANDLED


#include "Time.h"
#include "UpdateMgr.h"
#include "Player.h"
#include "UpdateMgr.h"
#include "PhysicsMgr.h"

#include "Map.h"
#include <string>
#include <list>



#include "Player.h"

#define FLT_EXPO_SIZE 5


#define TIMER_DROP_EGGBOMB 5.f

int recv_size, running, bind_error;

//Player OnlinePlayers [2];
Player* player;

SDL_Object* SDL_Obj;
NetworkManager* NM;
//SDL_Rect* map_obstacle;

Uint64 currentTime, previousTime;
//const float* Delta_Time_ref;
float deltaTime, FPS;

//int main2()
//{
//	printf("Hello");
//	Vector2 test;
//	test.x = 100;
//	test.y = 100;
//	Vector2 test2;
//	test2.x = 0;
//	test2.y = 0;
//	Vector2 result = Vector2::Lerp(test, test2, 0.5f);
//
//	std::string string_test = { 'C','I','A','A',65,'o' };
//	std::string string_to_append = { 'Z','Z','Z','Z','Z','Z', };
//	printf("\n STRING %s  ", string_test.c_str());
//	printf("\n STRING %s  ", string_to_append.c_str());
//
//	//byteconverter::BytesAppend(string_test, string_test.length(), 2, string_to_append, 5);
//	string_test.append(string_to_append);
//	printf("\n RESULT %f  :  %f ",result.x,result.y);
//	printf("\n STRING %s  ", string_test.c_str());
//	
//
//	return 0;
//}
//std::list<IUpdatable*> UPDATABLES;
float DeltaTimeUpdate()
{

    currentTime = SDL_GetPerformanceCounter();
    deltaTime = (float)(currentTime - previousTime) / (float)SDL_GetPerformanceFrequency();
    Time::DeltaTime = deltaTime;
    previousTime = currentTime;
    //timer_drop_eggbomb += deltaTime;
    
    float fps = (1.f / deltaTime);
    FPS = fps;
    
    char windowTitle[50];
    sprintf_s(windowTitle, "DeltaTime : %f  FPS: %f", deltaTime, fps);
    SDL_SetWindowTitle(SDL_Object::window, windowTitle);
    return fps;
}


class Fruit 
{
public:
    virtual void Test() = 0;
};
class Banana : public Fruit 
{
public:
    void Test() override 
    {

    }
};

  
int main(int argc, char** argv)
{
    Fruit* f;
    f = new Banana();
    
    /*char* server_ip = 37.;
    char* test = argv[2];
    int port = atoi(test);*/
    //printf("port IS %d\n", port);
    //bomberman_map_init();
    SDL_Obj = new SDL_Object();
    TextureFactory::LoadTexture("materials\\eggsplosion.png");
    TextureFactory::LoadTexture("materials\\EGGOLD.png");
    TextureFactory::LoadTexture("materials\\paperella.png");


   // auto eggs  = new std::shared_ptr<Eggbomb>[100]; 
   // for (int i = 0; i < 100; i++)
   // {
   //     eggs[i] = std::make_unique<Eggbomb>(1, 1);
   // }
   // 
   // for (int i = 0; i < 100; i++)
   // {
   //     delete(eggs[i].get());
   //     //UpdateMgr::RemoveItemImmediately(eggs[i].get());
   //     //delete(eggs[i].get());
   // }
   // //delete[] eggs;
   // //SDL_FreeSurface(sur);
   ///* SDL_FreeSurface(sur1);
   // SDL_FreeSurface(sur2);

   // SDL_FreeSurface(sur3);*/
 


   // //delete sur;
   // return 0;
   
   std::cout << "SDL Object created" << std::endl;
   Time::Time(deltaTime);
   player = new Player(SDL_Obj);

   auto map = std::make_shared<Map>();
   map.get()->BuildMap(0);
   map.get()->player = player;


   //std::cout << "Player created" << std::endl;

   //player->Delta_Time_ref = Delta_Time_ref;
    running = 1;
    //game loop
   // printf(" \n  POINTER TO KEYS: %p\n", SDL_Object::Keys);

    while (running)
    {

         DeltaTimeUpdate();
         
         SDL_Obj->StartFrameUpdate();
       
        UpdateMgr::Update();
        PhysicsMgr::Update();
        PhysicsMgr::CheckCollisions();
        
        SDL_Obj->EndFrameUpdate();

    }
    // server_reply[recv_size] = '\0';
    //closesocket(Server_socket);
    // WSACleanup();
    return 0;
}