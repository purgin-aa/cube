struct VS_INPUT
{
	float4 Pos : POSITION;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
};

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
}

VS_OUTPUT main( VS_INPUT input )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul( input.Pos, World );
	output.Pos = mul( output.Pos, View );
	output.Pos = mul( output.Pos, Projection );
	return output;
}