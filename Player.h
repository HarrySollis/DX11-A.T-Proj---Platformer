#pragma once
#include "DrawableBase.h"

class Player : public DrawableBase<Player>
{
public:
	Player();
	Player(Graphics& gfx /*std::mt19937& rng,*/
		//std::uniform_real_distribution<float>& adist,
		//std::uniform_real_distribution<float>& ddist,
		//std::uniform_real_distribution<float>& odist,
	/*float &rdist*/);
	void Update(float dt) noexcept override;
	void Translate(float rdist, float vdist, float ldist);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	float l;
	float v;
	float r;
private:
	// positional
	DirectX::XMFLOAT3 pos;

	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	static constexpr float travelSpeed = 12.0f;
	static constexpr float rotationSpeed = 0.004f;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};