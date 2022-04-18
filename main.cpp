#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>
#include <time.h>

/**
*  @programa: PC02_CV_Coronacion-Huamani_Dominguez-Acosta.cpp
*
*  @hora: 10:00 AM
*
*  @autor:  Coronación Huamaní, Maribel Inés (19200008)
*  @autor:  Dominguez Acosta ,Prish Anthony (19200054)
*
*
*  @fecha:  06-01-2022
*
*/

void rosa_polar(int N, int M, float trasZ);
void rosa_polar_cubo();
void definir_cubo();
void eje();

static GLfloat theta[] = {0.0,0.0,0.0};
static GLboolean GActivo = false;
static GLint axis = -1 ;
static GLint color = 1;
static GLint grosor = 1;
static GLint trazado = 0;
GLint M=1,N=1;
GLdouble const radio=1.0;
static GLboolean EjeActivo = true;

void iniciar(void)
{
     glClearColor (1.0, 1.0, 1.0, 0.0);
     glColor3f (1.0, 0.0, 0.0);
     glLineWidth(2.0);
     glShadeModel (GL_FLAT);
}

void myReshape(int w, int h)
{
     glViewport(0,0,(GLsizei)w, (GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-20.0,20.0,-20.0,20.0,-30.0,30.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void display(void)
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glPopMatrix();
     gluLookAt(0,0.0,5,0,0.0,4,0,1,0);
     glPushMatrix();
     glRotatef(theta[0],1.0,0.0,0.0);//Eje x
     glRotatef(theta[1],0.0,1.0,0.0);//Eje y
     glRotatef(theta[2],0.0,0.0,1.0);//Eje z
     glColor3f(1,1,0);
     glutWireCube(20);
     glColor3f(0.5,0.5,0.5);
     glutSolidCube(20);
     if(GActivo){
        definir_cubo();
     }
     glPopMatrix();
     glColor3f(1.0,0,0);
     if(EjeActivo){
        eje();
     }
     glFlush();
     glutSwapBuffers();
}

//Funcion que realiza el giro del cuerpo geometrico
void CubeSpin()
{
     theta[axis] += 0.5;
     if(theta[axis]>360) theta[axis] -= 360.0;
     display();
}

void eje()
{
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(18,0);
    glVertex2f(0,0);
    glVertex2f(0,18);
    glVertex3f(-15,-8,-18);
    glVertex3f(0,0,0);
    glEnd();
}

void definir_cubo(){

    //Definir el patron de trazado
    if(trazado==1){
        glLineStipple(1,0x00FF);
    }else
    if(trazado==2){
        glLineStipple(2,0x00FF);
    }
    glEnable(GL_LINE_STIPPLE);
    //Definir el color
    if(color==1){
        glColor3f(1.0,0.0,0.0);
    }else
    if(color==2){
        glColor3f(0.0,1.0,0.0);
    }else
    if (color==3){
        glColor3f(0.0,0.0,1.0);
    }else
    if (color==4){
        //Definir numero aleatorio
        float r = (1+rand()%100)/100.0;
        float g = (1+rand() % 100)/100.0;
        float b = (1+rand() % 100)/100.0;
        glColor3f(r,g,b);
    }

    //Definir el grosor
    if(grosor==1){
        glLineWidth(1.0);
    }else
    if(grosor==2){
        glLineWidth(2.0);
    }else
    if(grosor==3){
        glLineWidth(3.0);
    }
    //Dibujar la figura
    rosa_polar_cubo();
    glDisable(GL_LINE_STIPPLE);
}

void rosa_polar_cubo()
{
    rosa_polar(N, M,10.0001);
    rosa_polar(N,M,-10.0001);

    glPushMatrix();
    glRotatef(90,1.0,0.0,0.0);
    rosa_polar(N,M,10.0001);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90,1.0,0.0,0.0);
    rosa_polar(N,M,10.0001);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0,0,1.0,0.0);
    rosa_polar(N,M,10.0001);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90.0,0.0,1.0,0.0);
    rosa_polar(N,M,10.0001);
    glPopMatrix();
}


void rosa_polar(int N, int M,float trasZ)
{
    int radio = 8;
    float fr;
    GLfloat ang, x, y;
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0f; ang < M*2*M_PI; ang += M*M_PI/100) //M_PI=es una constante pi de la libreria math.h
    {
        fr =radio*sin(ang*N/M);
        x = fr*cos(ang);
        y = fr*sin(ang);
        glVertex3f(x,y,trasZ);
    }
    glEnd();
}

void menu_trazado(int opcion)
{
    switch(opcion){
        case 1: trazado=1; break;
        case 2: trazado=2;break;
    }
}

void menu_grosor(int opcion)
{
     switch(opcion){
        case 1: grosor=1; break;
        case 2: grosor=2; break;
        case 3: grosor=3; break;
    }
}

void menu_color(int opcion)
{
    switch(opcion){
        case 1: color=1; break;
        case 2: color=2; break;
        case 3: color=3; break;
        case 4: color=4; break;
    }
}

void menu_tipo_rosas(int opcion)
{
    switch(opcion){
        case 1: M=1;N=2;break;
        case 2: M=1;N=3; break;
        case 3: M=2;N=3; break;
        case 4: M=3;N=5; break;
        case 5: M=1+rand()%9;
                N=1+rand()%9;
                break;
    }
}

void menu_grafico_rosas(int opcion)
{
    switch(opcion){
        case 1: GActivo = true; break;
        case 2: GActivo = false; break;
        case 3: exit(0); break;
    }
}

void menu_eje_coordenada(int opcion)
{
    switch(opcion){
        case 1: EjeActivo = true; break;
        case 2: EjeActivo = false; break;
        case 3 : exit(0); break;
    }
}

void menu_rotaciones(int opcion)
{
    switch(opcion){
        case 1: axis = 0; break;//Eje x
        case 2: axis = 1; break;//Eje y
        case 3: axis = 2; break;//Eje z
        case 4 : exit(0); break;
    }
}

void menu_principal(int opcion)
{
    switch(opcion){
        case 7: exit( -1 );
    }
}

int main(int argc, char **argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(700,700);
     glutCreateWindow("PC02_CORONACION_DOMINGUEZ");

     int submenu_trazado = glutCreateMenu(menu_trazado);
     glutAddMenuEntry("Opcion 1",1);
     glutAddMenuEntry("Opcion 2",2);

     int submenu_grosor=glutCreateMenu(menu_grosor);
     glutAddMenuEntry("Grosor 1",1);
     glutAddMenuEntry("Grosor 2",2);
     glutAddMenuEntry("Grosor 3",3);

     int submenu_color=glutCreateMenu(menu_color);
     glutAddMenuEntry("Rojo",1);
     glutAddMenuEntry("Verde",2);
     glutAddMenuEntry("Azul",3);
     glutAddMenuEntry("Aleatorio",4);

     int submenu_tipo_rosas =glutCreateMenu(menu_tipo_rosas);
     glutAddMenuEntry("M=1 , N=2",1);
     glutAddMenuEntry("M=1 , N=3",2);
     glutAddMenuEntry("M=2 , N=3",3);
     glutAddMenuEntry("M=3 , N=5",4);
     glutAddMenuEntry("Aleatorio",5);

     int submenu_grafico_rosas =glutCreateMenu(menu_grafico_rosas);
     glutAddMenuEntry("Grafico activado",1);
     glutAddMenuEntry("Grafico desactivado",2);

     int submenu_eje_coordenada = glutCreateMenu(menu_eje_coordenada);
     glutAddMenuEntry("Activado",1);
     glutAddMenuEntry("Desactivado",2);

     int submenu_rotaciones=glutCreateMenu(menu_rotaciones);
     glutAddMenuEntry("Eje X",1);
     glutAddMenuEntry("Eje Y",2);
     glutAddMenuEntry("Eje Z",3);

     int menu=glutCreateMenu(menu_principal);
     glutAddSubMenu("Rotaciones",submenu_rotaciones);
     glutAddSubMenu("Eje de coordenada",submenu_eje_coordenada);
     glutAddSubMenu("Grafico de rosas",submenu_grafico_rosas);
     glutAddSubMenu("Tipo de rosas",submenu_tipo_rosas);
     glutAddSubMenu("Color",submenu_color);
     glutAddSubMenu("Grosor",submenu_grosor);
     glutAddSubMenu("Patron de trazado",submenu_trazado);
     glutAddMenuEntry("Esc",7);

     glutAttachMenu(GLUT_RIGHT_BUTTON);
     iniciar();
     glutReshapeFunc(myReshape);
     glutDisplayFunc(display);
     glutIdleFunc(CubeSpin);
     glEnable(GL_DEPTH_TEST);
     glutMainLoop();

 return 0;
}
