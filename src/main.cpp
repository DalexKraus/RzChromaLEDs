#include "ChromaSDK.hpp"
#include <stdio.h>

CChromaSDK chromaSDKInstance;

int main(int argc, char const *argv[])
{
    printf("----- RzLEDApp -----\n");
    chromaSDKInstance = CChromaSDK();
    if (!chromaSDKInstance.initialize())
        return -1;

    const COLORREF RED = RGB(255, 0, 0);
    
    chromaSDKInstance.setKeyboardColor(RED);
    chromaSDKInstance.setMouseColor(RED);

    getchar();
    chromaSDKInstance.unitialize();
    return 0;
}
