cmake_minimum_required (VERSION 3.16)	# Проверка версии

project (BattleCity LANGUAGES C CXX)	# Имя проекта и его язык

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable (BattleCity main.c)	# Компиляция исполняемых файлов

	 
