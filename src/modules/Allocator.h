/*

////////////////////////////////////////

Модуль представляет тип Object_map, этот тип имеет
анимацию, параметры, может быть размещен на карте.
Добавляет в лучшем случае 5( не рекомендуется больше ) 
таких объектов в обзор игрока, когда обзор сдвигается,
выделенная память под объекты используется для
отрисовки других, уже входящий в поле зрения игрока
объектов. 

////////////////////////////////////////

*/

#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ALLOCATOR_PRIVATE
{

using sf::Image;
using sf::Texture;
using sf::Sprite;

class Object_map
{

public:

    Image   *img = new Image;
    Texture *tex = new Texture;
    Sprite  *spr = new Sprite;
    // Аргументы: путь к файлу, позиция спрайта x y
    Object_map(const std::string&, const short, const short);
    // Хранит размер спрайта и устанавливает его
    void set_texture_rect(const short, const short);
    ~Object_map();
    // operator new(); // Нужно перегрузить
private:
    void save_texture_rect(const short, const short);
    short _last_position_tex_rect[2]{0,0};
};    

} // namespace ALLOCATOR_PRIVATE


namespace ALLOCATOR
{

using ALLOCATOR_PRIVATE::Object_map;

class Allocator
{

public:

    Allocator();
    ~Allocator();

    std::list<Object_map> *list_objs_on_map = new std::list<Object_map>;

private:

};

} // namespace ALLOCATOR
