if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG_INIT "/D_DEBUG /MDd /ZI /Ob0 /Od /RTC1")
  MESSAGE(STATUS "CMAKE_CXX_FLAGS_DEBUG_INIT is " ${CMAKE_CXX_FLAGS_DEBUG_INIT})
endif()
