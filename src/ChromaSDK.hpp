#ifndef _CHROMA_SDK_
#define _CHROMA_SDK_

#include <Windows.h>

#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

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

class CChromaSDK
{
public:
    bool initialize();
    bool unitialize();
    bool isDeviceConnected();
    void setKeyboardColor(COLORREF color);
    void setMouseColor(COLORREF color);
private:
    HMODULE m_ChromaSDKModule;
};

#endif