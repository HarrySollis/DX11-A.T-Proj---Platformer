#include "Camera.h"
#include "ObjMath.h"
#include "Player.h"

namespace dx = DirectX;

Camera::Camera() noexcept
{
	//FollowPlayer(dx::XMLoadFloat3(&Player().GetPlayerPos().pos()));
	Reset();
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{

	return dx::XMMatrixTranslation(-pos.x, -pos.y, -pos.z) *
		dx::XMMatrixRotationRollPitchYaw(-pitch, -yaw, roll);
}

void Camera::Reset() noexcept
{
	pos = { -5.0f, 2.5f, 0.0f };
	roll = 0.35f;
	pitch = 0.0f;
	yaw = 1.57f;
}

void Camera::FollowPlayer(dx::XMVECTOR player_pos)
{
	//player_pos = dx::XMLoadFloat3(&Player().GetPlayerPos.pos());
	static float phi = PI / 2;
	float CamX, CamY, CamZ;
	phi = rot.y / 10;
	CamX = xDist * cosf(((3.0f * PI) / 2.0f) * ((rot.x / 3) / 90)) * sinf(phi);
	CamY = yDist * cosf(phi);
	CamZ = zDist * sinf(((3.0f * PI) / 2.0f) * ((rot.x / 3) / 90)) * sinf(phi);
	dx::XMFLOAT3 pos;
	XMStoreFloat3(&pos, player_pos);
	position = dx::XMFLOAT3(pos.x + CamX, pos.y + -CamY, pos.z + CamZ);
	dx::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	m_viewMatrix = dx::XMMatrixLookAtLH(dx::XMLoadFloat3(&position), player_pos, XMLoadFloat3(&up));
}

void Camera::Rotate(float dx, float dy, float dz) noexcept
{
	roll = wrap_angle(roll + dz * rotationSpeed);
	yaw = wrap_angle(yaw + dx * rotationSpeed);
	pitch = std::clamp(pitch + dy * rotationSpeed, -PI / 2.0f, PI / 2.0f);
}

void Camera::Translate(DirectX::XMFLOAT3 translation) noexcept
{
	dx::XMStoreFloat3(&translation, dx::XMVector3Transform(
		dx::XMLoadFloat3(&translation),
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) *
		dx::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
	));
	pos = {
		pos.x + translation.x,
		pos.y + translation.y,
		pos.z + translation.z
	};
}