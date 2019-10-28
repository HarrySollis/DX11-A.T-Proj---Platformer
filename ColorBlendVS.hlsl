cbuffer CBuf
{
	matrix transform;
};

struct VSOut
{
	float4 Colour : Colour;
	float4 pos : SV_Position;
};

VSOut main( float3 pos : Position,float4 Colour : Colour )
{
	VSOut vso;
	vso.pos = mul( float4(pos,1.0f),transform );
	vso.Colour = Colour;
	return vso;
}