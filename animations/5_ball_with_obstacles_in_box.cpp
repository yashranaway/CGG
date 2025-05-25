#include <graphics.h>
#include <dos.h>
#include <conio.h>

#define STEP_DELAY 15
#define RADIUS 10

void drawBoundary() {
    setcolor(WHITE);
    rectangle(10, 10, 620, 470); // visible boundary
}

void drawObstacles() {
    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, 3);
    line(300, 0, 300, 200);   // top middle wall
    line(300, 250, 300, 480); // bottom middle wall
}

void drawBall(int x, int y) {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    circle(x, y, RADIUS);
    floodfill(x, y, BLUE);
}

void clearBall(int x, int y) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x, y, RADIUS + 1);
    floodfill(x, y, BLACK);
    
    // Redraw boundary and obstacles after clearing to keep them visible
    drawBoundary();
    drawObstacles();
}

void moveBall(int &x, int &y, int dx, int dy, int steps) {
    for (int i = 0; i < steps; i++) {
        clearBall(x, y);
        x += dx;
        y += dy;
        drawBall(x, y);
        delay(STEP_DELAY);
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    
    if (graphresult() != grOk) {
        cprintf("Graphics initialization failed!\n");
        getch();
        return;
    }
    
    setbkcolor(BLACK);
    cleardevice();
    
    drawBoundary();
    drawObstacles();
    
    int x = 30, y = 450; // Start point (bottom left inside, adjusted)
    drawBall(x, y);
    delay(500);
    
    // Movement path - Adjusted to stay within bounds (10,10 to 620,470)
    moveBall(x, y, 5, 0, 40);   // right to x=230
    moveBall(x, y, 0, -5, 30);  // up to y=300
    moveBall(x, y, 5, 0, 20);   // right to x=330 (past wall)
    moveBall(x, y, 0, 5, 30);   // down to y=450
    moveBall(x, y, 5, 0, 40);   // right to x=530
    moveBall(x, y, 0, -5, 80);  // up to y=50
    moveBall(x, y, -5, 0, 100); // left to x=30
    moveBall(x, y, 0, -5, 8);   // up to y=10 (stay within bound)
    moveBall(x, y, 5, 0, 100);  // right to x=530
    moveBall(x, y, 0, 5, 8);    // down to y=50
    moveBall(x, y, -5, 0, 40);  // left to x=330
    moveBall(x, y, 0, 5, 40);   // down to y=250 (under wall)
    moveBall(x, y, -5, 0, 40);  // left to x=130
    moveBall(x, y, 0, -5, 20);  // up to y=150
    moveBall(x, y, -5, 0, 20);  // left to x=30
    moveBall(x, y, 0, 5, 80);   // down to y=550 (but will stop at boundary)
    
    getch();
    closegraph();
}