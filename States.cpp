#include "States.h"
#include "StateManager.h" // Make sure this is NOT in "States.h" or circular reference.
#include "Engine.h"
#include "TextManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "EventManager.h" 
#include <iostream> 


// Begin State. CTRL+M+H and CTRL+M+U to turn on/off collapsed code.
void GameState::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
void GameState::Enter()
// End State. 

{
	{
		if (EVMA::LastKeyDown() >= 48 && EVMA::LastKeyDown() <= 51)
			m_pEnemy->SetState(EVMA::LastKeyDown() - 48); // 0, 1, 2, 3.
		if (EVMA::MousePressed(1)) // 1: left button, 2: middle, 3: right.
		{
			m_pTarget->GetDstP()->x = (float)(EVMA::GetMousePos().x - 18);
			m_pTarget->GetDstP()->y = (float)(EVMA::GetMousePos().y - 18);
			if (m_pEnemy->GetState() != idle)
				m_pEnemy->Start();
		}
		m_pEnemy->Update();
		for (unsigned i = 0; i < m_obstacles.size(); i++)
		{
			if (COMA::CircleAABBCheck({ m_obstacles[i]->GetDstP()->x + m_obstacles[i]->GetDstP()->w / 2,          m_obstacles[i]->GetDstP()->y + m_obstacles[i]->GetDstP()->h / 2 }, 25, *m_pEnemy->GetDstP()))
				std::cout << "Collision with asteroid!" << std::endl;
		}
	}
}
void GameState::Update()  
{
	if (EVMA::LastKeyDown() >= 48 && EVMA::LastKeyDown() <= 51)
		m_pEnemy->SetState(EVMA::LastKeyDown() - 48); // 0, 1, 2, 3.
	if (EVMA::MousePressed(1)) // 1: left button, 2: middle, 3: right.
	{
		m_pTarget->GetDstP()->x = (float)(EVMA::GetMousePos().x - 18);
		m_pTarget->GetDstP()->y = (float)(EVMA::GetMousePos().y - 18);
		if (m_pEnemy->GetState() != idle)
			m_pEnemy->Start();
	}
	m_pEnemy->Update();
	for (unsigned i = 0; i < m_obstacles.size(); i++)
	{
		if (COMA::CircleAABBCheck({ m_obstacles[i]->GetDstP()->x + m_obstacles[i]->GetDstP()->w / 2,          m_obstacles[i]->GetDstP()->y + m_obstacles[i]->GetDstP()->h / 2 }, 25, *m_pEnemy->GetDstP()))
			std::cout << "Collision with asteroid!" << std::endl;
	}
}

class State {

private: 
	State();

public: 
void Engine::  ();
{
m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
m_running = true; // Everything is okay, start the engine.
cout << "Engine Init success!" << endl;
return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	EVMA::HandleEvents();
}

void Engine::Update()



{
	if (EVMA::LastKeyDown() >= 48 && EVMA::LastKeyDown() <= 51)
		m_pEnemy->SetState(EVMA::LastKeyDown() - 48); // 0, 1, 2, 3.
	if (EVMA::MousePressed(1)) // 1: left button, 2: middle, 3: right.
	{
		m_pTarget->GetDstP()->x = (float)(EVMA::GetMousePos().x - 18);
		m_pTarget->GetDstP()->y = (float)(EVMA::GetMousePos().y - 18);
		if (m_pEnemy->GetState() != idle)
			m_pEnemy->Start();
	}
	m_pEnemy->Update();
	for (unsigned i = 0; i < m_obstacles.size(); i++)
	{
		if (COMA::CircleAABBCheck({ m_obstacles[i]->GetDstP()->x + m_obstacles[i]->GetDstP()->w / 2, m_obstacles[i]->GetDstP()->y + m_obstacles[i]->GetDstP()->h / 2 }, 25, *m_pEnemy->GetDstP()))
			std::cout << "Collision with asteroid!" << std::endl;
	}

}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	// Draw anew.
	m_pTarget->Render();
	m_pEnemy->Render();
	for (unsigned i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->Render();
	SDL_RenderPresent(m_pRenderer);
}