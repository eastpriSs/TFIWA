#include "Camera.h"

using namespace CameraKit;

short Camera::_cmr_view_distance_x_max = 0;
short Camera::_cmr_view_distance_x_min = 0;
sf::View Camera::cmr = sf::View();


void Camera::init( sf::RenderWindow& w ) {
    w.setView(cmr);
}

void Camera::reset_review( const sf::FloatRect& rv  ) { 
    cmr.reset();
}

void Camera::set_cmr_view(const short& x, const short& y) 
{
    if (x < _cmr_view_distance_x_min ||
        x > _cmr_view_distance_x_max) return; // Исключаем возможность камера вы ходить за пределы
    cmr.setCenter(x,y-130);
}

void Camera::set_cmr_locks(const short& mn, const short& mx) {
    _cmr_view_distance_x_max = mx;
    _cmr_view_distance_x_min = mn;
}
