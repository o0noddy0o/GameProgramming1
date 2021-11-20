//グローバル

Texture2D g_texDecal: register(t0);//テクスチャーは レジスターt(n)
SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)

cbuffer global
{
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_vDiffuse;//ディフューズ色
};

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS( float4 Pos : POSITION ,float2 Tex : TEXCOORD )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos,g_mWVP);
    output.Tex = Tex;

    return output;
}

//
//ピクセルシェーダー
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	float4 pix = g_texDecal.Sample(g_samLinear, input.Tex);
	pix.r = pix.r + g_vDiffuse.r;
	pix.g = pix.g + g_vDiffuse.g;
	pix.b = pix.b + g_vDiffuse.b;

	return pix;
}

//テクニックは不要。　どのシェーダーを使うかアプリ側で指定するので。
