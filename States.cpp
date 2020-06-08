#include "States.h"
#include "StateManager.h" // Make sure this is NOT in "States.h" or circular reference.
#include "Engine.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include<iostream>

// Begin State. CTRL+M+H and CTRL+M+U to turn on/off collapsed code.
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
void State::Resume() {}
// End State.

void GameState::Enter()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); // Call this before any textures are created.
    TEMA::RegisterTexture("Img/PlayerShip.png", "player");
    TEMA::RegisterTexture("Img/Enemies.png", "enemy");
    m_pTarget = new Sprite({ 594,270,36,36 }, { 36 / 2.0f, 36 / 2.0f, 36.0f, 36.0f }, Engine::Instance().GetRenderer(), TEMA::GetTexture("player"));
    m_pEnemy = new Enemy({ 160,0,40,57 }, { 100.0f, 100.0f, 40.0f, 57.0f }, Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy"), 4, 4, 4, m_pTarget->GetDstP());
    m_obstacles.push_back(new Sprite({ 282, 212, 61, 66 }, { 256, 256, 61, 66 }, Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy")));
    m_obstacles.push_back(new Sprite({ 282, 212, 61, 66 }, { 768, 512, 61, 66 }, Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy")));
    SOMA::Load("Aud/engines.wav", "engine", SOUND_SFX);
    SOMA::SetSoundVolume(32, 0);
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

void GameState::Render()
{
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::Instance().GetRenderer()); // Clear the screen with the draw color.
    // Draw anew.
    m_pTarget->Render();
    m_pEnemy->Render();
    for (unsigned i = 0; i < m_obstacles.size(); i++)
        m_obstacles[i]->Render();
    SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void GameState::Exit()
{
    std::cout << "Cleaning game." << std::endl;
    delete m_pTarget;
    delete m_pEnemy;
    for (unsigned i = 0; i < m_obstacles.size(); i++)
    {
        delete m_obstacles[i];
        m_obstacles[i] = nullptr; // Wrangle your dangle.
    }
    m_obstacles.clear();
    m_obstacles.shrink_to_fit();
}

void MenuState::Enter()
{
}

void MenuState::Update()
{
}

void MenuState::Render()
{
}

void MenuState::Exit()
{
}
