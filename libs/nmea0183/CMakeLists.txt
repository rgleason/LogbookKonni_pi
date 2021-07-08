##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   2015
## License:     GPLv3+
##---------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1.0)

if (TARGET ocpn::nmea0183)
    return ()
endif ()

SET(SRC
    src/apb.cpp
    src/apb.hpp
    src/dbt.cpp
    src/dbt.hpp
    src/dpt.cpp
    src/dpt.hpp
    src/expid.cpp
    src/gga.cpp
    src/gga.hpp
    src/gll.cpp
    src/gll.hpp
    src/gsv.cpp
    src/gsv.hpp
    src/hdg.cpp
    src/hdg.hpp
    src/hdm.cpp
    src/hdm.hpp
    src/hdt.cpp
    src/hdt.hpp
    src/hexvalue.cpp
    src/lat.cpp
    src/latlong.cpp
    src/LatLong.hpp
    src/long.cpp
    src/mtw.cpp
    src/mtw.hpp
    src/mwv.cpp
    src/mwv.hpp
    src/nmea0183.cpp
    src/nmea0183.hpp
    src/nmea0183/nmea0183.h
    src/response.cpp
    src/Response.hpp
    src/rmb.cpp
    src/rmb.hpp
    src/rmc.cpp
    src/rmc.hpp
    src/rsa.cpp
    src/rsa.hpp
    src/rte.cpp
    src/rte.hpp
    src/SatInfo.h
    src/sentence.cpp
    src/Sentence.hpp
    src/talkerid.cpp
    src/vhw.cpp
    src/vhw.hpp
    src/vtg.cpp
    src/vtg.hpp
    src/vwr.cpp
    src/vwr.hpp
    src/vwt.cpp
    src/vwt.hpp
    src/wpl.cpp
    src/wpl.hpp
    src/xdr.cpp
    src/xdr.hpp
    src/xte.cpp
    src/xte.hpp
    src/zda.cpp
    src/zda.hpp
)


add_library(_NMEA0183 STATIC ${SRC})
add_library(ocpn::nmea0183 ALIAS _NMEA0183)

target_include_directories(_NMEA0183 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/nmea0183
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set_property(TARGET _NMEA0183 PROPERTY COMPILE_FLAGS "-fvisibility=hidden")
endif ()

