// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "../ButtonPressEvent.h"
#include "../InputDevice.h"

#include <SDL/SDL.h>

namespace Buttons
{
	
	ButtonSpec Up   (Keyboard, SDLK_UP,    Keyboard, SDLK_w);
	ButtonSpec Down (Keyboard, SDLK_DOWN,  Keyboard, SDLK_s);
	ButtonSpec Left (Keyboard, SDLK_LEFT,  Keyboard, SDLK_a);
	ButtonSpec Right(Keyboard, SDLK_RIGHT, Keyboard, SDLK_d);
	
	ButtonSpec Confirm(Keyboard, SDLK_SPACE, Keyboard, SDLK_x, Keyboard, SDLK_q, Keyboard, SDLK_RETURN);
	ButtonSpec Abort  (Keyboard, SDLK_e, Keyboard, SDLK_c);
	
	ButtonSpec ActionA(Keyboard, SDLK_x, Keyboard, SDLK_e);
	ButtonSpec ActionB(Keyboard, SDLK_c, Keyboard, SDLK_q);
	ButtonSpec ActionC(Keyboard, SDLK_v);
	ButtonSpec ActionD(Keyboard, SDLK_b);
	
	ButtonSpec Start(Keyboard, SDLK_ESCAPE);
	
	ButtonSpec Space (Keyboard, SDLK_SPACE);
	ButtonSpec Escape(Keyboard, SDLK_ESCAPE);
	ButtonSpec Enter (Keyboard, SDLK_RETURN);
	
	ButtonSpec LeftMouseButton  (Mouse, SDL_BUTTON_LEFT);
	ButtonSpec RightMouseButton (Mouse, SDL_BUTTON_RIGHT);
	ButtonSpec MiddleMouseButton(Mouse, SDL_BUTTON_MIDDLE);
	
	ButtonSpec F1 (Keyboard, SDLK_F1);
	ButtonSpec F2 (Keyboard, SDLK_F2);
	ButtonSpec F3 (Keyboard, SDLK_F3);
	ButtonSpec F4 (Keyboard, SDLK_F4);
	ButtonSpec F5 (Keyboard, SDLK_F5);
	ButtonSpec F6 (Keyboard, SDLK_F6);
	ButtonSpec F7 (Keyboard, SDLK_F7);
	ButtonSpec F8 (Keyboard, SDLK_F8);
	ButtonSpec F9 (Keyboard, SDLK_F9);
	ButtonSpec F10(Keyboard, SDLK_F10);
	ButtonSpec F11(Keyboard, SDLK_F11);
	ButtonSpec F12(Keyboard, SDLK_F12);
	ButtonSpec F13(Keyboard, SDLK_F13);
	ButtonSpec F14(Keyboard, SDLK_F14);
	ButtonSpec F15(Keyboard, SDLK_F15);
}
