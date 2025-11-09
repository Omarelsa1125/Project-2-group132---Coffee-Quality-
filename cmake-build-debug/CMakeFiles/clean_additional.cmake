# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CoffeeQuality_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CoffeeQuality_autogen.dir/ParseCache.txt"
  "CoffeeQuality_autogen"
  )
endif()
