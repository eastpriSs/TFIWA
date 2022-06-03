/*

////////////////////////////////////////
    
Главный драйвер программы, курирует всеми поддрайверами( уровнями игры ) 
Содержатся в коде: настройки окна, сценарий поддрайверов
Не имеет сторонних модулей, кроме поддрайверов; 
Большая часть модулей крепится к поддрайверам   
Сохраняет данные о последнем запуске.

////////////////////////////////////////

*/

#include <SFML/Graphics.hpp> // Для создания окна
// #include <fstream>           // Сохранение информации о прошлом запуске 
#include <iostream>          // string

// Сценарий: 
#include "lvlsData/Menu.h"
// ;

// Вспомогательные процессы, девианты

// std::string& hesh_cfg()
// // Хешируем текущие данные об игре и о прогрессе
// {

// }

// Сохранения прогресса:

void save_cfg()
// Сохраняет настройки игры и информацию полученную при последнем запуске
// Допустим позицию персонажа или прогресс по сюжету.
{

}

// ;

int main()
{
    
    using sf::RenderWindow;
    using MENU_INTERFACE::Menu;
    
    // Х-ка окна:
        const short height = 630;  
        const short width  = 340;
        RenderWindow window(sf::VideoMode(height, width),
                                "testV1");
        Menu m(1);
    // ;

    // Главный цикл:
        m.draw_menu(&window);
    //;
    // getchar();
}