add_library(Vanguard STATIC
    VanguardClient.cpp
)

set_target_properties(Vanguard PROPERTIES LINK_FLAGS "/CLRTHREADATTRIBUTE:STA")

file (GLOB CLR_FILES
    VanguardClient.cpp
)
set_source_files_properties(${CLR_FILES} PROPERTIES COMPILE_FLAGS "/clr /EHa /Zc:twoPhase-")
set_target_properties(Vanguard PROPERTIES VS_DOTNET_REFERENCES_COPY_LOCAL ON )
set_target_properties(Vanguard PROPERTIES DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.1")
set_target_properties(Vanguard PROPERTIES VS_DOTNET_REFERENCE_CorruptCore "${PROJECT_SOURCE_DIR}/../../../../RTCV/Build/CorruptCore.dll")
set_target_properties(Vanguard PROPERTIES VS_DOTNET_REFERENCE_NetCore "${PROJECT_SOURCE_DIR}/../../../../RTCV/Build/NetCore.dll")
set_target_properties(Vanguard PROPERTIES VS_DOTNET_REFERENCE_RTCVCommon "${PROJECT_SOURCE_DIR}/../../../../RTCV/Build/RTCV.Common.dll")
set_target_properties(Vanguard PROPERTIES VS_DOTNET_REFERENCE_Vanguard "${PROJECT_SOURCE_DIR}/../../../../RTCV/Build/Vanguard.dll")
set_target_properties(Vanguard PROPERTIES VS_DOTNET_REFERENCES "System;System.Windows.Forms")
string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

target_link_libraries(Vanguard PUBLIC VanguardWrapper)