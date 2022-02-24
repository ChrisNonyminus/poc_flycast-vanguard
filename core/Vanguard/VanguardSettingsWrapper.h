#pragma once
#include <utility>
#include <string>

public ref class VanguardSettingsWrapper
{
    public:

    static VanguardSettingsWrapper ^ GetVanguardSettingsFromCitra();
    static void SetSettingsFromWrapper(VanguardSettingsWrapper ^ vSettings);
   // int birthmonth;
   // int birthday;
   // int language_index;
   // u8 country;
   // u16 play_coin;
    };
