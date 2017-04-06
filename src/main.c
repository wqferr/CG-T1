
#include <stdio.h>
#include <GL/glut.h>

#define WINDOW_W 600
#define WINDOW_H 600

// Ângulo de rotação do cata vento
float angle = 0;
int direction = 0;

void drawSail(void) {
    glBegin(GL_QUADS);
        glVertex2f(0.f, 0.f);
        glVertex2f(10.f, -20.f);
        glVertex2f(0.f, -40.f);
        glVertex2f(-10.f, -20.f);
    glEnd();
}

void drawWindmill(void) {
    glPushMatrix();
        glTranslatef(50.f, 50.f, 0.f);

        glColor3f(0.75f, 0.75f, 0.75f);
        glBegin(GL_QUADS);
            glVertex2f(3.f, -50.f);
            glVertex2f(3.f, 3.f);
            glVertex2f(-3.f, 3.f);
            glVertex2f(-3.f, -50.f);
        glEnd();

        glRotatef(angle, 0.f, 0.f, 1.f);

        glColor3ub(60, 186, 84);
        drawSail();

        glRotatef(90.f, 0.f, 0.f, 1.f);
        glColor3ub(244, 194, 13);
        drawSail();

        glRotatef(90.f, 0.f, 0.f, 1.f);
        glColor3ub(219, 50, 54);
        drawSail();

        glRotatef(90.f, 0.f, 0.f, 1.f);
        glColor3ub(72, 133, 237);
        drawSail();
    glPopMatrix();
}

void draw(void) {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawWindmill();

    glFlush();
}

void update(void) {
    angle += .005f * direction;
    glutPostRedisplay();
}

void mouseClicked(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        direction = 0;
    } else {
        direction = (button == GLUT_LEFT_BUTTON ? 1 : -1);
    }
}

void init(void) {
    glClearColor(0.f, 0.f, 0.f, 0.f);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("Cata-vento");
    gluOrtho2D(0, 100, 0, 100);

    init();
    glutDisplayFunc(&draw);
    glutIdleFunc(&update);
    glutMouseFunc(&mouseClicked);
    glutMainLoop();

    return 0;
}
