#pragma once
#include "SDL.h"
struct BitMapPack
{
	SDL_Texture* texture;
	int width;
	int height;
};

struct EventInfo
{
	int EventType;
	int EventData;
};

enum MyEventTypes
{
	KeyDown,
	KeyUp,
	LeftMouse,
	RightMouse,
	MiddleMouse,
	MouseWheel,
	MouseGesture
};

enum KeyBoardKeys
{
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
	shift,
	ctrl,
	space,
	SIZE_OF_KEYS_ENUM,
};