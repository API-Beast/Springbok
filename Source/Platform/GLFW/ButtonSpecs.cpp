// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "../ButtonPressEvent.h"
#include "../InputDevice.h"
#include <GLFW/glfw3.h>

namespace Buttons
{
	ButtonSpec Up   (Keyboard, GLFW_KEY_UP,    Keyboard, GLFW_KEY_W);
	ButtonSpec Down (Keyboard, GLFW_KEY_DOWN,  Keyboard, GLFW_KEY_S);
	ButtonSpec Left (Keyboard, GLFW_KEY_LEFT,  Keyboard, GLFW_KEY_A);
	ButtonSpec Right(Keyboard, GLFW_KEY_RIGHT, Keyboard, GLFW_KEY_D);
	
	ButtonSpec Confirm(Keyboard, GLFW_KEY_SPACE, Keyboard, GLFW_KEY_X, Keyboard, GLFW_KEY_Q, Keyboard, GLFW_KEY_ENTER);
	ButtonSpec Abort  (Keyboard, GLFW_KEY_E, Keyboard, GLFW_KEY_C);
	
	ButtonSpec ActionA(Keyboard, GLFW_KEY_X, Keyboard, GLFW_KEY_E);
	ButtonSpec ActionB(Keyboard, GLFW_KEY_C, Keyboard, GLFW_KEY_Q);
	ButtonSpec ActionC(Keyboard, GLFW_KEY_V);
	ButtonSpec ActionD(Keyboard, GLFW_KEY_B);
	
	ButtonSpec Start(Keyboard, GLFW_KEY_ESCAPE);
	
	ButtonSpec Space (Keyboard, GLFW_KEY_SPACE);
	ButtonSpec Escape(Keyboard, GLFW_KEY_ESCAPE);
	ButtonSpec Enter (Keyboard, GLFW_KEY_ENTER);
	
	ButtonSpec LeftMouseButton  (Mouse, GLFW_MOUSE_BUTTON_LEFT);
	ButtonSpec RightMouseButton (Mouse, GLFW_MOUSE_BUTTON_RIGHT);
	ButtonSpec MiddleMouseButton(Mouse, GLFW_MOUSE_BUTTON_MIDDLE);
	
	ButtonSpec F1 (Keyboard, GLFW_KEY_F1);
	ButtonSpec F2 (Keyboard, GLFW_KEY_F2);
	ButtonSpec F3 (Keyboard, GLFW_KEY_F3);
	ButtonSpec F4 (Keyboard, GLFW_KEY_F4);
	ButtonSpec F5 (Keyboard, GLFW_KEY_F5);
	ButtonSpec F6 (Keyboard, GLFW_KEY_F6);
	ButtonSpec F7 (Keyboard, GLFW_KEY_F7);
	ButtonSpec F8 (Keyboard, GLFW_KEY_F8);
	ButtonSpec F9 (Keyboard, GLFW_KEY_F9);
	ButtonSpec F10(Keyboard, GLFW_KEY_F10);
	ButtonSpec F11(Keyboard, GLFW_KEY_F11);
	ButtonSpec F12(Keyboard, GLFW_KEY_F12);
	ButtonSpec F13(Keyboard, GLFW_KEY_F13);
	ButtonSpec F14(Keyboard, GLFW_KEY_F14);
	ButtonSpec F15(Keyboard, GLFW_KEY_F15);
}
