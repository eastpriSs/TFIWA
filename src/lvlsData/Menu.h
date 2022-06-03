/*

////////////////////////////////////////

Главный поддрайвер, имеет доступ ко всем lvl и может запускать их
согласно сценарию      

////////////////////////////////////////

*/


#include <SFML/Graphics.hpp>
#include "D:\WORKONIT\cpp_experience\The_forest_in_which_we_will_all___V1.0\src\modules\Allocator.h"

namespace MENU_PRIVATE // Закрытый, для разработки
{ 

    
} // MenuPrivate

namespace MENU_INTERFACE // Открытый, для пользователя 
{
    using sf::RenderWindow;
    using ALLOCATOR::Allocator;

    class Menu
    {
    
    public:
        Menu(short);
        ~Menu();

        void take_memory();
        void draw_menu(RenderWindow* );

    private:
        RenderWindow _win;
        Allocator    _alloc;
        short        _current_lvl;
        bool        _is_shape_move_back;
        _lvl_next();

    };

} // Menu