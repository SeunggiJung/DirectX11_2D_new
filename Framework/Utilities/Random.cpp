#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int minI, int maxI)
{
    random_device randDevice;

    uniform_int_distribution<int> intRand(minI, maxI);

    int temp = intRand(randDevice);

    return temp;
}

float Random::GetRandomFloat(float minF, float maxF)
{
    random_device randDevice;

    uniform_real_distribution<float> floatRand(minF, maxF);

    float temp = floatRand(randDevice);

    return temp;
}
