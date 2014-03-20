// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "InputMonitor.h"

class InputDevice;
class InputMonitor;

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
	bool isPressed(InputMonitor* monitor);
};

constexpr ButtonSpec::ButtonSpec(ButtonType type, int button) : Type(type), Button(button){};
template<typename... Additional>
constexpr ButtonSpec::ButtonSpec(ButtonType type, int button, ButtonType typeB, int buttonB, Additional ...a)  : Type(type), Button(button), Alternative(new ButtonSpec(typeB, buttonB, a...)){};