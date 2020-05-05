#pragma once
#include "DrawableBase.h"

class TexturedCube : public DrawableBase<TexturedCube>
{
public:
	TexturedCube(Graphics& gfx);
		
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void Translate(float xdist, float ydist, float zdist);
	float X = 0.0f;
	float Y = -1.5f;
	float Z = 0.0f;

	float XVectorScale = 3.0f;
	float YVectorScale = .5f;
	float ZVectorScale = 3.0f;
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