#pragma once
#include <QOpenGLFunctions>            
#include <QOpenGLWidget>
#include <QMouseEvent>

class Object : protected QOpenGLFunctions {

public:
	Object(const QOpenGLWidget& canvas) : canvas(canvas), QOpenGLFunctions() {
		initializeOpenGLFunctions();
	}
	~Object() {}
	virtual void draw() = 0;
	virtual void draw_preview() = 0;
	virtual void on_canvas_click(const QMouseEvent& e) = 0;

protected:
	const QOpenGLWidget& canvas;

private:
	
	
};