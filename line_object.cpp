#include "line_object.h"

LineObject::LineObject(const QOpenGLWidget& canvas) : Object(canvas) {

}

LineObject::~LineObject() {

}

void LineObject::draw() {
    if (line_completed) {
        unsigned int p_vbo;
        glGenBuffers(1, &p_vbo);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, p_vbo);
        glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), &points[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glColor3f(0.5f, 0.5f, 0.5f);
        glLineWidth(2.f);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableVertexAttribArray(0);
    }
}

void LineObject::draw_preview() {
        
}

void LineObject::on_canvas_click(const QMouseEvent& e) {
    if (line_completed) return;
       
    
    int widget_width = canvas.width();
    int widget_height = canvas.height();

    float gl_x = (float)(e.x() - (widget_width / 2)) / (widget_width / 2);
    float gl_y = (float)((widget_height / 2) - e.y()) / (widget_height / 2);

    if (!click_count) {
        points[0] = gl_x, points[1] = gl_y, points[2] = 0;
    } else {
        points[3] = gl_x, points[4] = gl_y, points[5] = 0;
        line_completed = true;
    }
    click_count++;
}