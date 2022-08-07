#include "Script.h"

using namespace ScriptModule;

bool Script::is_pressed_F()
{
    using sf::Keyboard;

    if (Keyboard::isKeyPressed(Keyboard::F))
    {
        return true;
    } 
    return false; 
}

bool Script::is_pressed_E()
{
    using sf::Keyboard;

    if (Keyboard::isKeyPressed(Keyboard::E))
    {
        return true;
    } 
    return false;    
}

void Script::wait_mlsec(const short& mlseconds )
{
    sf::sleep(sf::milliseconds(mlseconds));
}

void Script::set_color(sf::Sprite& obj, short&& r,
                                        short&& g,
                                        short&& b) 
{
    obj.setColor(sf::Color(r,g,b, obj.getColor().a));                   
}

void Script::visibility(sf::Sprite& obj, const short& trns)
{
    obj.setColor(sf::Color(   obj.getColor().r, 
                              obj.getColor().g, 
                              obj.getColor().b,
                              trns ));
}
