#include "GemSelector.hpp"

#include "GemsGrid.hpp"

void GemSelector::HandleMouseMonion(const SDL_Event& event)
{
	Vector2f point(event.motion.x, event.motion.y);
	int pointRow;
	int pointColumn;
	grid.PositionToCell(point, pointRow, pointColumn);
	if ((pointRow != row || pointColumn != column) && grid.IsCorrectCell(pointRow, pointColumn))
	{
		switch (grid.GetState())
		{
		case GemsGrid::GameState::WAITING_SECOND_SELECT:
			if (!grid.IsNeighbors(pointRow, pointColumn, selectRow, selectColumn))
			{
				break;
			}
		case GemsGrid::GameState::WAITING_FIRST_SELECT:
			row = pointRow;
			column = pointColumn;
			grid.CellToPosition(targetPosition, pointRow, pointColumn);
			enabled = true;
			break;
		default:
			break;
		}
	}
}

void GemSelector::HandleMouseClick(const SDL_Event& event)
{
	Vector2f point(event.button.x, event.button.y);
	int pointRow;
	int pointColumn;
	grid.PositionToCell(point, pointRow, pointColumn);
	if (grid.IsCorrectCell(pointRow, pointColumn))
	{
		switch (grid.GetState())
		{
		case GemsGrid::GameState::WAITING_FIRST_SELECT:
			selectRow = pointRow;
			selectColumn = pointColumn;
			grid.CellToPosition(targetPosition, pointRow, pointColumn);
			grid.Select(pointRow, pointColumn);
			break;
		case GemsGrid::GameState::WAITING_SECOND_SELECT:
			if (grid.IsNeighbors(pointRow, pointColumn, selectRow, selectColumn))
			{
				grid.CellToPosition(targetPosition, pointRow, pointColumn);
				grid.Select(pointRow, pointColumn);
			}
			break;
		default:
			break;
		}
	}
}


GemSelector::GemSelector(const std::shared_ptr<RenderManager>& renderManager, GemsGrid& grid, const Transform& transform) : Updatable(false), EventListener(true), grid(grid), transform(transform)
{
	moveSpeed = 2000.f;
	visuals = std::make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::TOP, 6);
	renderManager->AddRenderObject(visuals);
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.05f ), Vector2f( 0.05f,0.9f));
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.05f ), Vector2f( 0.9f,0.05f));
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.9f,0.05f ), Vector2f( 0.05f,0.9f));
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.9f ), Vector2f( 0.9f,0.05f));
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::LINE, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.05f ), Vector2f( 0.95f,0.95f));
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::LINE, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.95f ), Vector2f( 0.95f,0.05f));
}

void GemSelector::Update(float deltaTime)
{
	float step = deltaTime * moveSpeed;
	if (transform.MoveLin(targetPosition, step))
	{
		enabled = false;
	}
}



void GemSelector::HandleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EventType::SDL_MOUSEMOTION)
	{
		HandleMouseMonion(event);
	}
	else if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
	{
		HandleMouseClick(event);
	}
}
