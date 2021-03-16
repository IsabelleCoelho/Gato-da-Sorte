#include <GL/glut.h>
#include <stdlib.h>

GLfloat anguloHorizontal = 0.0;
static int braco = 0;
static bool levantado = true;
void init(){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void definicaoIluminacao(){
    float luzAmbiente[] = {0.1f, 0.1f, 0.1f, 1.0f};
    float luzDifusa[] = {0.4f, 0.4f, 0.4f, 1.0f};
    float luzEspecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float posicaoLuz[] = {0.0f, 50.0f, 50.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    float luzAmbiente1[] = {0.4f, 0.4f, 0.0f, 1.0f};
    float luzDifusa1[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float luzEspecular1[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float posicaoLuz1[] = {0.0f, -50.0f, 50.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
}

void animacao(){
    if(levantado == true){
        braco = (braco + 1) % 90;
        glutPostRedisplay();
    }
    else{
        braco = (braco-1) % 90;
        glutPostRedisplay();
    }
    if(braco == 0){
        if(levantado == true){
            levantado = false;
            braco = 85;
        }
        else{
            levantado = true;
        }
    }
}

void display(){
    glClear (GL_COLOR_BUFFER_BIT);
    definicaoIluminacao();
    glPushMatrix();
    glRotatef(anguloHorizontal,0.0f,1.0f,0.0f); 
        //corpo
        glPushMatrix();
        glutSolidSphere(0.77, 30, 16);
        glPopMatrix();
        //cabeca
        glPushMatrix();
            glTranslatef(0.0, 1.1, 0.0);
            glutSolidSphere(0.5, 30, 16);
            //orelhaDireita
            glPushMatrix();
            glTranslatef(-0.32, 0.32, 0.0);
            glRotatef (270, 1.0, 0.0, 0.0);  
            glRotatef(-45,0.0,1.0,0.0);
            glScalef (0.3, 0.3, 0.3); 
            glutSolidCone(0.6, 1.5, 20, 16);
            glPopMatrix();
            //orelhaEsquerda
            glPushMatrix();
            glTranslatef(0.32, 0.32, 0.0);
            glRotatef (270, 1.0, 0.0, 0.0);  
            glRotatef(45,0.0,1.0,0.0);
            glScalef (0.3, 0.3, 0.3); 
            glutSolidCone(0.6, 1.5, 20, 16);
            glPopMatrix();
        glPopMatrix();
        //braco
        glPushMatrix();
            glTranslatef (0.75, 0.0, 0.0);
            glRotatef ((GLfloat) braco, 1.0, 0.0, 0.0);
            glTranslatef (0.0, 0.5, 0.0);
            //chamada da função responsável pela animação da pata
            animacao();
            glPushMatrix();
                glScalef (0.2, 0.8, 0.35);
                glutSolidSphere (0.6, 10, 12);
            glPopMatrix();
            //ponta da pata
            glTranslatef (0.0, 0.5, 0.0);
            glPushMatrix();
                glScalef (0.2, 0.5, 0.5);
                glutSolidSphere (0.15, 10, 20);
            glPopMatrix();
            glColor3f(1.0,1.0,1.0);
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void remodelar (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

void teclado (unsigned char key, int x, int y){
    switch (key) {
        case 'P':
            braco = (braco + 5) % 180;
            glutPostRedisplay();
            break;
        case 'p':
            braco = (braco - 5) % 180;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void mouse (int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_UP) {
            anguloHorizontal += 15;
            display(); 
        }  
    }
    if (button == GLUT_RIGHT_BUTTON){
        if (state == GLUT_UP) {
            anguloHorizontal -= 15;
            display();
        }  
    }
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Gato da Sorte");
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(remodelar);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
