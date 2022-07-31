#include "lvl_1.h"

using namespace LVL_ONE;
using namespace LVL1_PRIVATE;

lvl_1::lvl_1()
{

}

void lvl_1::_take_memory()
{
    using ALLOCATOR::Object_map;
    // 1400x300
    Object_map *background = new Object_map("image/lvlOneBackground.png",
                                            0, 20);
    // 700x300
    Object_map *house = new Object_map("image/houseLvlOne.png",
                                            1400, 20);   
    // 2100x300
    Object_map *filter = new Object_map("image/filterLvlOne.png",
                                            0, 20);                                                                                  

    _alloc->list_objs_on_map->push_back(std::move(*background));
    _alloc->list_objs_on_map->push_back(std::move(*house));
    _alloc->list_objs_on_map->push_back(std::move(*filter));
} 



void lvl_1::_play_intro(sf::RenderWindow& w )
/*

Проигрывает интро с надписью по центру

*/

{
    std::unique_ptr<CenterDialog> cntr_d( new CenterDialog() );
    
    cntr_d->set_font("fonts/1.ttf");
    cntr_d->create_text(
    L"Скрытое в отце проявляется в сыне, и часто в сыне я нахожу ответы на загадки отца. Ф. Ницше", 20);
     
    cntr_d->get_txt_var().setCharacterSize(75);

    short transparency       = 255;  
    short delay_transparency = 120;

    while (w.isOpen())
    {
        while (w.pollEvent(_event)){
            if (_event.type == sf::Event::Closed) 
                w.close();    
        }

        // Если надпись пропала, полный ВЫХОД
        if ( transparency <= 0 ) break; 
        
        // Тускнеет надпись с задержкой delay_transparency
        sf::sleep(sf::milliseconds(delay_transparency));
        cntr_d->get_txt_var().setFillColor(sf::Color(60,60,60, transparency));
        transparency -= 3; 

        w.clear(sf::Color(0,0,0,255));
        w.draw(cntr_d->txt_var());
        w.display();
    }
    
} 

bool LvlFunc::wait_button_on_pos(const short area)
{
    using sf::Keyboard;

    switch (area)
    {
    case 3: // Позиция игрока у дома, у двери
        if (Keyboard::isKeyPressed(Keyboard::E))
        {
            return true;
        }
    break;
    }
    return false;    
}

void lvl_1::_make_house_inside()
// Заполнение списка объектов снова
{
    using ALLOCATOR::Object_map;

    Object_map *filter = new Object_map("image/filterHouse.png",
                                            1700, 20);

    Object_map *angel = new Object_map("image/AngelTest.png",
                                            1900, 240);


    Object_map *father = new Object_map("image/father.png",
                                            2300, 240);

    Object_map *lamp_light = new Object_map("image/LampLight.png",
                                            1955, 80);
    lamp_light->set_resize_animation();

    Object_map *background_house = new Object_map("image/backgroundHouse.png",
                                            1700, 20);

    
    _alloc->list_objs_on_map->push_back(std::move(*background_house));
    _alloc->list_objs_on_map->push_back(std::move(*father));
    _alloc->list_objs_on_map->push_back(std::move(*angel));
    _alloc->list_objs_on_map->push_back(std::move(*lamp_light));
    _alloc->list_objs_on_map->push_back(std::move(*filter));                                            
}

inline void lvl_1::_clear_map()
{
    _alloc->list_objs_on_map->erase(
                            _alloc->list_objs_on_map->begin(),
                            _alloc->list_objs_on_map->end());
}

void lvl_1::draw_menu(sf::RenderWindow& win)
{
    using CameraKit::Camera;

    // _play_intro(win);
    
    // Объекты
    _take_memory();

    // Камера
    Camera::init(win);   
    Camera::reset_review();
    Camera::set_cmr_locks(20, 1750);
    
    bool isDialogNeed = 0;

    down_d->set_font("fonts/1.ttf");

    while (win.isOpen())
    {
        // Закрытие окна
        while (win.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                win.close();
        }

        win.clear(sf::Color(25,25,25,218)); 

        // Отрисовка объектов на карте 
        for(auto i = _alloc->list_objs_on_map->begin();
                i != _alloc->list_objs_on_map->end(); ++i)
        {
            i->play_animation();
            win.draw(*i->spr);

        }// Поледний объект(фильтер) упускается, так как, он должен быть выше игрока


        // Отслеживание игрока по карте 
        if ( mnc->x() > _house_door_area_s && 
             mnc->x() < _house_door_area_e    )
        {
            down_d->create_text(L"Нажать Е ..", mnc->x()-1, 320);

            if (LvlFunc::wait_button_on_pos(HOUSE_DOOR))
            {
                _clear_map();   
                _make_house_inside();
                Camera::set_cmr_locks(1700, 2200);
            }

            isDialogNeed = true;
        }
        else
        {
            isDialogNeed = false;
        }
        
        
        if (isDialogNeed) // Отрисока диалогов, если нужно
        {
            win.draw(uppr_d->txt_var());
            win.draw(down_d->txt_var());
        }

        // Камера
        Camera::set_cmr_view( mnc->x(), mnc->y() );
        Camera::init(win);

        // Управление игрока
        mnc->control();

        win.draw(mnc->get_sprite());
        
        if (_alloc->list_objs_on_map->size() > 0)
            win.draw(*_alloc->list_objs_on_map->back().spr); // Фильтер
        
        win.display();
    }
    
} 

lvl_1::~lvl_1()
{

}
