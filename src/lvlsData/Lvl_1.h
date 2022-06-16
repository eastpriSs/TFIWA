/*

////////////////////////////////////////

Модуль, отвечающий за сценарий первого уровня. 

////////////////////////////////////////

*/


#include <SFML/Graphics.hpp>

namespace LVL1_PRIVATE
{
    
} // namespace LVL_PRIVATE


namespace LVL_ONE
{

    class lvl_1
    {

    public:

        // Главный цикл
        void draw_menu(sf::RenderWindow*);
        
        lvl_1(/* args */);
        ~lvl_1();

    private:
        
        sf::Event _event;            

    };
    

} // namespace LVL_ONE
