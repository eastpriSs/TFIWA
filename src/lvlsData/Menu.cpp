
/*

////////////////////////////////////////

Главный поддрайвер, имеет доступ ко всем lvl и может запускать их
согласно сценарию      

////////////////////////////////////////

*/

#include <iostream>
#include "Menu.h"

using namespace MENU_INTERFACE;

Menu::Menu(const short curr_lvl) try
{
    // Инвариант 
    if (((curr_lvl > 0) && (curr_lvl < 10)) == false)
        throw std::out_of_range("Menu::_current_lvl have range 0 to 10.");  

    _current_lvl = curr_lvl; 
}
catch(const std::out_of_range& e)
{
    std::cerr << e.what() << '\n';
}

void Menu::take_memory()
{
    using namespace ALLOCATOR;
    short size_of_sprite[2]{128,128};
    
    // ------* Задний фон & Туман *------------------------------------------
    Object_map background("image/test.png", 0, 20);
    Object_map fog("image/fog.png", 0, 70);
    // Параметры объекта: NULL
    
    // ------------------------------------------------------------

    // ------* Скрипач *---------------------------------------------
    Object_map npc_violin("image/TestViol.png", 310, 192);
    // Параметры объекта: 
    npc_violin.set_texture_rect(size_of_sprite[0],size_of_sprite[1]);
    
    // ------------------------------------------------------------

    // ------* Нота & Тень от ноты *---------------------------------------------
    Object_map nota("image/Nota.png", 445, 70);
    Object_map shadow_of_nota("image/ShadowOfNota.png", 405, 45);
    // Параметры объекта: 
    nota.set_texture_rect(64,64);
    
    // ------------------------------------------------------------

    // Добаляем в список объектов для отрисовки 
    _alloc.list_objs_on_map->push_back(std::move(background));
    _alloc.list_objs_on_map->push_back(std::move(npc_violin));
    _alloc.list_objs_on_map->push_back(std::move(nota));
    _alloc.list_objs_on_map->push_back(std::move(shadow_of_nota));
    _alloc.list_objs_on_map->push_back(std::move(fog));
}

void Menu::draw_menu(RenderWindow* win)
{
    using namespace ALLOCATOR;
    take_memory();
    // Ограничение FPS под уровень.
    win->setFramerateLimit(30);

    sf::Event event;
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(150, 50, 250));

    while (win->isOpen())
    {
        while (win->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win->close();
        }

       win->clear(sf::Color(25,25,25,218)); 
       
        // Отрисовка обхектов на карте 
        for (Object_map i: *_alloc.list_objs_on_map ) 
            win->draw(*i.spr);   

        win->draw(shape);
        
        if ( shape.getPosition() == sf::Vector2f(100,100) ) _is_shape_move_back = false;
        if ( shape.getPosition() == sf::Vector2f(600,600) ) _is_shape_move_back = true;
        (_is_shape_move_back)?shape.move(-1,-1):shape.move(1,1); 

        win->display();
    }
}

Menu::~Menu(){

}