# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ShapeZ_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ShapeZ_autogen.dir\\ParseCache.txt"
  "ShapeZ_autogen"
  )
endif()
