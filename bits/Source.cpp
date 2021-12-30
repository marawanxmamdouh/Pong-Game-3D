#include<windows.h>
#include<GL/glu.h>
#include<glut.h>
#include<math.h>
#include<iostream>

//GLfloat blue[] = { 56/255, 148/255, 255/255, 1.0 };
//GLfloat green[] = { 103/255, 180/255, 71/255, 1.0 };
//GLfloat green[] = { 0.4, 0.7, 0.28, 1 };

GLfloat Cx = 0, Cy = 5, Cz = 4;
GLfloat red[] = { 1, 0, 0, 1 };
GLfloat green[] = {0,1,0,1};
GLfloat blue[] = {0,0,1,1};
GLfloat mainLightPosition[] = {0,1,0,1};

GLdouble translateX = 0;
GLdouble translateY = 0.25 + 0.16;
GLdouble translateZ = 0;
GLdouble translateValue = 0.05;


GLdouble rotateDegree = 0;
GLdouble rotateValue = 10;

//Top Bar
float topBarMinX = -50;
float topBarMaxX = 50;
float topBarTranslate = 0;

//Bottom Bar
float barDoun_min_x = -50;
float barDoun_max_x = 50;
float barDoun_translate = 0;

//
float xball = 0;
float yball = 0;

float speed_x = speed;
float speed_y = speed;

float ballRadius = 17;
float min_x = 0;
float max_x = 0;
float min_y = 0;
float max_y = 0;

float now_x = 0;
float now_y = 0;

int score1 = 0;
int score2 = 0;

bool x1 = false;
bool x2 = false;

void reset() {
    xball = 0;
    yball = 0;
}

void MyInit()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Square(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    glColor3f(1, 0, 0);
    Square(V0, V1, V2, V3);
    glColor3f(0, 1, 0);
    Square(V4, V5, V6, V7);
    glColor3f(0, 0, 1);
    Square(V0, V4, V7, V3);
    glColor3f(1, 1, 0);
    Square(V1, V5, V6, V2);
    glColor3f(1, 0, 1);
    Square(V3, V2, V6, V7);
    glColor3f(0, 1, 1);
    Square(V0, V1, V5, V4);
}

void Draw()
{
 /*   GLfloat V[8][3] = {
                            {-0.5, 0.5, 0.5},
                            { 0.5, 0.5, 0.5},
                            { 0.5,-0.5, 0.5},
                            {-0.5,-0.5, 0.5},
                            {-0.5, 0.5,-0.5},
                            { 0.5, 0.5,-0.5},
                            { 0.5,-0.5,-0.5},
                            {-0.5,-0.5,-0.5}
    };*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glLightfv(GL_LIGHT0,GL_POSITION, mainLightPosition);

    gluLookAt(Cx, Cy, Cz,
              0, 0, 0,
              0, 1, 0);

//    Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

    //TODO Draw plane and color it to green
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,green);
        glPushMatrix();
            glScalef(1, 0.08, 1);
            glutSolidCube(4);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Right Wall and color it to green
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,green);
        glPushMatrix();
            glTranslatef(1.9,0.32,0);
            glScalef(0.05, 0.08, 1);
            glutSolidCube(4);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Left Wall and color it to green
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,green);
        glPushMatrix();
            glTranslatef(-1.9,0.32,0);
            glScalef(0.05, 0.08, 1);
            glutSolidCube(4);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Sphere and color it to red
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,red);
        glPushMatrix();
            glTranslatef(translateX,translateY,translateZ);
            glRotatef(rotateDegree,0,0,1);
            glutSolidSphere(0.25,100,100);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Top Bar and color it to blue
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,blue);
        glPushMatrix();
            glTranslatef(0,0.2*1.25,-1.75);
            glScalef(1, 0.2, 0.2);
            glutSolidCube(1.25);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Bottom Bar and color it to blue
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,blue);
        glPushMatrix();
            glTranslatef(0,0.2*1.25,1.75);
            glScalef(1, 0.2, 0.2);
            glutSolidCube(1.25);
        glPopMatrix();
        glPopAttrib();
    glutSwapBuffers();
}

void Key(unsigned char ch, int x, int y)
{
    switch (ch)
    {
    case 'x': Cx = Cx - 0.5;   break;
    case 'X': Cx = Cx + 0.5;   break;

    case 'y': Cy = Cy - 0.5;   break;
    case 'Y': Cy = Cy + 0.5;   break;

    case 'z': Cz = Cz - 0.5;   break;
    case 'Z': Cz = Cz + 0.5;   break;
    }
    glutPostRedisplay();
}

//TODO Void specialKeys
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) {
        translateX += translateValue;
        rotateDegree += rotateValue;
    }
    else if (key == GLUT_KEY_LEFT){
        translateX -= translateValue;
        rotateDegree += rotateValue;
}
    else if (key == GLUT_KEY_UP){
        translateZ -= translateValue;
        rotateDegree += rotateValue;
        }
    else if (key == GLUT_KEY_DOWN){
        translateZ += translateValue;
        rotateDegree += rotateValue;
        }
    else if (key == GLUT_KEY_F1)
        translateY += translateValue;
    else if (key == GLUT_KEY_F2)
        translateY -= translateValue;
    glutPostRedisplay();
}

//TODO Main
int main(int argC, char* argV[])
{
    glutInit(&argC, argV);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("pong 3d");
    MyInit();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}