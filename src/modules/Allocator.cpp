#include "Allocator.h"

using namespace ALLOCATOR;
using namespace ALLOCATOR_PRIVATE;
using std::pair;

Object_map::Object_map(const std::string& lnk,
                       const short pos_x,
                       const short pos_y 
)
: _sprite_scale(new sf::Vector2f(1,1))
{
    img->loadFromFile(lnk);
    tex->loadFromImage(*img);
    spr->setTexture(*tex);
    spr->setPosition(pos_x, pos_y);
    spr->setScale(*_sprite_scale);

    // Сохраняем изначальное положение спрайта
    _origin_position_sprite[0] = pos_x;
    _origin_position_sprite[1] = pos_y;
}


// Работа со значениями класса ------------------------------------------

void Object_map::_save_texture_rect(const short x, short y )
{
    // добавляем, так как, нам нужен последний координат
    this->_last_position_tex_rect[0] += x;
    this->_last_position_tex_rect[1] += y;
}

void Object_map::set_texture_rect(const short x, const short y )
{
    // x - ширина прямоугольника
    // y - высота
    using sf::IntRect;
    spr->setTextureRect(IntRect(this->_last_position_tex_rect[0],
                                this->_last_position_tex_rect[1],
                                x, y));
    _save_texture_rect(x);
}
// ------------------------------------------------------------


// Анимация ------------------------------------------------------------

// Сохранение аргументов и парамторов при движении
void Object_map::set_move_animation( const pair<short,short>& dir,
                                     const pair<short,short>& end,
                                     short repeat)
                                // Направление движения, конечная координата
                                // repeat = -1 -- бескон. число повторений
{
   // Сохраняем направление
   this->_dir->first  = dir.first;
   this->_dir->second = dir.second;
   
   // Сохраняем конечные координаты
   this->_end->first  = end.first;
   this->_end->second = end.second;
   
   // Получаем кол-во повторений
   this->_repeat = repeat;

    this->_animation_type = 1;
}

// Сохранение аргументов и парамторов при анимации кадрами
void Object_map::set_frames_animation(short frames, 
                              const pair<short,short>& size_spr )
{
   // При анимации кадрами, нам не нужно направление и тд. 
   // объект не должен двигаться.
   delete _dir;
   delete _end;

   // Сохраняем размер прямоугольника
   this->_sz_rect->first  = size_spr.first;
   this->_sz_rect->second = size_spr.second;
   
   // Сохраняем кол-во кадров
   this->frames = frames; 

   this->_animation_type = 2; 
}


// Сохранение аргументов и парамторов при анимации resize
void Object_map::set_resize_animation( )
{
   this->_animation_type = 3; 
}


// Будет использована в постоянном цикле
void Object_map::play_animation(short delay, const short tme)
{
    using sf::Vector2f;

    static bool is_small = false;

    switch ( this->_animation_type )
    {
       
    // Движение        
    case 1: 
            spr->move(_dir->first, _dir->second );
            // Если достиг конечной точки
            if (spr->getPosition() == Vector2f(_end->first, _end->second))
                spr->setPosition(_origin_position_sprite[0],
                                 _origin_position_sprite[1] );
    break;

    // Кадры
    case 2: 
            // Если кадры закончились, т. е. последняя кордината пикселя,
            // деленная на кол-во кадров равна размеру изнач. заданному,
            // то значит это был последний кадр.
            if (this->_last_position_tex_rect[0] / this->frames == _sz_rect->first) 
                this->_last_position_tex_rect[0] = 0; // Возвращаем на последний кадр
            
            // Если пересек задержку
            if ( tme >= delay )     
                set_texture_rect(_sz_rect->first, _sz_rect->second);
                
    break;

    // Изменение размера
    case 3:
        if (*_sprite_scale == sf::Vector2f(0.97,0.97))
            is_small = true;
    
        if (*_sprite_scale == Vector2f(0.995,0.995)) {
            is_small = false;
            *_sprite_scale = Vector2f(1, 1);
        }    

        spr->setScale(Vector2f(*_sprite_scale));    
        
        if (is_small) *_sprite_scale += Vector2f(0.005, 0.005); 
            else *_sprite_scale -= Vector2f(0.01, 0.01); 

    break;
    
    default: return;
    
    }
}

// ------------------------------------------------------------

Object_map::~Object_map()
{
    std::cout << "Object destroed x,y: " << _origin_position_sprite[0] << ',' << 
                                            _origin_position_sprite[1] << '\n';
    delete img;
    delete tex;
    delete spr;  
    delete _sprite_scale;
}

Allocator::Allocator()
{

}

Allocator::~Allocator()
{
    
}