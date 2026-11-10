#include <stdio.h>
#include "widget.h"
#include "random.h"
#include "pt5.h"  // list structs and function declarations for test code

int main(void) {
   int status = 0;
   const char * shapes[4] = {"square", "triangle", "circle", "hexagon"};
   initWidgetShapes(shapes, 4);
   const unsigned int palette[3] = {0xffccff, // pink
                                    0xe5ccff, // lavender
                                    0xffffff  // white
                                    };
   int numWidgets = 16*12;  // 16 of each color+shape combination

   // TASK 1: use appendWidget to create a list of widgets
   // include 16 widgets of each color+shape combination listed above
   // in other words, 16 pink squares, 16 lavender squares, 16 white squares, 16 pink triangles, ...

   struct widgetList wList = {NULL, 0};  // create empty list
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
         for (int k = 0; k < 16; k++) {
            Widget w = createWidget(shapes[i], palette[j]);
            appendWidget(&wList, w);
        }
      }
   }


   // You can use printWidgetList to test your code, but it won't be used
   // in the testing functions.

   // after creating the list, this function will test whether
   // the list is correct
   status = checkTask1(&wList, 16, shapes, 4, palette, 3);
   printf("TASK 1: ");
   if (status == 1) {
      printf("PASSED\n");
   }
   else {
      printf("FAILED\n");
   }

   // TASK 2: use appendWidget to create a list of 50 random widgets
   seedRandom("Willy Wonka's Widget Factory");
   struct widgetList rList = {NULL, 0};  // creating an initial list
   // add code here to create and add widgets to rList

   // this list will not be tested -- assumed to be correct since you passed Task 1

   // sort the list by color only
   sortByColor(&rList);

   status = 0;
   status = checkTask2(&rList);
   printf("TASK 2: ");
   if (status == 1) {
      printf("PASSED\n");
   }
   else {
      printf("FAILED\n");
   }

   // TASK 3: sort the same list by shape

   sortByShape(&rList);

   status = 0;
   status = checkTask3(&rList);
   printf("TASK 3: ");
   if (status == 1) {
      printf("PASSED\n");
   }
   else {
      printf("FAILED\n");
   }

   return 0;
}

// TASK 1
void appendWidget(struct widgetList* theList, Widget w) {}

// TASK 2
// suggestion: implement the following two functions first
struct widgetNode * popNode(struct widgetList* theList);  // remove and return first node
void insertNodeByColor(struct widgetList * theList, struct widgetNode *node);  // insert a node into sorted list

// NOTE: Comparison functions are provided in widget.h

void sortByColor(struct widgetList* theList) {}

// TASK 3
// suggestion: implement the following function first
void insertNodeByShape(struct widgetList * theList, struct widgetNode *node);  // insert a node into sorted list

// NOTE: Comparison functions are provided in widget.h

void sortByShape(struct widgetList* theList) {}

