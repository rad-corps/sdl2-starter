#pragma once

#include <string>
#include <array>
#include <memory>
#include "IGameScene.h"
#include "GameTexture.h"
#include "Globals.h"

namespace game
{
	class GameSceneUserInput : public rcgf::IGameScene
	{
	public:
		GameSceneUserInput();
		void update() override;
		void render() override;
		void keyDown(SDL_Keycode) override;
		void keyUp(SDL_Keycode) override;

	private:
		struct Pimpl;
		std::unique_ptr<Pimpl> m_impl;
	};
}