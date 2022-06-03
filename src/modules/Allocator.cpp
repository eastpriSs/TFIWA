#include "Allocator.h"

using namespace ALLOCATOR;
using namespace ALLOCATOR_PRIVATE;

Object_map::Object_map(const std::string& lnk,
                       const short pox_x,
                       const short pox_y 
)
{
    img->loadFromFile(lnk);
    tex->loadFromImage(*img);
    spr->setTexture(*tex);
    spr->setPosition(pox_x, pox_y);
}

void Object_map::save_texture_rect(const short x, const short y )
{
    _last_position_tex_rect[0] = x;
    _last_position_tex_rect[1] = y;
}

void Object_map::set_texture_rect(const short x, const short y )
{
    using sf::IntRect;
    spr->setTextureRect(IntRect(_last_position_tex_rect[0],
                                _last_position_tex_rect[1],
                                x, y));
    save_texture_rect(x,y);
}

Object_map::~Object_map()
{
    
}

Allocator::Allocator()
{

}

Allocator::~Allocator()
{
    
}