#pragma once
#include "Window.h"
#include "Timer.h"
#include "Camera.h"
#include "Player.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;


	//Player play;
	Camera cam;
	//std::vector<std::unique_ptr<class Drawable>> drawables;
	//static constexpr size_t nDrawables = 2;

	std::vector<std::unique_ptr<class Player>> player;
	//static constexpr size_t nPlayer = 1;

	std::vector<std::unique_ptr<class Box>> boxes;
	std::vector<std::unique_ptr<class TexturedCube>> spawn;
};