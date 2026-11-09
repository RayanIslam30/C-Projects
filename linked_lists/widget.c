#include "widget.h"

#include "random.h"
#include <stdlib.h>  // malloc, NULL, size_t
#include <string.h>  // strcmp
#include <stdio.h>   // sprintf

// We're choosing to represent shape as a number
// instead of a string, because it's faster to compare.
// Will save all specified colors in an array, and will
// lookup when we need the string representation.
// Array is sorted alphabetically, so ordering is the same
// as if we had used strings.

// If shape string cannot be found in array, shape will be "none".

struct widget {
   unsigned int shape;  // index into shape array
   unsigned int color;  // RGB color (24 bits)
};

// array of strings representing shapes, sorted alphabetically (case-sensitive)
static const char ** widgetShapes = NULL;
static size_t numShapes = 0;

const char * widgetShape(Widget w) {
   if (w->shape >= numShapes) return "none";
   return widgetShapes[w->shape];
}

unsigned int widgetColor(Widget w) {
   return w->color;
}

static char widgetStringBuffer[100];  // hope this is big enough!

const char * widgetString(Widget w) {
   char * widgetStringBuffer = malloc(100 * sizeof(char));  // big enough, I hope!
   sprintf(widgetStringBuffer, "[%s,0x%06x]", widgetShape(w), widgetColor(w));
   return widgetStringBuffer;
}

// creating widgets

Widget createWidget(const char * shape, unsigned int color) {
   Widget w = malloc(sizeof(*w));  // allocate space
   if (!w) return NULL;
   // find index of color -- if doesn't exist, return "none" as color
   unsigned int i = 0;
   for (i = 0; i<numShapes; i++) {
      if (!strcmp(shape, widgetShapes[i])) break;
   }
   w->shape = i;
   w->color = color;
   return w;
}

Widget createRandomWidget() {
   Widget w = malloc(sizeof(*w));
   if (!w) return NULL;
   if (numShapes > 0) w->shape = getRandom(numShapes);
   else w->shape = 0;
   w->color = getRandom(1<<24);  // all possible colors
   return w;
}

// comparing widgets

// compare by color only
int widgetCompareColor(Widget w1, Widget w2) {
   if (w1->color < w2->color) return -1;
   if (w1->color > w2->color) return 1;
   return 0;
}

// compare by shape, then color
int widgetCompareShape(Widget w1, Widget w2) {
   if (w1->shape < w2->shape) return -1;
   if (w1->shape > w2->shape) return 1;
   // shapes are equal, now consider color
   return widgetCompareColor(w1, w2);
}

// set up widget shapes

static void sortStrings(const char * array[], size_t n);

// before creating any widgets, initialize the set of shapes
void initWidgetShapes(const char * shapes[], size_t n) {
   // deallocate previous array, if any
   if (widgetShapes) free(widgetShapes);
   // allocate array and copy pointers -- assume that strings are literals
   // or otherwise can just be referenced and will not be changed
   widgetShapes = (const char **) malloc(n * sizeof(const char *));
   if (!widgetShapes) return;  // silent error
   numShapes = n;
   int i;
   for (i=0; i<n; i++) widgetShapes[i] = shapes[i];
   // now sort alphabetically
   sortStrings(widgetShapes, n);
}

// selection sort for array of string pointers
void sortStrings(const char * array[], size_t n) {
   int i, j, m;
   for (i=0; i<n-1; i++) {
      m = i;
      for (j=i; j<n; j++) {
         // if j less than m, set new minimum index
         if (strcmp(array[j],array[m]) < 0) m = j;
      }
      // swap element i with minimum
      const char * tmp = array[i];
      array[i] = array[m];
      array[m] = tmp;
   }
}




