project(api)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/Client.h
    ${HEADER_DIR}/Console.h
    ${HEADER_DIR}/ConsoleFramebuffer.h
    ${HEADER_DIR}/EchoCommand.h
    ${HEADER_DIR}/Factory.h
    ${HEADER_DIR}/ICommand.h
    ${HEADER_DIR}/InterpreterBuilder.h
    ${HEADER_DIR}/LibraryManager.h
    ${HEADER_DIR}/Media.h
    ${HEADER_DIR}/Book.h
    ${HEADER_DIR}/Movie.h
    ${HEADER_DIR}/VideoGames.h
)

set (SOURCES
    ${SOURCE_DIR}/Client.cpp
    ${SOURCE_DIR}/Console.cpp
    ${SOURCE_DIR}/ConsoleFramebuffer.cpp
    ${SOURCE_DIR}/EchoCommand.cpp
    ${SOURCE_DIR}/Factory.cpp
    ${SOURCE_DIR}/ICommand.cpp
    ${SOURCE_DIR}/InterpreterBuilder.cpp
    ${SOURCE_DIR}/LibraryManager.cpp
    ${SOURCE_DIR}/Media.cpp
    ${SOURCE_DIR}/Book.cpp
    ${SOURCE_DIR}/Movie.cpp
    ${SOURCE_DIR}/VideoGames.cpp
)

add_library(${PROJECT_NAME}
STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} 
PUBLIC 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
