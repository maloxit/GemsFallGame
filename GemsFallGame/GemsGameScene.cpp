#include "GemsGameScene.hpp"

GemsGameScene::GemsGameScene(std::shared_ptr<EventManager>& eventManager, std::shared_ptr<RenderManager>& renderManager) : Scene(eventManager, renderManager)
{
  auto gemsGrid = std::make_shared<GemsGrid>(*this, 10, 10);
  AddGameObject(std::static_pointer_cast<GameObject, GemsGrid>(gemsGrid));
}
