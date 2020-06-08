#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include <SDL.h>
#include "Button.h"

class State // This is the abstract base class for all specific states.
{
protected:
	State() {}
public:
	virtual void Update() = 0; // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Enter() = 0;  // Virtual keyword means we can override in derived class.
	virtual void Exit() = 0;
	virtual void Resume();
};

class MenuState : public State {
private:
    std::vector<Button*> m_vButtons;
public:
    MenuState() {}
    void Enter();
    void Update();
    void Render();
    void Exit();
};

class GameState : public State {
private:
    Sprite* m_pTarget;
    Enemy* m_pEnemy;
    std::vector<Sprite*> m_obstacles;
public:
    GameState() {}
    void Enter();
    void Update();
    void Render();
    void Exit();
};

#endif