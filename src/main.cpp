#include <stdio.h>
#include "ChromaSDK.hpp"
#include "Debug.hpp"

CChromaSDK chromaSDKInstance;

int main(int argc, char const *argv[])
{
    printf("----- RzLEDApp -----\n");
    chromaSDKInstance = CChromaSDK();
    if (!chromaSDKInstance.initialize())
        return -1;

    const COLORREF RED = RGB(255, 0, 64);
    chromaSDKInstance.setKeyboardColor(RED);
    chromaSDKInstance.setMouseColor(RED);

    getchar();
    chromaSDKInstance.unitialize();
    return 0;
}
