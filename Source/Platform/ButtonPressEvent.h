// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

class InputDevice;

enum ButtonType
{
	Any=0,
	Mouse,
	Keyboard,
	Gamepad,
	Misc
};

struct ButtonPressEvent
{
	InputDevice* From;
	ButtonType Type;
	int Button;
	bool Released;
};

struct ButtonSpec
{
	InputDevice* From = nullptr; //!< \c nullptr is any.
	ButtonType Type = Any;
	int Button = -1; //!< \c -1 is any.
	int ComboButton = -1; //!< Button that needs to be pressed in Addition to \c Button. -1 is none.
	ButtonSpec* Alternative = nullptr; //!< Alternative Button Specification. You can chain ButtonSpec's this way, and if any alternative matches \c this will too.
public:
	constexpr ButtonSpec() = default;
	constexpr ButtonSpec(ButtonType type, int button);
	template<typename... Additional>
	constexpr ButtonSpec(ButtonType type, int button, ButtonType typeB, int buttonB, Additional ...a);
	~ButtonSpec();
public:
	bool matches(const ButtonPressEvent& event);
};

constexpr ButtonSpec::ButtonSpec(ButtonType type, int button) : Type(type), Button(button){};
template<typename... Additional>
constexpr ButtonSpec::ButtonSpec(ButtonType type, int button, ButtonType typeB, int buttonB, Additional ...a)  : Type(type), Button(button), Alternative(new ButtonSpec(typeB, buttonB, a...)){};

namespace Buttons
{
	extern ButtonSpec Up;    //!< \c W or \c Up on Keyboards.   For Gamepads check the Axes.
	extern ButtonSpec Down;  //!< \c S or \c Down on Keyboards. For Gamepads check the Axes.
	extern ButtonSpec Left;  //!< \c A or \c Left on Keyboards. For Gamepads check the Axes.
	extern ButtonSpec Right; //!< \c D or \c Down on Keyboards. For Gamepads check the Axes.
	
	extern ButtonSpec Confirm; //!< \c Space, \c X, \c Q or \c Enter on Keyboards. First Button on Gamepads.
	extern ButtonSpec Abort;   //!< \c C or \c E on Keyboards. Second Button on Gamepads.
	
	extern ButtonSpec ActionA; //!< \c X or \c Q on Keyboards. First Button on Gamepads.
	extern ButtonSpec ActionB; //!< \c C or \c E on Keyboards. Second Button on Gamepads.
	extern ButtonSpec ActionC; //!< \c V on Keyboards. Third Button on Gamepads.
	extern ButtonSpec ActionD; //!< \c B on Keyboards. Fourth Button on Gamepads.
	
	extern ButtonSpec Start; //!< \c Escape on Keyboards. \c Start Button on Gamepads.
	
	extern ButtonSpec Space;  //!< The \c Space Key on Keyboards.
	extern ButtonSpec Escape; //!< The \c Escape Key on Keyboards.
	extern ButtonSpec Enter;  //!< The \c Enter Key on Keyboards.
	
	extern ButtonSpec LeftMouseButton;
	extern ButtonSpec RightMouseButton;
	extern ButtonSpec MiddleMouseButton;
	
	//! Function Keys
	//@{
	extern ButtonSpec F1;
	extern ButtonSpec F2;
	extern ButtonSpec F3;
	extern ButtonSpec F4;
	extern ButtonSpec F5;
	extern ButtonSpec F6;
	extern ButtonSpec F7;
	extern ButtonSpec F8;
	extern ButtonSpec F9;
	extern ButtonSpec F10;
	extern ButtonSpec F11;
	extern ButtonSpec F12;
	extern ButtonSpec F13;
	extern ButtonSpec F14;
	extern ButtonSpec F15;
	//@}
}
