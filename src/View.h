//View.h
//Declaration of class View

#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include "Model.h"


class View {
private:
	Model* model;

public:
	View();
	View(Model* model);
	~View();
	void drawAll(int frame_no);
};


#endif//VIEW_H