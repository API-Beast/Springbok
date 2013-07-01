#include "../InputMonitor.h"
#include "../GameSurface.h"
#include "../InputDevice.h"
#include <GLFW/glfw3.h>

struct GLFWMouse : public InputDevice
{
	GLFWwindow* mWindow;
	
	virtual const char* getIdentifier() const { return "Mouse"; };
	virtual bool isMouse() const { return true; };
	
	virtual int numberOfButtons() const { return GLFW_MOUSE_BUTTON_LAST; };
	virtual int numberOfCursors() const { return 1; };
	
	virtual bool getButtonState(int index) const 
	{
		return glfwGetMouseButton(mWindow, index);
	};
	
	virtual Vec2F getCursorPosition(int index) const 
	{
		double x,y;
		glfwGetCursorPos(mWindow, &x, &y);
		return Vec2F(x, y);
	};
};

struct GLFWKeyboard : public InputDevice
{
	GLFWwindow* mWindow;
	
	virtual const char* getIdentifier() const { return "Keyboard"; };
	virtual bool isKeyboard() const { return true; };
		
	virtual int numberOfButtons() const { return GLFW_KEY_LAST; };
	virtual bool getButtonState(int index) const 
	{
		return glfwGetKey(mWindow, index);
	};
};

struct InputMonitorData
{
	GLFWwindow* Window;
	GLFWKeyboard KeyboardDevice;
	GLFWMouse MouseDevice;
	std::vector<ButtonPressEvent> Events;
};

namespace
{
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputMonitorData* d = (InputMonitorData*)glfwGetWindowUserPointer(window);
	ButtonPressEvent event;
	event.Type = Keyboard;
	event.Button = key;
	event.From = &(d->KeyboardDevice);
	event.Released = action;
	d->Events.push_back(event);
};

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputMonitorData* d = (InputMonitorData*)glfwGetWindowUserPointer(window);
	ButtonPressEvent event;
	event.Type = Mouse;
	event.Button = button;
	event.From = &(d->MouseDevice);
	event.Released = action;
	d->Events.push_back(event);
};

}

InputMonitor::InputMonitor(GameSurface* surface)
{
	d = new InputMonitorData;
	GLFWwindow* window = (GLFWwindow*)surface->getWindowHandle();
	d->Window = window;
	glfwSetKeyCallback(window, &keyCallback);
	glfwSetMouseButtonCallback(window, &mouseButtonCallback);
	glfwSetWindowUserPointer(window, d);
};

int InputMonitor::numberOfDevices()
{
	return 2;
};

InputDevice* InputMonitor::deviceByIndex(int index)
{
	switch(index)
	{
		case 0:
			return &(d->KeyboardDevice);
		case 1:
			return &(d->MouseDevice);
	}
	return nullptr;
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