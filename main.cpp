#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Constantes para melhorar a legibilidade do código
const float SUN_RADIUS = 2.0f;
const int NUM_SLICES = 50;
const int NUM_STACKS = 50;
const float PLANET_RADIUS[] = {1.0f, 1.5f, 2.0f, 1.8f, 4.0f, 3.5f, 2.5f, 2.3f, 1.2f};
const float PLANET_DISTANCE[] = {5.0f, 8.0f, 11.0f, 15.0f, 22.0f, 30.0f, 40.0f, 45.0f, 50.0f};

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

void writeplanetName(const std::string& planetName) {
    for (char c : planetName) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawSun() {
    // Configuração de iluminação para o Sol
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPosition[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Luz direcional do Sol
    GLfloat lightColor[] = {1.0f, 1.0f, 0.0f, 1.0f};     // Cor amarela
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

    // Desenha o Sol
    glColor3f(1.0f, 1.0f, 0.0f); // Cor amarela
    for (int i = 0; i < NUM_STACKS; ++i) {
        float theta1 = i * (M_PI / NUM_STACKS);
        float theta2 = (i + 1) * (M_PI / NUM_STACKS);

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= NUM_SLICES; ++j) {
            float phi = j * (2.0f * M_PI / NUM_SLICES);
            float x1 = SUN_RADIUS * sin(theta1) * cos(phi);
            float y1 = SUN_RADIUS * sin(theta1) * sin(phi);
            float z1 = SUN_RADIUS * cos(theta1);

            float x2 = SUN_RADIUS * sin(theta2) * cos(phi);
            float y2 = SUN_RADIUS * sin(theta2) * sin(phi);
            float z2 = SUN_RADIUS * cos(theta2);

            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);

            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    glRasterPos3f(1.5f, 2.5f, 0.0f);
    writeplanetName("Sol");

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void drawSaturnRings() {
    // Anéis de Saturno
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 1.0f, 0.05f);
    glutSolidTorus(1.5, 7.0, 20, 20);
}

void drawPlanet(float radius, float distance, float colorR, float colorG, float colorB, const std::string& planetName, bool hasRings = false) {
    glPushMatrix();
    glRotatef(angle * (5.0f / distance), 0.0f, 1.0f, 0.0f);
    glTranslatef(distance, 0.0f, 0.0f);
    glColor3f(colorR, colorG, colorB);
    glutSolidSphere(radius, 20, 20);
    glRasterPos3f(1.5f, 2.5f, 0.0f);
    writeplanetName(planetName);
    if (hasRings) {
        drawSaturnRings();
    }
    glPopMatrix();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -cameraZ);
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
    glTranslatef(cameraX, cameraY, cameraZ);

    gluLookAt(cameraX, cameraY, cameraZ, cameraX, cameraY, cameraZ - 1.0, 0.0, 1.0, 0.0);

    // Sol
    drawSun();

    // Planetas
    drawPlanet(1.0f, PLANET_DISTANCE[0], 0.1f, 0.1f, 0.1f, "Mercurio");
    drawPlanet(1.5f, PLANET_DISTANCE[1], 1.0f, 0.0f, 0.0f, "Venus");
    drawPlanet(2.0f, PLANET_DISTANCE[2], 0.0f, 0.0f, 1.0f, "Terra");
    drawPlanet(1.8f, PLANET_DISTANCE[3], 1.0f, 0.5f, 0.0f, "Marte");
    drawPlanet(4.0f, PLANET_DISTANCE[4], 0.1f, 0.2f, 0.0f, "Jupiter");
    drawPlanet(3.5f, PLANET_DISTANCE[5], 1.0f, 1.0f, 0.0f, "Saturno", true);
    drawPlanet(2.5f, PLANET_DISTANCE[6], 0.0f, 1.0f, 1.0f, "Urano");
    drawPlanet(2.3f, PLANET_DISTANCE[7], 0.0f, 0.0f, 0.5f, "Netuno");
    drawPlanet(1.2f, PLANET_DISTANCE[8], 0.5f, 0.0f, 0.5f, "Plutao");

    glutSwapBuffers();
}

void updateScene() {
    angle += 0.01f;
    glutPostRedisplay();
}

void processUserInput(unsigned char key, int x, int y) {
    switch (key) {
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

void processMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isLeftButtonPressed = true;
            prevMouseX = x;
            prevMouseY = y;
        } else if (state == GLUT_UP) {
            isLeftButtonPressed = false;
        }
    }
}

void processMouseMotion(int x, int y) {
    if (isLeftButtonPressed) {
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

        float angleYRad = cameraAngleY * M_PI / 180.0f;
        float angleXRad = cameraAngleX * M_PI / 180.0f;

        cameraX = cameraZ * sin(angleYRad) * cos(angleXRad);
        cameraY = cameraZ * sin(angleXRad);

        glutPostRedisplay();
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 1000.0f);
}

int main(int argc, char** argv) {
    std::cout << "w: Movimentar a camera para frente\n";
    std::cout << "s: Movimentar a camera para tras\n";
    std::cout << "a: Movimentar a camera para a esquerda\n";
    std::cout << "d: Movimentar a camera para a direita\n";
    std::cout << "Mouse (Botao esquerdo): Fazer rotação em relação ao sol\n";
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
