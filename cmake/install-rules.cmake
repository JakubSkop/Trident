install(
    TARGETS Trident_exe
    RUNTIME COMPONENT Trident_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
