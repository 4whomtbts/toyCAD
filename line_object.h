#pragma once
#include "object.h"
#include <vector>

class LineObject : public Object {
	
public:
	LineObject(const QOpenGLWidget& canvas);
	~LineObject();
	void draw() override;
	void draw_preview() override;
	void on_canvas_click(const QMouseEvent& e) override;

private:
	bool line_completed = false;
	int click_count = 0;
	float points[6];

};