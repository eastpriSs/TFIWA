
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
    _alloc.list_objs_on_map->push_back(std::move(*background));
    _alloc.list_objs_on_map->push_back(std::move(*npc_violin));
    _alloc.list_objs_on_map->push_back(std::move(*rain_drops));
    _alloc.list_objs_on_map->push_back(std::move(*rain));
}


void set_cmr_view(sf::View& vw, const short x, const short y)
/* 
    Предполагается, что камера не всегда будет
   следовать за игроком, собственно нам нужно
   убедиться, что при данных координатах игрока
   нам нужно передвинуть камеру. Как раз для этого
   создана функция, а не использован напрямую
   метод setCenter 

*/ 
{
    if (x < 250 || x > 1150) return; // Исключаем возможность камера вы ходить за пределы
    vw.setCenter(x,y-130);
}


void wait_button(const short area, sf::RenderWindow& wn, 
                ALLOCATOR::Allocator& mmr )
// При определенных координатах ожидает нажатие
// соответсвующей клавиши
// Действие при нажатии определяется сценарием игры
{
    using sf::Keyboard;

    switch (area)
    {
    case 3: // Позиция игрока у стола
        // По сценарию переход на следующий уровень( которого нет)
        if (Keyboard::isKeyPressed(Keyboard::E))
        {
            for(auto i = mmr.list_objs_on_map->begin(); 
                        i != mmr.list_objs_on_map->end(); ++i)
            {
                i->spr->setRotation(10);
            }
            // wn.close();
        }

    break;
    
    default:
        break;
    }
}

void Menu::draw_menu(RenderWindow* win)
{
    using namespace ALLOCATOR;
    using namespace DialogManager;

    // Выделения памяти под объекты на карте
    _take_memory();
    
    // Ограничение FPS под уровень.
    win->setFramerateLimit(30);
    
    // Линии сверху и снизу экрана
    sf::RectangleShape *upper_frame_display = new sf::RectangleShape(sf::Vector2f(800, 20));
    sf::RectangleShape *down_frame_display  = new sf::RectangleShape(sf::Vector2f(800, 20));
    
    // Параметры:
    upper_frame_display->setPosition(0,0);
    upper_frame_display->setFillColor(sf::Color(25,25,25,255));
    
    // Параметры:
    down_frame_display->setPosition(0,320);
    down_frame_display->setFillColor(sf::Color(25,25,25,255));
    // ------------------------------

    // Игрок
    MainCharacter *mnc = new MainCharacter("image/Lamp.png", 20,300);
    // ------------------------------

    // Диалоги
    CenterDialog *cntr_d = new CenterDialog; // Для фразы в начале уровня
    UpperDialog  *uppr_d = new UpperDialog;
    DownDialog   *down_d = new DownDialog;
    
    // Параметры uppr_d:
    uppr_d->set_font("fonts/1.ttf");
    
    // Параметры down_d:
    down_d->set_font("fonts/1.ttf");
    // ------------------------------

    sf::Event event;
    
    sf::View cmr; // Камера за игроком
    // Параметры:
    cmr.reset(sf::FloatRect(0,0,500,340));
    
    sf::Clock cl; // Счетчик милисекунд
    short anim_time;
    bool isDialogNeed = false;
    
    // Главный цикл игры:
    while (win->isOpen())
    {
        while (win->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win->close();
        }

        // Получаем милисекунды
        anim_time = cl.getElapsedTime().asMilliseconds();

        // Серые линии сверху, снизу
        win->clear(sf::Color(25,25,25,218)); 

        /* """"""""""""""""""""""""""

            Сценарий отрисовки:
            1 Рисока объектов согласно добавлению их в список   
            2 Линии сверху и снизу
            3 Игрок
            4 Диалоги

         """""""""""""""""""""""""" */

        // Отрисовка объектов на карте 
        for(auto i = _alloc.list_objs_on_map->begin(); 
                        i != _alloc.list_objs_on_map->end(); ++i)
        {
            i->play_animation(600, anim_time); // Задержка
            win->draw(*i->spr);
        }

        
        // Отрисовка линий сверху и снизу        
        win->draw(*upper_frame_display);
        win->draw(*down_frame_display);

        // Игрок
        win->draw(mnc->get_sprite());
        
        // Отслеживание нажатий клавиш для картинки игрока:
        mnc->control();

        // Избижать выход за карту
        if ( mnc->x() == 20 ) mnc->move_right(); // Если дошли до левого предела
        if (mnc->x() == 1270) mnc->move_left();  // Если дошли до правого предела
        // --------------------------

        // Камера за игроком
        set_cmr_view(cmr, mnc->x(), mnc->y() );
        win->setView(cmr);
        //----------------------------

        // Диалоги
        
        // Скрипач
        if ( mnc->x() > 320 && mnc->x() < 350 ) 
        {
            uppr_d->create_text(L"1", mnc->x(), 0);
            down_d->create_text(L"2", mnc->x()-25, 320);
            isDialogNeed = true;
        }
        // Позиция не дойдя до стола
        else if(mnc->x() > 1050 && mnc->x() < 1130) 
        {
            uppr_d->create_text(L"3", 
                                mnc->x()-25, 0);  
            down_d->create_text(L"");                                                                                              
            isDialogNeed = true;
        } 
        //  Позиция у стола // AREA 3
        else if (mnc->x() > 1200 && mnc->x() < 1270) 
        {
            uppr_d->create_text(L"... Апраам", 
                                mnc->x()-65, 0);                                                                
            down_d->create_text(L"Нажать Е ... ", mnc->x()-50, 320);
            // Ждем нажатия
            wait_button(3, *win, _alloc); 
            isDialogNeed = true;
        }
        else // В любом другом месте
        {
            isDialogNeed = false;
        }
        

        if (isDialogNeed) // Отрисока диалогов, если нужно
        {
            win->draw(uppr_d->txt_var());
            win->draw(down_d->txt_var());
        }

        win->display();

        // Обнуляем таймеры:
        if ( anim_time > 600) cl.restart(); // После каждых anim_time милисекунд 
    }
}

Menu::~Menu()
{    
}