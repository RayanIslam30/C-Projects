#ifndef PS6_WIDGET_H
#define PS6_WIDGET_H

#include <stdlib.h>

typedef struct widget * Widget;

// Widget is an abstract data type.
// Every Widget has a shape, specified by a string,
// and a color, specified by an unsigned 24-bit RGB value.

const char * widgetShape(Widget);
unsigned int widgetColor(Widget);
const char * widgetString(Widget);  // create string for printing (not saving)

// compare two widgets by their color values only
// returns -1 if w1 < w2, 0 if w1 == w2, +1 if w1 > w2
int widgetCompareColor(Widget w1, Widget w2);

// compare two widgets by their shapes and then by color
// if two widgets are the same shape, then the color will determine the order
// returns -1 if w1 < w2, 0 if w1 == w2, +1 if w1 > w2
int widgetCompareShape(Widget w1, Widget w2);

// before creating any widgets, initialize the set of shapes
void initWidgetShapes(const char * shapes[], size_t n);

// create a widget with a specified shape and color
// returns NULL if illegal shape or cannot allocate
Widget createWidget(const char *shape, unsigned int color);

// create a widget with a random shape and color
// returns NULL if cannot allocate
Widget createRandomWidget();




#endif //PS6_WIDGET_H
