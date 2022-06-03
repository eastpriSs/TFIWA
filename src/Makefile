
#
# Создает объектные файлы в src
# Кидает Main.exe в LIBS
# С помощью ссылки на Main.exe запускаем приложение 
#

all: compile link clean-obj

compile: lvlsData/Menu.h lvlsData/Lvl_1.h modules/MainCharacter.h modules/Allocator.h
	g++ -I LIBS/include -c Main.cpp lvlsData/Menu.cpp lvlsData/Lvl_1.cpp modules/MainCharacter.cpp modules/Allocator.cpp

#------------------ Имена -------------------------------------------------------------------
exe-name := Main # Исправить, также добавить ярлык
#--------------------------------------------------------------------------------------------------

#------------------ Пути линковки и компиляции	-------------------------------------------------------------------
exe-link := D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\dll_libs\main 
dll-link := D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\dll_libs 
#--------------------------------------------------------------------------------------------------

#------------------ Список объектных ------------------
obj-files := Main.o Lvl_1.o Menu.o MainCharacter.o Allocator.o
#--------------------------------------------------------------------------------------------------


#------------------ Флаги и аргументы ------------------
link-settings := -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l libgcc_s_seh-1 -l libstdc++ -l libwinpthread
#--------------------------------------------------------------------------------------------------

link: 
	g++ -o $(exe-link) $(obj-files) -L LIBS/lib $(link-settings)

clean-obj:
	rm 	$(obj-files)