#include "GemSelector.hpp"

GemSelector::GemSelector(Scene& scene, GemsGrid& grid, Vector2f& position, Vector2f& size) : GameObject(scene, false), EventListener(true), grid(grid), transform(position, size)
{
	moveSpeed = 2000.f;
	visuals = std::make_shared<RenderObject>(true, this->transform, RenderLayer::TOP, 6);
	scene.renderManager->AddRenderObject(visuals);
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.05f ), Vector2f( 0.05f,0.9f) });
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.05f ), Vector2f( 0.9f,0.05f) });
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.9f,0.05f ), Vector2f( 0.05f,0.9f) });
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.9f ), Vector2f( 0.9f,0.05f) });
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::LINE, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.05f ), Vector2f( 0.95f,0.95f) });
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::LINE, Vector4uc(242, 244, 243, 255), Vector2f(0.05f,0.95f ), Vector2f( 0.95f,0.05f) });
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
		Vector2f point(event.motion.x , event.motion.y);
		int pointRow;
		int pointColumn;
		grid.PositionToCell(point, pointRow, pointColumn);
		if ((pointRow != row || pointColumn != column) && pointRow < grid.rowsCount && pointColumn < grid.columnsCount && pointRow >= 0 && pointColumn >= 0)
		{
			switch (grid.state)
			{
			case GemsGrid::GameState::WAITING_FIRST_SELECT:
				row = pointRow;
				column = pointColumn;
				grid.CellToPosition(targetPosition, pointRow, pointColumn);
				enabled = true;
				break;
			case GemsGrid::GameState::WAITING_SECOND_SELECT:
				if (grid.IsNeighbors(pointRow, pointColumn, grid.selectRow1, grid.selectColumn1))
				{
					row = pointRow;
					column = pointColumn;
					grid.CellToPosition(targetPosition, pointRow, pointColumn);
					enabled = true;
				}
				break;
			default:
				break;
			}
		}
	}
	else if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
	{
		Vector2f point(event.button.x, event.button.y);
		int pointRow;
		int pointColumn;
		grid.PositionToCell(point, pointRow, pointColumn);
		if (pointRow < grid.rowsCount && pointColumn < grid.columnsCount && pointRow >= 0 && pointColumn >= 0)
		{
			switch (grid.state)
			{
			case GemsGrid::GameState::WAITING_FIRST_SELECT:
				row = pointRow;
				column = pointColumn;
				grid.CellToPosition(targetPosition, pointRow, pointColumn);
				enabled = true;
				grid.Select(pointRow, pointColumn);
				break;
			case GemsGrid::GameState::WAITING_SECOND_SELECT:
				if (grid.IsNeighbors(pointRow, pointColumn, grid.selectRow1, grid.selectColumn1))
				{
					row = pointRow;
					column = pointColumn;
					grid.CellToPosition(targetPosition, pointRow, pointColumn);
					enabled = true;
					grid.Select(pointRow, pointColumn);
				}
				break;
			default:
				break;
			}
		}
	}
}
