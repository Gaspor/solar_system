#include <GL/glut.h>
#include <cmath>
#include <iostream>

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 30.0f;

float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;

float angle = 0.0f;

float cameraSpeed = 0.5f;
float cameraRotationSpeed = 0.1f;

bool isLeftButtonPressed = false;
int prevMouseX = 0;
int prevMouseY = 0;

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Posição da luz pontual
    GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Parâmetros de atenuação (opcional, dependendo da aparência desejada)
    GLfloat attenuation[] = { 1.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation);

    // Cor da luz pontual
    GLfloat lightColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupLighting();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, cameraX, cameraY, cameraZ - 1.0, 0.0, 1.0, 0.0);

    glColor3f(1.0f, 1.0f, 0.0f); // Cor amarela
    glutSolidSphere(2.0, 20, 20);
    glRasterPos3f(1.5f, 1.5f, 0.0f);
    std::string sunName = "Sol";
    for (char c : sunName)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Mercúrio
    glPushMatrix();
    glRotatef(angle * 2.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(5.0f, 0.0f, 0.0f);
    glColor3f(0.1f, 0.1f, 0.1f); // Cor cinza escuro
    glutSolidSphere(1.0, 20, 20);
    glRasterPos3f(1.5f, 1.5f, 0.0f);
    std::string planet1Name = "Mercurio";
    for (char c : planet1Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Vênus
    glPushMatrix();
    glRotatef(angle * 1.5f, 0.0f, 1.0f, 0.0f);
    glTranslatef(8.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    glutSolidSphere(1.5, 20, 20);
    glRasterPos3f(1.5f, 1.5f, 0.0f);
    std::string planet2Name = "Venus";
    for (char c : planet2Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Terra
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(11.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul
    glutSolidSphere(2.0, 20, 20);
    glRasterPos3f(1.5f, 2.5f, 0.0f);
    std::string planet3Name = "Terra";
    for (char c : planet3Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Marte
    glPushMatrix();
    glRotatef(angle * 0.8f, 0.0f, 1.0f, 0.0f);
    glTranslatef(15.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja
    glutSolidSphere(1.8, 20, 20);
    glRasterPos3f(1.5f, 2.5f, 0.0f);
    std::string planet4Name = "Marte";
    for (char c : planet4Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Júpiter
    glPushMatrix();
    glRotatef(angle * 0.6f, 0.0f, 1.0f, 0.0f);
    glTranslatef(22.0f, 0.0f, 0.0f);
    glColor3f(0.1f, 0.2f, 0.0f); // Cor verde musgo
    glutSolidSphere(4.0, 20, 20);
    glRasterPos3f(1.5f, 4.5f, 0.0f);
    std::string planet5Name = "Jupiter";
    for (char c : planet5Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Saturno
    glPushMatrix();
    glRotatef(angle * 0.4f, 0.0f, 1.0f, 0.0f);
    glTranslatef(30.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f); // Cor amarela
    glutSolidSphere(3.5, 20, 20);

    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 1.0f, 0.05f);
    glutSolidTorus(1.5, 7.0, 20, 20);
    glRasterPos3f(1.5f, 3.5f, 0.0f);
    std::string planet6Name = "Saturno";
    for (char c : planet6Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Urano
    glPushMatrix();
    glRotatef(angle * 0.3f, 0.0f, 1.0f, 0.0f);
    glTranslatef(40.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f); // Cor ciano
    glutSolidSphere(2.5, 20, 20);
    glRasterPos3f(1.5f, 2.5f, 0.0f);
    std::string planet7Name = "Urano";
    for (char c : planet7Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Netuno
    glPushMatrix();
    glRotatef(angle * 0.2f, 0.0f, 1.0f, 0.0f);
    glTranslatef(45.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.5f); // Cor azul escuro
    glutSolidSphere(2.3, 20, 20);
    glRasterPos3f(1.5f, 2.5f, 0.0f);
    std::string planet8Name = "Netuno";
    for (char c : planet8Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    // Plutão
    glPushMatrix();
    glRotatef(angle * 0.1f, 0.0f, 1.0f, 0.0f);
    glTranslatef(50.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.0f, 0.5f); // Cor roxa
    glutSolidSphere(1.2, 20, 20);
    glRasterPos3f(1.5f, 1.5f, 0.0f);
    std::string planet9Name = "Plutao";
    for (char c : planet9Name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void updateScene()
{
    angle += 0.01f;
    glutPostRedisplay();
}

void processUserInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        cameraZ -= cameraSpeed;
        break;
    case 's':
        cameraZ += cameraSpeed;
        break;
    case 'a':
        cameraX -= cameraSpeed;
        break;
    case 'd':
        cameraX += cameraSpeed;
        break;
    case 'q':
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void processMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isLeftButtonPressed = true;
            prevMouseX = x;
            prevMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            isLeftButtonPressed = false;
        }
    }
}

void processMouseMotion(int x, int y)
{
    if (isLeftButtonPressed)
    {
        int deltaX = x - prevMouseX;
        int deltaY = y - prevMouseY;
        prevMouseX = x;
        prevMouseY = y;

        cameraAngleY -= deltaX * cameraRotationSpeed;
        cameraAngleX += deltaY * cameraRotationSpeed;

        if (cameraAngleY >= 360.0f)
            cameraAngleY -= 360.0f;
        else if (cameraAngleY < 0.0f)
            cameraAngleY += 360.0f;

        float angleYRad = cameraAngleY * 3.1415926535f / 180.0f;
        float angleXRad = cameraAngleX * 3.1415926535f / 180.0f;

        cameraX = cameraZ * sin(angleYRad) * cos(angleXRad);
        cameraY = cameraZ * sin(angleXRad);

        glutPostRedisplay();
    }
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 1000.0f);
}

int main(int argc, char** argv)
{
    std::cout << "w: Movimentar a camera para frente\n";
    std::cout << "s: Movimentar a camera para tras\n";
    std::cout << "a: Movimentar a camera para a esquerda\n";
    std::cout << "d: Movimentar a camera para a direita\n";
    std::cout << "q: Sair do programa\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar 3D - CGPDI");

    glutDisplayFunc(renderScene);
    glutIdleFunc(updateScene);
    glutKeyboardFunc(processUserInput);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
    glutReshapeFunc(reshape);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
