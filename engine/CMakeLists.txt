file(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
file(GLOB_RECURSE ENGINE_HEADERS *.hpp *.h *.inl)

add_executable(engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	target_link_libraries(engine SDL2.lib SDL2main.lib glew32.lib opengl32.lib assimp-vc143-mt.lib)

	# copy dll to binary directory
endif()

if(APPLE)
	target_link_libraries(engine ${SDL2_LIBRARIES} GLEW::GLEW ${ASSIMP_LIBRARIES} OpenGL::GL)
endif()
