
#include <stdio.h>
#include <GL/glut.h>

#define WINDOW_W 600
#define WINDOW_H 600

// Ângulo de rotação do cata vento
float angle = 10;

float sunAngle = 0;
int direction = 0;

void drawSun(void) {
    glBegin(GL_QUADS);
        glVertex2f(-5.f, 5.f);
        glVertex2f(-5.f, -5.f);
        glVertex2f(5.f, -5.f);
        glVertex2f(5.f, 5.f);
    glEnd();
}

void drawBackground(void) {
    // Desenha o sol
    glPushMatrix();
        // Posiciona os eixos de acordo com a rotação atual
        glTranslatef(-35.f, 35.f, 0.f);
        glRotatef(sunAngle, 0.f, 0.f, 1.f);

        // Desenha primeiro quadrado do sol (mais claro)
        glColor3ub(255, 255, 175);
        drawSun();

        // Desenha segundo quadrado do sol (mais forte)
        glRotatef(45.f, 0.f, 0.f, 1.f);
        glColor3ub(255, 255, 50);
        drawSun();
    glPopMatrix();

    // Estrada
    glColor3ub(50, 50, 50);
    glBegin(GL_QUADS);
        glVertex2f(50.f, -50.f);
        glVertex2f(3.f, -10.f);
        glVertex2f(-3.f, -10.f);
        glVertex2f(-50.f, -50.f);
    glEnd();

    // Grama
    glColor3ub(34, 139, 34);
    glBegin(GL_TRIANGLES);
        // À direita
        glVertex2f(50.f, -50.f);
        glVertex2f(50.f, -20.f);
        glVertex2f(3.f, -10.f);

        // À esquerda
        glVertex2f(-50.f, -50.f);
        glVertex2f(-50.f, -20.f);
        glVertex2f(-3.f, -10.f);
    glEnd();
}

// Desenha uma hélice do catavento
// Supõe que a rotação e translação já foram feitas antes
void drawSail(void) {
    glBegin(GL_QUADS);
        glVertex2f(0.f, 0.f);
        glVertex2f(10.f, -20.f);
        glVertex2f(0.f, -40.f);
        glVertex2f(-10.f, -20.f);
    glEnd();
}

// Desenha o catavento
void drawWindmill(void) {
    glPushMatrix();
        glScalef(0.25f, 0.25f, 1.f);

        // Desenha a haste
        glColor3f(0.75f, 0.75f, 0.75f);
        glBegin(GL_QUADS);
            glVertex2f(3.f, -50.f);
            glVertex2f(3.f, 3.f);
            glVertex2f(-3.f, 3.f);
            glVertex2f(-3.f, -50.f);
        glEnd();

        // Rotaciona para o desenho da hélice no angulo correto
        glRotatef(angle, 0.f, 0.f, 1.f);

        // Hélice verde
        glColor3ub(60, 186, 84);
        drawSail();

        // Hélice amarela
        glRotatef(90.f, 0.f, 0.f, 1.f);
        glColor3ub(244, 194, 13);
        drawSail();

        // Hélice vermelha
        glRotatef(90.f, 0.f, 0.f, 1.f);
        glColor3ub(219, 50, 54);
        drawSail();

        // Hélice azul
        glRotatef(90.f, 0.f, 0.f, 1.f);
        glColor3ub(72, 133, 237);
        drawSail();
    glPopMatrix();
}

// Callback de desenho
void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawWindmill();

    glFlush();
}

// Callback de update
void update(void) {
    // Animar catavento
    angle += .005f * direction;

    // Animar sol
    sunAngle += 0.001;


    // Limitar ângulo do catavento
    if (angle > 360)
        angle -= 360;
    if (angle < 0)
        angle += 360;

    // Limitar ângulo do sol
    if (sunAngle > 360)
        sunAngle -= 360;
    if (sunAngle < 0)
        sunAngle += 360;

    // Forçar redraw
    glutPostRedisplay();
}

void mouseClicked(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        // Parar catavento
        direction = 0;
    } else {
        // Girar para direita ou esquerda dependendo do botão
        direction = (button == GLUT_LEFT_BUTTON ? 1 : -1);
    }
}

void init(void) {
    // Setar cor do céu como background
    glClearColor(0.53f, 0.8f, 0.92f, 1.f);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("Cata-vento");

    gluOrtho2D(-50, 50, -50, 50);

    init();

    // Setar callbacks
    glutDisplayFunc(&draw);
    glutIdleFunc(&update);
    glutMouseFunc(&mouseClicked);

    // Abrir janela
    glutMainLoop();

    return 0;
}
