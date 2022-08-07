#include "lvl_1.h"

using namespace LVL_ONE;

lvl_1::lvl_1() // 25,25,25,218
: win_back_clr(26,67,50,255)
{
    main_filter->setPosition(_near_table_s-300, 0); // Изначально
    main_filter->setFillColor(sf::Color(243,110,1,0));
}

void lvl_1::_make_outside()
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
    using ScriptModule::Script;

    std::unique_ptr<CenterDialog> cntr_d( new CenterDialog() );
    
    cntr_d->set_font("fonts/1.ttf");
    cntr_d->create_text(
    L"Скрытое в отце проявляется в сыне, и часто в сыне я нахожу ответы на загадки отца. Ф. Ницше", 20);
     
    cntr_d->get_txt_var().setCharacterSize(75);

    Script::set_color(cntr_d->get_txt_var(), 60,60,60);

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
        Script::wait_mlsec(delay_transparency);
        Script::visibility(cntr_d->get_txt_var(), transparency);
        transparency -= 3; 

        w.clear(win_back_clr);
        w.draw(cntr_d->txt_var());
        w.display();
    }
    
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

const short lvl_1::_check_area_player() 
// Отслеживание игрока по карте
{ 
    if ( mnc->x() > _house_door_area_s && 
         mnc->x() < _house_door_area_e    ) return AREAS::HOUSE_DOOR;

	else if ( mnc->x() > _near_table_s && 
			  mnc->x() < _near_table_e    ) return AREAS::NEAR_TABLE;
	
    else if (mnc->x() > _untitled_house_s)  return AREAS::HOUSE_UNTITLED;
	
    else return AREAS::UNTITLED;
    
}


void lvl_1::_check_active()
{
    using ScriptModule::Script;

    static short stage_dialog    = 1; 
    const short transparency     = 200;

    // Только если в обычном сценарии
    // для финального свои инструкции
    if (_final_stage == false) {
        
        switch (_check_area_player())
        {
        
        case AREAS::HOUSE_DOOR:
            down_d->create_text(L"Нажать Е..", mnc->x(), 320);
            if ( Script::is_pressed_E() )
            {
                _clear_map();   
                _make_house_inside();
                CameraKit::Camera::set_cmr_locks(1700, 2200);
            }
        break;
        
        case AREAS::HOUSE_UNTITLED:
            uppr_d->create_text(L"И тут ворвался Апраам, но кто тебя звал?", mnc->x(), 0);
        break;

        case AREAS::NEAR_TABLE:
            
            if (!_final_stage) // Костыль(
                mnc->set_speed(0); // Останавливаем персонажа
    
            if (stage_dialog == 2)
            {
                if ( Script::is_pressed_F() ) 
                    uppr_d->create_text(L"Зачем ты клонишь диалог к лести? Я же знаю. Уходи отсюда, слышишь меня? Вон. Я тебе дам денег, раз уж так надо.", mnc->x()-100, 0);
                
                else if ( Script::is_pressed_E() ) {
                    uppr_d->create_text(L"Человек-льстец виртуозен и самовлюблен. Уходи отсюда, слышишь меня? Вон. Я тебе дам денег, раз уж так надо.", mnc->x()-100, 0);
                    mnc->money -= 70;
                }
                down_d->create_text(L"Спасибо, пап..", mnc->x()-70, 320);

                _n_play_clip = true; // Проиграть клип  
                stage_dialog = 3;    
            }
            else if (stage_dialog == 1) 
            { 
                uppr_d->create_text(L"Ты что-то забыл Апраам?", mnc->x()-30, 0);
                
                Script::visibility(down_d->get_txt_var(), transparency);	
                Script::set_color(down_d->get_txt_var(), 60,60,60);
                
                down_d->create_text(L"[E] Мне нужно извиниться перед вами. \t [F] Я забыл сказать спасибо вам.", mnc->x()-70, 320);     
            }

            if ( (Script::is_pressed_E()  || 
                Script::is_pressed_F()) && 
                stage_dialog == 1 ) stage_dialog = 2;
            
            if ( Script::is_pressed_E() && stage_dialog == 0 )  stage_dialog = 1;
            
        break;

        }    
    }
}

void lvl_1::_final_stage_script()
{
    static short transparency_objs = 0;
    mnc->set_speed(mnc->default_speed);
    // Выполняем один раз
    if ( _alloc->list_objs_on_map->empty() )
        _make_outside();
    
    objects_visidility = transparency_objs;
    
    if (transparency_objs < 100)
        transparency_objs++;     
}

// Используется в цикле
void lvl_1::_play_clip() 
{
    using ScriptModule::Script;
    
    static short transparency_rect = 0;
    static short transparency_txt  = 255;
    
    transparency_rect += 1;
    transparency_txt  -= 1;

    // Script::wait_mlsec(200);
    
    switch (transparency_rect)
    {
   
    case 250:
        mnc->set_x(2200);
        Script::repaint_white(uppr_d->get_txt_var());
        Script::visibility(uppr_d->get_txt_var(), 255);
        Script::visibility(down_d->get_txt_var(), 0);
        uppr_d->create_text(
        L"..Брат выгоняет взгядом меня, Отец спроваживает словом!\nИз раза в раз спотыкаюсь от боли. \nПадаю, утопаю, во мрак недовольства собою.\nЯ ничего им не сделал плохого...\n\n\n\t\tОтрывок из \"Монструозность\" 1965г. автор: Ночь(урожд. Неер) Апраам М.", mnc->x()-50, 140);
    break;
    
    case 140: 
        Script::repaint_grey(  uppr_d->get_txt_var());
        Script::repaint_white( down_d->get_txt_var());
        down_d->create_text(
        L"Спасибо, пап?.. За что 'спасибо' ?", mnc->x()-70, 320);    
    break;
   
    }

    if (transparency_rect < 140)
        Script::visibility(uppr_d->get_txt_var(), transparency_txt);
   
    Script::visibility(*main_filter, transparency_rect);
    
    if (transparency_rect >= 255) { 
        _clear_map(); 
        transparency_rect = 0;
        _n_play_clip = false;
        _final_stage = true;
    }
}

inline void lvl_1::_draw_objects( sf::RenderWindow& win) {
    // Отрисовка объектов на карте 
    for(auto i = _alloc->list_objs_on_map->begin();
                i != _alloc->list_objs_on_map->end(); ++i)
    {
        if (objects_visidility != 255) 
            ScriptModule::Script::visibility(*i->spr, objects_visidility );

        i->play_animation();
        win.draw(*i->spr);

    }// Поледний объект(фильтер) упускается, так как, он должен быть выше игрока    
}

void lvl_1::draw_menu(sf::RenderWindow& win)
{
    using CameraKit::Camera;

    // _play_intro(win);
    
    // Объекты
    _make_outside();

    // Камера
    Camera::init(win);   
    Camera::reset_review();
    Camera::set_cmr_locks(20, 1750);
    
    bool isDialogNeed = 0;
	
	uppr_d->set_font("fonts/1.ttf");
    down_d->set_font("fonts/1.ttf");

    while (win.isOpen())
    {
        // Закрытие окна
        while (win.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                win.close();
        }

        win.clear(win_back_clr); 

        _draw_objects(win);
        
        if (_check_area_player()) // Отрисока диалогов, если нужно
        {
            _check_active();
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
        
        // Затмить экран для клипа 
        if (_n_play_clip) 
        { 
            _play_clip();
            win.draw(*main_filter);
        }

        if (_final_stage)
        {
            CameraKit::Camera::set_cmr_locks(20,2260);
            _final_stage_script();
        }

        win.display();
    }
    
} 

lvl_1::~lvl_1()
{
    delete _alloc;
}
