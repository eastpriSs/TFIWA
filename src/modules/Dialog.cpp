

#include "Dialog.h"

using sf::Text;
using sf::Font;

using namespace DialogManager;


// Параметры
// Будет использована в цикле
void CenterDialog::create_text(const std::wstring&& str, const short x, 
                    const short y )
{
    // Для поддрежки кириллицы
    txt->setString(str);
    // Выставляет согласно объекту из которого был вызван
    txt->setPosition(x, y);
}


void CenterDialog::set_font(const std::string& lnk)
{
    if (!fnt->loadFromFile(lnk)){
        throw std::invalid_argument(
                "set_font_dialog_up:File don't exist in dir ");
    }
    fnt->loadFromFile(lnk);
    txt->setFont(*fnt);
    // Для адекватного отображения шрифта
    txt->setCharacterSize(35);
    txt->setScale(sf::Vector2f(0.2f,0.3f));
}


CenterDialog::~CenterDialog()
{
    std::cout << "Dialog deleted" << '\n';
    delete txt;
    delete fnt;
}


UpperDialog& UpperDialog::operator=(const UpperDialog& rhs)
{
    // Проверка на присваивание самому себе
    if ( this == &rhs ) return *this;
    
    this->txt = rhs.txt;
    this->fnt = rhs.fnt;

    return *this;
}