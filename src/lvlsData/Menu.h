/*

////////////////////////////////////////

Главный поддрайвер, имеет доступ ко всем lvl и может запускать их
согласно сценарию      

////////////////////////////////////////

*/


#include <SFML/Graphics.hpp>
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Allocator.h"
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\MainCharacter.h"
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Dialog.h"


namespace MENU_PRIVATE // Закрытый, для разработки
{ 

    
} // MenuPrivate

namespace MENU_INTERFACE // Открытый, для пользователя 
{

    using sf::RenderWindow;
    using ALLOCATOR::Allocator;
    using DialogManager::CenterDialog;
    using DialogManager::UpperDialog;
    using DialogManager::DownDialog;

class Menu
{
    
public:

    Menu(short);
    ~Menu();
        
void draw_menu(RenderWindow* );

private:

    sf::Event event;
    
    sf::View cmr; // Камера за игроком

    // Линии сверху и снизу экрана
    sf::RectangleShape *upper_frame_display = new sf::RectangleShape(sf::Vector2f(800, 20));
    sf::RectangleShape *down_frame_display  = new sf::RectangleShape(sf::Vector2f(800, 20));

    // Игрок
    MainCharacter *mnc = new MainCharacter("image/Lamp.png", 20,300);
    

    // Диалоги
    CenterDialog *cntr_d = new CenterDialog;
    UpperDialog  *uppr_d = new UpperDialog;
    DownDialog   *down_d = new DownDialog;
            
    // Память
    Allocator    *_alloc =  new Allocator;
            

    sf::Clock cl; // Счетчик милисекунд
    short anim_time;
    bool isDialogNeed = false;

    short        _current_lvl;
    bool         _is_shape_move_back;
    void _take_memory();


};

} // Menu