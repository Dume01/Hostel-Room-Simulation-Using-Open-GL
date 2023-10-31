#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

/// Global variables
GLboolean switchOne = false, switchTwo = false, switchLamp = false, amb1 = true, diff1 = true, spec1 = true, amb2 = true, diff2 = true, spec2 = true, amb3 = true, diff3 = true, spec3 = true;
double windowHeight = 800, windowWidth = 600;
double eyeX = 4.0, eyeY = 2.0, eyeZ = 15.0, refX = 0, refY = 0, refZ = 0;
double theta = 180.0, y = 1.36, z = 7.97888;

/// Cube vertices
static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

/// Indices for the cube faces
static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

/// Calculate and set the normal of a triangle
static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

/// Draw a cube with materials
void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
            v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
            v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}


/// Quad indices for the pyramid base
static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

/// Draw a sphere with materials
void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(3.0, 20, 16);
}


/**
 * @brief Draw a cupboard.
 */
void cupboard() {
    glPushMatrix();
    glTranslatef(3.0, 0, 2.0);
    glScalef(0.5, 1, 0.5);
    drawCube1(0.545, 0.271, 0.075, 0.275, 0.137, 0.038);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 1, 3.5);
    glScalef(0.5, 0.01, 0.0001);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 0.5, 3.5);
    glScalef(0.5, 0.01, 0.0001);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 0, 3.5);
    glScalef(0.5, 0.01, 0.0001);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5, 0, 3.5);
    glScalef(0.01, 1, 0.0001);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75, 1, 3.5);
    glScalef(0.01, 0.67, 0.0001);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 0, 3.5);
    glScalef(0.01, 1, 0.0001);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0, 1.4, 3.5);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.02, 1.9, 3.51);
    glScalef(0.02, 0.02, 0.01);
    drawSphere(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5, 1.4, 3.5);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.52, 1.9, 3.51);
    glScalef(0.02, 0.02, 0.01);
    drawSphere(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5, 0.7, 3.5);
    glScalef(0.16, 0.02, 0.01);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5, 0.25, 3.5);
    glScalef(0.16, 0.02, 0.01);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

/**
 * @brief Draw the room with walls, ceiling, and floor.
 */
void room() {
    glPushMatrix();
    glTranslatef(-1.5, -1, 0.5);
    glScalef(5, 2, 0.1);
    drawCube1(0.18, 0.55, 0.34, 0.18, 0.55, 0.34);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, -1, 0);
    glScalef(0.2, 2, 5);
    drawCube1(0.53, 0.81, 0.92, 0.53, 0.81, 0.92);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8, -1, 0);
    glScalef(0.2, 2, 5);
    drawCube1(0.53, 0.81, 0.92, 0.53, 0.81, 0.92);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 5.1, 0);
    glScalef(5, 0.1, 7);
    drawCube1(0.75, 0.75, 0.75, 0.75, 0.75, 0.75);
    glPopMatrix();

    glPushMatrix();
    glScalef(5, 0.1, 7);
    glTranslatef(-1, -5, 0);
    drawCube1(0.75, 0.75, 0.75, 0.75, 0.75, 0.75);
    glPopMatrix();
}

/**
 * @brief Draw a single bed.
 */
void singleBed() {
    glPushMatrix();
    glScalef(0.1, 0.5, 0.7);
    glTranslatef(-2, -0.5, 8.7); // Adjust the z-axis position
    drawCube1(0.863, 0.078, 0.235, 0.431, 0.047, 0.141);
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 0.2, 0.7);
    glTranslatef(0, -0.5, 8.7); // Adjust the z-axis position
    drawCube1(0.957, 0.643, 0.376, 0.482, 0.322, 0.188);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0.5, 7.); // Adjust the z-axis position
    glRotatef(20, 0, 0, 1);
    glScalef(0.1, 0.15, 0.28);
    drawCube1(1.0, 0.627, 0.478, 1.0, 0.627, 0.478);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.4, 0.45, 6.1); // Adjust the z-axis position
    glScalef(0.5, 0.05, 0.65);
    drawCube1(0.255, 0.412, 0.882, 0.110, 0.180, 0.392);
    glPopMatrix();
}

/**
 * @brief Draw a table.
 */
void table() {
    glPushMatrix();
    glTranslatef(5, 1, 1); // Position the table top at the desired height
    glScalef(1.0, 0.05, 1.0); // Set the dimensions of the table top (adjust as needed)
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    GLfloat legY = -0.2;

    glPushMatrix();
    glTranslatef(5.2, legY, 1.6);
    glScalef(0.05, 0.4, 0.05);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.6, legY, 1.6);
    glScalef(0.05, 0.4, 0.05);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2, legY, 2.4);
    glScalef(0.05, 0.4, 0.05);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.6, legY, 2.4);
    glScalef(0.05, 0.4, 0.05);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();
}

/**
 * @brief Draw a chair.
 */
void chair() {
    GLfloat legY = -0.2;

    glColor3f(0.36, 0.25, 0.20); // Dark Brown

    glPushMatrix();
    glTranslatef(6.2, 0.44, 4.8);
    glScalef(0.25, 0.025, 0.25);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.2, 0.5, 5.4);
    glScalef(0.25, 0.33, 0.025);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.2, legY, 4.8);
    glScalef(0.025, 0.3, 0.025);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.8, legY, 4.8);
    glScalef(0.025, 0.3, 0.025);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.2, -0.2, 5.2);
    glScalef(0.025, 0.3, 0.025);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.8, legY, 5.2);
    glScalef(0.025, 0.3, 0.025);
    drawCube1(0.627, 0.322, 0.176, 0.3135, 0.161, 0.088);
    glPopMatrix();
}

/**
 * @brief Draw a window.
 */
void window() {
    glPushMatrix();
    glTranslatef(-0.9, 1.3, 6.5);
    glScalef(0.0001, 0.6, 0.3);
    drawCube1(1.0, 1.0, 1.0, 0.05, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9, 1.3, 6.5);
    glScalef(0.04, 0.6, 0.0001);
    drawCube1(0.8, 0.6, 0.4, 0.4, 0.3, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9, 1.3, 7.4);
    glScalef(0.04, 0.6, 0.0001);
    drawCube1(0.8, 0.6, 0.4, 0.4, 0.3, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7, 3.0, 6.5);
    glScalef(0.0001, 0.05, 0.4);
    drawCube1(0.7, 0.6, 0.5, 0.35, 0.3, 0.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 1.32, 6.5);
    glScalef(0.0001, 0.02, 0.34);
    drawCube1(0.7, 0.6, 0.5, 0.35, 0.3, 0.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.87, 2.4, 6.5);
    glScalef(0.0001, 0.02, 0.3);
    drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.87, 1.9, 6.5);
    glScalef(0.0001, 0.02, 0.3);
    drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.87, 1.3, 7.0);
    glScalef(0.0001, 0.6, 0.02);
    drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5);
    glPopMatrix();
}







void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1.000, 1,1, 0.0};
    
    glPushMatrix();
    glTranslatef (5, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    switchOne=true;
    
    if(switchOne == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}


/**
 * @brief Function to set up and enable the first light source.
 */
void lightOne() {
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 5.0, 8.0, 1.0 };

    glEnable(GL_LIGHT0);

    amb1 = true;
    diff1 = true;
    spec1 = true;

    if (amb1 == true) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    } else {
        glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
    }

    if (diff1 == true) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    } else {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
    }

    if (spec1 == true) {
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    } else {
        glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
    }

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

/**
 * @brief Function to display the scene.
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);

    glEnable(GL_LIGHTING);
    lightOne();
    room();
    singleBed();
    cupboard();
    window();
    table();
    chair();
    lightBulb1();
    glDisable(GL_LIGHTING);
    glFlush();
    glutSwapBuffers();
}

/**
 * @brief Function to handle keyboard input.
 * @param key The pressed key.
 * @param x The x-coordinate of the mouse pointer.
 * @param y The y-coordinate of the mouse pointer.
 */
void myKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move eye point upwards along Y axis
            eyeY += 1.0;
            break;
        case 's': // Move eye point downwards along Y axis
            eyeY -= 1.0;
            break;
        case 'a': // Move eye point left along X axis
            eyeX -= 1.0;
            break;
        case 'd': // Move eye point right along X axis
            eyeX += 1.0;
            break;
        case 'o': // Zoom out
            eyeZ += 1;
            break;
        case 'i': // Zoom in
            eyeZ -= 1;
            break;
        case 'q': // Reset to default eye point and ref point
            eyeX = 4.0;
            eyeY = 2.0;
            eyeZ = 15.0;
            refX = 0.0;
            refY = 0.0;
            refZ = 0.0;
            break;
        case 'j': // Move ref point upwards along Y axis
            refY += 1.0;
            break;
        case 'n': // Move ref point downwards along Y axis
            refY -= 1.0;
            break;
        case 'b': // Move ref point left along X axis
            refX -= 1.0;
            break;
        case 'm': // Move ref point right along X axis
            refX += 1.0;
            break;
        case 'k':  // Move ref point away from the screen/along z axis
            refZ += 1;
            break;
        case 'l': // Move ref point towards the screen/along z axis
            refZ -= 1;
            break;
        case 'e': // Turn on/off ambient lamp light
            if (amb3 == false) {
                amb3 = true;
                break;
            } else {
                amb3 = false;
                break;
            }
        case 'r':
            if (diff3 == false) {
                diff3 = true;
                break;
            } else {
                diff3 = false;
                break;
            }
        case 't':
            if (spec3 == false) {
                spec3 = true;
                break;
            } else {
                spec3 = false;
                break;
            }
        case 27:    // Escape key
            exit(1);
    }

    glutPostRedisplay();
}


/**
 * @brief Function to set up the full-screen perspective projection.
 * @param w Width of the window.
 * @param h Height of the window.
 */
void fullScreen(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    float ratio = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60, ratio, 1, 500);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    // Print usage instructions
    cout << "To move Eye point:" << std::endl;
    cout << "w: up" << std::endl;
    cout << "s: down" << std::endl;
    cout << "a: left" << std::endl;
    cout << "d: right" << std::endl;
    cout << "i: zoom in" << std::endl;
    cout << "o: zoom out" << std::endl;
    cout << "      " << std::endl;
    cout << "To move Camera point:" << std::endl;
    cout << "j: up" << std::endl;
    cout << "n: down" << std::endl;
    cout << "b: left" << std::endl;
    cout << "m: right" << std::endl;
    cout << "l: move nearer" << std::endl;
    cout << "k: move far" << std::endl;
    cout << "      " << std::endl;
    cout << "Press q to move to the default position" << std::endl;
    cout << "      " << std::endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Assignment-2 Hostel Bedroom");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutMainLoop();

    return 0;
}