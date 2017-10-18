#include <stdafx.h>

#include <Game.h>

Game::Game()
{
	GameEngine = nullptr;
	GameInputHandler = new InputHandler();
}

void Game::Update()
{

}

void Game::Draw()
{
	GameEngine->Draw();
}