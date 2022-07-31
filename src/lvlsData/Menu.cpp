
/*

////////////////////////////////////////

Главный поддрайвер, имеет доступ ко всем lvl и может запускать их
согласно сценарию      

////////////////////////////////////////

*/

#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"

using namespace MENU_INTERFACE;
using std::pair;
using std::make_pair;

// Думаю, что спрайты будут меняться и это предельно важно
// отправлять правилбный аргумент, порядковый номер уровня 
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

void Menu::_take_memory()
{
    using namespace ALLOCATOR;

    // ------* BACKGROUND *------------------------------------------
    
    // Задний фон
    Object_map *background = new Object_map("image/test.png", 0, 20);
    // Параметры объекта: NULL

    // Дождь
    Object_map *rain = new Object_map("image/Rain.png", 0, 20);
    // Параметры объекта: NULL

    // Капли дождя
    Object_map *rain_drops = new Object_map("image/RainDrops.png", 0, 10);
    
    // Значения:
    pair<short,short> dir_move = make_pair(0,15); // Направление и скорость движения
    pair<short,short> end_move = make_pair(0,85); // Конечные координаты

    // Параметры объекта:
    rain_drops->set_move_animation(dir_move, end_move);

    // ------------------------------------------------------------


    // ------* NPC *---------------------------------------------
    
    // Скрипач
    Object_map *npc_violin = new Object_map("image/ViolT.png", 310, 192);
    
    // Значения:
    const pair<short,short> size_of_sprite = make_pair(128,128);
    const short amount_frames = 5;

    // Параметры объекта: 
    npc_violin->set_texture_rect(size_of_sprite.first, size_of_sprite.second);
    npc_violin->set_frames_animation(amount_frames, size_of_sprite);

    // ------------------------------------------------------------


        /* """"""""""""""""""""""""""

            Сценарий отрисовки:
            1 Фон - НИЖЕ ВСЕХ
            2 Скрипач
            3 Капли дождя с анимацией движения
            4 Дождь - можно сказать фильтер для красоты    
                      и ощущения пасмурности. ВЫШЕ ВСЕХ

         """""""""""""""""""""""""" */


    // Добаляем в список объектов для отрисовки 
    _alloc->list_objs_on_map->push_back(std::move(*background));
    _alloc->list_objs_on_map->push_back(std::move(*npc_violin));
    _alloc->list_objs_on_map->push_back(std::move(*rain_drops));
    _alloc->list_objs_on_map->push_back(std::move(*rain));
}


bool wait_button_on_pos(const short area )
// При определенных координатах ожидает нажатие
// соответсвующей клавиши
// Действие при нажатии определяется сценарием игры
{
    using sf::Keyboard;

    switch (area)
    {
    case 3: // Позиция игрока у стола
        if (Keyboard::isKeyPressed(Keyboard::E))
        {
            return true;
        }
    break;
    }
    return false;
}

void Menu::draw_menu(RenderWindow& win)
{
    using CameraKit::Camera;
    using namespace ALLOCATOR;
    using namespace DialogManager;

    // Выделения памяти под объекты на карте
    _take_memory();
    
    // Параметры:
    upper_frame_display->setPosition(0,0);
    upper_frame_display->setFillColor(sf::Color(25,25,25,255));
    
    // Параметры:
    down_frame_display->setPosition(0,320);
    down_frame_display->setFillColor(sf::Color(25,25,25,255));
    // ------------------------------
    
    
    // Параметры uppr_d:
    uppr_d->set_font("fonts/1.ttf");
    
    // Параметры down_d:
    down_d->set_font("fonts/1.ttf");
    // ------------------------------
    
    // Параметры:
    Camera::reset_review();
    Camera::set_cmr_locks(0, 1150);

    // Главный цикл игры:
    while (win.isOpen())
    {
        // Закрытие окна
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        // Получаем миллисекунды
        anim_time = cl.getElapsedTime().asMilliseconds();

        // Серые линии сверху, снизу
        win.clear(sf::Color(25,25,25,218)); 

        /* """"""""""""""""""""""""""

            Сценарий отрисовки:
            1 Рисока объектов согласно добавлению их в список   
            2 Линии сверху и снизу
            3 Игрок
            4 Диалоги

         """""""""""""""""""""""""" */

        // Отрисовка объектов на карте 
        for(auto i = _alloc->list_objs_on_map->begin(); 
                        i != _alloc->list_objs_on_map->end(); ++i)
        {
            i->play_animation(600, anim_time); // Задержка
            win.draw(*i->spr);
        }

        
        // Отрисовка линий сверху и снизу        
        win.draw(*upper_frame_display);
        win.draw(*down_frame_display);

        // Игрок
        win.draw(mnc->get_sprite());
        
        // Отслеживание нажатий клавиш для картинки игрока:
        mnc->control();

        // Избижать выход за карту
        if ( mnc->x() == _left_wall ) mnc->move_right(); // Если дошли до левого предела
        if ( mnc->x() == _right_wall ) mnc->move_left();  // Если дошли до правого предела
        // --------------------------

        // Камера за игроком
        Camera::set_cmr_view( mnc->x(), mnc->y() );
        Camera::init(win);
        //----------------------------

        // Диалоги
        
        // Скрипач _viol_area
        if ( mnc->x() > _viol_area_start && mnc->x() < _viol_area_end ) 
        {
            uppr_d->create_text(L"Здравствуй, Я Оскар. Могу играть хоть вечность.",
                                                        mnc->x(), 0);
            down_d->create_text(L"Нажать Е\b , чтобы прибавить громкость в игре.", 
                                                        mnc->x()-25, 320);
            isDialogNeed = true;
        }
        // Позиция не дойдя до стола _near_table
        else if(mnc->x() > _near_table_start && mnc->x() < _near_table_end) 
        {
            uppr_d->create_text(L"Конец музыки и утомление дождя. До сих пор ли стоит там этот скрипач?", 
                                                        mnc->x()-25, 0);  
            down_d->create_text(L"");                                                                                          
            isDialogNeed = true;
        } 
        //  Позиция у стола  _table
        else if (mnc->x() > _table_start && mnc->x() < _table_end) 
        {
            uppr_d->create_text(L"Вот и конец твоим скитаниям, Апраам, не пора ли их поведать нам?", 
                                                        mnc->x()-65, 0);                                                                
            down_d->create_text(L"Нажать Е , чтобы взяться за текст", mnc->x()-50, 320);
            // Ждем нажатия (ВЫХОД С УРОВНЯ)
            if (wait_button_on_pos(TABEL)) return; 
            isDialogNeed = true;
        }
        else // В любом другом месте
        {
            isDialogNeed = false;
        }

        if (isDialogNeed) // Отрисока диалогов, если нужно
        {
            win.draw(uppr_d->txt_var());
            win.draw(down_d->txt_var());
        }

        win.display();

        // Обнуляем таймеры:
        if ( anim_time > _anim_delay) cl.restart(); // После каждых _anim_delay миллисекунд 
    }
}

Menu::~Menu()
{  
    // Очитка памяти.
    // Заполнено 45.5
    // После 41.
    
    delete mnc;
    delete down_d;
    delete uppr_d;
    delete cntr_d;
    delete _alloc->list_objs_on_map;
    delete _alloc;  
    
}