# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WhatToEat_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WhatToEat_autogen.dir\\ParseCache.txt"
  "WhatToEat_autogen"
  )
endif()
