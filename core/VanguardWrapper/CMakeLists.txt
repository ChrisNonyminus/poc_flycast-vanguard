add_library(VanguardWrapper STATIC
            ../emulator.h
            UnmanagedWrapper.cpp
            ManagedWrapper.cpp
)

target_link_libraries(VanguardWrapper PUBLIC Vanguard)