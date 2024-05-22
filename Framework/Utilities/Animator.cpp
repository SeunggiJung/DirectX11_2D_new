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

	// �̹��� ���� ũ��  400
	// �߶�� �� ũ�� 100
	texelFrameSize.x = frameSize.x / imageWidth; // uv ���� 0.25�� ����
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;

	texelFrameSize.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++) 
	{
		// �����ų �ִϸ��̼� �������� x,y ��ǥ ���
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
			// ������ �ε����� �ִ�ġ�� �Ǹ� �ٽ� 0���� �ʱ�ȭ
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
		deltaTime += Time::Delta(); // �ð��� ���� ���
	}
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip)); // animClips.find(L"1")->second �̷������� Ÿ���� ���缭 �Ű������� �־�ߵ�
} 

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip != nullptr)
		if (currentClip->clipName == clipName) return; // ���� ������� Ŭ���� �����Ϸ��� Ŭ���� ������ �Լ� ����

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
			currentFrameIndex = 0; // ù ��° ������ �������� �ʱ�ȭ
		}

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}

}
