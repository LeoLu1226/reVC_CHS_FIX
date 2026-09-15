#pragma once

class CCutsceneObject;
class CXboxHands {
public:
	static void Init();
	static void Shutdown();
	static void Request(int slot, const char *name);
	static void PreRender(CCutsceneObject *object);
	static void Render(CCutsceneObject *object);
};
