#include "common.hlsl"
Texture2D g_Texture : register(t0); //テクスチャ０番
SamplerState g_SamplerState : register(s0); //サンプラー０番
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal); //ピクセルの法線を正規化
	float light = 0.5 - 0.5 * dot(normal.xyz, Light.Direction.xyz); //光源計算をする
	
	//このピクセルに使われるテクスチャの色を取得
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light; //テクスチャ*明るさ*頂点色
	outDiffuse.a *= In.Diffuse.a; //αに明るさは関係ないので別計算

	//スペキュラー(フォン鏡面反射)
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する

	//光の反射ベクトルを計算
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //正規化する

	float specular = -dot(eyev, refv); //鏡面反射の計算
	specular = saturate(specular); //値をサチュレート

	zspecular = pow(specular, 30); //ここでは３０乗してみる

	outDiffuse.rgb += specular;
}