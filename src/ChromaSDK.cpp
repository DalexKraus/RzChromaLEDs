#include "ChromaSDK.hpp"
#include "Debug.hpp"

#include <stdio.h>

#ifdef _WIN64
#define CHROMASDKDLL "RzChromaSDK64.dll"
#else
#define CHROMASDKDLL "RzChromaSDK.dll"
#endif

#define INIT_TIMEOUT 1000 // Timeout for the chroma service

INIT                    init                    = NULL;
CREATEEFFECT            createEffect            = NULL;
CREATEKEYBOARDEFFECT    createKeyboardEffect    = NULL;
CREATEMOUSEEFFECT       createMouseEffect       = NULL;
SETEFFECT               setEffect               = NULL;
DELETEEFFECT            deleteEffect            = NULL;
QUERYDEVICE             queryDevice             = NULL;

HMODULE m_ChromaSDKModule;

CHROMA_API void setKeyboardColor(COLORREF color)
{
    using namespace ChromaSDK::Keyboard;
    CUSTOM_KEY_EFFECT_TYPE effect = {};

    for (int row = 0; row < MAX_ROW; row++)
        for (int col = 0; col < MAX_COLUMN; col++)
            effect.Key[row][col] = 0x01000000 | RGB(GetRValue(color), GetGValue(color), GetBValue(color));

    createKeyboardEffect(CHROMA_CUSTOM_KEY, &effect, NULL);
}

CHROMA_API void setMouseColor(COLORREF color)
{
    using namespace ChromaSDK::Mouse;
    CUSTOM_EFFECT_TYPE effect = {};
    
    for (int led = 1; led < RZLED_SIDE_STRIP14; led++)
        effect.Color[led] = RGB(GetRValue(color), GetGValue(color), GetBValue(color));

    createMouseEffect(CHROMA_CUSTOM, &effect, NULL);
}

CHROMA_API bool initialize()
{
    dbgInfo("Initializing ChomaSDK ...");
    bool success = false;

    // Load ChromaSDK DLL
    dbgInfo("==> Loading DLL");
    if (!m_ChromaSDKModule)
    {
        LPCSTR moduleName = LPCSTR(CHROMASDKDLL);
        m_ChromaSDKModule = LoadLibraryA(moduleName);

        // Check if the library could be loaded, else exit.
        if (!m_ChromaSDKModule)
        {
            char errorMsg[128];
            sprintf_s(errorMsg, "Unable to load Razer Chroma DLL '%s'!", CHROMASDKDLL);
            dbgErrBox(errorMsg);
        }
    }

    dbgInfo("==> Initializing");
    if (init == NULL)
    {
        init = (INIT) GetProcAddress(m_ChromaSDKModule, "Init");
        if (init)
        {
            RZRESULT result = init();
            if (result == RZRESULT_SUCCESS)
            {
                dbgInfo("==> Loading functions");
                HMODULE module          = m_ChromaSDKModule;
                createEffect            = (CREATEEFFECT)            GetProcAddress(module, "CreateEffect");
                createKeyboardEffect    = (CREATEKEYBOARDEFFECT)    GetProcAddress(module, "CreateKeyboardEffect");
                createMouseEffect       = (CREATEMOUSEEFFECT)       GetProcAddress(module, "CreateMouseEffect");
                setEffect               = (SETEFFECT)               GetProcAddress(module, "SetEffect");
                deleteEffect            = (DELETEEFFECT)            GetProcAddress(module, "DeleteEffect");
                queryDevice             = (QUERYDEVICE)             GetProcAddress(module, "QueryDevice");

                //Return the state of the function loading procedure
                success = createEffect && createKeyboardEffect && createMouseEffect && setEffect && deleteEffect && queryDevice;
                if (success) Sleep(INIT_TIMEOUT);
            }
            else dbgErr("Unable to initialize ChromaSDK.");
        }
    }

    return success;
}

CHROMA_API bool unitialize()
{
    dbgInfo("UnInitializing ChromaSDK ...");
    bool success = false;
    if (m_ChromaSDKModule != NULL)
    {
        RZRESULT result = RZRESULT_INVALID;
        UNINIT unInit   = (UNINIT) GetProcAddress(m_ChromaSDKModule, "UnInit");
        if (unInit)
        {
            result = unInit();
            if (result == RZRESULT_SUCCESS)
            {
                FreeLibrary(m_ChromaSDKModule);
                m_ChromaSDKModule = NULL;

                dbgInfo("==> Done.");
                success = true;
            }
        }
    }
    return success;
}

CHROMA_API bool isDeviceConnected(RZDEVICEID deviceId)
{
    bool deviceConnected = false;
    if (queryDevice != NULL)
    {
        ChromaSDK::DEVICE_INFO_TYPE deviceInfo = {};
        RZRESULT queryResult = queryDevice(deviceId, deviceInfo);
        deviceConnected = deviceInfo.Connected;
    }
    else dbgErr("Undefined reference to procedure 'queryDevice'!");

    return deviceConnected;
}
