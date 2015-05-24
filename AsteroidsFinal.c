
#include <unistd.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdlib.h>

typedef struct Vertex{
    float x;
    float y;
} Vertex_t;

typedef struct Speed{
    float x;
    float y;
} Speed_t;

typedef struct Rectangle{
    Vertex_t one;
    Vertex_t two;
    Vertex_t three;
    Vertex_t four;

    Vertex_t middle;

    Speed_t speed;

} Rectangle_t;

Rectangle_t asteroids[1000];

void init(){
int i;
    for( i = 0; i < sizeof(asteroids)/sizeof(Rectangle_t); i++){
        asteroids[i].speed.x = (int) (rand()%10);
        asteroids[i].speed.y = (int) (rand()%10);

        int r = (int) (rand()%400 + 1);
        r = (r%2==0) ? r *= -1 : r ;

        asteroids[i].one.x = 0 + r;
        asteroids[i].one.y = 0 + r;

        asteroids[i].two.x = 0 + r;
        asteroids[i].two.y = 20 + r;
        
        asteroids[i].three.x = 20 + r;
        asteroids[i].three.y = 20 + r;

        asteroids[i].four.x = 20 + r;
        asteroids[i].four.y = 0 + r;

        asteroids[i].middle.x = ( (asteroids[i].one.x + asteroids[i].four.x)/2 );
        asteroids[i].middle.y = ( (asteroids[i].one.y + asteroids[i].two.y)/2 );
    }

}

void update(){
int i;
   for( i = 0; i < sizeof(asteroids)/sizeof(Rectangle_t); i++){

    if( asteroids[i].middle.x == 240 || asteroids[i].middle.x == -240 ){
        asteroids[i].speed.x *= -1;
    }
    if( asteroids[i].middle.y == 240 || asteroids[i].middle.y == -240 ){
        asteroids[i].speed.y *= -1;
    }

    asteroids[i].one.x += asteroids[i].speed.x;
    asteroids[i].one.y += asteroids[i].speed.y;

    asteroids[i].two.x += asteroids[i].speed.x;
    asteroids[i].two.y += asteroids[i].speed.y;

    asteroids[i].three.x += asteroids[i].speed.x;
    asteroids[i].three.y += asteroids[i].speed.y;

    asteroids[i].four.x += asteroids[i].speed.x;
    asteroids[i].four.y += asteroids[i].speed.y;

    if( asteroids[i].middle.x > 200 ){ asteroids[i].middle.x = 200; } 
    else if( asteroids[i].middle.x < -200){ asteroids[i].middle.x = -200; }

    if( asteroids[i].middle.y > 200 ){ asteroids[i].middle.y = 240; } 
    else if( asteroids[i].middle.y < -200){ asteroids[i].middle.y = -200; }

}	printf("One x: %d\n", (int)(asteroids[0].one.x));
	printf("One y: %d\n",(int)( asteroids[0].one.y));
	printf("Two x: %d\n", (int)(asteroids[0].two.x));
	printf("Two y: %d\n", (int)(asteroids[0].two.y));
	printf("Three x: %d\n",(int)( asteroids[0].three.x));
	printf("Three y: %d\n", (int)(asteroids[0].three.y));
	printf("Four x: %d\n", (int)(asteroids[0].four.x));
	printf("Four y: %d\n\n", (int)(asteroids[0].four.y));	
	 

}

void renderFunction(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    update();
int i;
    for( i = 0; i < sizeof(asteroids)/sizeof(Rectangle_t); i++ ){
        glBegin(GL_QUADS);
        glVertex2f(asteroids[i].one.x/250, asteroids[i].one.y/250);
        glVertex2f(asteroids[i].two.x/250, asteroids[i].two.y/250);
        glVertex2f(asteroids[i].three.x/250, asteroids[i].three.y/250);
        glVertex2f(asteroids[i].four.x/250, asteroids[i].four.y/250);
        glEnd();
    }

    glFlush();

}

/* Main method - main entry point of application
the freeglut library does the window creation work for us, 
regardless of the platform. */
int main(int argc, char** argv){
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Yeah");
    
    while(1){
        renderFunction();
//	sleep(1);
    }

    return 0;
}
