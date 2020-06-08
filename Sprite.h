#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"

class Sprite // Inline class.
{
public: // Inherited and public.
	Sprite(SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t)
		:m_src(s), m_dst(d), m_pRend(r), m_pText(t), m_angle(0.0) {}
	virtual void Render() {	SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE); }
	SDL_Rect* GetSrcP() { return &m_src; }
	SDL_FRect* GetDstP() { return &m_dst; }
	double& GetAngle() { return m_angle; }
	void SetAngle(double a) { m_angle = a; }
protected: // Private BUT inherited.
	double m_angle;
	SDL_Rect m_src;
	SDL_FRect m_dst;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
private: // Private NOT inherited.
};

class AnimatedSprite : public Sprite// Also inline.
{
public:
	AnimatedSprite(SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t, int ss, int ns, int nf)
		:Sprite(s, d, r, t), m_sprite(ss), m_spriteMax(ns), m_frameMax(nf) {}
	void Animate()
	{
		m_frame++;
		if (m_frame == m_frameMax)
		{
			m_frame = 0;
			if (++m_sprite == m_spriteMax)
				m_sprite = 0;
		}
	}
protected:
	int m_sprite,		// Which sprite to start on for animation.
		m_spriteMax,	// How many sprites total.
		m_frame = 0,	// Frame counter.
		m_frameMax;		// Number of frames per sprite.
};

#endif