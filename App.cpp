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
#include <fstream>
#include <string>
#include <iostream>

namespace dx = DirectX;

GDIPlusManager gdipm;
//float move = 0.0f;
float rdist;
float vdist;
float ldist;

std::mt19937 rng{ std::random_device{}() };
//std::uniform_real_distribution<float> xdist{ 0.0f, 0.0f };
//std::uniform_real_distribution<float> ydist{ -2.0f, -2.0f };
//std::uniform_real_distribution<float> zdist{ 0.0f, 0.0f };


App::App()
	:
	wnd(800, 600, "Test window")
{
	class LevelLoader
	{
	public:
		bool Load(const char* _level)
		{
			std::string line_;
			bool result;

			std::ifstream file(_level);

			file.open("level.txt", std::ifstream::in);
			if (file.is_open())
			{
				while (getline(file, line_))
				{
					if (line_ == "1")
					{
						
					}
				}
			}
		}

	private:

	};


	player.push_back(std::make_unique<Player>(wnd.Gfx()));
	//spawn.push_back(std::make_unique<Box>(wnd.Gfx(), rng, xdist, ydist, zdist));
	for (int i = 0; i < 3; i++)
	{
		std::uniform_real_distribution<float> xdist{ 0.0f, 10.0f };
		std::uniform_real_distribution<float> ydist{ 0.0f, 0.0f };
		std::uniform_real_distribution<float> zdist{ -3.0f, 6.0f };
		boxes.push_back(std::make_unique<Box>(wnd.Gfx(), rng, xdist, ydist, zdist));
	}



	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

bool grounded = true;
bool jumping = false;
bool falling = false;
float jumpTimer = 0.0f;

void App::DoFrame()
{
	const auto dt = timer.Mark();
	wnd.Gfx().SetCamera(cam.GetMatrix());
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	
	
	
	
	
	for (auto& p : player)
	{

		//rdist = 0.0f;
		if (wnd.kbd.KeyIsPressed('W'))
		{
			rdist = rdist + dt * 3;
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			ldist = ldist + dt * 4;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			rdist = rdist + dt * -3;
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			ldist = ldist + dt * -4;
		}
		if (wnd.kbd.KeyIsPressed((VK_SPACE)) & grounded)
		{
			vdist = vdist + dt * 3;
			jumping = true;
			//falling = true;
		}
		if (p->pos.y > 2.5f || (jumping || falling) & !wnd.kbd.KeyIsPressed((VK_SPACE)))
		{
			vdist = vdist + dt * -4;
			grounded = false;
			falling = true;
		}
		if (p->pos.y < -1.0f )
		{
			falling = false;
			grounded = true;
			jumping = false;
		}
		

		//if (vdist > 0 & !wnd.kbd.KeyIsPressed((VK_SPACE)))
		//{
		//	vdist = vdist + dt * -3;
		//}
		//if (playr.pos.x - 0.5f > box.pos.x - 1.0f) 
		//{
		//	vdist = vdist + dt * 0;
		//}
		for (auto& b : boxes)
		{
			//Collision detection stuff here
			//pushing box forward
			if (p->pos.x + 0.5f > b->pos.x - 1 & p->pos.x - 0.5f < b->pos.x - 1 & p->pos.y - 0.5f < b->pos.y + 0.25f & p->pos.z + 0.5f > b->pos.z - 1.0f & p->pos.z - 0.5f < b->pos.z + 1.0f)
			{
				b->pos.x = b->pos.x +dt * 3;
			}
			//pushing box backwards
			else if (p->pos.x - 0.5f < b->pos.x + 1 & p->pos.x + 0.5f > b->pos.x + 1 & p->pos.y - 0.5f < b->pos.y + 0.25f & p->pos.z + 0.5f > b->pos.z - 1.0f & p->pos.z - 0.5f < b->pos.z + 1.0f)
			{
				b->pos.x = b->pos.x + dt * -3;
			}
			//pushing box right
			else if (p->pos.z + 0.75f > b->pos.z - 1.0f & p->pos.z - 0.75f < b->pos.z - 1 & p->pos.y - 0.5f < b->pos.y + 0.25f & p->pos.x - 0.5f < b->pos.x + 1.0f & p->pos.x + 0.5f > b->pos.x - 1)
			{
				b->pos.z = b->pos.z + dt * 4;
			}
			//pushing box left
			else if (p->pos.z - 0.75f < b->pos.z + 1.0f & p->pos.z + 0.75f > b->pos.z + 1 & p->pos.y - 0.5f < b->pos.y + 0.25f & p->pos.x - 0.5f < b->pos.x + 1.0f & p->pos.x + 0.5f > b->pos.x - 1)
			{
				b->pos.z = b->pos.z + dt * -4;
			}

			//jumping
			if (/*(grounded & p->pos.y > -1.0f)*/ falling & (p->pos.z - 0.75f > b->pos.z + 1.0f || p->pos.z + 0.75f < b->pos.z - 1.0f || p->pos.x - 0.75f > b->pos.x + 1.0f || p->pos.x + 0.75f < b->pos.x - 1.0f))
			{
				falling = false;
			}
			if ((jumping || !grounded || falling) & p->pos.y - 0.75f < b->pos.y + 0.25f & p->pos.x + 0.75 > b->pos.x - 1.0f & p->pos.x - 0.75 < b->pos.x + 1.0f & p->pos.z + 0.75f > b->pos.z -1.0f & p->pos.z - 0.75f < b->pos.z + 1.0f)
			{
				jumping = false;
				grounded = true;
				falling = false;
			}
			//else if ((falling /*& (p->pos.z - 0.75f > b->pos.z + 1.0f || p->pos.z + 0.75f < b->pos.z - 1.0f || p->pos.x - 0.75f > b->pos.x + 1.0f || p->pos.x + 0.75f < b->pos.x - 1.0f))*/))
			//{
			//	vdist = vdist + dt * -3;
			//	//if (p->pos.y - 0.75f <= -2.0f)
			//	//{
			//	//	falling = false;
			//	//	grounded = true;
			//	//	
			//	//}
			//}
			//else if (falling & p->pos.y - 0.75f >= b->pos.y - 1.0f & (p->pos.z - 0.75f > b->pos.z + 1.0f || p->pos.z + 0.75f < b->pos.z - 1.0f || p->pos.x - 0.75f > b->pos.x + 1.0f || p->pos.x + 0.75f < b->pos.x - 1.0f))
			//{
			//	vdist = vdist + dt * -3;
			//	if (p->pos.y - 0.75f <= b->pos.y - 1.0f)
			//	{
			//		falling = false;
			//		grounded = true;
			//
			//	}
			//}
			//if (!grounded & p->pos.y - 0.75f > b->pos.y - 1.0f /*|| p->pos.y - 0.75f < b->pos.y -0.6f & p->pos.x + 0.75 < b->pos.x - 1.0f & p->pos.x - 0.75 > b->pos.x + 1.0f & p->pos.z + 0.75f < b->pos.z -1.0f & p->pos.z - 0.75f > b->pos.z + 1.0f*/)
			//{
			//	falling = true;
			//	vdist = vdist + dt * -3;
			//	
			//	if (p->pos.y - 0.75f < b->pos.y - 0.6f)
			//	{
			//		falling = false;
			//		//jumping = false;
			//		grounded = true;
			//	}
			//}
			//if (p->pos.y - 0.75f > b->pos.y + 0.25f /*& p->pos.x + 0.75 > b->pos.x - 1.0f & p->pos.x - 0.75 < b->pos.x + 1.0f & p->pos.z + 0.75f > b->pos.z - 1.0f & p->pos.z - 0.75f < b->pos.z + 1.0f*/)
			//{
			//	vdist = vdist + dt * -3;
			//	grounded = true;
			//}
			//if (wnd.kbd.KeyIsPressed((VK_SPACE)) & p->pos.z - 0.75f < b->pos.z + 1.0f & p->pos.z + 0.75f > b->pos.z - 1.0f & p->pos.x - 0.75f < b->pos.x + 1.0f & p->pos.x + 0.75f > b->pos.x - 1.0f & grounded)
			//{
			//	vdist = vdist + dt * 3;
			//}
			//if (p->pos.y >= 3)
			//{
			//	//grounded = false;
			//}
			//if (p->pos.y - 0.75f > b->pos.y + 0.5f & !(p->pos.z - 0.75f < b->pos.z + 1.0f & p->pos.z + 0.75f > b->pos.z - 1.0f & p->pos.x - 0.75f < b->pos.x + 1.0f & p->pos.x + 0.75f > b->pos.x - 1.0f))
			//{
			//	//grounded = false;
			//	vdist = vdist + dt * -3;
			//}
		                                        
		b->Draw(wnd.Gfx());
	
		}

		p->Translate(rdist, vdist, ldist);
		p->Draw(wnd.Gfx());
		
	}


	//cam.FollowPlayer(dx::XMLoadFloat3(playr->pos().x));
	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.Translate({ 0.0f, 0.0f, dt / 4.0f });
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Translate({ -dt / 3.0f,0.0f,0.0f });
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.Translate({ 0.0f,0.0f,-dt / 4.0f });
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Translate({ dt / 3.0f,0.0f,0.0f });
	}
	//if (wnd.kbd.KeyIsPressed('R'))
	//{
	//	cam.Translate({ 0.0f,dt,0.0f });
	//}
	//if (wnd.kbd.KeyIsPressed('F'))
	//{
	//	cam.Translate({ 0.0f,-dt,0.0f });
	//}
	//if (wnd.kbd.KeyIsPressed('E'))
	//{
	//	cam.Rotate(dt * 300.0f, 0.0f, 0.0f);
	//}
	//if (wnd.kbd.KeyIsPressed('Q'))
	//{
	//	cam.Rotate(-dt * 300.0f, 0.0f, 0.0f);
	//}

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