
// VertexInput 구조체 정의
struct VertexInput	// VertexShdaer에서 사용할 목적
{
	// VertexType에서 지정한 세멘틱 이름과 번호를 사용해야 한다.
	float4 position : POSITION0;	// 정점의 위치
	float2 uv		: TEXCOORD0;	// 그림의 좌표
};

// PixelInput 구조체 정의
struct PixelInput	// PixelShdaer에서 사용할 목적
{
	// VertexType에서 지정한 세멘틱 이름과 번호를 사용해야 한다.
	float4 position : SV_POSITION0; // 정점의 위치
	float2 uv		: TEXCOORD0;	// 그림의 좌표
};

cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _proj;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _proj);
	
	output.uv = input.uv;
	
	return output;
};

Texture2D _sourceTex	: register(t0);
SamplerState _samp		: register(s0);

cbuffer AlphaBuffer : register(b0)
{
	float4 _alphaColor;
	float _alpha;
}

float4 PS(PixelInput input) : SV_Target
{
	float4 color = _sourceTex.Sample(
	_samp, (float2)input.uv);
	
	if(_alpha >= 0.001f)
	{
		color = (color - (color * _alpha) + (_alphaColor * _alpha));
	}
	
	return color;
};

/*
Semantic : 세멘틱
- HLSL 쉐이더에서 데이터의 의미를 지정하는데 사용되는 문자
- 쉐이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리할 수 있도록
도와준다. // VertexType과 InputLayout을 이용한다.
- 변수 이름뒤에 : 과 함깨 지정
- 시스템 값 세멘틱은 SV_ 접두사로 시작하며, DirectX에서 지정한 특별한
의미를 지니게 된다.
- 시스템 값 세멘틱은 보통 쉐이더 스테이지 간에 데이터를 전달하는데 사용된다.
// VS에서 output으로 만든 PixelInput값을 PS가 낚아채서 사용할수 있게 했다.

slot
- GPU에서 사용하는 상수 버퍼, 텍스처, 셈플러 등의 자원들을 식별하는 인덱스
- 각 슬롯은 고유한 번호를 가지며, 해당 자원의 유형과 역할에 따라 다르게
지정한다.
- register라는 키워드를 사용하여 지정
- 각 자원이 어떤 슬롯에서 할당 될 것인지를 명시적으로 지정할 수 있다.
- 주요 슬롯
	1) 상수 버퍼 슬롯
	- 상수 데이터를 저장하는데 사용되며, VS와 PS에서 공유될 수 있다.
	- register(b#)에 할당하여 지정
	
	2) 텍스처 슬롯
	- 이미지 데이터를 저장하는데 사용
	- register(t#)에 할당하여 지정

	3) 샘플러 슬롯
	- 텍스처를 샘플링할 방법의 데이터를 저장하는데 사용
	- 샘플링은 텍스처의 데이터를 읽어오는 방식을 말한다.
	- register(s#)에 할당하여 지정

cbuffer = Constant Buffer : 상수 버퍼
- 쉐이더에서 사용하는 전역 변수를 저장하는데 사용
- 각 상수 버퍼 레지스터는 한 개의 상수 버퍼만 할당할 수 있다.
- 상수 버퍼 내부에서 변수를 여러개 만들 수 있다.
- CPU에서 GPU로 정점이 아닌 데이터를 건내주기 위해서는 
cbuffer를 사용 해야한다.
*/