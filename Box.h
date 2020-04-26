#pragma once
#include "DrawableBase.h"

class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& xdist,
		std::uniform_real_distribution<float>& ydist,
		std::uniform_real_distribution<float>& zdist);
	void Update(float dt) noexcept override;
	void Translate(float xdist, float ydist, float zdist);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	float XVectorTransform;
	float YVectorTransform;
	float ZVectorTransform;

private:
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
	// model transform
	DirectX::XMFLOAT3X3 mt;
};