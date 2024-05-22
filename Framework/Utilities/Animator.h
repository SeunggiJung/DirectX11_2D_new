#pragma once
class AnimationClip
{
public:
    friend class Animator;

    AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed = false);
private:
    wstring clipName = L"";
    vector<Vector2> keyFrames;
    UINT frameCount = 0;
    ID3D11ShaderResourceView* srv = nullptr;
    Vector2 texelFrameSize;
    bool bReversed = false;
};


class Animator
{
    Animator();
    ~Animator();

    void Update();

    Vector2 GetCurrentFrame() { return currentFrame; }
    Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
    ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

    void AddAnimClip(AnimationClip* animClip);

    void SetCurrentAnimClip(wstring clipName);

    wstring GetCurrentClipName() { return currentClip->clipName; }
    void SetPlayRate(float playRate) { this->playRate = playRate; }

private:
    unordered_map<wstring, AnimationClip*> animClips;
    bool CheckExist(wstring clipName) {
        return animClips.find(clipName) != animClips.end();
    }

    AnimationClip* currentClip = nullptr;
    UINT currentFrameIndex = 0;
    Vector2 currentFrame;

    float deltaTime = 0.0f; // 애니메이션 제작 속도
    float playRate = 1.0f / 15.0f;
    
};

