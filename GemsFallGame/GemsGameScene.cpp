#include "GemsGameScene.hpp"

#include "GemsGrid.hpp"

GemsGameScene::GemsGameScene(const std::shared_ptr<EventManager>& eventManager, const std::shared_ptr<RenderManager>& renderManager) : Scene(eventManager, renderManager)
{
  gemsGrid = std::make_shared<GemsGrid>(*this, 8, 8, 5, 5);
  AddUpdatable(std::static_pointer_cast<Updatable, GemsGrid>(gemsGrid));
}
