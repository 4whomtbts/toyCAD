#include "mycad.h"
#include <QPushButton>
mycad::mycad(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    main_canvas = new MainCanvas;
    connect(ui.line_comp, &QPushButton::clicked, main_canvas, &MainCanvas::line_draw_icon_clicked);
    ui.main_canvas_container->addWidget(main_canvas);
}
