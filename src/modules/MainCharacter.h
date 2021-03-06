/*
////////////////////////////////////////////////

Объявление способностей персонажа, его соприкосновение с картой tilesMap
позиция, направление, скорость, анимация, управление.

////////////////////////////////////////////////
*/

#include <SFML/Graphics.hpp>
#include <iostream>

using sf::Image;
using sf::Texture;
using sf::Sprite;

class MainCharacter
{

public:
    MainCharacter(const std::string&, const short,
                    const short);
    ~MainCharacter();

    Sprite& get_sprite() noexcept;

    // Перемещение спрайта
    void    move_left();
    void    move_right();

    // Отслеживание нажатых клавиш
    void    control();

    // Подступ к значениям
    const short x() const;
    const short y() const;

    // Изменение значений
    void set_x(const short) noexcept;

private:

    // Сохранение значений
    void _change_x(const short& m);
    void _change_y(const short& m);

    short move_speed = 5;

    Image   *img = new Image;
    Texture *tex = new Texture;
    Sprite  *spr = new Sprite;

    short _x = 0,
          _y = 0;
};

inline const short MainCharacter::x() const{
    return _x;
}

inline const short MainCharacter::y() const{
    return _y;
}

inline Sprite& MainCharacter::get_sprite() noexcept
{
    return *spr;
}

inline void MainCharacter::set_x(const short m) noexcept
{
    _x = m; 
}