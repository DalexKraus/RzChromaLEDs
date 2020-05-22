#ifndef _CHROMA_SDK_
#define _CHROMA_SDK_

#include <Windows.h>

#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

#ifndef CHROMA_API
#define CHROMA_API __declspec(dllexport)
#endif

// Generic
typedef RZRESULT (*INIT)(void);
typedef RZRESULT (*UNINIT)(void);

// Effects
typedef RZRESULT (*CREATEEFFECT)
    (RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

typedef RZRESULT (*CREATEKEYBOARDEFFECT)    
    (ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

typedef RZRESULT (*CREATEMOUSEEFFECT)
    (ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

typedef RZRESULT (*SETEFFECT)       (RZEFFECTID EffectId);
typedef RZRESULT (*DELETEEFFECT)    (RZEFFECTID EffectId);
typedef RZRESULT (*QUERYDEVICE)     (RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

extern "C"
{
    CHROMA_API bool initialize();
    CHROMA_API bool unitialize();
    CHROMA_API bool isDeviceConnected(RZDEVICEID deviceId);
    CHROMA_API void setKeyboardColor(COLORREF color);
    CHROMA_API void setMouseColor(COLORREF color);
}

#endif