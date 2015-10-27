#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"
#include <string>
#include <iostream>

#define PI 3.1415

#define SOLID_CLOSED_CYLINDER(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS) \
		glPushMatrix();\
		gluCylinder(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS); \
		glRotatef(180, 1,0,0); \
		gluDisk(QUAD, 0.0f, BASE, SLICES, 1); \
		glRotatef(180, 1,0,0); \
		glTranslatef(0.0f, 0.0f, HEIGHT); \
		gluDisk(QUAD, 0.0f, TOP, SLICES, 1); \
		glTranslatef(0.0f, 0.0f, -HEIGHT); \
		glPopMatrix();

GLUquadricObj *quadratic;

GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
//GLfloat luzAmbiente[4]={0.9,0.9,0.3,1.0};
GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
//GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
GLfloat posicaoLuzSol[4]={60.0, 70.0, 55.0, 1.0};
GLfloat posicao_lampada[] = {-10.0, 7.0, -46.0, 1};

GLuint texture_id[10];

GLint WIDTH =800;
GLint HEIGHT=600;

// camera
GLfloat obs[3]={-200.0,10.0,-50.0};
GLfloat look[3]={-10.0,1.0,-10.0};

static int eixoy = 0;

GLfloat tetaxz=10;
GLfloat raioxz=-60;

GLuint  predio, grade, cadeiras;


void reshape(int width, int height){
	WIDTH=width;
	HEIGHT=height;
	glViewport(0,0,(GLint)width,(GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0,width/(float)height,0.1,200.0);
	glMatrixMode(GL_MODELVIEW);
}

void compoe_divisorias_aluminio_janela1(void)
{

	//janela1 vertical
	glColor3f(0.8 , 0.8, 0.8);
	//janela1 parede vertical1
	glPushMatrix();
	//tras/frente - cima/baixo - direita/esquerda
	glTranslatef (-34.0, 0, -75.0);
	//largura(z), altura(y), espessura(x)
	glScalef (0.1, 2, 0.06);
	glutSolidCube (5.0);
	glPopMatrix();


	glPushMatrix();
	//tras/frente - cima/baixo - direita/esquerda
	glTranslatef (-34.0, 0, -62.0);
	//largura(z), altura(y), espessura(x)
	glScalef (0.1, 2, 0.06);
	glutSolidCube (5.0);
	glPopMatrix();

}


void compoe_divisorias_aluminio_janela2(void)
{

	GLfloat p_inicial = 0.0;


	for(int i = 0; i < 15; ++i)
	{
		if( i == 0 || i == 2)
			goto end;
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-35.0, 0, (-30.25 + p_inicial));
		//largura, altura, espessura
		glScalef (0.1, 2, 0.06);
		glutSolidCube (5.0);
		glPopMatrix();
		end:
		p_inicial += 6.76;

	}

}

void compoe_janela_aluminio_janela3(void)
{

	GLfloat p_inicial = 0.0;

	for(int i = 0; i < 28; ++i)
	{
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-34.0, 15, -80.7 + p_inicial);
		//largura(z), altura(y), espessura(x)
		glScalef (0.1, 2, 0.1);
		glutSolidCube (5.0);
		glPopMatrix();
		p_inicial += 6.25;

	}

	glPushMatrix();
	//tras/frente - cima/baixo - direita/esquerda(posicao)
	glTranslatef (-34.00, 17.0, 6.0);
	//largura(z), altura(y), espessura(x)
	glScalef (0.1, 0.1, 34.5);
	glutSolidCube (5.0);
	glPopMatrix();


}

void compoe_janela_aluminio(void)
{

	//janela1 vertical
	glColor3f(0.8 , 0.8, 0.8);
	//janela1 parede vertical1
	glPushMatrix();
	//tras/frente - cima/baixo - direita/esquerda
	glTranslatef (-34.0, 0, -68.2);
	//largura(z), altura(y), espessura(x)
	glScalef (0.1, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();


	//janela1 terreo horizontal
	glPushMatrix();
	//tras/frente - cima/baixo - direita/esquerda(posicao)
	glTranslatef (-34.00, 2.0, -68.0);
	//largura, altura, espessura
	glScalef (0.1, 0.1, 5.0);
	glutSolidCube (5.0);
	glPopMatrix();


	GLfloat p_inicial = 0.0;
	for(int i = 0; i < 7; ++i){

		//janela2 parede vertical1
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-35.0, 0, (-19.5 + p_inicial));
		//largura, altura, espessura
		glScalef (0.1, 2, 0.1);
		glutSolidCube (5.0);
		glPopMatrix();



	}

	//janela2 terreo base
	glPushMatrix();
	//tras/frente - cima/baixo - direita/esquerda(posicao)
	glTranslatef (-34.00, 2.0, 18.0);
	//largura(z), altura(y), espessura(x)
	glScalef (0.1, 0.1, 20.5);
	glutSolidCube (5.0);
	glPopMatrix();

}

void compoe_grade(void){
	GLUquadricObj *quadric;
	// inicia a composicao da grade
	grade = glGenLists(1);
	glNewList(grade, GL_COMPILE);
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	GLfloat p_inicial = 5.2;
	//compoe 8 grades para janela2
	for(int i = 0; i < 8; i++){
		p_inicial += 1.0;
		//grade
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-36.0, 10 - p_inicial, 18.0);
		//largura, altura, espessura
		glScalef (0.2, 0.2, 200);
		glutSolidCube (0.5);
		glPopMatrix();
	}

	p_inicial = 5.2;
	//compoe 8 grades para janela1
	for(int i = 0; i < 8; i++){
		p_inicial += 1.0;
		//grade
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-36.0, 10 - p_inicial, -68.0);
		//largura, altura, espessura
		glScalef (0.2, 0.2, 47);
		glutSolidCube (0.5);
		glPopMatrix();
	}
	p_inicial = -9.8;
	//compoe 8 grades para janela3
	for(int i = 0; i < 8; i++){
		p_inicial += 1.0;
		//grade
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-36.0, 10 - p_inicial, 5.7);
		//largura, altura, espessura
		glScalef (0.2, 0.2, 344);
		glutSolidCube (0.5);
		glPopMatrix();
	}

	//compoe  grades para porta de entrada
	for(int i = 0; i < 14; i++){
		p_inicial += 1.0;
		//grade
		glPushMatrix();
		//tras/frente - cima/baixo - direita/esquerda
		glTranslatef (-34.2, 3.5 - p_inicial, -48.7);
		//largura, altura, espessura
		glScalef (0.2, 0.2, 15);
		glutSolidCube (0.5);
		glPopMatrix();
	}


}

//TODO chamar a função para desenhas todas as paredes

//Desenha as paredes e adiciona as texturas previamente carregadas
void compoe_texturas(GLfloat x_trans, GLfloat y_trans, GLfloat  z_trans,
		GLfloat x_scalef, GLfloat y_scalef, GLfloat z_scalef, int tex_id, GLfloat value_cube)
{
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	glTranslatef (z_trans, y_trans, x_trans);
	glScalef (z_scalef, y_scalef, x_scalef);
	glBindTexture(GL_TEXTURE_2D, texture_id[tex_id]);
	//TODO nao está recebendo o paramentro da funcao
	glutSolidCube (10.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);


}
void compoe_cadeiras1(void){

	GLUquadricObj *quadric;
	cadeiras = glGenLists(1);
	glNewList(cadeiras, GL_COMPILE);
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	GLfloat lado;
	for(int i = 0; i < 6; ++i){
		lado = i * 6.0;
		if (i > 2){
			lado += 8;
		}

		//Composição pés
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (8-lado, -52.8, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (6-lado,-52.8, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (8-lado, -54.2, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (6-lado, -54.2, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();

		//Composicao assento
		glPushMatrix();
		glTranslatef (7-lado, -6.8, -54.3);
		glScalef(4.0,0.3,3.0);
		quadric=gluNewQuadric();
		glColor3f(0.3,0.5,1);
		gluSphere(quadric,0.5,15,12);
		glPopMatrix();

		//Composicao encosto
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,1,0,0);
		glTranslatef (7-lado, -55.5, 5);
		SOLID_CLOSED_CYLINDER(quadric, 0.15, 0.15, 2.2, 30, 1)
		glPopMatrix();
		glPushMatrix();
		glTranslatef (7-lado, -4.75, -55.5);
		glRotatef(-15,1,0,1);
		glScalef(4,3,0.5);
		quadric=gluNewQuadric();
		glColor3f(0.3,0.5,1);
		gluSphere(quadric,0.5,15,12);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef (7-lado, -7, -56);
		SOLID_CLOSED_CYLINDER(quadric, 0.15, 0.15, 2.2, 30, 1)
		gluDeleteQuadric(quadric);
		glPopMatrix();
	}
}

void compoe_cadeiras2(void){

	GLUquadricObj *quadric;
	cadeiras = glGenLists(1);
	glNewList(cadeiras, GL_COMPILE);
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	GLfloat lado;
	for(int i = 0; i < 5; ++i){
		lado = i * 8.7;
		if (i > 2){
			lado += 3;
		}

		//Composicao pes
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (72-lado, -52.8, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (70-lado,-52.8, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (72-lado, -54.2, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		gluQuadricTexture(quadric, GL_TRUE);
		glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef (70-lado, -54.2, 6.8);
		SOLID_CLOSED_CYLINDER(quadric, 0.1, 0.1, 3.3, 30, 5)
		gluDeleteQuadric(quadric);
		glPopMatrix();


		//Composicao assentos
		glPushMatrix();
		glTranslatef (70.5-lado, -6.8, -54.3);
		glScalef(4.0,0.3,3.0);
		quadric=gluNewQuadric();
		glColor3f(0.3,0.5,1);
		gluSphere(quadric,0.5,15,12);
		glPopMatrix();

		//Composicao encosto
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,1,0,0);
		glTranslatef (70-lado, -55.7, 5.0);
		SOLID_CLOSED_CYLINDER(quadric, 0.15, 0.15, 2.2, 30, 1)
		glPopMatrix();
		glPushMatrix();
		glTranslatef (70-lado, -4.75, -55.5);
		glRotatef(-15,1,0,1);
		glScalef(4,3,0.5);
		quadric=gluNewQuadric();
		glColor3f(0.3,0.5,1);
		gluSphere(quadric,0.5,15,12);
		glPopMatrix();
		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricOrientation(quadric, GLU_INSIDE);
		glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef (70-lado, -7, -56);
		SOLID_CLOSED_CYLINDER(quadric, 0.15, 0.15, 2.2, 30, 1)
		gluDeleteQuadric(quadric);
		glPopMatrix();
	}
}


void desenhar_grades_laterais(int SLICES, int STACKS, float SCALE_X, float SCALE_Y, float
		SCALE_Z) {
	glEnable(GL_NORMALIZE);

	GLfloat aux = 0.0;
	//Esquerda
	glColor3f(0.372549, 0.623529, 0.623529); // azul
	for(int i = 0; i < 1000; ++i)
	{
		glPushMatrix();
		glTranslatef(-10,28 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	glColor3f(1.0, 0.8, 0.0);
	aux = 0.0;

	for(int i = 0; i < 300; ++i)
	{
		glPushMatrix();
		glTranslatef(-10,20 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,19 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,18 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,15 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,14 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,13 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,10 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10, 9 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,8 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,5 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,4 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,3 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,0 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-1 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-2 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-5 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-6 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 300; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-7 + aux,-81);
		glRotatef(90,1.,0.0, 0.0);
		gluPartialDisk(quadratic, 15.0, 16.0, 20, 4, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	//direita 1
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,5 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,4 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,3 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,0 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-1 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-2 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-4 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-6 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-7 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-8 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-10,-9 + aux,75);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(90,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 6.0, 7.0, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

	//parte2
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,5 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,4 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,3 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,2 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,1 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-2 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-3 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-4 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-6 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-7 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-8 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}
	aux = 0.0;
	for(int i = 0; i < 250; ++i)
	{

		glPushMatrix();
		glTranslatef(-22,-9 + aux,87);
		glRotatef(270,1.0,0.0, 0.0);
		glRotatef(270,0.0,0.0, 1.0);
		gluPartialDisk(quadratic, 5.5, 6.5, 20, 50, 90.0, 180.0);
		glPopMatrix();
		aux -= 0.005;
	}

}


void compoe_portas_estaticas(void)
{

	//Seleciona as texturas
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glTranslatef (60.5, 10.0, 43.0);
	glBegin(GL_QUADS);

	//coordendas da porta
	glTexCoord2f(6.0f, 5.0f); glVertex3f( 10.5f, -10.5f, -10.5f);
	glTexCoord2f(6.0f, 6.0f); glVertex3f( 10.5f,  10.5f, -10.5f);
	glTexCoord2f(5.0f, 6.0f); glVertex3f( 10.5f,  10.5f,  10.5f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f( 10.5f, -10.5f,  10.5f);
	glEnd();

	glTranslatef (0.0, 4.0, -43.0);
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.5f, -10.5f, -10.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.5f,  10.5f, -10.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.5f,  10.5f,  10.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.5f, -10.5f,  10.5f);

	glEnd();

	glBegin(GL_QUADS);

	glTexCoord2f(300.0f, 300.0f); glVertex3f(-7.5f, -7.5f, -7.5f);
	glTexCoord2f(301.0f, 300.0f); glVertex3f(-7.5f, -7.5f,  7.5f);
	glTexCoord2f(301.0f, 301.0f); glVertex3f(-7.5f,  7.5f,  7.5f);
	glTexCoord2f(300.0f, 301.0f); glVertex3f(-7.5f,  7.5f, -7.5f);

	glEnd();

	glTranslatef(-18,-3,-15);

	glNormal3f(1.0, 1.0f, 1.0f);

}

void desenha_predio(void){


	GLUquadricObj *quadric;

	/* inicia a composicao do predio */
	predio = glGenLists(1);
	glNewList(predio, GL_COMPILE);

	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);


	glColor3f(1,1,1);

	compoe_portas_estaticas();

	//quadro
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	//z, y, x
	glTranslatef (38.7, 1.0, -55.5);
	//largura, altura, espessura
	glScalef (4, 1.5, 0.05);
	glutSolidCube (5.0);
	glPopMatrix();

	//placa formandos
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef (-4.0, 1., -33.2);
	glScalef (2.5, 1.5, 0.05);
	glutSolidCube (5.0);
	glPopMatrix();


	//teto1
	glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef (16.5, 10.0, 6.0);
	glScalef (20.0, -0.1, 34);
	glutSolidCube (5.0);
	glPopMatrix();

	//teto2
	glColor3f(0.8,0.8,0.8);
	glPushMatrix();
	glTranslatef (14.6, 21.0, 6.0);
	glScalef (21.0, -0.1, 34.6);
	glutSolidCube (5.0);
	glPopMatrix();


	//janela1 parede vertical1
	glColor3f(3, 3, 3);
	glPushMatrix();
	glTranslatef (-35.0, 0, -80.7);
	glScalef (0.5, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();


	//janela1 parede vertical2
	glPushMatrix();
	glTranslatef (-35.0, 0, -55.7);
	glScalef (0.5, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela2 parede vertical1
	glPushMatrix();
	glTranslatef (-35.0, 0, -33.0);
	glScalef (0.5, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela2 parede vertical2
	glPushMatrix();
	glTranslatef (-35.0, 0, 68.7);
	glScalef (0.5, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela3 primeiro andar base
	glPushMatrix();
	glTranslatef (-35.00, 10.0, 6.0);
	glScalef (0.5, 0.1, 34.8);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela3 primeiro andar superior
	glPushMatrix();
	glTranslatef (-35.00, 20.0, 6.0);
	glScalef (0.5, 0.1, 34.8);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela3 parede vertical1
	glPushMatrix();
	glTranslatef (-35.0, 15, -80.7);
	glScalef (0.5, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela3 parede vertical2
	glPushMatrix();
	glTranslatef (-35.0, 15, 93.0);
	//largura, altura, espessura
	glScalef (0.5, 2, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela1 terreo base
	glPushMatrix();
	glTranslatef (-35.00, -5.0, -68.0);
	glScalef (0.5, 0.1, 5.0);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela1 terreo superior
	glPushMatrix();
	glTranslatef (-35.00, 5.0, -68.0);
	glScalef (0.5, 0.1, 5.0);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela2 terreo base
	glPushMatrix();
	glTranslatef (-35.00, -5.0, 18.0);
	glScalef (0.5, 0.1, 20.5);
	glutSolidCube (5.0);
	glPopMatrix();

	//janela2 terreo superior
	glPushMatrix();
	glTranslatef (-35.00, 5.0, 18.0);
	glScalef (0.5, 0.1, 20.5);
	glutSolidCube (5.0);
	glPopMatrix();

	//piso
	compoe_texturas(6.0, -9.7, 13.5, 19, 0.3, 12.0, 1, 5.0);
	compoe_texturas(-44.0, -9.0, -74.0, 3.0, 0.3, 8.05, 0, 5.0);

	//grama1
	compoe_texturas(34.0, -10.0, -72.85, 12.5, 0.1, 6.05, 2, 5.0);

	//grama2
	compoe_texturas(-75.0, -10.0, -72.85, 4.5, 0.1, 6.05, 2, 0.1);

	//parede esquerda interna1
	compoe_texturas(-56.0, -0.1, -11.4, 0.1, 2.0, 4.3, 3, 5.0);

	//parede esquerda interna2
	glPushMatrix();

	glColor3f( 1.0, 1.0,1.0);
	glTranslatef (47.5, 0.0, -56.0);
	glScalef (7.5, 4.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede inteira bebedouro
	compoe_texturas(-68.0, 0.0, 28.5, 2.4, 2.0, 0.1, 3, 5.0);

	//parede inteira escada
	compoe_texturas(-68.0, 0.0, 10.0, 2.5, 2.0, 0.1, 3, 5.0);

	//parede direita interna1
	glPushMatrix();
	glColor3f( 1.0, 1.0,1.0);
	glTranslatef (-12, 0.0, -33.0);
	glScalef (8.7, 4.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede direita interna2
	glPushMatrix();
	glColor3f( 1.0, 1.0,1.0);
	glTranslatef (47.5, 0.0, -33.0);
	glScalef (7.5, 4.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede interna corredor professores
	compoe_texturas(17.5, 0.0, 10.0, 10.1, 2.0, 0.1, 3, 5.0);

	//parede interna corredor professores2
	compoe_texturas(29.5, 0.0, 29.5, 12.5, 2.0, 0.1, 3, 3.0);

	//parede interna final professores
	glPushMatrix();
	glColor3f( 1.0, 1.0,1.0);
	glTranslatef (-12, 0.0, 68.0);
	glScalef (8.7, 4.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede direita interna final corredor
	glPushMatrix();
	glColor3f( 1.0, 1.0,1.0);
	glTranslatef (38.7, 0.0, 92.0);
	glScalef (11.1, 4.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede esquerda1
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (16.5, 4.8, -80.7);
	glScalef (20.0, 6.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede esquerda1.1
	glPushMatrix();
	glColor3f(0.372549, 0.623529, 0.623529);
	glTranslatef (14.2, 22.5, -80.7);
	glScalef (21.0, 1, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede direita1.1
	glPushMatrix();
	glColor3f(0.372549, 0.623529, 0.623529);
	glTranslatef (14.2, 22.5, 92.7);
	glScalef (21.0, 1, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede traseira
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (66.5, 4.8, 6.0);
	glScalef (0.1, 6.1, 34.8);
	glutSolidCube (5.0);
	glPopMatrix();

	//vidro janela1
	glPushMatrix();
	glColor4f( 0.8, 0.8, 0.8, 0.3);
	glTranslatef (-33.5, 0, -68.1);
	glScalef (0.1, 2, 5.0);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte1.1
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (-33.5, 7.5, -67.2);
	glScalef (0.1, 1, 5.6);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte1.2
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (-33.5, -7.5, -67.2);
	glScalef (0.1, 1, 5.6);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte1.3
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (-33.5, 0.0, -54.5);
	glScalef (0.1, 2, 0.5);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte2.1
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (-33.5, 7.5, 16.0);
	glScalef (0.1, 1, 31);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte2.2
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	//glColor3f(1,1,1);
	//tras/frente - cima/baixo - direita/esquerda
	glTranslatef (-33.5, -7.5, 16.0);
	//largura, altura, espessura
	glScalef (0.1, 1, 21);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte2.3
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	//tras/frente - cima/baixo - direita/esquerda
	glTranslatef (-33.5, 0.0, -34.5);
	//largura, altura, espessura
	glScalef (0.1, 2, 0.7);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte3
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (-33.5, 7.5, -45.0);
	glScalef (0.1, 1, 3.4);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede frontal parte4
	glPushMatrix();
	glColor3f(0.372549, 0.623529, 0.623529); // azul
	glTranslatef (-38.5, 22.5, 6.3);
	glScalef (0.1, 1, 34.7);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede traseira parte2
	glPushMatrix();
	glColor3f(0.372549, 0.623529, 0.623529); // azul
	glTranslatef (66.5, 22.5, 6.3);
	glScalef (0.1, 1, 34.7);
	glutSolidCube (5.0);
	glPopMatrix();

	//porta entrada parte1
	glColor4f( 0.8, 0.8, 0.8, 0.3);
	glPushMatrix();
	glTranslatef (-33.5, -1.8, -50.0);
	glScalef (0.1, 4, 2.45);
	glutSolidCube (4.0);
	glPopMatrix();

	//parede direita2
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (16.5, 12.5, 93.0);
	glScalef (20, 3.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede direita3
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.0);
	glTranslatef (-5.5, 2.4, 93.0);
	glScalef (6.3, 1.1, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede direita4
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.0);
	glTranslatef (-5.5, -3.6, 93.0);
	glScalef (6.3, 0.7, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	//parede direita5
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.0);
	glTranslatef (-5.5, -8.3, 93.0);
	glScalef (6.3, 0.8, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	compoe_cadeiras1();
	compoe_cadeiras2();

	quadratic = gluNewQuadric();

	desenhar_grades_laterais(90, 100, 6.5, 8.6, 10.7);

	glColor3f(0,0,1.0);
	compoe_grade();
	compoe_janela_aluminio();
	compoe_janela_aluminio_janela3();
	compoe_divisorias_aluminio_janela1();
	compoe_divisorias_aluminio_janela2();

	glEndList();
}

void display(void){

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glDepthMask(GL_TRUE);
	glClearColor(0.5,0.5,0.5,0.5);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// calcula a posicao do observador
	obs[0]=raioxz*cos(2*PI*tetaxz/360);
	obs[2]=raioxz*sin(2*PI*tetaxz/360);
	gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);
	glShadeModel(GL_SMOOTH);

	glCallList(predio);
	glCallList(grade);
	glCallList(cadeiras);

	// porta entrada movel
	glColor4f( 0.8, 0.8, 0.8, 0.3);
	glPushMatrix();

	// eixo de rotação
	glTranslatef (-33.5, -1.8, -37.25);
	glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
	glTranslatef (33.5, 1.8, 37.25);
	glTranslatef (-33.5, -1.8, -40.0);
	glScalef (0.1, 4, 2.45);
	glutSolidCube (4.0);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void special(int key, int x, int y){
	switch (key) {
	case GLUT_KEY_UP:
		obs[1]=obs[1]+1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		obs[1] =obs[1]-1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		tetaxz=tetaxz+2;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		tetaxz=tetaxz-2;
		glutPostRedisplay();
		break;
	}
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 'a':
			if (eixoy == 90){
				break;
			}
			eixoy = (eixoy + 5);
			glutPostRedisplay();

			break;
	case 'f':
			if (eixoy == 0){
				break;
			}
			eixoy = (eixoy - 5);
			glutPostRedisplay();
			break;
	case 'w':
		raioxz=raioxz+1;
		glutPostRedisplay();
		break;
	case 's':
		raioxz=raioxz-1;
		glutPostRedisplay();
		break;
	case 27:
			exit(0);
			break;
	}
}

void carrega_texturas_arquivo(char *filename,int index)
{

	int width, height;
	unsigned char* image =
			SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	printf("%d %d\n", width, height);

	glGenTextures(1, &texture_id[index]);
	glBindTexture(GL_TEXTURE_2D, texture_id[index]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void inicia_texturas(){

	carrega_texturas_arquivo("piso_entrada.jpg",0);
	carrega_texturas_arquivo("piso_interno.jpg",1);
	carrega_texturas_arquivo("grama.jpg",2);
	carrega_texturas_arquivo("parede_externa.jpg",3);
	carrega_texturas_arquivo("porta.jpg"		 ,4);
}

//iluminacao
void iluminacao_externa(void)
{
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_AMBIENT, especularidade);


	// Define a concentração do brilho e que sera iluminado nas duas faces e
	// o tipo do material
	glMateriali(GL_FRONT_AND_BACK,GL_AMBIENT,especMaterial);


	// mistura de tipos de ilumminacao para ficar mais realista e a posicao que
	// ficara a luz(posicaoluz)
	//resultado da luz refletida no ambiente; é uma luz que vem de todas as direções;
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	//luz que vem de uma direção, atinge a superfície e é refletida em
	//todas as direções; assim, parece possuir o mesmo brilho independente
	//de onde a câmera está posicionada;
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	///simula a luz que se origina de um objeto; a cor emissiva de uma superfície
	//adiciona intensidade ao objeto, mas não é afetada por qualquer fonte de luz;
	//ela também não introduz luz adicional da cena.

	//glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuzSol );
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	// Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita o uso de iluminação
	glEnable(GL_LIGHT0);
	// permite habilitar o Z-Buffer.
	glEnable(GL_DEPTH_TEST);

}


void init(){

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	inicia_texturas();
	iluminacao_externa();
	desenha_predio();
}

//TODO corrigir o aspecto do predio assim que o projeto é executado.
//ao movimentar a camera as cores e texturas voltam ao normal
int main(int argc,char **argv){
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);

	if(!glutCreateWindow("Instituto de Computação - UFAL")) {
		printf("Erro ao carregar a janela.\n");
		exit(-1);
	}

	init();

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
