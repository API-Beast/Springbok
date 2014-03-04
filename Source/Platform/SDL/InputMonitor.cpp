#include "../InputMonitor.h"
#include "../GameSurface.h"
#include "../InputDevice.h"
#include <SDL/SDL.h>

struct SDLMouse : public InputDevice
{
	virtual const char* getIdentifier() const { return "Mouse"; };
	virtual bool isMouse() const { return true; };
	
	virtual int numberOfButtons() const { return 3; }; // Hm. It's 2014.
	virtual int numberOfCursors() const { return 1; };
	
	virtual bool getButtonState(int index) const 
	{
		return SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(index);
	};
	
	virtual bool anyButtonPressed() const
	{
		Uint8 state = SDL_GetMouseState(NULL,NULL);
		return state&SDL_BUTTON(1) || state&SDL_BUTTON(2) || state&SDL_BUTTON(3);
	};
	
	virtual Vec2F getCursorPosition(int index) const 
	{
		int x,y;
		SDL_GetMouseState(&x,&y);
		return Vec2F(x, y);
	};
};

struct SDLKeyboard : public InputDevice
{
	virtual const char* getIdentifier() const { return "Keyboard"; };
	virtual bool isKeyboard() const { return true; };
		
	virtual int numberOfButtons() const { int out; SDL_GetKeyboardState(&out); return out; };
	virtual bool getButtonState(int index) const 
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		return state[index];
	};
	virtual bool anyButtonPressed() const
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		for (int i = 1; i < 100; ++i)
			if(state[i])
				return true;
		return false;
	};
};

struct InputMonitorData
{
	SDLKeyboard KeyboardDevice;
	SDLMouse MouseDevice;
	std::vector<InputDevice*> Devices;
	std::vector<ButtonPressEvent> Events;
};

namespace
{
void keyCallback(InputMonitorData* d, int key, int scancode, bool released, int mods)
{
	ButtonPressEvent event;
	event.Type = Keyboard;
	event.Button = key;
	event.From = &(d->KeyboardDevice);
	event.Released = released;
	d->Events.push_back(event);
};

void mouseButtonCallback(InputMonitorData* d, int button, bool released, int mods)
{
	ButtonPressEvent event;
	event.Type = Mouse;
	event.Button = button;
	event.From = &(d->MouseDevice);
	event.Released = released;
	d->Events.push_back(event);
};

}

InputMonitor::InputMonitor(GameSurface* surface)
{
	d = new InputMonitorData;
	d->Devices = {&(d->KeyboardDevice), &(d->MouseDevice)};
};

std::vector< InputDevice* > InputMonitor::getDevices() const
{
	return d->Devices;
}

InputDevice* InputMonitor::getPrimaryPointerDevice() const
{
	return &(d->MouseDevice);
}

InputMonitor::~InputMonitor()
{
	delete d;
};

std::vector<ButtonPressEvent> InputMonitor::poll()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				keyCallback(d,event.key.keysym.sym,event.key.keysym.scancode,false,0);
				break;
			case SDL_KEYUP:
				keyCallback(d,event.key.keysym.sym,event.key.keysym.scancode,true,0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtonCallback(d, event.button.button,false,0);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtonCallback(d, event.button.button,true,0);
				break;
		}
	}
	std::vector<ButtonPressEvent> retVal;
	retVal.swap(d->Events);
	return retVal;
};
