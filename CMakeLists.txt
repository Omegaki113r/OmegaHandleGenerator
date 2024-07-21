set( STC_INCLUDES submodules/third-party/STC/inc/c11 submodules/third-party/STC/inc/stc submodules/third-party/STC/inc/stc/algo submodules/third-party/STC/inc/stc/priv )
set( HEADER_DIRECTORIES inc priv/inc ${STC_INCLUDES} )
set( SOURCES src/OmegaHandleGenerator.c )

idf_component_register  (   INCLUDE_DIRS    ${HEADER_DIRECTORIES}  
                            SRCS            ${SOURCES}
                            PRIV_REQUIRES   json esp_timer
                            REQUIRES        OmegaBaseLoggingController OmegaUtilityDriver
                        )

set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)