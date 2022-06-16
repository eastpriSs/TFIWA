#include "lvl_1.h"

using namespace LVL_ONE;

lvl_1::lvl_1()
{

}

void lvl_1::draw_menu(sf::RenderWindow* win)
{
    while (win->isOpen())
    {
        // Закрытие окна
        while (win->pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                win->close();
        }

        win->clear();
        win->display();
    }
    
} 

lvl_1::~lvl_1()
{

}
