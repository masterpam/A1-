#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite.h"
#include <SDL.h>

// Button will be an example of the command design pattern.
class Button : public Sprite
{
public:
	int Update();
	void Render();
protected: // Private but inherited!
	Button(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t);
	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	bool MouseCollision();
	virtual void Execute() = 0; // Pure virtual method, meaning Button is now an abstract class (interface)!
};

class StartButton : public Button
{
protected:
	StartButton(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t) : Button(src, dst, r, t) {}
	void Execute();
};

class QuitButton : public Button
{
protected:
	QuitButton(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t) : Button(src, dst, r, t) {}
	void Execute();
};

// List button subclasses here...

#endif