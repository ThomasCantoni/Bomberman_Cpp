#pragma once


#include "BombermanCore.h"





//Player OnlinePlayers [2];
Player* player;

SDL_Object* SDL_Obj;
BombermanClientMgr* NM;
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



int main(int argc, char** argv)
{
    
    
    SDL_Obj = new SDL_Object();
    TextureFactory::LoadTexture("materials\\eggsplosion.png");
    TextureFactory::LoadTexture("materials\\EGGOLD.png");
    TextureFactory::LoadTexture("materials\\paperella.png");

    MapManager::Initialize("..\\BombermanCore\\Include\\Maps");

   std::cout << "SDL Object created" << std::endl;
   BombermanTime::BombermanTime(deltaTime);
   


   player = new Player(SDL_Obj);
   
  
   int  running = 1;
  
   
    while (running)
    {

         DeltaTimeUpdate();
         
         SDL_Obj->StartFrameUpdate();
       
        UpdateMgr::Update();
        PhysicsMgr::Update();
        //PhysicsMgr::CheckCollisions();
        BombermanClientMgr::Update();
        SDL_Obj->EndFrameUpdate();

    }
    // server_reply[recv_size] = '\0';
    //closesocket(Server_socket);
     WSACleanup();
    return 0;
}
