#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include <memory>
#include <exception>

#include "Simple2DGameEngine.hpp"
#include "GameManager.hpp"

void Poc()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>(std::make_shared<GameWindow>(800, 800));
  gameManager->Run();
  SDL_Quit();
}

int main(int a, char* v[])
{
  Poc();
#ifdef _DEBUG
  _CrtDumpMemoryLeaks();
#endif // _DEBUG
  return 0;
}
