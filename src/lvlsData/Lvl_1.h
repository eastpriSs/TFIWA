/*

////////////////////////////////////////

Модуль, отвечающий за сценарий первого уровня. 

////////////////////////////////////////

*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Allocator.h"
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\MainCharacter.h"
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Dialog.h"
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Camera.h"
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Script.h"


namespace LVL_ONE
{

    using ALLOCATOR::Allocator;
    using DialogManager::CenterDialog;
    using DialogManager::UpperDialog;
    using DialogManager::DownDialog; 
    using sf::RectangleShape;

    class lvl_1
    {

    public:

        // Главный цикл
        void draw_menu(sf::RenderWindow&);
        
        lvl_1(/* args */);
        ~lvl_1();

    private:
            
        UpperDialog    *uppr_d      = new UpperDialog;
        DownDialog     *down_d      = new DownDialog;
        RectangleShape *main_filter = new RectangleShape(sf::Vector2f(700,340));  
        MainCharacter  *mnc         = new MainCharacter("image/Lamp.png", 20,300);

        void        _draw_objects( sf::RenderWindow& );
        const short _check_area_player();
        void        _play_intro(sf::RenderWindow&);
        void        _take_memory();        
        void        _make_house_inside();
        void        _clear_map();   
        void        _check_active();
        void        _play_clip();

        // Areas
        const short _house_door_area_s = 1700;
        const short _house_door_area_e = 1750;

        const short _untitled_house_s  = 2000;  

		const short _near_table_s 	   = 2100;
		const short _near_table_e 	   = 2260;

        bool _n_play_clip = false;

        enum AREAS{
            UNTITLED   = 0,
            HOUSE_DOOR = 3,
        	NEAR_TABLE = 4,
            HOUSE_UNTITLED = 5
		};

        sf::Clock _cl;
        sf::Event _event;            
        Allocator *_alloc = new Allocator;

    };
    

} // namespace LVL_ONE
