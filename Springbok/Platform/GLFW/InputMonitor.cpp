#include "../InputMonitor.h"
#include "../GameSurface.h"
#include "../InputDevice.h"
#include <GLFW/glfw3.h>
#include <Springbok/Foundation/Vec3.h>
#include <Springbok/Utils/Functions.h>

namespace
{
#include "../Common/KeyNames.h"
};

#include "WindowUserData.h"

struct GLFWMouse : public InputDevice
{
	GLFWwindow* mWindow;
	GameSurface* mSurface;
	Vec2F mScrollWheel;
	
	virtual const char* id() const { return "Mouse"; };
	virtual bool isMouse() const { return true; };
	
	virtual int numberOfKeys() const { return GLFW_MOUSE_BUTTON_LAST; };
	virtual int numberOfCursors() const { return 1; };
	
	virtual Vec2F cursorPosition(int index = 0) const 
	{
		double x, y;
		glfwGetCursorPos(mWindow, &x, &y);
		return Vec2F(x, y) + mSurface->topLeft();
	};
	virtual Vec2F scrollWheelState(int index = 0) const
	{
		return mScrollWheel;
	};
	virtual void setScrollWheelState(Vec2F value, int index = 0)
	{
		mScrollWheel = value;
	};
};

struct GLFWKeyboard : public InputDevice
{
	GLFWwindow* mWindow;
	
	virtual const char* id() const { return "Keyboard"; };
	virtual bool isKeyboard() const { return true; };
		
	virtual int numberOfKeys() const { return GLFW_KEY_LAST; };
	virtual std::string buttonName(int index) const
	{
		return KeyCodeToKeyName(index);
	};
};

struct InputMonitorData
{
	GLFWwindow* Window;
	GameSurface* Surface;
	GLFWKeyboard KeyboardDevice;
	GLFWMouse MouseDevice;
	std::vector<InputDevice*> Devices;
	std::vector<ButtonPressEvent> Events;
};

namespace
{
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputMonitorData* d = ((WindowUserData*)glfwGetWindowUserPointer(window))->imd;
	
	if(action == GLFW_RELEASE)
	{
		d->KeyboardDevice.registerKeyRelease(key);
		return;
	}
	else if(action == GLFW_REPEAT) return;
	else if(action == GLFW_PRESS)
	{
		ButtonPressEvent event;
		event.Type = Keyboard;
		event.Button = key;
		event.From = &(d->KeyboardDevice);
		d->Events.push_back(event);
		d->KeyboardDevice.registerKeyPress(key);
	}
};

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputMonitorData* d = ((WindowUserData*)glfwGetWindowUserPointer(window))->imd;
	if(action == GLFW_RELEASE)
	{
		d->MouseDevice.registerKeyRelease(button);
		return;
	}
	else if(action == GLFW_REPEAT) return;
	else if(action == GLFW_PRESS)
	{
		ButtonPressEvent event;
		event.Type = Mouse;
		event.Button = button;
		event.From = &(d->MouseDevice);
		d->Events.push_back(event);
		d->MouseDevice.registerKeyPress(button);
	}
};

void scrollCallback(GLFWwindow* window, double scrollX, double scrollY)
{
	InputMonitorData* d = ((WindowUserData*)glfwGetWindowUserPointer(window))->imd;
	d->MouseDevice.mScrollWheel[0] += scrollX;
	d->MouseDevice.mScrollWheel[1] += scrollY;
};

}

InputMonitor::InputMonitor(GameSurface* surface)
{
	d = new InputMonitorData;
	GLFWwindow* window = (GLFWwindow*)surface->getWindowHandle();
	d->Surface = surface;
	d->Window = window;
	d->Devices = {&(d->KeyboardDevice), &(d->MouseDevice)};
	d->KeyboardDevice.mWindow = window;
	d->MouseDevice.mWindow = window;
	d->MouseDevice.mSurface = surface;
	glfwSetKeyCallback(window, &keyCallback);
	glfwSetMouseButtonCallback(window, &mouseButtonCallback);
	glfwSetScrollCallback(window, &scrollCallback);
	WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
	userData->imd = d;
};

std::vector< InputDevice* > InputMonitor::getDevices() const
{
	return d->Devices;
}

InputMonitor::~InputMonitor()
{
	delete d;
};

std::vector<ButtonPressEvent> InputMonitor::poll()
{
	glfwPollEvents();
	{
		std::vector<ButtonPressEvent> retVal;
		retVal.swap(d->Events);
		return retVal;
	}
};

InputDevice* InputMonitor::mouse() const
{
	return &d->MouseDevice;
}

InputDevice* InputMonitor::keyboard() const
{
	return &d->KeyboardDevice;
}

bool InputMonitor::isKeyPressed(int key)
{
	return d->KeyboardDevice.isKeyPressed(key);
}

bool InputMonitor::isMouseButtonPressed(int button)
{
	return d->MouseDevice.isKeyPressed(button);
}

bool InputMonitor::isKeyPressed(const std::string& key)
{
	for(InputDevice* device : getDevices())
		if(device->isKeyPressed(key))
			return true;

	return false;
}

Vec2F InputMonitor::mousePosition()
{
	return d->MouseDevice.cursorPosition();
}

float InputMonitor::scrollState()
{
	return d->MouseDevice.scrollWheelState()[1];
}

void InputMonitor::setScrollState(float state)
{
	d->MouseDevice.setScrollWheelState(state);
}