//kompajliraj sa g++ proba.cpp -o nesto -framework OpenGL -framework GLUT -Wno-deprecated

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>
using namespace std;
class Palica {
  float sirina, duzina, pozicija, brzina;
public:
  Palica(float sirina , float duzina, float pozicija){
    this->sirina = sirina;
    this->duzina = duzina;
    this->brzina = 0.025;
    this->pozicija = 0;
  };
  Palica(){
    this->sirina = 0.1;
    this->duzina = 0.05;
    this->brzina = 0.025;
    this->pozicija = 0;
  };
  void crtaj(){
    glBegin(GL_QUADS);
      glColor3f(1,1,1);
      glVertex3f(this->pozicija - this->sirina, -1, 0);
      glColor3f(1,0,0);
      glVertex3f(this->pozicija + this->sirina, -1, 0);
      glColor3f(1,0,0);
      glVertex3f(this->pozicija + this->sirina, -1 + this->duzina, 0);
      glColor3f(1,0,0);
      glVertex3f(this->pozicija - this->sirina, -1 + this->duzina, 0);
    glEnd();
  }
  void levo(double dt){
    this->pozicija -= this->pozicija - this->sirina > -1 ? this->brzina * dt : 0;
  }
  void desno(double dt){
    this->pozicija += this->pozicija + this->sirina < 1 ? this->brzina * dt : 0;
  }
  float getPozicija(){
    return this->pozicija;
  }
  float getSirina(){
    return this->sirina;
  }
  float getX(){
    return this->pozicija - this->sirina;
  }
  float getW(){
    return 2 * this->sirina;
  }
  float getH(){
    return this->duzina;
  }
  float getY(){
    return -1 + this->duzina;
  }
};
class Lopta {
  float x,y,brzina;
  int dx, dy;
public:
  Lopta(){
    this->y = -0.95;
    this->x = 0;
    this->brzina = 0.015;
    this->dx = 1;
    this->dy = 1;
  }
  Lopta(float x, float y, float brzina){
    this->y = y;
    this->x = x;
    this->brzina = brzina;
    this->dx = 1;
    this->dy = 1;
  }
  template <class t>
  bool udar(t T, int p){
    if (((this->x - 0.015 >= T.getX() && this->x - 0.015 <= T.getX() + T.getW())
        || (this->x + 0.015 >= T.getX() && this->x + 0.015 <= T.getX() + T.getW()))
        && ((this->y + 0.03 >= T.getY() - T.getH() && this->y + 0.03 <= T.getY())
        || (this->y <= T.getY() && this->y >= T.getY()-T.getH()))){
      cout << "Udar!" << p << '\n';
      return true;
    }
    return false;
  };
  void pisi(){
    cout<<"Ja sam Lopta :)"<<'\n';
  }
  void crtaj(){
    glBegin(GL_QUADS);
      glColor3f(1,1,1);
      glVertex3f(this->x - 0.015, this->y, 0);
      glColor3f(1,1,1);
      glVertex3f(this->x - 0.015, this->y + 0.03, 0);
      glColor3f(1,1,1);
      glVertex3f(this->x + 0.015, this->y + 0.03, 0);
      glColor3f(1,1,1);
      glVertex3f(this->x + 0.015, this->y, 0);
    glEnd();
  }
  void korak(){
    if (this->x + 0.015 >= 1 || this->x < -1){
      this->dx = -this->dx;
    }
    if (this->y + 0.03 >= 1){//}|| this->y < -1){
      this->dy = -this->dy;
    }
    this->x += this->brzina * this->dx;
    this->y += this->brzina * this->dy;
  }
  void obrniX(){
    this->dx = -this->dx;
  }
  void obrniY(){
    this->dy = -this->dy;
  }
  void setX(float x){
    this->x = x;
  }
  float getX(){
    return this->x;
  }
  float getY(){
    return this->y;
  }
};
class Cigla{
static int poeni, poz;
float x, y;
public:
  Cigla(){
    this->x = -1 + (this->poz % 10) * 0.2;
    this->y = 1 - ((int) this->poz++ / 10) * 0.05;
  }
  void pisi(){
    cout<<this->x<<'\n';
  }
  void crtaj(){
    glBegin(GL_QUADS);
      glColor3f(1,1,1);
      glVertex3f(this->x, this->y, 0);
      glColor3f(1,1,1);
      glVertex3f(this->x + 0.2, this->y, 0);
      glColor3f(1,1,1);
      glVertex3f(this->x + 0.2, this->y - 0.05, 0);
      glColor3f(1,1,1);
      glVertex3f(this->x, this->y - 0.05, 0);
      glColor3f(0.1f,0.4f,0.12f);
      glVertex3f(this->x + 0.005, this->y - 0.005, 0);
      glColor3f(0.1f,0.4f,0.12f);
      glVertex3f(this->x + 0.2 - 0.005, this->y - 0.005, 0);
      glColor3f(0.1f,0.4f,0.12f);
      glVertex3f(this->x + 0.2 -0.005, this->y - 0.05 + 0.005, 0);
      glColor3f(0.1f,0.4f,0.12f);
      glVertex3f(this->x + 0.005, this->y - 0.05 + 0.005, 0);
    glEnd();
  }
  float getX(){
    return this->x;
  }
  float getW(){
    return 0.2;
  }
  float getH(){
    return 0.05;
  }
  float getY(){
    return this->y;
  }
};
bool proba = false;
int Cigla::poz = 0;
int Cigla::poeni = 0;
bool levo = false, desno = false, start = false;
Palica stap(0.1,0.05,.0);
Lopta loptica;
double vreme = 0;
double dt = 0;
Cigla cigla[100];
void crtaj(){
  glClearColor(0.2235f -0.2f ,0.3059f - 0.2f ,0.4392f -0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(0,0,-1);
  stap.crtaj();
  if (start) {
    loptica.korak();
  } else{
    loptica.setX(stap.getPozicija());
  }
  loptica.crtaj();
  if(loptica.udar(stap, 1000)) loptica.obrniY();
  for (int i = 0; i<100; i++){
    cigla[i].crtaj();
    if (!proba) proba = loptica.udar(cigla[i], i);
  }
  if (proba) loptica.obrniY();
  proba = false;
  glPopMatrix();
  glutSwapBuffers();
}
void logika(int value){
  dt = glutGet(GLUT_ELAPSED_TIME) - vreme;
  vreme += dt;
  if (levo) stap.levo(dt / (1000 / 60.));
  if (desno) stap.desno(dt / (1000 / 60.));
  glutPostRedisplay();
  glutTimerFunc(1000 / 60., logika, 0 );
}
void stisnutTaster(int key, int x, int y){
  switch(key){
    case GLUT_KEY_LEFT:
      levo = true;
      break;
    case GLUT_KEY_RIGHT:
      desno = true;
      break;
    case 32:
      start = true;
      break;
    default:
      break;
  }
}
void pustenTaster(int key, int x, int y){
  switch(key){
    case GLUT_KEY_LEFT:
      levo = false;
      break;
    case GLUT_KEY_RIGHT:
      desno = false;
      break;
    default:
      break;
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutCreateWindow("Igrica");
  glutSpecialFunc(stisnutTaster);
  glutSpecialUpFunc(pustenTaster);
  glutDisplayFunc(crtaj);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glutTimerFunc(1000/60., logika, 0 );
  vreme = glutGet(GLUT_ELAPSED_TIME);
  glutMainLoop();
  return 0;
}
