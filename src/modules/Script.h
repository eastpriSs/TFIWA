/*
*
*   Модуль для разгрузки классов lvl   
*   - Реализует функции над объектами         
*
*
*
*/

#include <SFML/Graphics.hpp>

namespace ScriptModule
{

    class Script
    {

    public:    

        static bool is_pressed_F();
        static bool is_pressed_E();
        static void wait_mlsec(const short& );

        template<typename T>
        static void set_color(T&, short&&,
                                  short&&,
                                  short&& );
        
        static void set_color(sf::Sprite&, short&&,
                                           short&&,
                                           short&& );


        template<typename T>
        static void visibility(T&, const short&);

        template<typename T>
        static void repaint_white(T&);

        template<typename T>
        static void repaint_grey(T&);

    private:
        Script() = default;    
    };

} // namespace ScriptModule



// Определение находиться здесь во избежание явного истанцирования 
template<typename T>
void ScriptModule::Script::visibility(T& obj, const short& trns)
{
    obj.setFillColor(sf::Color(   obj.getFillColor().r, 
                                  obj.getFillColor().g, 
                                  obj.getFillColor().b,
                                  trns ));
}

template<typename T>
void ScriptModule::Script::repaint_white(T& obj)
{
    obj.setFillColor(sf::Color::White);
}


template<typename T>
void ScriptModule::Script::repaint_grey(T& obj)
{
    obj.setFillColor(sf::Color(60,60,60, obj.getFillColor().a));
}


template<typename T>
void  ScriptModule::Script::set_color(T& obj, short&& r,
                                              short&& g,
                                              short&& b) 
{
    obj.setFillColor(sf::Color(r,g,b, obj.getFillColor().a));                   
}   