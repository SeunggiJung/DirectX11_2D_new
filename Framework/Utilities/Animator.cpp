#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	Vector2 ClipSize = endPos - startPos;

	Vector2 frameSize;
	frameSize.x = ClipSize.x / frameCount;
	frameSize.y = ClipSize.y;

	// 이미지 가로 크기  400
	// 잘라야 할 크기 100
	texelFrameSize.x = frameSize.x / imageWidth; // uv 값이 0.25로 나옴
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;

	texelFrameSize.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++) 
	{
		// 실행시킬 애니메이션 프레임의 x,y 좌표 계산
		keyFrame.x = texelStartPos.x + (texelFrameSize.x*i);
		keyFrame.y = texelStartPos.y;

		keyFrames.push_back(keyFrame);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
	{
		SAFE_DELETE(clip.second);
	}
}

void Animator::Update()
{
	if (deltaTime >= playRate)
	{
		if (currentClip->bReversed == false) // 1-2-3-4
		{
			currentFrameIndex++;
			// 프레임 인덱스가 최대치가 되면 다시 0으로 초기화
			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else								// 4-3-2-1
		{
			currentFrameIndex--;
			
			if (currentFrameIndex == -1)
			{
				currentFrameIndex = currentClip->frameCount - 1;
			}
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}

		deltaTime = 0.0f;

	}

	else
	{
		deltaTime += Time::Delta(); // 시간에 맞춰 출력
	}
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip)); // animClips.find(L"1")->second 이런식으로 타입을 맞춰서 매개변수를 넣어야됨
} 

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip != nullptr)
		if (currentClip->clipName == clipName) return; // 현재 재생중인 클립과 설정하려는 클립이 같으면 함수 종료

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;

		deltaTime = 0.0f;

		if (currentClip->bReversed)
		{
			currentFrameIndex = currentClip->frameCount - 1;
		}

		else
		{
			currentFrameIndex = 0; // 첫 번째 사진이 나오도록 초기화
		}

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}

}
