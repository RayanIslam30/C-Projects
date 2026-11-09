#include "widget.h"
#include "pt5.h"
#include <stdio.h>

void printWidgetList(const struct widgetList* list) {
   const int perLine = 6;
   const struct widgetNode * p;
   int counter = 0;
   for (p = list->head; p; p = p->next) {
      int index = counter % perLine;
      if (index != 0) printf(", ");
      printf("%s", widgetString(p->w));
      if (index == perLine-1) printf("\n");
      ++counter;
   }
   if (counter % perLine) printf("\n");
}

int checkTask1(struct widgetList *list, int numEach,
        const char *shapes[], int numShapes,
        const unsigned int colors[], int numColors) {
   // first check to see if append is working
   struct widgetList testList = {NULL, 0};
   Widget testWidgets[5];
   int status = 1;
   int i, j, k;
   for (i=0; i<5; i++) {
      testWidgets[i] = createWidget(shapes[i%numShapes], colors[i%numColors]);
      appendWidget(&testList, testWidgets[i]);
      if (testList.count != i+1) {
         printf("Task 1 error: After %d appends, list has %d items.\n",
                i+1, testList.count);
         status = 0;
      }
   }
   // check order of items in list
   struct widgetNode *p;
   for (i=0, p = testList.head; p; p = p->next, i++) {
      if (widgetCompareShape(p->w, testWidgets[i])) {
         printf("Task 1 error: List items are not in the correct order.\n");
         status = 0;
         break;
      }
   }
   // now check that the correct set of widgets were created
   for (i=0; i<numShapes; i++) {
      for (j=0; j<numColors; j++) {
         // how many widgets in list are equal to this one?
         Widget w = createWidget(shapes[i], colors[j]);
         k = 0;
         for (p = list->head; p; p = p->next) {
            if (!widgetCompareShape(p->w, w)) k++;
         }
         if (k != numEach) {
            printf("Task 1 error: Expected %d of %s, counted %d\n",
                   numEach, widgetString(w), k);
            status = 0;
         }
      }
   }
   return status;
}

int checkTask2(struct widgetList* list) {
   // check to see if list is in sorted by color
   struct widgetNode *p = list->head;
   if (!p) {
      printf("Task 2 error: list is empty\n");
      return 0;
   }
   unsigned int prevColor = widgetColor(p->w);
   for (p = p->next; p; p = p->next) {
      unsigned int thisColor = widgetColor(p->w);
      if (thisColor < prevColor) {
         printf("Task 2 error: out of order -- color 0x%u after 0x%u\n",
                thisColor, prevColor);
         return 0;
      }
      prevColor = thisColor;
   }
   return 1;
}

int checkTask3(struct widgetList* list) {
   // check to see if list is in sorted by shape+color
   struct widgetNode *p = list->head;
   if (!p) {
      printf("Task 3 error: list is empty\n");
      return 0;
   }
   struct widgetNode *prev = p;
   p = p->next;
   while (p) {
      if (widgetCompareShape(p->w, prev->w) < 0) {
         printf("Task 3 error: out of order -- %s after %s\n",
                widgetString(p->w), widgetString(prev->w));
         return 0;
      }
      prev = p; p = p->next;
   }
   return 1;
}
