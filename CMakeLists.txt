cmake_minimum_required (VERSION 3.0)	# Проверка версии

project (BattleCity)	# Имя проекта и его язык

#find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

#include_directories(
	#external/AntTweakBar-1.16/include/
	#external/glfw-3.3.2/include/
	#external/glm-0.9.7.1/
	#external/glew-1.13.0/include/
	#external/assimp-3.0.1270/include/
	#external/bullet-2.81-rev2613/src/
#	.
#)
include_directories(headers)
file(GLOB_RECURSE SRC_LIST *.c* *.h*)

add_executable (BattleCity SRC_LIST)	# Компиляция исполняемых файлов

	 
