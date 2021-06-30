##---------------------------------------------------------------------------
## Author:      nohal aka. Pavel Kalian
## Copyright:
## License:     wxWidgets License
#-----------------------------------------------------------------------------
# Frontend2 Author: Jon Gough
# Frontend2 Version: 1.0.172 28/06/2021
# ---------------------------------------------------------------------------
## buildCI:yes useODAPI:no validateJSON:no
##
## ----- When changing this file do NOT change the order in which sections occur        ----- ##
## ----- Changes should only be made between the section blocks that identify where     ----- ##
## ----- these changes should be. The whole configuration process relies on this        ----- ##
## ----- sequence to be successful                                                      ----- ##
##

##
## ----- Modify section below to include all the details for your plugin ----- ##
##

set(CMLOC "CMakeLists: ")

# define minimum cmake version
cmake_minimum_required(VERSION 3.1.1)
if(COMMAND cmake_policy)
    if(POLICY CMP0043)
        cmake_policy(SET CMP0043 NEW)
    endif(POLICY CMP0043)
    cmake_policy(SET CMP0048 NEW)
    if(POLICY CMP0077)
        cmake_policy(SET CMP0077 NEW)
    endif(POLICY CMP0077)
endif(COMMAND cmake_policy)

# define plugin name, owner and versions
set(VERBOSE_NAME "Logbookkonni")
set(COMMON_NAME "Logbook")
set(TITLE_NAME "LOGBOOKKONNI")
set(PACKAGE_CONTACT "Del Elson")
set(PACKAGE "logbookkonni")
set(SHORT_DESCRIPTION "Logbook for OpenCPN")
set(LONG_DESCRIPTION "Help on YouTube search LogbookKonni.")

set(VERSION_MAJOR "1")
set(VERSION_MINOR "4")
set(VERSION_PATCH "14")
set(VERSION_TWEAK "8")
set(VERSION_DATE "30-06-2020")  # DD/MM/YYYY format
set(OCPN_MIN_VERSION "ov50")
set(OCPN_API_VERSION_MAJOR "1")
set(OCPN_API_VERSION_MINOR "16")
set(TP_COMMENT "  * Release for O5 using CI")

set(PARENT "opencpn")

# The next line allows for setting up your own local webserver with git on it for testing purposes, the default is github.com
#set(GIT_REPOSITORY_SERVER "github.com")

# Specific cloudsmith repository suffixes
set(PROD "prod") # Standard Repos
set(BETA "beta") # Standard Repos
set(ALPHA "alpha") # Standard Repos

# set this if your cloudsmith repository name does not match your git repository name set(CLOUDSMITH_BASE_REPOSITORY "testplugin_pi")
set(CLOUDSMITH_BASE_REPOSITORY "logbookkonni")  #without the pi
# Set the following to use OpenCPN cloudsmith repositories instead of own repositories
set(CLOUDSMITH_USER "opencpn")
#set(CLOUDSMITH_USER "rick-gleason")

set(XML_INFO_URL "https://opencpn.org/OpenCPN/plugins/logbookkonni.html")
set(XML_SUMMARY ${SHORT_DESCRIPTION})
set(XML_DESCRIPTION ${LONG_DESCRIPTION})

## ----- Modify section above to include all the details for your plugin ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(CMAKE_CXX_STANDARD 11)

# Use local version of GLU library
#set(USE_LOCAL_GLU TRUE)
# Prefer libGL.so to libOpenGL.so, see CMP0072
set(OpenGL_GL_PREFERENCE "LEGACY")
# Don't use local version of GLU library
set(USE_LOCAL_GLU FALSE)

option(USE_GL "Enable OpenGL support" OFF)
message(STATUS "${CMLOC}USE_GL: ${USE_GL}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "" "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
message(STATUS "${CMLOC}Build type: ${CMAKE_BUILD_TYPE}")

## ----- The statements below are used to setup standard variables that are required by the CMAKE process - do not remove ----- ##

project(${PACKAGE})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# -----------------------------------------
include("PluginSetup")
# -----------------------------------------
## ----- The above is used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##


set(CMAKE_VERBOSE_MAKEFILE "Activate verbose mode for make files" ON)

option(Plugin_CXX11 "Use c++11" OFF)


## ----- Modify section above if there are special requirements for the plugin ----- ##
## ----- do not change next section - needed to configure build process ----- ##
# -----------------------------------------
include("PluginConfigure")
# -----------------------------------------
## ----- do not change section above - needed to configure build process ----- ##
## ----- Change below to match project requirements for source, headers, etc. ----- ##

# ----Remember to Add your project Set(SRCS and set(HDRS  etc..
# ++++++++++++++Section below is direct from Watchdog +++++++++##


add_definitions(-DUSE_S57)

# Keep this order there seems to be some dependency on that resulting in undefined. Leave ExGrid etc commented out.
# Cannot move h files into separate include folder, errors occur.

SET(SRCS
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
#		src/EzGrid.cpp  
#  -when not commented - error C3861: 'getcol': identifier not found
#		src/FastComboEditor.cpp
#  - when not commented - error C3861: 'getcol': identifier not found
#		src/GridCellChoiceRenderer.cpp
#  - when not commented - error C3861: 'getcol': identifier not found
#		src/EzGrid.h
#		src/FastComboEditor.h
#		src/GridCellChoiceRenderer.h
 	)

# Cannot move h files into separate include folder, errors occur.
#SET(HDRS
#  		include/logbook_pi.h
#		include/Logbook.h
#		include/LogbookDialog.h
#		include/LogbookOptions.h
#		include/LogbookHTML.h
#		include/boat.h
#		include/CrewList.h
#		include/Export.h
#		include/icons.h
#		include/Maintenance.h
#		include/EzGrid.h
#		include/FastComboEditor.h
#		include/GridCellChoiceRenderer.h
#		include/Options.h
#		include/OverView.h
#		)

# See Try-Lib-Nmea0183-Issue-Class=NMEA0183L..txt
SET(SRC_LNMEA0183
		src/nmea0183/LatLong.hpp
		src/nmea0183/latlong.cpp
		src/nmea0183/long.cpp
		src/nmea0183/nmea0183.cpp
		src/nmea0183/nmea0183.hpp
		src/nmea0183/Response.hpp
		src/nmea0183/response.cpp
		src/nmea0183/RMB.hpp
		src/nmea0183/rmb.cpp
		src/nmea0183/Sentence.hpp
		src/nmea0183/sentence.cpp
		src/nmea0183/talkerid.cpp
		src/nmea0183/RMC.HPP
		src/nmea0183/rmc.cpp
		src/nmea0183/hexvalue.cpp
		src/nmea0183/lat.cpp
		src/nmea0183/expid.cpp
		src/nmea0183/wpl.hpp
		src/nmea0183/wpl.cpp
		src/nmea0183/rte.hpp
		src/nmea0183/rte.cpp
		src/nmea0183/hdt.hpp
		src/nmea0183/hdt.cpp
		src/nmea0183/hdg.hpp
		src/nmea0183/hdg.cpp
		src/nmea0183/hdm.hpp
		src/nmea0183/hdm.cpp
		src/nmea0183/gll.hpp
		src/nmea0183/gll.cpp
		src/nmea0183/vtg.hpp
		src/nmea0183/vtg.cpp
		src/nmea0183/gga.hpp
		src/nmea0183/gga.cpp
		src/nmea0183/gsv.hpp
		src/nmea0183/gsv.cpp
		src/nmea0183/dbt.cpp
		src/nmea0183/dbt.hpp
		src/nmea0183/dpt.cpp
		src/nmea0183/dpt.hpp
		src/nmea0183/mtw.cpp
		src/nmea0183/mtw.hpp
		src/nmea0183/mwv.cpp
		src/nmea0183/mwv.hpp
		src/nmea0183/vhw.hpp
		src/nmea0183/vhw.cpp
		src/nmea0183/vwr.cpp
		src/nmea0183/vwr.hpp
		src/nmea0183/vwt.cpp
		src/nmea0183/vwt.hpp
		src/nmea0183/xdr.cpp
		src/nmea0183/xdr.hpp
		src/nmea0183/zda.cpp
		src/nmea0183/zda.hpp
		src/nmea0183/rsa.hpp
		src/nmea0183/rsa.cpp
		src/nmea0183/SatInfo.h
        )

#   now using libs/wxJSON
# set(LIBS_JSON
#        libs/json/json_defs.h
#      	libs/json/jsonreader.h
#        libs/json/jsonval.h
#        libs/json/jsonwriter.h
#        libs/json/jsonreader.cpp
#        libs/json/jsonval.cpp
#        libs/json/jsonwriter.cpp
#		)

set(OCPNSRC ocpnsrc/TexFont.cpp)

# Don't have these files and dont need them
#set(OCPNHDRS
#    ocpninclude/ocpn_plugin.h
#    ocpninclude/pluginmanager.h
#    ocpninclude/TexFont.h
#    libs/ocpn-api/ocpn_plugin.h
#)

set(EXTSRC
)

set(LIBSSRC libs/wxJSON/src/jsonreader.cpp libs/wxJSON/src/jsonval.cpp libs/wxJSON/src/jsonwriter.cpp)

set(LIBHDRS
    libs/GL/gl.h
    libs/GL/gl_private.h
    libs/GL/glext.h
    libs/GL/glu.h
    libs/wxJSON/include/json_defs.h
    libs/wxJSON/include/jsonreader.h
    libs/wxJSON/include/jsonval.h
    libs/wxJSON/include/jsonwriter.h)

add_definitions(-DPLUGIN_USE_SVG)

# No PI_JSON_SCHEMA_VALIDATOR  needed

include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include/)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/glu/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/${EXTINCLUDE_DIR})
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/ocpn-api)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wx/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wxJSON/include)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/nmea0183/src)

# -----------------------------------------
target_sources(${PACKAGE_NAME} PUBLIC ${SRCS}  ${SRC_LNMEA0183} ${LIBSSRC} ${LIBHDRS}  ${OCPNSRC} ${EXTSRC})
# -----------------------------------------
#target_sources(${PACKAGE_NAME} PUBLIC ${SRCS}  ${SRC_LNMEA0183} ${LIBSSRC} ${LIBHDRS}  ${OCPNSRC} ${OCPNHDRS} ${EXTSRC})
# target_sources(${PACKAGE_NAME} PUBLIC ${SRCS} ${HDRS} ${LIBHDRS} ${LIBSSRC} ${OCPNSRC} ${EXTSRC} ${LIBSSRC})
# add_library( ${PACKAGE_NAME} SHARED ${SRCS} ${SRC_LTINYXML} ${SRC_LNMEA0183} )

if(NOT OCPN_FLATPAK_CONFIG)
# Build environment is not available when flatpak is being configured so following statements will not work
    message(STATUS "${CMLOC}Adding target link libraries to ${PACKAGE_NAME}")

#    add_subdirectory(libs/nmea0183)
    add_subdirectory(libs/tinyxml)

#    target_link_libraries(${PACKAGE_NAME} ocpn::nmea0183)
    target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

endif(NOT OCPN_FLATPAK_CONFIG)

add_definitions(-DTIXML_USE_STL)

# Disables Logbook Install and Uninstall Preferences buttons.
#add_definitions("-DLAYOUTS_HACK")
# Not doing json schema validation

## ----- Change above to match project requirements ----- ##
## ----- do not change next section - needed to configure build process ----- ##

# Needed for android builds
if(QT_ANDROID)
    include_directories(BEFORE ${qt_android_include})
endif(QT_ANDROID)

# Needed for all builds
include("PluginInstall")
include("PluginLocalization")
include("PluginPackage")
# -----------------------------------------
## ----- do not change section above - needed to configure build process ----- ##

message(STATUS "${CMLOC}include directories: ")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "${CMLOC}dir='${dir}'")
endforeach()
