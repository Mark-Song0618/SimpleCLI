# to build

set(sources Command.c Mainloop.c BasicCmds.c)
set(headers Command.h Mainloop.h BasicCmds.h Define.h)

add_library (
	simpleCli
	SHARED
	${sources}
	${headers}
)

# to install
#set (CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
#message(STATUS "Project will be installed at: ${CMAKE_INSTALL_PREFIX}")

#set(INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)           #设置静态库安装路径
#set(INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)           #设置动态库安装路径
#set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)   #设置头文件安装路径

set_target_properties(
    simpleCli
    PROPERTIES
        POSITION_INDEPENDENT_CODE 1
        C_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1
        OUTPUT_NAME "simple_cli"
        DEBUG_POSTFIX "_d"
        PUBLIC_HEADER "Mainloop.h;Command.h;${INSTALL_INCLUDEDIR}/simpleCliExport.h"
        MACOSX_RPATH ON
)

include(GenerateExportHeader)
generate_export_header(simpleCli
    BASE_NAME "simpleCli"
    EXPORT_MACRO_NAME "simpleCli_EXPORT"
    EXPORT_FILE_NAME "${INSTALL_INCLUDEDIR}/simpleCliExport.h"
    DEPRECATED_MACRO_NAME "simpleCli_DEPRECATED"
    NO_EXPORT_MACRO_NAME "simpleCli_NO_EXPORT"
    STATIC_DEFINE "simpleCli_STATIC_DEFINE"
    NO_DEPRECATED_MACRO_NAME "simpleCli_NO_DEPRECATED"
    DEFINE_NO_DEPRECATED
)

target_include_directories(
    simpleCli
    PUBLIC
    ${INSTALL_INCLUDEDIR}
)
install(
TARGETS
    simpleCli
ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR} 
    COMPONENT dev
 )

