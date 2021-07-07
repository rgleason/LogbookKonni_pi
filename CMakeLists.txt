# ~~~
# Author:      Rasbats aka. Mike Rossiter
# Copyright:
# License:     wxWidgets License
# ~~~

# -------- Cmake setup ---------
#
cmake_minimum_required(VERSION 3.12.0)

cmake_policy(SET CMP0042 NEW)

if (POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif ()

if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif ()

# Locations where cmake looks for cmake modules.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build ${CMAKE_SOURCE_DIR}/cmake)

if (WIN32)
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/buildwin)
endif ()
message(STATUS "Cmake version: ${CMAKE_VERSION}.")


# -------- Build setup (mostly in PluginCompiler) --------
#
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
message(STATUS "Building: ${BUILD_TYPE}")


# -------- Options ----------

set(OCPN_TEST_REPO
    "opencpn/logbookkonni-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "opencpn/logbookkonni-beta"
    CACHE STRING 
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "opencpn/logbookkonni-prod"
    CACHE STRING 
    "Default repository for tagged builds not matching 'beta'"
)

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(OCPN_TARGET_TUPLE "" CACHE STRING
  "Target spec: \"platform;version;arch\""
)

string(TOLOWER "${OCPN_TARGET_TUPLE}" _lc_target)
if ("${_lc_target}" MATCHES "android*")
  set(QT_ANDROID ON)
  # Until we have a proper toolchain file:
  set(CMAKE_CROSSCOMPILING ON)
else ()
  set(QT_ANDROID OFF)
  add_definitions(-D__OCPN_USE_CURL__)
endif ()

#
# -------  Plugin setup --------
#
project(LogbookKonni_pi VERSION 1.4.15.2)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME Logbook)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME Logbook) # As of GetCommonName() in plugin API
set(CPACK_PACKAGE_CONTACT "Del Elson")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Complex, feature-rich logbook")
set(CPACK_PACKAGE_DESCRIPTION [=[
Complex logbook with a lot of features including a customizable layout.
To use all the features, you will have to download and install the Layout Files as instructed when you run the plugin for the first time.

Help is available on YouTube, search LogbookKonni
]=])

set(PKG_AUTHOR "Del Elson")
set(PKG_IS_OPEN_SOURCE "yes")
set(CPACK_PACKAGE_HOMEPAGE_URL https://github.com/rgleason/LogbookKonni_pi)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/logbookkonni.html)
SET(SRC
  src/logbook_pi.h
  src/logbook_pi.cpp
  src/Options.h
  src/Options.cpp
  src/icons.h
  src/icons.cpp
  src/Logbook.h
  src/Logbook.cpp
  src/LogbookDialog.h
  src/LogbookDialog.cpp
  src/LogbookOptions.h
  src/LogbookOptions.cpp
  src/LogbookHTML.h
  src/LogbookHTML.cpp
  src/CrewList.h
  src/CrewList.cpp
  src/boat.h
  src/boat.cpp
  src/Maintenance.h
  src/Maintenance.cpp
  src/OverView.h
  src/OverView.cpp
  src/Export.h
  src/Export.cpp
)

# -------- Setup completed, build the plugin --------
#
add_library(${CMAKE_PROJECT_NAME} SHARED ${SRC})
include_directories(BEFORE ${CMAKE_BINARY_DIR}/include)

add_subdirectory("libs/api-16")
target_link_libraries(${CMAKE_PROJECT_NAME} ocpn::api)

set(VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(PACKAGE_NAME ${CMAKE_PROJECT_NAME})

# Create the minimim ocpn version id string like ov50
string(REGEX REPLACE "\([0-9]\)\.\([0-9]\).*" "ov\\1\\2"
       OCPN_MIN_VERSION ${API_OCPN_MIN_VERSION})

if (PLUGIN_USE_SVG)
  add_definitions(-DPLUGIN_USE_SVG)
endif ()

# Set up targets. Targets sets up a recursive call with BUILD_TYPE set to
# 'flatpak', 'pkg' or 'tarball'. The initial call without BUILD_TYPE ends
# here.
#
include(Targets)
create_targets(
  ${PROJECT_SOURCE_DIR}/flatpak/org.opencpn.OpenCPN.Plugin.logbook.yaml
)
if ("${BUILD_TYPE}" STREQUAL "")
  return ()
endif ()

if (NOT ${BUILD_TYPE} STREQUAL "flatpak")
  # Build package as required (flatpak already dealt with).
  #
  include(PluginCompiler)
  include(PluginInstall)
  include(PluginPackage)
  if (QT_ANDROID)
    include(libs/AndroidLibs.cmake)
  else ()
    include(PluginLibs)
  endif ()
  include(PluginLocalization)

  include_directories(BEFORE ${CMAKE_BINARY_DIR}/include)

  
  add_subdirectory("libs/nmea0183")
  target_link_libraries(${PACKAGE_NAME} ocpn::nmea0183)

  add_subdirectory("libs/tinyxml")
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)
  
  add_subdirectory("libs/wxJSON")
  target_link_libraries(${PACKAGE_NAME} ocpn::wxjson)
endif ()

configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/include//config.h
  @ONLY
)

configure_file(
  # The cloudsmith upload script
  ${CMAKE_SOURCE_DIR}/ci/upload.sh.in ${CMAKE_BINARY_DIR}/upload.sh
  @ONLY
)
configure_file(
  # The cloudsmith upload script, windows bat file.
  ${CMAKE_SOURCE_DIR}/ci/upload.bat.in ${CMAKE_BINARY_DIR}/upload.bat
  @ONLY
)


set(checksum "@checksum@")
configure_file(
  # The XML metadata file
  ${CMAKE_SOURCE_DIR}/plugin.xml.in
  ${CMAKE_BINARY_DIR}/${pkg_displayname}.xml.in
  @ONLY
)
