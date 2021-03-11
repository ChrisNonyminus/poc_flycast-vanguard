# Install script for directory: M:/sourcecode/flycast/core/deps/glslang/SPIRV

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/Debug/SPVRemapperd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/Release/SPVRemapper.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/MinSizeRel/SPVRemapper.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/RelWithDebInfo/SPVRemapper.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/Debug/SPIRVd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/Release/SPIRV.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/MinSizeRel/SPIRV.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/RelWithDebInfo/SPIRV.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPVRemapperTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPVRemapperTargets.cmake"
         "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPVRemapperTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPVRemapperTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPVRemapperTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPVRemapperTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPVRemapperTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPVRemapperTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPVRemapperTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPVRemapperTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPIRVTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPIRVTargets.cmake"
         "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPIRVTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPIRVTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SPIRVTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPIRVTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPIRVTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPIRVTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPIRVTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "M:/sourcecode/flycast/vs2019/core/deps/glslang/SPIRV/CMakeFiles/Export/lib/cmake/SPIRVTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SPIRV" TYPE FILE FILES
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/bitutils.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/spirv.hpp"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.std.450.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.EXT.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.KHR.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GlslangToSpv.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/hex_float.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/Logger.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/SpvBuilder.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/spvIR.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/doc.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/SpvTools.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/disassemble.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.AMD.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.NV.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/NonSemanticDebugPrintf.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/SPVRemapper.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/doc.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/SPIRV" TYPE FILE FILES
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/bitutils.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/spirv.hpp"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.std.450.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.EXT.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.KHR.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GlslangToSpv.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/hex_float.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/Logger.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/SpvBuilder.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/spvIR.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/doc.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/SpvTools.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/disassemble.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.AMD.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/GLSL.ext.NV.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/NonSemanticDebugPrintf.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/SPVRemapper.h"
    "M:/sourcecode/flycast/core/deps/glslang/SPIRV/doc.h"
    )
endif()

