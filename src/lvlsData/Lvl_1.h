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


namespace LVL1_PRIVATE
{

class LvlFunc
{

public:
    operator=(LvlFunc&) = delete;    
    static bool wait_button_on_pos(const short); 

private:
    LvlFunc() = default;

};

} // namespace LVL_PRIVATE


namespace LVL_ONE
{

    using ALLOCATOR::Allocator;
    using DialogManager::CenterDialog;
    using DialogManager::UpperDialog;
    using DialogManager::DownDialog; 

    class lvl_1
    {

    public:

        // Главный цикл
        void draw_menu(sf::RenderWindow&);
        
        lvl_1(/* args */);
        ~lvl_1();

    private:
            
        UpperDialog  *uppr_d = new UpperDialog;
        DownDialog   *down_d = new DownDialog;
        
        MainCharacter *mnc = new MainCharacter("image/Lamp.png", 20,300);

        void _play_intro(sf::RenderWindow&);
        void _take_memory();        
        void _make_house_inside();
        void _clear_map();   

        // Areas
        const short _house_door_area_s = 1700;
        const short _house_door_area_e = 1750;


        enum AREAS{
            HOUSE_DOOR = 3
        };

        sf::Clock _cl;
        sf::Event _event;            
        Allocator *_alloc = new Allocator;

    };
    

} // namespace LVL_ONE
