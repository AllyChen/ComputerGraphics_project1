#include "main.h"

static int draw_mode = 1;
static int action = 0;
static GLuint inner_mode = GL_SMOOTH;
static GLuint tex_state = GL_TRUE;
static int state_chang;

float time = 0;

float Up_joint_angle = 20, Down_joint_angle = 50;
float walk_angle = -40;
float jump_angle, Left_angle, Right_angle, Back_angle;
float Hand_transformer_x, Hand_transformer_y, Hand_transformer_z, Hand_transformer_angle;
float Body_transformer_x, Body_transformer_y;
float tail_transformer_y;
int Button_color_R = 255;
int Button_color_G = 255;
int Button_color_B = 255;
float Button_transformer_z;
float Fire_value;
float fly_x, fly_y;
float fly_x_last, fly_y_last;// fly from where
bool fly = false;
bool Mickey_Hello = false;
int a;
bool transformer = false;
bool MickeyRun = false;

int state = 1;

static int WinWidth = 600;
static int WinHeight = 600;

void DrawCube(float Length, float Width, float Height)
{
	glBegin(GL_QUADS);

	//bottom
	//glNormal3f();
	glVertex3f(-Length/2, -Height/2, Width/2);
	glVertex3f(Length / 2, -Height / 2 , Width / 2);
	glVertex3f(Length / 2, -Height / 2, -Width / 2);
	glVertex3f(-Length / 2, -Height / 2, -Width / 2);

	//top
	//glNormal3f();
	glVertex3f(-Length / 2, Height / 2, Width / 2);
	glVertex3f(Length / 2, Height / 2, Width / 2);
	glVertex3f(Length / 2, Height / 2, -Width / 2);
	glVertex3f(-Length / 2, Height / 2, -Width / 2);

	//right
	//glNormal3f();
	glVertex3f(Length / 2, Height / 2, Width / 2);
	glVertex3f(Length / 2, -Height / 2, Width / 2);
	glVertex3f(Length / 2, -Height / 2, -Width / 2);
	glVertex3f(Length / 2, Height / 2, -Width / 2);


	//left
	//glNormal3f();
	glVertex3f(-Length / 2, Height / 2, Width / 2);
	glVertex3f(-Length / 2, -Height / 2, Width / 2);
	glVertex3f(-Length / 2, -Height / 2, -Width / 2);
	glVertex3f(-Length / 2, Height / 2, -Width / 2);

	//front
	//glNormal3f();
	glVertex3f(-Length / 2, Height / 2, Width / 2);
	glVertex3f(Length / 2, Height / 2, Width / 2);
	glVertex3f(Length / 2, Height / 2, -Width / 2);
	glVertex3f(-Length / 2, Height / 2, -Width / 2);


	//back
	//glNormal3f();
	glVertex3f(-Length / 2, Height / 2, -Width / 2);
	glVertex3f(-Length / 2, -Height / 2, -Width / 2);
	glVertex3f(Length / 2, -Height / 2, -Width / 2);
	glVertex3f(Length / 2, Height / 2, -Width / 2);

	glEnd();
}

void DrawCylinder(GLUquadric*   quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks)
{
	glPushMatrix();
	gluCylinder(quad, base, top, height, slices, stacks);
	glPopMatrix();
	
	glPushMatrix();
	glScaled(1, 1, 0.00001);
	glutSolidSphere(base, slices, slices);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, height);
	glScaled(1, 1, 0.00001);
	glutSolidSphere(base, slices, slices);
	glPopMatrix();
}

void drawMark()
{
	glTranslatef(-80.0, -60.0, 0.0);
	glRotated(-20, 0, 0, 1);
	glScaled(0.5, 0.5, 0.5);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(30.0, 50.0, 50.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25.0, 30.0, 0.0);
	glColor3ub(255, 255, 255);
	glutSolidSphere(25.0, 50.0, 50.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25.0, 30.0, 0.0);
	glColor3ub(255, 255, 255);
	glutSolidSphere(25.0, 50.0, 50.0);
	glPopMatrix();
}

void finger()
{
	glTranslatef(-8, 0.0, 0.0);
	glRotatef(45, 0, 0, 1);
	// Up_finger
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScaled(0.8, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
	// finger_joint
	glTranslatef(-8, 0.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(3.0, 50.0, 15.0);
	glPopMatrix();
	// Down_finger
	glTranslatef(-5.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScaled(0.5, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();

	glScaled(1, -1, -1);
	glTranslatef(-5, 18.0, 0.0);
	// Up_finger
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScaled(0.8, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
	// finger_joint
	glTranslatef(-8, 0.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(3.0, 50.0, 15.0);
	glPopMatrix();
	// Down_finger
	glTranslatef(-5.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScaled(0.5, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
}

void tail()
{
	glRotated(walk_angle, 0, 1, 0);
	glRotated(jump_angle, 1, 0, 0);
	// joint
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(3.0, 50.0, 50.0);
	glPopMatrix();
	// tail
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidCube(2);
	glPopMatrix();
	for (int i = 0; i < 10; i++)
	{
		glTranslatef(0.0, -1.0, -2.0);
		glPushMatrix();
		glColor3ub(0, 0, 0);
		glutSolidCube(2);
		glPopMatrix();
	}

	glTranslatef(0.0, 0.0, -2.0);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidCube(2);
	glPopMatrix();

	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, 0.5, -2.0);
		glPushMatrix();
		glColor3ub(0, 0, 0);
		glutSolidCube(2);
		glPopMatrix();
	}

}

void leg()
{
	// Leg-----------
	// joint
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	glColor3ub(0, 0, 0);
	glutSolidSphere(3.0, 50.0, 15.0);
	glPopMatrix();
	// leg
	glPushMatrix();
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glColor3ub(0, 0, 0);
	glTranslatef(0.0, -11.5, .0);
	glRotated(90, 1, 0, 0);
	DrawCylinder(quadratic, 5.f, 5.f, 15.f, 32, 32);
	glPopMatrix();
	// shoes
	glPushMatrix();
	glColor3ub(255, 255, 0);
	glTranslatef(-5.0, -26.5, 4.0);
	glRotated(40, 0, 1, 0);
	glScaled(5.0, 1.0, 3.0);
	glutSolidCube(5);
	glPopMatrix();
	// fire
	glPushMatrix();
	glTranslatef(0.0, -30, 0.0);
	glRotated(90, 1, 0, 0);
	glColor3ub(255, 0, 0);
	glutSolidCone(Fire_value, Fire_value, 50, 50);
	glPopMatrix();
}

void draw_head(void)
{
	// Head---------
	glPushMatrix();					
	glScalef(1.5, 1, 1);
	glColor3ub(0, 0, 0);
	glutSolidCube(30);
	glPopMatrix();
	
	// Ear----------
	// Left
	glPushMatrix();
	glTranslatef(-25.0, 20.0, 0.0);
	glColor3ub(0, 0, 0);
	glutSolidSphere(15.0, 50.0, 15.0);
	glPopMatrix();
	// Right
	glPushMatrix();
	glTranslatef(25.0, 20.0, 0.0);
	glColor3ub(0, 0, 0);
	glutSolidSphere(15.0, 50.0, 15.0);
	glPopMatrix();
	
	// Nose---------
	glPushMatrix();
	glTranslatef(0.0, -5.0, 18.0);
	glColor3ub(0, 0, 0);
	glutSolidSphere(6.0, 50.0, 5.0);
	glTranslatef(0.0, 0.0, 7.0);
	glColor3ub(0, 0, 0);
	glutSolidSphere(2.0, 50.0, 5.0);
	glPopMatrix();
	
	// Eye----------
	// Left
	glPushMatrix();
	glTranslatef(-15.0, 0.0, 15.0);
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 15.0);
	glPopMatrix();
	// Right
	glPushMatrix();
	glTranslatef(15.0, 0.0, 15.0);
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 15.0);
	glPopMatrix();

	// tail
	glPushMatrix();
	glTranslatef(0.0, -22.0 + tail_transformer_y, -15.0);
	tail();
	glPopMatrix();
}

void draw_leftBody(void)
{
	// Body---------
	glPushMatrix();
	glScaled(1.0, 1.0, 2.0);
	glColor3ub(255, 0, 0);
	//glutWireCube(15);
	glutSolidCube(15);
	glPopMatrix();
	// button
	glPushMatrix();
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glColor3ub(Button_color_R, Button_color_G, Button_color_B);
	glTranslatef(0.0, 0.0, Button_transformer_z);
	DrawCylinder(quadratic, 5.f, 5.f, 17.f, 32, 32);
	glPopMatrix();		
	// leg
	glPushMatrix();
	glTranslatef(-5.0, 0.0, 0.0);
	glRotated(walk_angle, 1, 0, 0);
	glRotatef(jump_angle/2, 1, 0, 0);
	leg();
	glPopMatrix();
}

void draw_rightBoday(void)
{
	// Body---------
	glPushMatrix();
	glScaled(1.0, 1.0, 2.0);
	glColor3ub(255, 0, 0);
	//glutWireCube(15);
	glutSolidCube(15);
	glPopMatrix();
	// button
	glPushMatrix();
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glColor3ub(Button_color_R, Button_color_G, Button_color_B);
	glTranslatef(0.0, 0.0, Button_transformer_z);
	DrawCylinder(quadratic, 5.f, 5.f, 17.f, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0, 0.0, 0.0);
	glRotated(90, 0, 1, 0);
	glRotated(-walk_angle, 0, 0, 1);
	glRotatef(jump_angle/2, 0, 0, 1);
	leg();
	glPopMatrix();
}

void draw_leftHand(void)
{
	// Hand-----------
	// Up_joint
	glRotatef(Up_joint_angle, 0, 0, 1);
	glRotatef(-jump_angle, 0, 0, 1);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 50.0);
	glPopMatrix();
	// Up_arm
	glTranslatef(-15.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(2, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
	// Down_joint
	glTranslatef(-15, 0.0, 0.0);
	glRotatef(Down_joint_angle, 0, 0, 1);
	glRotatef(-jump_angle*2, 0, 0, 1);
	glRotated(walk_angle*1.5, 0, 0, 1);
	glPushMatrix();	
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 50.0);
	glPopMatrix();
	// Down_arm
	glTranslatef(-10.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(1, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
	// wrist
	glTranslatef(-10.0, 0.0, 0.0);
	glRotatef(-jump_angle * 20, 1, 0, 0);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 15.0);
	glPopMatrix();
	// palm
	glTranslatef(-10.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(8.0, 50.0, 15.0);
	glPopMatrix();
	// finger
	glTranslatef(-10.0, 0.0, 0.0);
	glRotated(-90, 0, 0, 1);
	glPushMatrix();
	finger();
	glPopMatrix();
}

void draw_rightHand(void)
{
	// Hand-----------
	// Up_joint
	glRotatef(Up_joint_angle, 0, 0, 1);
	glRotatef(-jump_angle, 0, 0, 1);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 50.0);
	glPopMatrix();
	// Up_arm
	glTranslatef(-15.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(2, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
	// Down_joint
	glTranslatef(-15, 0.0, 0.0);
	glRotatef(Down_joint_angle, 0, 0, 1);
	glRotatef(-jump_angle * 2, 0, 0, 1);
	glRotated(-walk_angle*1.5, 0, 0, 1);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 50.0);
	glPopMatrix();
	// Down_arm
	glTranslatef(-10.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(1, 0.3, 0.3);
	glutSolidCube(15);
	glPopMatrix();
	// wrist
	glTranslatef(-10.0, 0.0, 0.0);
	glRotatef(-jump_angle * 20, 1, 0, 0);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(5.0, 50.0, 15.0);
	glPopMatrix();
	// palm
	glTranslatef(-10.0, 0.0, 0.0);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glutSolidSphere(8.0, 50.0, 15.0);
	glPopMatrix();
	// finger
	glTranslatef(-10.0, 0.0, 0.0);
	glRotated(-90, 0, 0, 1);
	glPushMatrix();
	finger();
	glPopMatrix();
}

void draw(void)
{  
	glTranslatef(0.0 + fly_x, -20.0 + jump_angle + fly_y, -200.0);
	
	if (action == 7) {
		glTranslatef(sin(time / 180 * 3.1415) * 100, -20.0, cos(time / 180 * 3.1415) * 100 - 100.0);
		glRotated(time + 90, 0, 1, 0);
	}

	glPushMatrix();
	glRotated(Left_angle - Right_angle, 0, 1, 0);
	//--------------------------Turn
	glPushMatrix();
		glTranslatef(0.0, 20.0, 0.0);
		glRotatef(-walk_angle/3, 0, 1, 0);
		draw_head();//
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-7.5 - Body_transformer_x, -2.5 + Body_transformer_y, 0.0);
		draw_leftBody();//
	glPopMatrix();
	glPushMatrix();
		glTranslatef(7.5 + Body_transformer_x, -2.5 + Body_transformer_y, 0.0);
		draw_rightBoday();//
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-18 - Hand_transformer_x, 0.0 + Body_transformer_y, 0.0 - Hand_transformer_z);
		glScaled(0.5, 0.5, 0.5);
		glRotatef(-walk_angle, 1, 0, 0);
		glRotatef(-Hand_transformer_angle, 0, 1, 0);
		draw_leftHand();//
	glPopMatrix();
	glPushMatrix();
		glTranslatef(18 + Hand_transformer_x, 0.0 + Body_transformer_y, 0.0 - Hand_transformer_z);
		glScaled(-0.5, 0.5, -0.5);
		glRotatef(-walk_angle, 1, 0, 0);
		glRotatef(Hand_transformer_angle, 0, 1, 0);
		draw_rightHand();//
	glPopMatrix();
	//--------------------------Turn
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(inner_mode);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	WinWidth = w;
	WinHeight = h;
	GLfloat aspect;
	aspect = (GLfloat)w / (GLfloat)h;
	//glViewport(0,0,(GLsizei)w,(GLsizei)h);
	if (aspect > 1.0f)
		glViewport((w - h) / 2.0f, 0, (GLsizei)h, (GLsizei)h);
	else
		glViewport(0, (h - w) / 2.0f, (GLsizei)w, (GLsizei)w);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
	GLfloat  ambientLight[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat  diffuseLight[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat  specular[] = { 0.3f, 0.3f, 0.3f, 0.0f }; // the light from look at
	GLfloat  specref[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat  pos[] = { 0.0f, 20.0f, -50.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 32);
	// backgroundColor
	glClearColor(0.8f, 0.5f, 1.0f, 0.0f);
}

void Mickey_Fire_value(void)
{
	if (fly_y > fly_y_last && Fire_value < 10) Fire_value++;
	if (fly_y < fly_y_last && fly_y < 15 && Fire_value > 0) Fire_value--;

	fly_y_last = fly_y;
}

void Mickey_itial()
{
	walk_angle = 0;
	jump_angle = 0;
	
	// transform hand
	if (Hand_transformer_angle > 0)
	{
		if (Hand_transformer_y > 0) Hand_transformer_y--;				
		Hand_transformer_angle--;
	}
	// transform Body
	if (Hand_transformer_angle == 0)
	{
		if (Up_joint_angle != 20) Up_joint_angle++;
		if (Down_joint_angle != 50) Down_joint_angle++;
		if (Hand_transformer_x > 0) Hand_transformer_x--;
		if (Hand_transformer_z > 0) Hand_transformer_z = Hand_transformer_z - 0.5;
	}
	if (Body_transformer_y > 0) Body_transformer_y--;
	if (Body_transformer_y == 0 && Body_transformer_x > 0) Body_transformer_x = Body_transformer_x - 0.5;	
	// transform tail
	if (tail_transformer_y > 0) tail_transformer_y--;
	// change button color
	if (Button_color_R < 255) Button_color_R++;
	if (Button_color_G < 255) Button_color_G++;
	if (Button_transformer_z > 0) Button_transformer_z = Button_transformer_z - 0.5;
	// No transformer
	if (
		Up_joint_angle == 20 &&
		Down_joint_angle == 50 &&
		walk_angle == -40 &&
		(
		(int)jump_angle | (int)Left_angle | (int)Right_angle | (int)Back_angle |
		(int)Hand_transformer_x | (int)Hand_transformer_y | (int)Hand_transformer_z | 
		(int)Hand_transformer_angle | (int)Body_transformer_x | (int)Body_transformer_y |
		(int)tail_transformer_y 
			) == 0 &&
		Button_color_R == 255 &&
		Button_color_G == 255 &&
		Button_transformer_z == 0)transformer = false;
	// fly
	if (fly_y > 0) fly_y--;
	if (fly_y == 0 && fly_x > 0) fly_x--;
	if (fly_y == 0 && fly_x < 0) fly_x++;
	Mickey_Fire_value();

	if (Left_angle > 0) Left_angle--;
	if (Right_angle > 0) Right_angle--;
}

void Mickey_Walk(void)
{	
	if (walk_angle == -40) a=1;
	if (walk_angle == 40) a=-1;

	walk_angle = walk_angle + a;

	glutPostRedisplay();// replay draw
}

void Mickey_Run(void)
{	
	if (time >= 360) time = 0;
	else time = time + 1;

	if (walk_angle == -40) a = 5;
	if (walk_angle == 40) a = -5;
	walk_angle = walk_angle + a;

	glutPostRedisplay();// replay draw
}

void Mickey_Jump(void)
{	
	if (jump_angle == 0) a = 1;
	if (jump_angle == 40) a = -1;

	jump_angle = jump_angle + a;

	glutPostRedisplay();// replay draw
}

void Mickey_TurnLeft(void)
{
	if (a < 90) Left_angle++;
	
	a++;

	glutPostRedisplay();// replay draw
}

void Mickey_TurnRight(void)
{
	if (a < 90) Right_angle++;
	
	a++;

	glutPostRedisplay();// replay draw
}

void Mickey_transformer(void)
{
	// transform hand
	if (Hand_transformer_angle < 90) 
	{
		if (Up_joint_angle != 0) Up_joint_angle--;
		if (Down_joint_angle != 0) Down_joint_angle--;
		if (Hand_transformer_x < 15) Hand_transformer_x++;
		if (Hand_transformer_z < 15) Hand_transformer_z = Hand_transformer_z + 0.5;
		Hand_transformer_angle++;
	}
	// transform Body
	if (Hand_transformer_angle == 90)
	{
		if (Hand_transformer_y < 10) Hand_transformer_y++;
		if (Body_transformer_y < 15) Body_transformer_y++;
	}
	if (Body_transformer_x < 25) Body_transformer_x = Body_transformer_x + 0.5;
	// transform tail
	if (tail_transformer_y < 20) tail_transformer_y++;
	// change button color
	if (Button_color_R > 0) Button_color_R--;
	if (Button_color_G > 0) Button_color_G--;
	if (Button_transformer_z < 10) Button_transformer_z = Button_transformer_z + 0.5;

	transformer = true;
}

void keyin(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's': // stand
		action = 0;
		MickeyRun = false;
		break;
	case 'w': // walk
		walk_angle = -40;
		jump_angle = 0;
		action = 1;
		MickeyRun = false;
		break;
	case 'j':
		walk_angle = 0;
		jump_angle = 0;
		action = 2;
		MickeyRun = false;
		break;	
	case 'l': // TurnLeft
		walk_angle = 0;
		jump_angle = 0;
		a = 0;
		action = 3;
		MickeyRun = false;
		break;
	case 'r': // TurnRight
		walk_angle = 0;
		jump_angle = 0;
		a = 0;
		action = 4;
		MickeyRun = false;
		break;
	case 't': // transformer
		walk_angle = 0;
		jump_angle = 0;
		action = 5;
		MickeyRun = false;
		break;	
	case 'm':
		PlaySound(TEXT("Mickey.wav"), NULL, SND_SYNC);
		break;
	case 'f':		
		jump_angle = 0;
		walk_angle = -40;
		Left_angle = 0;
		Right_angle = 0;
		time = 0;
		action = 7;
		break;
	}
}

void directional_key(int key, int x, int y)
{
	switch (key)
	{
	
	case GLUT_KEY_UP:
		walk_angle = 0;
		jump_angle = 0;
		fly_y++;		
		fly = true;
		action = 6;
		break;
	case GLUT_KEY_DOWN:
		if (fly_y > 0)
		{
			walk_angle = 0;
			jump_angle = 0;
			fly_y--;
			fly = true;
			action = 6;
		}
		break;
	case GLUT_KEY_RIGHT:
		fly_x++;
		action = 6;
		break;
	case GLUT_KEY_LEFT:
		fly_x--;
		action = 6;
		break;
	
	}
}

void timerFunction(int value)
{
	switch (action)
	{
	case 0:
		Mickey_itial();
		break;
	case 1:
		Mickey_Walk();
		break;
	case 2:
		Mickey_Jump();
		break;
	case 3:
		Mickey_TurnLeft();
		break;
	case 4:
		Mickey_TurnRight();
		break;
	case 5:
		Mickey_transformer();
		break;
	case 6:
		Mickey_Fire_value();
		break;
	case 7:
		Mickey_Run();
		break;
	}
	glutPostRedisplay();
	glutTimerFunc(5, timerFunction, 1);
}

int main(int argc, char** argv)
{
	int main_menu, action_menu, count_menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	//glutInitWindowSize(1200,600);	//< Dual view
	glutInitWindowSize(WinWidth, WinHeight);	//< Single view

	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	init();
	printf("(event) : (key)  \n");
	printf("stand & remove transformer : S \n");
	printf("turn left : L \n");
	printf("turn right : R \n");
	printf("walk : W \n");
	printf("fast walk : F \n");
	printf("jump : J \n");
	printf("transformer : T \n");
	printf("fly : ¡ô¡õ¡ö ¡÷ \n");
	printf("mickey speak : M \n");
	action = 0;
	Mickey_itial();

	glutKeyboardFunc(keyin);
	glutSpecialFunc(directional_key);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(5, timerFunction, 1);
	glutMainLoop();
	return 0;

}
