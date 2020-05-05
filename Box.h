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

	DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(XVectorTransform, YVectorTransform, ZVectorTransform);

	
	float XVectorScale=2.0f;
	float YVectorScale=0.5f;
	float ZVectorScale=2.5f;

	float BoxminXBound;
	float BoxmaxXBound;
	float BoxminYBound;
	float BoxmaxYBound;

	void GetPositionX(float minXBound, float maxXBound);
	void GetPositionY(float minYBound, float maxYBound);
	void GetPositionZ(float minZBound, float maxZBound);

	//float BoxBoundingSphere = 0.0f;
	//std::vector<DirectX::XMFLOAT3> BoundingBoxVertPosArray;
	//std::vector<DWORD> BoundingBoxVertIndexArray;
	//DirectX::XMVECTOR boxCentreOffset;
	//
	//void CreateBoundingVolumes(std::vector<dx::XMFLOAT3>& vertPosArray,
	//	std::vector<dx::XMFLOAT3>& boundingBoxVerts,
	//	std::vector<DWORD>& boundingBoxIndex,
	//	float& boundingSphere,
	//	dx::XMVECTOR& objectCenterOffset);

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