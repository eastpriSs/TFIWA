/*

"Работа с диалогами", есть небольшая иерархия:
Базовый класс CenterDialog, его координаты
расположения на экране стоят изначально, от него
два производных.

operator= определен один раз в качестве пробы.
(оказался бесполезен) 

*/

#include <SFML/Graphics.hpp>
#include <iostream>

namespace DialogManager
{


using sf::Text;
using sf::Font;


class CenterDialog
{

public:

// По умолчанию текст располагается по центру
void create_text(const std::wstring&, 
            const short x = 40, const short y = 170);

void set_font(const std::string&);

virtual ~CenterDialog();

// Будет спользована в цикле
inline const Text& txt_var(){ return *txt; }

private:

Text *txt = new Text;
Font *fnt = new Font;

};

class UpperDialog: public CenterDialog
{

public: 

UpperDialog& operator=(const UpperDialog&);

private:

Text *txt = new Text;
Font *fnt = new Font;

};

class DownDialog: public CenterDialog
{

private:

Text *txt = new Text;
Font *fnt = new Font;

};


} // namespace Dialog
