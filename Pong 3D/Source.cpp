#include<glut.h>
#include<iostream>


#define windowSize 600


GLfloat Cx = 0, Cy = 5, Cz = 4;


GLfloat red[] = { 1, 0, 0, 1 };
GLfloat green[] = { 0,1,0,1 };
GLfloat blue[] = { 0,0,1,1 };
GLfloat yellow[] = { 1,1,0,1 };
GLfloat black[] = { 0,0,0,1 };
GLfloat mainLightPosition[] = { 0,1,0,1 };

GLdouble translateX = 0;
GLdouble translateY = 0.25 + 0.16;
GLdouble translateValue = 0.05;


GLdouble rotateDegree = 10;
GLdouble rotateValue = 10;

#define barSpeed 0.1
//Top Bar
float topBarMinX = -1.9;
float topBarMaxX = 1.9;
float topBarRightPos = 0.75;
float topBarLeftPos = -0.75;
float topBarTranslate = barSpeed;
float topBarTranslateValue = 0;

//Bottom Bar
float bottomBarMinX = -1.9;
float bottomBarMaxX = 1.9;
float bottomBarRightPos = 0.75;
float bottomBarLeftPos = -0.75;
float bottomBarTranslate = barSpeed;
float bottomBarTranslateValue = 0;


//Ball
#define ballRadius 0.25
GLfloat ballXTranslateValue = 0;
GLfloat ballYTranslateValue = ballRadius + 0.16;
GLfloat ballZTranslateValue = 0;

//ball positions
GLfloat ballXPos = ballXTranslateValue + ballRadius;
GLfloat ballZPos = ballZTranslateValue + ballRadius;

//ball max
GLfloat ballXMinPos = -1.9 + 2.4 * ballRadius;
GLfloat ballXMaxPos = 2 - ballRadius;
GLfloat ballZMinPos = -1.9 + 3 * ballRadius;
GLfloat ballZMaxPos = 1.9 - ballRadius;

//ball speed
#define ballSpeed 0.025
GLfloat ballXSpeed = ballSpeed;
GLfloat ballZSpeed = ballSpeed;

//Temporary Speed
GLfloat ballXTemporarySpeed = 0;
GLfloat ballZTemporarySpeed = 0;

int score1 = 0;
int score2 = 0;

bool x1 = false;
bool x2 = false;

void reset() {
    ballXTranslateValue = 0;
    ballZTranslateValue = 0;
}

void MyInit()
{
    glClearColor(0.2, 0.2, 0.2, 1);
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

void timer(int) {

    if (!x1 && !x2) {
        glutPostRedisplay();
    }

    glutTimerFunc(1000 / 60, timer, 0);

    //Move Ball in X Axis
    if (ballXPos >= ballXMaxPos) {
        ballXSpeed = -ballXSpeed;
    }
    else if (ballXPos <= ballXMinPos) {
        ballXSpeed = -ballXSpeed;
    }
    ballXTranslateValue += ballXSpeed;

    //Move Ball in Z Axis
    if (ballZPos <= ballZMinPos &&/*collide with top bar*/(ballXPos > topBarLeftPos && ballXPos < topBarRightPos)) {
        ballZSpeed = -ballZSpeed;
    }
    else if (ballZPos < ballZMinPos &&/*don't collide*/!(ballXPos > topBarLeftPos && ballXPos < topBarRightPos)) {
        if (score1 == 4) {
            x1 = true;
        }
        score1++;
        reset();
    }
    if (ballZPos > ballZMaxPos &&/*collide with bottom bar*/(ballXPos > bottomBarLeftPos && ballXPos < bottomBarRightPos)) {
        ballZSpeed = -ballZSpeed;
    }
    else if (ballZPos > ballZMaxPos && /*don't collide*/!(ballXPos > bottomBarLeftPos && ballXPos < bottomBarRightPos)) {
        if (score2 == 4) {
            x2 = true;
        }
        score2++;
        reset();
    }
    ballZTranslateValue += ballZSpeed;
}

void text(GLfloat x, GLfloat y, const char* s, void* font) {
    glRasterPos2f(x, y); //define position

    const char* string = s;	 //your text

    while (*string) {
        glutBitmapCharacter(font, *string++);
    }
}

void text(GLfloat x, GLfloat y, char s) {

    glRasterPos2f(x, y); //define position
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 48 + s);
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
    glLightfv(GL_LIGHT0, GL_POSITION, mainLightPosition);

    gluLookAt(Cx, Cy, Cz,
        0, 0, 0,
        0, 1, 0);

    //    Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

    //TODO Draw plane and color it to green
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glPushMatrix();
            glScalef(1, 0.08, 1);
            glutSolidCube(4);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Right Wall and color it to green
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glPushMatrix();
            glTranslatef(1.9, 0.32, 0);
            glScalef(0.05, 0.08, 1);
            glutSolidCube(4);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Left Wall and color it to green
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glPushMatrix();
            glTranslatef(-1.9, 0.32, 0);
            glScalef(0.05, 0.08, 1);
            glutSolidCube(4);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Sphere and color it to red
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
        glPushMatrix();
            glTranslatef(ballXTranslateValue, translateY, ballZTranslateValue);
            glRotatef(rotateDegree,0,0,1);
            glutSolidSphere(ballRadius, 100, 100);
            ballXPos = ballXTranslateValue + ballRadius;
            ballZPos = ballZTranslateValue + ballRadius;
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Top Bar and color it to blue
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glPushMatrix();
            glTranslatef(topBarTranslateValue, 0.2 * 1.25, -1.75);
            glScalef(1, 0.2, 0.2);
            glutSolidCube(1.25);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Bottom Bar and color it to blue
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glPushMatrix();
            glTranslatef(bottomBarTranslateValue, 0.2 * 1.25, 1.75);
            glScalef(1, 0.2, 0.2);
            glutSolidCube(1.25);
        glPopMatrix();
    glPopAttrib();

    //TODO Draw Text
    text(-1.9, 2.9, "player 1 ", GLUT_BITMAP_8_BY_13);
    text(-1.30, 2.9, score1);
    text(-1.97, 2.7, "player 2 ", GLUT_BITMAP_8_BY_13);
    text(-1.36, 2.7, score2);

    if (x1) {
        glColor3f(1, 1, 1);
        text(-0.55, 1.20, "Player 1 Win", GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3f(1, 1, 1);
        text(-0.70, 0.85, "Press r to Replay", GLUT_BITMAP_9_BY_15);
    }
    if (x2) {
        glColor3f(1, 1, 1);
        text(-0.55, 1.20, "Player 2 Win", GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3f(1, 1, 1);
        text(-0.70, 0.85, "Press r to Replay", GLUT_BITMAP_9_BY_15);
    }

    glutSwapBuffers();
}

void Key(unsigned char key, int x, int y)
{
    if (key == 27) {
        exit(0);
    }
    if (key == 'a' && bottomBarLeftPos > bottomBarMinX) {
        bottomBarRightPos += -bottomBarTranslate;
        bottomBarLeftPos += -bottomBarTranslate;
        bottomBarTranslateValue += -bottomBarTranslate;
    }
    if (key == 'd' && bottomBarRightPos < bottomBarMaxX) {
        bottomBarRightPos += bottomBarTranslate;
        bottomBarLeftPos += bottomBarTranslate;
        bottomBarTranslateValue += bottomBarTranslate;
    }
    if (key == 'r') {
        score1 = 0;
        score2 = 0;
        ballXSpeed = ballSpeed;
        ballZSpeed = ballSpeed;
        x1 = false;
        x2 = false;
        reset();
        glutPostRedisplay();
    }

    if (key == ' ') {
        if (ballXSpeed == 0) {
            ballXSpeed = ballXTemporarySpeed;
            ballXTemporarySpeed = 0;
        }
        else if (ballXSpeed != 0) {
            ballXTemporarySpeed = ballXSpeed;
            ballXSpeed = 0;
        }
        if (ballZSpeed == 0) {
            ballZSpeed = ballZTemporarySpeed;
            ballZTemporarySpeed = 0;
        }
        else if (ballZSpeed != 0) {
            ballZTemporarySpeed = ballZSpeed;
            ballZSpeed = 0;
        }
    }

    switch (key)
    {
        case 'x': Cx = Cx - 0.5;   break;
        case 'X': Cx = Cx + 0.5;   break;

        case 'y': Cy = Cy - 0.5;   break;
        case 'Y': Cy = Cy + 0.5;   break;

        case 'z': Cz = Cz - 0.5;   break;
        case 'Z': Cz = Cz + 0.5;   break;
    }
}

//TODO Void specialKeys
void specialKeys(int key, int x, int y)
{
    //Top Bar Movement
    if (key == GLUT_KEY_LEFT && topBarLeftPos > topBarMinX) {
        topBarRightPos += -topBarTranslate;
        topBarLeftPos += -topBarTranslate;
        topBarTranslateValue += -topBarTranslate;
    }

    else if (key == GLUT_KEY_RIGHT && topBarRightPos < topBarMaxX) {
        topBarRightPos += topBarTranslate;
        topBarLeftPos += topBarTranslate;
        topBarTranslateValue += topBarTranslate;
    }

    //Move ball in Y Axis
    else if (key == GLUT_KEY_F1) {
        translateY += translateValue;
    }
    else if (key == GLUT_KEY_F2) {
        translateY -= translateValue;
    }
    glutPostRedisplay();


    if (key == GLUT_KEY_PAGE_DOWN) {
        if (ballXSpeed > 0 && ballXSpeed != ballSpeed) {
            ballXSpeed -= 0.005;
        }
        else if (ballXSpeed < 0 && ballXSpeed != -ballSpeed) {
            ballXSpeed += 0.005;
        }
        if (ballZSpeed > 0 && ballZSpeed != ballSpeed) {
            ballZSpeed -= 0.005;
        }
        else if (ballZSpeed < 0 && ballZSpeed != -ballSpeed) {
            ballZSpeed += 0.005;
        }
    }

    if (key == GLUT_KEY_PAGE_UP) {
        if (ballXSpeed > 0 && ballXSpeed != -ballSpeed) {
            ballXSpeed += 0.005;
        }
        else if (ballXSpeed < 0 && ballXSpeed != ballSpeed) {
            ballXSpeed -= 0.005;
        }
        if (ballZSpeed > 0 && ballXSpeed != -ballSpeed) {
            ballZSpeed += 0.005;
        }
        else if (ballZSpeed < 0 && ballXSpeed != ballSpeed) {
            ballZSpeed -= 0.005;
        }
    }
}

//TODO Main
int main(int argC, char* argV[])
{
    glutInit(&argC, argV);
    glutInitWindowSize(windowSize, windowSize);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowSize) / 2,
        (glutGet(GLUT_SCREEN_HEIGHT) - windowSize) / 2);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Pong 3D");
    MyInit();
    glutDisplayFunc(Draw);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(Key);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}