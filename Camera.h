#pragma once
#include "Graphics.h"

class Camera
{
public:

	Camera() noexcept;
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void Reset() noexcept;
	void Rotate(float dx, float dy, float dz) noexcept;
	void Translate(DirectX::XMFLOAT3 translation) noexcept;
	void FollowPlayer(DirectX::XMVECTOR player_pos);

	float xDist;
	float yDist;
	float zDist;
	DirectX::XMFLOAT3 position;
	DirectX::XMMATRIX m_viewMatrix;

	DirectX::XMFLOAT3 rot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
private:
	float r = 20.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	DirectX::XMFLOAT3 pos;
	//float pitch;
	//float yaw;
	//float roll;
	static constexpr float travelSpeed = 12.0f;
	static constexpr float rotationSpeed = 0.004f;
};
