#include "main_canvas.h"
#include "line_object.h"
#include <math.h>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <QScreen>
#include <QWindow>
#include <QVector>
#include <QPainter>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QCoreApplication>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>

std::vector<std::vector<std::pair<float, float>>> lines;

MainCanvas::MainCanvas(QWidget* parent) : QOpenGLWidget(parent) {

}

MainCanvas::~MainCanvas() {

}

static const char* vertexShaderSourceCore =
"#version 330 core\n"
// Input vertex data, different for all executions of this shader.
"layout(location = 0) in vec3 posAttr;\n"
"layout(location = 1) in vec3 colAttr;\n"
// Output data ; will be interpolated for each fragment.
"flat out vec3 fragmentColor;\n"
// Values that stay constant for the whole mesh.
"uniform mat4 matrix;\n"
"void main() {\n"
// Output position of the vertex, in clip space : MVP * position
"gl_Position = matrix * vec4(posAttr, 1);\n"
// The color of each vertex will be interpolated
// to produce the color of each fragment
"fragmentColor = colAttr;\n"
"}\n";

static const char* fragmentShaderSourceCore =
"#version 330 core\n"
"flat in vec3 fragmentColor;\n"
"out vec3 color;\n"
"void main() {\n"
"color = fragmentColor;\n"
"}\n";

void MainCanvas::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MainCanvas::cleanup);

    initializeOpenGLFunctions();
    glClearColor(255, 255, 255, 0);
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = m_program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    m_program->release();
}

void MainCanvas::resizeGL(int w, int h) {
    m_proj.setToIdentity();
    m_proj.perspective(0.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void MainCanvas::paintGL() {

    QVector4D position(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glEnable(GL_CULL_FACE);
    m_program->bind();
    QMatrix4x4 matrix;
    matrix.perspective(0.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);
    float x = 0,
        y = 0,
        z = 0;

    static const unsigned int cube_elements[] = {
             0, 1, 2,
             0, 2, 3,
             1, 4, 5,
             1, 5, 2,
             6, 5, 4,
             6, 7, 5,
             0, 7, 6,
             0, 3, 7,
             3, 2, 5,
             3, 5, 7,
             0, 4, 1,
             0, 6, 4,
    };

    static const float cube_colors[] = {
       1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0,
       1.0, 0.5323, 0.1235,
       1.0, 0.0, 0.5f,
       1.0, 0.0, 1.0,
       1.0, 0.1233, 0.1942,
       1.0, 0.0, 1.0,

    };

    float cube_vertices[] = {

                x + -0.5, y + -0.5, z + 0.5,
                 x + 0.5, y + -0.5, z + 0.5,
                 x + 0.5, y + 0.5, z + 0.5,
                 x + -0.5, y + 0.5, z + 0.5,
                 x + 0.5, y + -0.5, z + -0.5,
                 x + 0.5, y + 0.5, z + -0.5,
                 x + -0.5, y + -0.5, z + -0.5,
                 x + -0.5, y + 0.5, z + -0.5,
    };
    /*

    unsigned int ibo;
    unsigned int vbo;
    unsigned int colorBuffer;
    glGenBuffers(1, &ibo);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &colorBuffer);


    glBindBuffer(GL_ARRAY_BUFFER, (vbo));
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    //vertex color buffer
    glBindBuffer(GL_ARRAY_BUFFER, (colorBuffer));
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(1);

    //Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (ibo));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    //glDrawElements(GL_TRIANGLES, 36, GL_BYTE, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    */

    /*
    unsigned int p_vbo;
    float points[] = {
        0, 0, 0,
        0.5, 0.5, 0
    };
    glGenBuffers(1, &p_vbo);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, p_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(2.f);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(0);

    m_program->release();
    ++m_frame;
    float points[] = {
        -0.267500013f, 0.104999997f, 0,
        0.262499988f, -0.234999999f, 0
    };

     unsigned int p_vbo;

    std::vector<float> points;

    for (int i = 0; i < lines.size(); i++) {
        auto curr_line_vertexes = lines[i];
        for (std::pair<float, float> coord : curr_line_vertexes) {
            points.insert(points.end(), { (float)coord.first, (float)coord.second, 0.0f });
        }
    }

    if (points.size()) {
        glGenBuffers(1, &p_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, p_vbo);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glColor3f(0.5f, 0.5f, 0.5f);
        glLineWidth(2.f);
        glDrawArrays(GL_LINES, 0, (points.size()) / 3);
        glDisableVertexAttribArray(0);
    }

    */
    for (int i = 0; i < objects.size(); i++) {
        auto curr = objects.at(i).get();
        curr->draw();
    }
    m_program->release();
    ++m_frame;
    update();
}

void MainCanvas::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

void MainCanvas::setXRotation(int angle)
{
    update();
}

void MainCanvas::setYRotation(int angle)
{
    update();

}

void MainCanvas::setZRotation(int angle)
{
    update();
}

QSize MainCanvas::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MainCanvas::sizeHint() const
{
    return QSize(400, 400);
}

void MainCanvas::mousePressEvent(QMouseEvent* e) {
    focused.get()->on_canvas_click(*e);
    /*
    static int click_cnt = 0;
    int widget_width = width();
    int widget_height = height();

    float gl_x = (float)(e->x() - (widget_width / 2)) / (widget_width / 2);
    float gl_y = (float)((widget_height / 2) - e->y()) / (widget_height / 2);

    if (click_cnt == 0) {
        click_cnt++;
        auto coord_vector = std::vector<std::pair<float, float>>();
        coord_vector.push_back({ gl_x, gl_y });
        lines.push_back(coord_vector);
    }
    else {
        click_cnt = 0;
        std::vector<std::pair<float, float>>& coord_vector = lines.back();
        coord_vector.push_back({ gl_x, gl_y });
    }
    */
}

void MainCanvas::line_draw_icon_clicked() {
    auto new_line = std::shared_ptr<Object>(new LineObject(*this));
    objects.push_back(new_line);
    focused = new_line;
}