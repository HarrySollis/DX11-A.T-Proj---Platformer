#pragma once
#include "DrawableBase.h"

class Player : public DrawableBase<Player>
{
public:
	Player(Graphics& gfx);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void Translate(DirectX::XMFLOAT3 translation) noexcept;
private:
	// positional
	DirectX::XMFLOAT3 pos;
	float r;
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