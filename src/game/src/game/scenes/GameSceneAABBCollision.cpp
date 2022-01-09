#include "GameSceneAABBCollision.h"
#include "GameSceneMain.h"
#include "Globals.h"

namespace
{
}

namespace game
{
	struct GameSceneAABBCollision::Pimpl
	{
		SDL_Rect r1;
		SDL_Rect r2;
		std::unique_ptr<rcgf::Texture> texNoCollision;
		std::unique_ptr<rcgf::Texture> texCollision;
		bool collisionFlag;
		
		Pimpl() 
			: r1{100, 100, 100, 100}
			, r2{220, 220, 100, 100}
			, texNoCollision{std::make_unique<rcgf::Texture>(global::instance.getFont(), "No Collision")}
			, texCollision{ std::make_unique<rcgf::Texture>(global::instance.getFont(), "Collision Detected") }
			, collisionFlag{false}
		{
		}
	};

	GameSceneAABBCollision::GameSceneAABBCollision()
		: m_impl{ std::make_unique<Pimpl>() }
	{}

	void GameSceneAABBCollision::update()
	{
		// check for collision
		SDL_Rect* r1 = &m_impl->r1;
		SDL_Rect* r2 = &m_impl->r2;

		if (r1->x + r1->w < r2->x // rect 1 on the left
			|| r2->x + r2->w < r1->x  // rect 1 on the right
			|| r2->y + r2->h < r1->y  //
			|| r1->y + r1->h < r2->y  // 
			)
			m_impl->collisionFlag = false;
		else
			m_impl->collisionFlag = true;
	}

	void GameSceneAABBCollision::render()
	{
		SDL_SetRenderDrawColor(global::instance.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(global::instance.getRenderer(),
			&m_impl->r1);
		SDL_RenderDrawRect(global::instance.getRenderer(),
			&m_impl->r2);

		if ( m_impl->collisionFlag )
			m_impl->texCollision->render(1000, 600);
		else
			m_impl->texNoCollision->render(1000, 600);
	}

	void GameSceneAABBCollision::keyDown(SDL_Keycode keycode)
	{
		switch (keycode)
		{
		case SDLK_0:
		case SDLK_KP_0:
			printf("switching to game state main\n"); 
			pushPendingState(std::make_unique<GameSceneMain>());
			break;
		case SDLK_UP:
			m_impl->r1.y -= 1;
			break;
		case SDLK_DOWN:
			m_impl->r1.y += 1;
			break;
		case SDLK_RIGHT:
			m_impl->r1.x += 1;
			break;
		case SDLK_LEFT:
			m_impl->r1.x -= 1;
			break;

		}

	}

	void GameSceneAABBCollision::keyUp(SDL_Keycode)
	{

	}
}
