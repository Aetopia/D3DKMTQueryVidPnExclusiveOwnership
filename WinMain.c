#include <windows.h>

// https://github.com/microsoft/libdxg/blob/main/include/d3dkmthk.h#L3833
// https://learn.microsoft.com/windows-hardware/drivers/ddi/d3dkmthk/ne-d3dkmthk-_d3dkmt_vidpnsourceowner_type
typedef enum _D3DKMT_VIDPNSOURCEOWNER_TYPE
{
    D3DKMT_VIDPNSOURCEOWNER_UNOWNED = 0,
    D3DKMT_VIDPNSOURCEOWNER_SHARED = 1,
    D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVE = 2,
    D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVEGDI = 3,
    D3DKMT_VIDPNSOURCEOWNER_EMULATED = 4
} D3DKMT_VIDPNSOURCEOWNER_TYPE;

// https://learn.microsoft.com/windows-hardware/drivers/ddi/d3dkmthk/ns-d3dkmthk-_d3dkmt_queryvidpnexclusiveownership
typedef struct _D3DKMT_QUERYVIDPNEXCLUSIVEOWNERSHIP
{
    HANDLE hProcess;
    HWND hWindow;
    UINT VidPnSourceId;
    LUID AdapterLuid;
    D3DKMT_VIDPNSOURCEOWNER_TYPE OwnerType;
} D3DKMT_QUERYVIDPNEXCLUSIVEOWNERSHIP;

// https://learn.microsoft.com/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtqueryvidpnexclusiveownership
NTSTATUS D3DKMTQueryVidPnExclusiveOwnership(D3DKMT_QUERYVIDPNEXCLUSIVEOWNERSHIP *);

int WinMainCRTStartup()
{
    DWORD dwProcessId = 0;
    D3DKMT_QUERYVIDPNEXCLUSIVEOWNERSHIP unnamedParam1 = {.hWindow = GetForegroundWindow()};
    GetWindowThreadProcessId(unnamedParam1.hWindow, &dwProcessId);

    if ((unnamedParam1.hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwProcessId)))
    {
        D3DKMTQueryVidPnExclusiveOwnership(&unnamedParam1);
        CloseHandle(unnamedParam1.hProcess);

        LPCWSTR szOwnerType = NULL;
        switch (unnamedParam1.OwnerType)
        {
        case D3DKMT_VIDPNSOURCEOWNER_UNOWNED:
            szOwnerType = L"Not owned.";
            break;
        case D3DKMT_VIDPNSOURCEOWNER_SHARED:
            szOwnerType = L"Shared.";
            break;
        case D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVE:
            szOwnerType = L"Exclusive.";
            break;
        case D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVEGDI:
            szOwnerType = L"Exclusive GDI.";
            break;
        case D3DKMT_VIDPNSOURCEOWNER_EMULATED:
            szOwnerType = L"Emulated.";
            break;
        }

        MessageBoxW(NULL, szOwnerType, L"D3DKMTQueryVidPnExclusiveOwnership", MB_OK);
    }
    return 0;
}