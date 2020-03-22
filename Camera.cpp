#include "Camera.h"
#include "ObjMath.h"

namespace dx = DirectX;

Camera::Camera() noexcept
{
	Reset();
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	//const auto pos = dx::XMVector3Transform(
	//	dx::XMVectorSet(0.0f, 0.0f, -r, 0.0f),
	//	dx::XMMatrixRotationRollPitchYaw(phi, -theta, 0.0f)
	//);
	//return dx::XMMatrixLookAtLH(
	//	pos, dx::XMVectorZero(),
	//	dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	//) * dx::XMMatrixRotationRollPitchYaw(
	//	pitch, -yaw, roll
	//);

	return dx::XMMatrixTranslation(-pos.x, -pos.y, -pos.z) *
		dx::XMMatrixRotationRollPitchYaw(-pitch, -yaw, 0.0f);
}

void Camera::Reset() noexcept
{
	pos = { 0.0f, 7.5f, -18.0f };
	pitch = 0.0f;
	yaw = 0.0f;
}

void Camera::Rotate(float dx, float dy) noexcept
{
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