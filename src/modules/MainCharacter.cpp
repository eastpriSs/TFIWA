/*
////////////////////////////////////////////////

Определение способностей персонажа, его соприкосновение с картой tilesMap
позиция, направление, скорость, анимация, управление.

////////////////////////////////////////////////
*/

#include "MainCharacter.h"
#include <iostream>

MainCharacter::MainCharacter(const std::string& lnk, const short pos_x,
                                const short pos_y)
: money(140)
{
    // Создание спрайта и размещение на координаты
    img->loadFromFile(lnk);
    tex->loadFromImage(*img);
    spr->setTexture(*tex);
    spr->setPosition(pos_x,pos_y);
    _x = pos_x;
    _y = pos_y;
}




// Сохранение значений
void MainCharacter::_change_x(const short& m)
{
    _x += m;
}

void MainCharacter::_change_y(const short& m)
{
    _y += m;
}

// Перемещение спрайта
void MainCharacter::move_left()
{   
    spr->move(-move_speed,0); 
    _change_x(-move_speed);   
}

void MainCharacter::move_right()
{   
    spr->move(move_speed,0);   
    _change_x(move_speed);    
}

// Отслеживание нажатых клавиш
// Будет использована в главном цикле
void MainCharacter::control()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move_right();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move_left(); 
    
    spr->setColor(sf::Color(rand()% 255,rand()% 255,rand()% 255)); // НЕ ВКЛЮЧАТЬ
}   

MainCharacter::~MainCharacter()
{
    std::cout << "MainCh destroyed" << '\n';
    delete spr;
    delete tex;
    delete img;
}
