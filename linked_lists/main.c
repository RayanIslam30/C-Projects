#include <stdio.h>
#include <stdlib.h>
#include "widget.h"
#include "random.h"
#include "pt5.h"

// Helper function prototypes
struct widgetNode *popNode(struct widgetList *theList);

void insertNodeByColor(struct widgetList *theList,
                       struct widgetNode *node);

void insertNodeByShape(struct widgetList *theList,
                       struct widgetNode *node);

int main(void) {
    int status = 0;

    const char *shapes[4] = {
        "square", "triangle", "circle", "hexagon"
    };

    initWidgetShapes(shapes, 4);

    const unsigned int palette[3] = {
        0xffccff,  // pink
        0xe5ccff,  // lavender
        0xffffff   // white
    };

    // TASK 1: Create 16 widgets of each color and shape combination

    struct widgetList wList = {NULL, 0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 16; k++) {
                Widget w = createWidget(shapes[i], palette[j]);
                appendWidget(&wList, w);
            }
        }
    }

    status = checkTask1(&wList, 16, shapes, 4, palette, 3);

    printf("TASK 1: ");
    if (status == 1) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }

    // TASK 2: Create a list of 50 random widgets

    seedRandom("Willy Wonka's Widget Factory");

    struct widgetList rList = {NULL, 0};

    for (int i = 0; i < 50; i++) {
        Widget w = createRandomWidget();
        appendWidget(&rList, w);
    }

    // Sort the list by color

    sortByColor(&rList);

    status = checkTask2(&rList);

    printf("TASK 2: ");
    if (status == 1) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }

    // TASK 3: Sort the same list by shape

    sortByShape(&rList);

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


// TASK 1: Append a widget to the end of the list

void appendWidget(struct widgetList *theList, Widget w) {
    if (w == NULL) {
        return;
    }

    struct widgetNode *newNode = malloc(sizeof(struct widgetNode));

    if (newNode == NULL) {
        return;
    }

    newNode->w = w;
    newNode->next = NULL;

    if (theList->head == NULL) {
        theList->head = newNode;
    }
    else {
        struct widgetNode *current = theList->head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
    }

    theList->count++;
}


// TASK 2: Remove and return the first node

struct widgetNode *popNode(struct widgetList *theList) {
    if (theList->head == NULL) {
        return NULL;
    }

    struct widgetNode *node = theList->head;

    theList->head = node->next;
    node->next = NULL;

    theList->count--;

    return node;
}


// TASK 2: Insert a node into a list sorted by color

void insertNodeByColor(struct widgetList *theList,
                       struct widgetNode *node) {

    if (theList->head == NULL ||
        widgetCompareColor(node->w, theList->head->w) <= 0) {

        node->next = theList->head;
        theList->head = node;
    }
    else {
        struct widgetNode *current = theList->head;

        while (current->next != NULL &&
               widgetCompareColor(node->w, current->next->w) > 0) {

            current = current->next;
        }

        node->next = current->next;
        current->next = node;
    }

    theList->count++;
}


// TASK 2: Sort the list by color

void sortByColor(struct widgetList *theList) {
    struct widgetList sortedList = {NULL, 0};

    struct widgetNode *node;

    while ((node = popNode(theList)) != NULL) {
        insertNodeByColor(&sortedList, node);
    }

    *theList = sortedList;
}


// TASK 3: Insert a node into a list sorted by shape

void insertNodeByShape(struct widgetList *theList,
                       struct widgetNode *node) {

    if (theList->head == NULL ||
        widgetCompareShape(node->w, theList->head->w) <= 0) {

        node->next = theList->head;
        theList->head = node;
    }
    else {
        struct widgetNode *current = theList->head;

        while (current->next != NULL &&
               widgetCompareShape(node->w, current->next->w) > 0) {

            current = current->next;
        }

        node->next = current->next;
        current->next = node;
    }

    theList->count++;
}


// TASK 3: Sort the list by shape

void sortByShape(struct widgetList *theList) {
    struct widgetList sortedList = {NULL, 0};

    struct widgetNode *node;

    while ((node = popNode(theList)) != NULL) {
        insertNodeByShape(&sortedList, node);
    }

    *theList = sortedList;
}