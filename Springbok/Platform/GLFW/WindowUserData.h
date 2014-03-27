#include <GLFW/glfw3.h>

struct InputMonitorData;
struct GameSurfaceData;

struct WindowUserData
{
	InputMonitorData* imd = nullptr;
	GameSurfaceData*  gsd = nullptr;
};