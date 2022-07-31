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
#include <memory>

// Сценарий: 
#include "lvlsData/Menu.h"
#include "lvlsData/Lvl_1.h"
// ;

// Вспомогательные процессы, предикаты

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

// Можно сделать аргументом лвл, который нужно
// запустить, но красивее пожалуй будет смотреться
// так...
void display_lvl_one(const short height = 630,  
        const short width  = 340)
{
    using LVL_ONE::lvl_1;

    std::unique_ptr<sf::RenderWindow> w( 
                new sf::RenderWindow(
                                sf::VideoMode(height, width),
                                "testV1",
                                sf::Style::Default ));
    // Ограничение FPS под уровень.
    w->setFramerateLimit(30);

    std::unique_ptr<lvl_1> lvl( new lvl_1() );
    // Главный цикл
    lvl->draw_menu(*w);
}


void display_menu(const short height = 630,  
        const short width  = 340)
{
    using MENU_INTERFACE::Menu;

    std::unique_ptr<sf::RenderWindow> w( 
                new sf::RenderWindow(
                                sf::VideoMode(height, width),
                                "testV1",
                                sf::Style::Default ));
    // Ограничение FPS под уровень.
    w->setFramerateLimit(30);

    std::unique_ptr<Menu> m( new Menu(1) );
    // Главный цикл
    m->draw_menu(*w);
}

int main()
{
    // Главный цикл:
        // display_menu();        
        display_lvl_one();    
    //;
}

