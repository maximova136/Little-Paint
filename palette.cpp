#include "palette.h"

Palette::Palette(QToolBar *toolBar) : QToolBar(tr("Colors"))
{
    col1 = Qt::black;
    col2 = Qt::white;
    mToolBar = toolBar;
    setMovable(false);
    initializeItems();


}

void Palette::initializeItems()
{
    mColorButton = new paletteButton(Qt::black);
    addWidget(mColorButton);
    mColorButton = new paletteButton(Qt::white);
    addWidget(mColorButton);

}
