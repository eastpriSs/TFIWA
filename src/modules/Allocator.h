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

#pragma once 
namespace ALLOCATOR_PRIVATE
{

using std::pair;
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
    
    // Сохраняет параметры для проигрывания апнимации
    // средством передвижения спрайта
    void set_move_animation( const pair<short,short>&,
                             const pair<short,short>&,
                             short repeat = -1
                           );

    // Сохраняет параметры для проигрывания апнимации
    // средством смены кадра спрайта
    void set_frames_animation(short, 
                              const pair<short,short>& );

    void set_resize_animation();

    // Проигрывает анимацию
    // Первй - задержка секунд между анимациями
    // Второй аргумент милисекунды
    void play_animation(const short dalay = 0, const short tme = 0);

    ~Object_map();
    // operator new(); // Нужно перегрузить

private:

    // Анимация движения
    // Могут быть удалены при кадровой анимации
    pair<short,short> *_dir = new pair<short,short>;
    pair<short,short> *_end = new pair<short,short>; 
    short _repeat = -1;
    
    // Анимация с помощбю кадров
    pair<short,short> *_sz_rect = new pair<short,short>;
    short frames     = 0;
    short delay_anim = 0;

    // _animation_type: 1 - движение
    //                  2 - кадры
    //                  3 - все вместе
    //                  0 - не указан
    unsigned short _animation_type = 0;
    
    sf::Vector2f *_sprite_scale;
    
    void  _save_texture_rect(const short, short y = 0);
    short _last_position_tex_rect[2]{0,0};
    short _origin_position_sprite[2]{0,0};
    

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
