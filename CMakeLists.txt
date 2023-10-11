
# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)



# -------------------------------------------------------------------------
# Global define
# -------------------------------------------------------------------------

# Enable factory test
add_definitions(-DENABLE_FACTORY_TEST)

# WiFi test setting
add_definitions(-DFACTORY_TEST_WIFI_SSID="?")
add_definitions(-DFACTORY_TEST_WIFI_PASSWORD="?")
# add_definitions(-DFACTORY_TEST_WIFI_SSID="?")
# add_definitions(-DFACTORY_TEST_WIFI_PASSWORD="?")


# Font setting
add_definitions(-DGUI_FONT_CN_BIG=&fonts::efontCN_24)
# add_definitions(-DGUI_FONT_CN_SMALL=&fonts::efontCN_16)
add_definitions(-DGUI_FONT_CN_SMALL=&fonts::efontCN_16_b)

# -------------------------------------------------------------------------



include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(stamp_ring_factory_test)
