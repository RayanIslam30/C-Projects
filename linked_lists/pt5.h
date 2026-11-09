#ifndef PT5_H
#define PT5_H

#include "widget.h"

struct widgetNode {
   Widget w;
   struct widgetNode * next;
};
struct widgetList {
   struct widgetNode * head;
   unsigned int count;
};

// these are to be defined by you -- see stubs below main
void appendWidget(struct widgetList* theList, Widget w);
void sortByColor(struct widgetList* theList);
void sortByShape(struct widgetList* theList);

// these are defined in testCode.c
void printWidgetList(const struct widgetList*);
int checkTask1(struct widgetList *list, int numEach,
               const char * shapes[], int numShapes,
               const unsigned int colors[], int numColors);
int checkTask2(struct widgetList *list);
int checkTask3(struct widgetList *list);

#endif //PT5_H
