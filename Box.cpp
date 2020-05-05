#include "Box.h"
#include "BindableBase.h"
////#include "GraphicsThrowMacros.h"
#include "Cube.h"

namespace dx = DirectX;

Box::Box(Graphics& gfx,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& xdist,
	std::uniform_real_distribution<float>& ydist,
	std::uniform_real_distribution<float>& zdist)
	:
	pos{ (xdist(rng)) ,
	(ydist(rng)),
	(zdist(rng)) }
{
	float BoxBoundingSphere = 0.0f;
	std::vector<DirectX::XMFLOAT3> BoundingBoxVertPosArray;
	std::vector<DWORD> BoundingBoxVertIndexArray;
	DirectX::XMVECTOR boxCentreOffset;

	

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};
		const auto model = Cube::Make<Vertex>();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"ColorIndexVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorIndexPS.cso"));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		struct PixelShaderConstants
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[8];
		};
		const PixelShaderConstants cb2 =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};
		AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling( XVectorScale, YVectorScale, ZVectorScale )
	);
}

//void CreateBoundingVolumes(std::vector<dx::XMFLOAT3> & vertPosArray,
//	std::vector<dx::XMFLOAT3>& boundingBoxVerts,
//	std::vector<DWORD>& boundingBoxIndex,
//	float& boundingSphere,
//	dx::XMVECTOR& objectCenterOffset)
//{
//
//}
void Box::Update(float dt) noexcept
{
	
}


void Box::Translate(float xdist, float ydist, float zdist)
{
	pos.x = xdist;
	pos.y = ydist;
	pos.z = zdist;
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
	 dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		dx::XMMatrixTranslation(pos.x, pos.y, pos.z) *
		dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
	//dx::XMMatrixTranslation( 0.0f,0.0f,20.0f );
}
