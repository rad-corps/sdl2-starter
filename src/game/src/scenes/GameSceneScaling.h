#pragma once

#include <string>
#include <array>
#include <memory>
#include "IGameScene.h"
#include "../GameTexture.h"
#include "../GameInclude.h"

namespace game
{
	class GameSceneScaling : public IGameScene
	{
	public:
		GameSceneScaling();
		void update() override;
		void render() override;
		void keyDown(SDL_Keycode) override;
		void keyUp(SDL_Keycode) override;

	private:
		struct Pimpl;
		std::unique_ptr<Pimpl> m_impl;
	};
}