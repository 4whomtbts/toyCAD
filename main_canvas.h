#pragma once
#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include "object.h"
#include <memory>
#include <QWindow>
#include <QOpenGLFunctions>            
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class MainCanvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

public:
	MainCanvas(QWidget* parent = nullptr);
	~MainCanvas();
	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void cleanup();
	void line_draw_icon_clicked();
signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	std::vector<std::shared_ptr<Object>> objects;
	std::shared_ptr<Object> focused;
	
private:
	bool m_core;
	int m_projMatrixLoc = 0;
	int m_mvMatrixLoc = 0;
	int m_normalMatrixLoc = 0;
	int m_lightPosLoc = 0;
	int m_frame = 0;
	GLint m_posAttr = 0;
	GLint m_colAttr = 0;
	GLint m_iAttr = 1;
	GLint m_matrixUniform = 0;
	QMatrix4x4 m_proj;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;
	QOpenGLShaderProgram* m_program = nullptr;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLContext* m_context = nullptr;
	QOpenGLPaintDevice* m_device = nullptr;

};
#endif