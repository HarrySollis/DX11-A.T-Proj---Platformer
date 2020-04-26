#include "App.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include "TexturedCube.h"
#include "Player.h"
#include <memory>
#include <algorithm>
#include "Sheet.h"
#include "ObjMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"

namespace dx = DirectX;

GDIPlusManager gdipm;
//float move = 0.0f;
float rdist;
float vdist;
float ldist;
App::App()
	:
	wnd(800, 600, "Test window")
{
	std::mt19937 rng{ std::random_device{}() };
	std::uniform_real_distribution<float> xdist{ 2.0f,10.0f };
	std::uniform_real_distribution<float> ydist{ 0.0f,9.0f };
	std::uniform_real_distribution<float> zdist{ 0.0f,0.0f };
	//std::uniform_real<float> rdist{ move };


	player.push_back(std::make_unique<Player>(wnd.Gfx() /*adist, ddist, odist,*/));
	
	for (int i = 0; i < 2; i++)
	{
		boxes.push_back(std::make_unique<Box>(wnd.Gfx(), rng, xdist, ydist, zdist));
	}

	//class Factory
	//{
	//public:
	//	Factory(Graphics& gfx)
	//		:
	//		gfx(gfx)
	//	{}
	//
	//	std::unique_ptr<Drawable> operator()()
	//	{
	//		return std::make_unique<Box>(
	//			gfx, rng, adist, ddist,
	//			odist, rdist
	//			);
	//	}
	//private:
	//	Graphics& gfx;
	//	std::mt19937 rng{ std::random_device{}() };
	//	std::uniform_real_distribution<float> adist{ 0.0f,0.0f };
	//	std::uniform_real_distribution<float> ddist{ 0.0f,0.0f };
	//	std::uniform_real_distribution<float> odist{ 0.0f,0.0f };
	//	std::uniform_real_distribution<float> rdist{ 6.0f,6.0f };
	//};
	//
	//drawables.reserve(nDrawables);
	//std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ wnd.Gfx() });

	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::DoFrame()
{
	const auto dt = timer.Mark();
	wnd.Gfx().SetCamera(cam.GetMatrix());
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);

	for (auto& b : boxes)
	{
		b->Draw(wnd.Gfx());
	}
	for (auto& p : player)
	{
		if (wnd.kbd.KeyIsPressed('A'))
		{
			rdist = rdist + dt * -3;
		}
		if (wnd.kbd.KeyIsPressed((VK_SPACE)))
		{
			vdist = vdist + dt * 3;
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			rdist = rdist + dt * 3;
		}
		//p->GetTransformXM();
		if (vdist > 0 & !wnd.kbd.KeyIsPressed((VK_SPACE)))
		{
			vdist = vdist + dt * -3;
		}
		p->Translate(rdist, vdist, ldist);
		p->Draw(wnd.Gfx());
	}


	//if (wnd.kbd.KeyIsPressed('W'))
	//{
	//	cam.Translate({ 0.0f, 0.0f, dt });
	//}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Translate({ -dt / 2,0.0f,0.0f });
	}
	//if (wnd.kbd.KeyIsPressed('S'))
	//{
	//	cam.Translate({ 0.0f,0.0f,-dt });
	//}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Translate({ dt / 2,0.0f,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		cam.Translate({ 0.0f,dt,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		cam.Translate({ 0.0f,-dt,0.0f });
	}

	wnd.Gfx().EndFrame();
}

App::~App()
{}


int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}