/**
* @file graphics.c
* @author Tahirah Ahmad
* @date November 1st 
* @brief A graphics library for drawing geometry, for Homework 9 of Georgia Tech
*        CS 2110, Fall 2018.
*/

// Please take a look at the header file below to understand what's required for
// each of the functions.
#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>


// Don't touch this. It's used for sorting for the drawFilledPolygon function.
int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return *ia  - *ib;
}

Pixel noFilter(Pixel c) {
    // Don't touch this.
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel greyscaleFilter(Pixel c) {
    //grab each 5 bits and multiply them i guess, put them back
    int r = ((1 << 5) - 1) & c;
    int g = ((1 << 5) - 1) & (c >> 5);
    int b = ((1 << 5) - 1) & (c >> 10);
    int ans = ((r * 77) + (g * 151) + (b * 28)) >> 8;
    c = (ans << 10) | (ans << 5) | (ans);
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel redOnlyFilter(Pixel c) {
    int r = ((1 << 5) - 1) & c;
    c = (0 << 10) | (0 << 5) | (r);
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel brighterFilter(Pixel c) {
    int r = ((1 << 5) - 1) & c;
    int g = ((1 << 5) - 1) & (c >> 5);
    int b = ((1 << 5) - 1) & (c >> 10);
    int max = 31;
    int diffR = max - r;
    int diffB = max - b;
    int diffG = max - g;
    r = r + (diffR >> 1);
    g = g + (diffG >> 1);
    b = b + (diffB >> 1);
    c = (b << 10) | (g << 5) | (r);
    return c;
}


// TODO: Complete according to the prototype in graphics.h
void drawPixel(Screen *screen, Vector coordinates, Pixel pixel) {
    int x = coordinates.x;
    int y = coordinates.y;
    Vector size = screen->size;
    int width = size.x;
    int height = size.y;
    if (x < 0 || y < 0 || x >= width|| y >= height) {
        return;
    }
    int offset = ((y)*(width)+(x));
    Pixel *buff = (screen->buffer);
    buff[offset] = pixel;
    return;

}

// TODO: Complete according to the prototype in graphics.h
void drawFilledRectangle(Screen *screen, Rectangle *rectangle) {
    int width = (rectangle->size).x;
    int height = (rectangle->size).y;

    Vector tD;
    int row = (rectangle->top_left).y;
    int col = (rectangle->top_left).x;
    int r,c;
    for(r = 0; r < height; r++) {
        for(c = 0; c < width; c++) {
            tD.x = col + c;
            tD.y = row + r;
            if(tD.x < (screen->size).x && tD.y < (screen->size).y)
            drawPixel(screen, tD, rectangle->color);
        }
    }
    return;
}


// TODO: Complete according to the prototype in graphics.h
void drawLine(Screen *screen, Line *line) {

    int x0 = (line->start).x;
    int y0 = (line->start).y;
    int x1 = (line->end).x;
    int y1 = (line->end).y;
    Vector tD;

    int changed = 0;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int x = x0;
    int y = y0;

    int diff = x1 - x0;
    int signx = (diff > 0) - (diff < 0);
    diff = y1 - y0;
    int signy = (diff > 0) - (diff < 0);

    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        changed = 1;
    }

    int e = 2 * dy - dx;

    for (int i = 1; i <= dx; i++) {
        tD.x = x;
        tD.y = y;
        //if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, line->color);
        //}
        while (e >= 0) {
            if (changed){
                x = x + signx;
            }
            else{
                y = y + signy;
            }
            e = e - 2 * dx; 
        }    
        if (changed){
            y += signy;
        }
        else{
            x += signx;
        }
        e = e + 2 * dy;
    }
    tD.x = x;
    tD.y = y;
    //if(tD.x < (screen->size).x && tD.y < (screen->size).y){
        drawPixel(screen, tD, line->color);
    //}

}

// TODO: Complete according to the prototype in graphics.h
void drawPolygon(Screen *screen, Polygon *polygon) {
    int x0,y0,x1,y1;
    int verts = polygon->num_vertices;
    Vector *vertices = polygon->vertices;
    Line line;// = malloc(sizeof(Line));
    Vector beg;
    Vector endo;
    line.color = polygon->color;
    int i = 0;
    while(i < verts-1) {
        x0 = vertices[i].x;
        y0 = vertices[i].y;

        x1 = vertices[i+1].x;
        y1 = vertices[i+1].y;

        beg.x = x0;
        beg.y = y0;

        endo.x = x1;
        endo.y = y1;

        (line).start = beg;
        (line).end = endo;

            drawLine(screen, &line);

        i++;
    }
    x0 = vertices[verts-1].x;
    y0 = vertices[verts-1].y;

    x1 = vertices[0].x;
    y1 = vertices[0].y;

    beg.x = x0;
    beg.y = y0;

    endo.x = x1;
    endo.y = y1;

    (line).start = beg;
    (line).end = endo;

    drawLine(screen, &line);


}

// TODO: Complete according to the prototype in graphics.h
void drawFilledPolygon(Screen *screen, Polygon *polygon) {
    UNUSED(screen);
    int min_y = INT_MAX;
    int max_y = INT_MIN;

    // -------------------------------------------------------------------------
    // TODO: Here, write some code that will find the minimum and maximum
    // Y values that belong to vertices of the polygon, and store them as
    // min_y and max_y.
    // -------------------------------------------------------------------------

    Vector *vertices = polygon->vertices;
    int i = 0;
    while (i < polygon->num_vertices) {
        if(vertices[i].y < min_y) {
            min_y = vertices[i].y;
        }
        if(vertices[i].y > max_y) {
            max_y = vertices[i].y;
        }
        i++;
    }
    // -------------------------------------------------------------------------
    // END OF TODO
    // -------------------------------------------------------------------------

    // Now we iterate through the rows of our polygon
    for (int row = min_y; row <= max_y; row++) {
        // This variable contains the number of nodes found. We start with 0.
        int nNodes = 0;

        // This array will contain the X coords of the nodes we find.
        // Note that there are at most num_vertices of those. We allocate
        // that much room, but at any time only the first nNodes ints will
        // be our actual data.
        int nodeX[polygon->num_vertices];

        // This loop finds the nodes on this row. It intersects the line
        // segments between consecutive pairs of vertices with the horizontal
        // line corresponding to the row we're on. Don't worry about the
        // details, it just works.
        int j = polygon->num_vertices - 1;
        for (int i = 0; i < polygon->num_vertices; i++) {
            if ((polygon->vertices[i].y < row && polygon->vertices[j].y >= row) ||
                (polygon->vertices[j].y < row && polygon->vertices[i].y >= row)) {
                nodeX[nNodes++] = (polygon->vertices[i].x +
                    (row - polygon->vertices[i].y) *
                    (polygon->vertices[j].x - polygon->vertices[i].x) /
                    (polygon->vertices[j].y - polygon->vertices[i].y));
            }
            j = i;
        }
        // ---------------------------------------------------------------------
        // TODO: Make a call to qsort here to sort the nodeX array we made,
        // from small to large x coordinate. Note that there are nNodes elements
        // that we want to sort, and each is an integer. We give you int_cmp
        // at the top of the file to use as the comparator for the qsort call,
        // so you can just pass it to qsort and not need to write your own
        // comparator.
        // ---------------------------------------------------------------------

        int sizeo = sizeof(nodeX[0]);
        qsort(&nodeX, polygon->num_vertices, sizeo, int_cmp);
        // int i = 0;
        // int sizeoof = sizeof(nodeX)/sizeof(nodeX[0]);
        // while(i < sizeoof && i < 5) {
        //     printf("%d, ", nodeX[i]);
        //     i++;
        // }
        // printf("nexto \n");

        //void qsort(void *base, size_t nitems, size_t size, int (*compar)
        //(const void *, const void*))
        // ---------------------------------------------------------------------
        // END OF TODO
        // ---------------------------------------------------------------------



        // ---------------------------------------------------------------------
        // TODO: Now we fill the x coordinates corresponding to the interior of
        // the polygon. Note that after every node we switch sides on the
        // polygon, that is, if we are on the outside, when we pass a node we
        // end up on the inside, and if are inside, we end up on the outside.
        // As a result, all you need to do is start at the 0th node, iterate
        // through all of the even-indexed nodes, and fill until the next node.
        // For example, you need to fill between nodes 0-1, between nodes 2-3,
        // nodes 4-5 etc. but not between nodes 1-2, or nodes 3-4.
        // ---------------------------------------------------------------------
        // int jo = 0;
        // Vector vD;
        // int start = nodeX[0];
        // int end = nodeX[1];

        // int size = sizeof(nodeX)/sizeof(nodeX[0]);


        // for(int i = 0; i < size; i+=2) {
        //     int start = nodeX[i];
        //     int end = nodeX[i+2];
        //     while(start < end) {
        //         vD.x = 
        //     }
        // }

        // while(jo < polygon->num_vertices-2) {
        //     //screen, vector coord, pixel color
        //     vD.x = nodeX[jo];
        //     vD.y = nodeX[jo];
        //     //printf("in here\n");
        //     drawPixel(screen,vD,polygon->color);
        //     jo++;
        // }

        // ---------------------------------------------------------------------
        // END OF TODO
        // ---------------------------------------------------------------------
    }
}

// TODO: Complete according to the prototype in graphics.h
void drawRectangle(Screen *screen, Rectangle *rectangle) {
    Polygon poly;
    int top_left_col = (rectangle->top_left).x;
    int top_left_row = (rectangle->top_left).y;

    int size_x = (rectangle->size).x;
    int size_y = (rectangle->size).y;

    Vector top_left;
    top_left.x = top_left_col;
    top_left.y = top_left_row;

    Vector top_right;
    top_right.x = top_left_col + (size_x- 1);
    top_right.y = top_left_row;

    Vector bottom_right;
    bottom_right.x = top_left_col + (size_x - 1);
    bottom_right.y = top_left_row + (size_y - 1);

    Vector bottom_left;
    bottom_left.x = top_left_col;
    bottom_left.y = top_left_row + (size_y - 1);

    Vector vects[4];
    vects[0] = top_left;
    vects[1] = top_right;
    vects[2] = bottom_right;
    vects[3] = bottom_left;

    poly.vertices = &(vects[0]);
    poly.num_vertices = 4;
    poly.color = rectangle->color;
    drawPolygon(screen, &poly);
}

// TODO: Complete according to the prototype in graphics.h
void drawCircle(Screen *screen, Circle *circle) {
    int x = 0;
    int y = circle->radius;
    int radius = circle->radius;
    int d = 1 - radius;

    int mx = (circle->center).x;
    int my = (circle->center).y;

    Vector tD;

    while(x <= y) {
        tD.x = mx + x;
        tD.y = my + y;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx + x;
        tD.y = my - y;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx - x;
        tD.y = my + y;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx - x;
        tD.y = my - y;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx + y;
        tD.y = my + x;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx + y;
        tD.y = my - x;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx - y;
        tD.y = my + x;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        tD.x = mx - y;
        tD.y = my - x;
        if(tD.x < (screen->size).x && tD.y < (screen->size).y){
            drawPixel(screen, tD, circle->color);
        }
        if (d < 0) {
            d = d + 2 * x + 3;
            x += 1;
        } else {
            d = d + 2 * (x-y) + 5;
            x += 1;
            y -= 1;
         }
    }
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledCircle(Screen *screen, Circle *circle) {
    int x = 0;
    int y = circle->radius;
    int radius = circle->radius;
    int d = 1 - radius;

    int mx = (circle->center).x;
    int my = (circle->center).y;

    Vector p1,p2,p3,p4,p5,p6,p7,p8;
    Line l1, l2, l3, l4;

    while(x <= y) {
        p1.x = mx + x;
        p1.y = my + y;
        p2.x = mx + x;
        p2.y = (my > y) ? (my - y) : 0;

        l1.start = p1;
        l1.end = p2;
        l1.color = circle->color;
        drawLine(screen, &l1);

        if(mx >= x) {
            p3.x = mx - x;
            p3.y = my + y;
            p4.x = mx - x;
            p4.y = (my > y) ? my - y : 0;

            l2.start = p3;
            l2.end = p4;
            l2.color = circle->color;
            drawLine(screen, &l2);
        }

        p5.x = mx + y;
        p5.y = my + x;
        p6.x = mx + y;
        p6.y = (my > x) ? (my - x) : 0;

        l3.start = p5;
        l3.end = p6;
        l3.color = circle->color;
        drawLine(screen, &l3);

        if(mx >= y) {
            p7.x = mx - y;
            p7.y = my + x;
            p8.x = mx - y;
            p8.y = (my > x) ? (my - x) : 0;

            l4.start = p7;
            l4.end = p8;
            l4.color = circle->color;
            drawLine(screen, &l4);
        }
        if (d < 0) {
            d = d + 2 * x + 3;
            x += 1;
        } else {
            d = d + 2 * (x-y) + 5;
            x += 1;
            y -= 1;
        }

    }

}
// TODO: Complete according to the prototype in graphics.h
void drawImage(Screen *screen, Image *image, Pixel (*colorFilter)(Pixel)) {
    int widthI = (image->size).x;
    int heightI = (image->size).y;
    int widthS = (screen->size).x;

    Vector tD;
    int row = (image->top_left).y;
    int col = (image->top_left).x;
    Pixel *buff = (screen->buffer);
    Pixel *imageBuff = (image->buffer);
    int r,c;
    int j = 0;
    for(r = 0; r < heightI; r++) {
        for(c = 0; c < widthI; c++) {
            tD.x = col + c;
            tD.y = row + r;
            Pixel pix = colorFilter(imageBuff[j]);
            if(tD.x < (screen->size).x && tD.y < (screen->size).y
                && tD.x >=0 && tD.y >=0){

                int offset = ((tD.y)*(widthS)+(tD.x));
                buff[offset] = pix;
             
            }
            j++;
        }
    }
    return;

}

// TODO: Complete according to the prototype in graphics.
Image rotateImage(Image *image, int degrees) {
     UNUSED(image);
     UNUSED(degrees);

     // This is just here to keep the compiler from complaining.
     // Delete this line when you're starting to work on this function.
     return (Image){(Vector){0, 0}, (Vector){0, 0}, malloc(1)};
}

