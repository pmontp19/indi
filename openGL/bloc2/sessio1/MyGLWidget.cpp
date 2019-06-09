#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  scale = 1.0f;
  anglegir = 0.0;
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
  glEnable (GL_DEPTH_TEST | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  m.load("../models/HomerProves.obj");
  creaBuffers();
  ini_camera();
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
  
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();
  projectTransform();
  viewTransform();

  // Activem el VAO per a pintar la caseta 
  glBindVertexArray (VAO);

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  modelTransformTerra();

  glBindVertexArray(VAO_terra);
  glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransform () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, anglegir, glm::vec3(0,1,0));
  transform = glm::scale(transform, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}
void MyGLWidget::modelTransformTerra () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
   transform = glm::scale(transform, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
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
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    case Qt::Key_R: { // escalar a més petit
      anglegir += float(M_PI)/4.0f;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffers () 
{

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO[4];
  glGenBuffers(4, VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW); // posicio

  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);


  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW); // color

  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glm::vec3 Vertices[4];
  Vertices[3] = glm::vec3(0, -1.0 , 1.0);
  Vertices[2] = glm::vec3(-1.0, -1.0, 0);
  Vertices[0] = glm::vec3(1, -1, 0); 
  Vertices[1] = glm::vec3(0, -1.0, -1.0);
  
  glm::vec3 Colors[4];
  Colors[0] = glm::vec3(1.0, 0.6, 0.3);
  Colors[1] = glm::vec3(1.0, 0.6, 0.3);
  Colors[2] = glm::vec3(1.0, 0.6, 0.3);
  Colors[3] = glm::vec3(1.0, 0.6, 0.3);

  glGenVertexArrays(1, &VAO_terra);
  glBindVertexArray(VAO_terra);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
  glBufferData (GL_ARRAY_BUFFER ,sizeof(Colors),Colors, GL_STATIC_DRAW); // posició
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);


  glBindVertexArray (0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
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
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");

  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");

}


void MyGLWidget::projectTransform () {
    // glm::perspective (FOV en radians , ra window , znear, zfar)
    glm::mat4 Proj = glm::perspective (fov, ra, znear, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
    // glm::lookAt (OBS, VRP, UP)
    glm::mat4 View = glm::lookAt (obs, vrp, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::ini_camera() {
    obs = glm::vec3(0,0,1);
    vrp = glm::vec3(0,0,0);
    up = glm::vec3(0,1,0);

    fov = float(M_PI)/2.0f;
    ra = 1.0f;
    znear = 0.4f;
    zfar = 3.0f;
}
