#include "Player.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "Surface.h"
#include "Texture.h"

namespace dx = DirectX;

Player::Player(Graphics& gfx)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			struct
			{
				float u;
				float v;
			} tex;
		};
		const auto model = Cube::MakeSkinned<Vertex>();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		AddStaticBind(std::make_unique<Texture>(gfx, Surface::FromFile("Images\\PlayerHead.png")));

		auto pvs = std::make_unique<VertexShader>(gfx, L"TextureVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"TexturePS.cso"));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

void Player::Update(float dt) noexcept
{

}

void Player::Translate(float rdist, float vdist, float ldist)
{
	l = ldist;
	v = vdist;
	r = rdist;
}

DirectX::XMMATRIX Player::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		dx::XMMatrixTranslation(r, v, 0.0f) *
		dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
	//dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}



//void Player::Translate(float x, float y, float z) noexcept
//{
//	dx::XMMATRIX t = dx::XMLoadFloat4x4(&_translate);
//	dx::XMStoreFloat4x4(&_translate, dx::XMMatrixTranslation(x, y, z) * t);
//}

//void Player::Translate(DirectX::XMFLOAT3 translation) noexcept
//{
//	dx::XMStoreFloat3(&translation, dx::XMVector3Transform(
//		dx::XMLoadFloat3(&translation),
//		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) *
//		dx::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
//	));
//	pos = {
//		pos.x + translation.x,
//		pos.y + translation.y,
//		pos.z + translation.z
//	};
//}
