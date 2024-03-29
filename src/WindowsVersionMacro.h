#pragma once

#if defined(_MSC_VER)
#include <sdkddkver.h>

//https://www.techthoughts.info/windows-version-numbers/
//https://github.com/microsoft/DMF/blob/master/Dmf/Framework/DmfIncludes_KERNEL_MODE.h
//NTDDI_WINTHRESHOLD    0x0A000000    10.0.10240.0
//NTDDI_WIN10           0x0A000000    10.0.10240.0
//NTDDI_WIN10_TH2       0x0A000001    10.0.10586.0
//NTDDI_WIN10_RS1       0x0A000002    10.0.14393.0
//NTDDI_WIN10_RS2       0x0A000003    10.0.15063.0
//NTDDI_WIN10_RS3       0x0A000004    10.0.16299.0
//NTDDI_WIN10_RS4       0x0A000005    10.0.17134.0
//NTDDI_WIN10_RS5       0x0A000006    10.0.17763.0
//NTDDI_WIN10_19H1      0x0A000007    10.0.18362.0
//NTDDI_WIN10_VB        0x0A000008    10.0.19041.0
//NTDDI_WIN10_MN        0x0A000009    10.0.19042.0
//NTDDI_WIN10_FE        0x0A00000A    10.0.19043.0
//NTDDI_WIN10_CO        0x0A00000B    10.0.22000.0
//NTDDI_WIN10_NI        0x0A00000C    10.0.22621.0

#define WIN11_22H2 (NTDDI_WIN10_NI) && (NTDDI_VERSION >= NTDDI_WIN10_NI)
#define WIN11_21H2 (NTDDI_WIN10_CO) && (NTDDI_VERSION >= NTDDI_WIN10_CO)
#define WIN10_21H1 (NTDDI_WIN10_FE) && (NTDDI_VERSION >= NTDDI_WIN10_FE)
#define WIN10_20H2 (NTDDI_WIN10_MN) && (NTDDI_VERSION >= NTDDI_WIN10_MN)
#define WIN10_20H1 (NTDDI_WIN10_VB) && (NTDDI_VERSION >= NTDDI_WIN10_VB)
#define WIN10_1903 (NTDDI_WIN10_19H1) && (NTDDI_VERSION >= NTDDI_WIN10_19H1)
#define WIN10_1809 (NTDDI_WIN10_RS5) && (NTDDI_VERSION >= NTDDI_WIN10_RS5)
#define WIN10_1803 (NTDDI_WIN10_RS4) && (NTDDI_VERSION >= NTDDI_WIN10_RS4)
#define WIN10_1709 (NTDDI_WIN10_RS3) && (NTDDI_VERSION >= NTDDI_WIN10_RS3)
#define WIN10_1703 (NTDDI_WIN10_RS2) && (NTDDI_VERSION >= NTDDI_WIN10_RS2)
#define WIN10_1607 (NTDDI_WIN10_RS1) && (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define WIN10_1511 (NTDDI_WIN10_TH2) && (NTDDI_VERSION >= NTDDI_WIN10_TH2)
#define WIN10_1507 (NTDDI_WIN10) && (NTDDI_VERSION >= NTDDI_WIN10)

#if WIN11_22H2
#define WIN10_SDK_BUILD_VER 22621
#elif WIN11_21H2
#define WIN10_SDK_BUILD_VER 22000
#elif WIN10_21H1
#define WIN10_SDK_BUILD_VER 19043
#elif WIN10_20H2
#define WIN10_SDK_BUILD_VER 19042
#elif WIN10_20H1
#define WIN10_SDK_BUILD_VER 19041
#elif WIN10_1903
#define WIN10_SDK_BUILD_VER 18362
#elif WIN10_1809
#define WIN10_SDK_BUILD_VER 17763
#elif WIN10_1803
#define WIN10_SDK_BUILD_VER 17134
#elif WIN10_1709
#define WIN10_SDK_BUILD_VER 16299
#elif WIN10_1703
#define WIN10_SDK_BUILD_VER 15063
#elif WIN10_1607
#define WIN10_SDK_BUILD_VER 14393
#elif WIN10_1511
#define WIN10_SDK_BUILD_VER 10586
#else WIN10_1507
#define WIN10_SDK_BUILD_VER 10240
#else
#error NTDDI_VERSION is defined for pre-Windows 10 builds.
#endif

#if WIN10_SDK_BUILD_VER >= 22000
#define WIN11
#else
#define WIN10
#endif

#endif