//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersArbre();
  anglegirArbre1 = anglegirArbre2 = 0.0;
}

void MyGLWidget::pintaArbre ()
{
  // Activem l'Array a pintar
  glBindVertexArray(VAO1);
  // Pintem
  glDrawArrays(GL_TRIANGLES, 0, 12);
}

void MyGLWidget::paintGL ()
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Pintem tots dos arbres cadascú amb la seva transformació
  modelTransformArbre(glm::vec3(-0.5, 0.0, 0.0), 1.5, anglegirArbre1);
  pintaArbre();
  modelTransformArbre(glm::vec3(0.5, 0.0, 0.0), 0.5, anglegirArbre2);
  pintaArbre();

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformArbre (glm::vec3 posicio, float escalat, float anglegir)
{
  // Codi per a la TG necessària
  glm::mat4 TG(1.0); // Matriu de transformació, inicialment identitat
  TG = glm::translate(TG, posicio);
  TG = glm::rotate(TG, anglegir, glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalat, escalat, 0) );
  TG = glm::translate(TG, glm::vec3(0.5,0.0,0.0));

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::resizeGL (int w, int h)
{
  ample = w;
  alt = h;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_R: { // rotació arbre1 respecte eix Y...
      anglegirArbre1 += float(M_PI)/36.0f; // 5 graus
      break;
    }
    case Qt::Key_T: { // rotació arbre2 respecte eix Y...
      anglegirArbre2 += float(M_PI)/18.0f; // 10 graus
      break;
    }
    case Qt::Key_I: { // Inicialització
      anglegirArbre1 = anglegirArbre2 = 0.0;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffersArbre ()
{
  // Dades de les coordenades dels vèrtexs
  glm::vec3 Vertices[12];
  Vertices[0] = glm::vec3(-0.55, -0.35, 0.0);  // tronc de l'arbre
  Vertices[1] = glm::vec3(-0.45, -0.35, 0.0);
  Vertices[2] = glm::vec3(-0.55, 0.05, 0.0);
  Vertices[3] = glm::vec3(-0.55, 0.05, 0.0);
  Vertices[4] = glm::vec3(-0.45, -0.35, 0.0);
  Vertices[5] = glm::vec3(-0.45, 0.05, 0.0);
  Vertices[6] = glm::vec3(-0.65, 0.05, 0.01);  // fulles de l'arbre
  Vertices[7] = glm::vec3(-0.35, 0.05, 0.01);
  Vertices[8] = glm::vec3(-0.5, 0.35, 0.01);
  Vertices[9] = glm::vec3(-0.35, 0.25, 0.01);
  Vertices[10] = glm::vec3(-0.65, 0.25, 0.01);
  Vertices[11] = glm::vec3(-0.5, -0.05, 0.01);
  
  // Dades de les colors dels vèrtexs
  glm::vec3 Colors[12];
  Colors[0] = glm::vec3(1.0, 0.6, 0.3);  // tronc de l'arbre
  Colors[1] = glm::vec3(1.0, 0.6, 0.3);
  Colors[2] = glm::vec3(1.0, 0.6, 0.3);
  Colors[3] = glm::vec3(1.0, 0.6, 0.3);
  Colors[4] = glm::vec3(1.0, 0.6, 0.3);
  Colors[5] = glm::vec3(1.0, 0.6, 0.3);
  Colors[6] = glm::vec3(0.0, 1.0, 0.0);  // fulles de l'arbre
  Colors[7] = glm::vec3(0.0, 1.0, 0.0);
  Colors[8] = glm::vec3(0.0, 1.0, 0.0);
  Colors[9] = glm::vec3(0.0, 1.0, 0.0);
  Colors[10] = glm::vec3(0.0, 1.0, 0.0);
  Colors[11] = glm::vec3(0.0, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  GLuint VBOs[2];
  glGenBuffers(2, VBOs);
  // Creació del buffer amb les coordenades dels vèrtexs
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Creació del buffer amb els colors dels vèrtexs
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);


  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("./shaders/basicShader.frag");
  vs.compileSourceFile("./shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");
  transLoc = glGetUniformLocation (program->programId (), "TG");

}
