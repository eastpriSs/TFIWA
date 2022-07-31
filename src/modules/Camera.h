#include <SFML/Graphics.hpp>

#pragma once

namespace CameraKit
{

    class Camera 
    {
        public:

            static void reset_review(  const sf::FloatRect& rv 
                                                = sf::FloatRect(0,0,500,340) );
            static void set_cmr_view(  const short&, const short& );
            static void set_cmr_locks( const short&, const short& );
            static void init( sf::RenderWindow& );

        private:

            static       sf::View cmr;
            static short _cmr_view_distance_x_min;
            static short _cmr_view_distance_x_max;
    };

} // namespace CameraKit
