#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  scale = 1.0f;
  ortho = false;
  orthoZoomFactor = 0.9;
  anglePsi = 0;
  angleTheta = 0;
  pat1.angle = 0;
  pat2.angle = 90 * float(M_PI)/180;
  pat3.angle = 180 * float(M_PI)/180;
  posActual = glm::vec2(0);
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
  glEnable (GL_DEPTH_TEST);

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  m.load("../models/Patricio.obj");
  creaBuffers();

  calculaCapsa(pat1);
  calculaCapsa(pat2);
  calculaCapsa(pat3);
  calculaCapsaEscena(escena);
  ini_camera();
  /*
  std::cout << "fov " << fov << std::endl;
  std::cout << "ra " << ra << std::endl;
  std::cout << "znear " << znear << std::endl;
  std::cout << "zfar " << zfar << std::endl;
  std::cout << "vrp.x " << vrp.x << std::endl;
  std::cout << "vrp.y " << vrp.y << std::endl;
  std::cout << "vrp.z " << vrp.z << std::endl;
  std::cout << "obs.x " << obs.x << std::endl;
  std::cout << "obs.y " << obs.y << std::endl;
  std::cout << "obs.z " << obs.z << std::endl;
  std::cout << "escena.centre.x " << escena.centre.x << std::endl;
  std::cout << "escena.centre.y " << escena.centre.y << std::endl;
  std::cout << "escena.centre.z " << escena.centre.z << std::endl;
  std::cout << "pat1.min.y " << pat1.min.y << std::endl;
  std::cout << "pat1.centreBase.x " << pat1.centreBase.x << std::endl;
  std::cout << "pat1.centreBase.y " << pat1.centreBase.y << std::endl;
  std::cout << "pat1.centreBase.z " << pat1.centreBase.z << std::endl;
  */
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
  //modelTransform ();
  modelTransform1();
  projectTransform();
  viewTransform();
  glBindVertexArray (VAO);  // activar vao patricio
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);  //pintar patricio

  modelTransform2();
  projectTransform();
  viewTransform();
  glBindVertexArray (VAO);  // activar vao patricio
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);  //pintar patricio

  modelTransform3();
  projectTransform();
  viewTransform();
  glBindVertexArray (VAO);  // activar vao patricio
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);  //pintar patricio


  modelTransformTerra();

  glBindVertexArray(VAO_terra);
  glDrawArrays (GL_TRIANGLES, 0, 6);


  glBindVertexArray (0);
}


void MyGLWidget::modelTransform () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
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

void MyGLWidget::modelTransform1() {
  glm::mat4 transform (1.0f);
  transform = glm::translate(transform, glm::vec3(2,0,2));
  transform = glm::scale(transform, glm::vec3(pat1.escalat));
  transform = glm::rotate(transform, pat1.angle, glm::vec3(0,1,0));
  transform = glm::translate(transform, -pat1.centreBase);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform2() {
  glm::mat4 transform (1.0f);
  transform = glm::translate(transform, glm::vec3(0,0,0));
  transform = glm::scale(transform, glm::vec3(pat2.escalat));
  transform = glm::rotate(transform, pat2.angle, glm::vec3(0,1,0));
  transform = glm::translate(transform, -pat2.centreBase);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform3() {
  glm::mat4 transform (1.0f);
  transform = glm::translate(transform, glm::vec3(-2,0,-2));
  transform = glm::scale(transform, glm::vec3(pat3.escalat));
  transform = glm::rotate(transform, pat3.angle, glm::vec3(0,1,0));
  transform = glm::translate(transform, -pat3.centreBase);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform() {
  glm::mat4 Proj;
  if (ortho) {
    // glm::mat4 Proj = glm::ortho (left, right, bottom, top, ZNear, ZFar);
    Proj = glm::ortho (left, right, bottom, top, znear, zfar);
  }
  else {
    // glm::perspective (FOV en radians , ra window , znear, zfar)
    Proj = glm::perspective (fov, ra, znear, zfar);
  }
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
  // glm::lookAt (OBS, VRP, UP)
  //glm::mat4 View = glm::lookAt (obs, vrp, up);
  glm::mat4 View = glm::mat4(1.0f);
  View = glm::translate(View,glm::vec3(0,0,-escena.radi * 2));
  View = glm::rotate(View, anglePsi, glm::vec3(1,0,0));
  View = glm::rotate(View, angleTheta, glm::vec3(0,1,0));
  View = glm::translate(View, -vrp);
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::ini_camera() {
  float dist;
  dist = escena.radi * 2.0;
  vrp = escena.centre;
  obs = vrp + dist * glm::vec3(0,0,1);
  up = glm::vec3(0,1,0);

  fov = 2 * glm::asin(escena.radi/dist);
  fov_original = fov;
  ra = 1.0f;
  znear = dist - escena.radi;
  zfar = dist + escena.radi;

  top = escena.radi;
  right = escena.radi;
  bottom = -escena.radi;
  left = -escena.radi;
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;
  ra = float(w) / float(h);
  
  // TODO refactoritzar ifs
  if (!ortho) {
    if (ra < 1) {
      fov = 2 * glm::atan(glm::tan((fov_original/2))/ra);  //revisar que sigui 0.5
      // std::cout << fov_original << std::endl;
      // std::cout << fov << std::endl;
    }
  } else {
    if (ra < 1) {
      right = (ra*(top-bottom))/2;
      left = -right;
    } else {
      right = (ra*(top-bottom))/2;
      left = -right;
    }
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      pat1.escalat += 0.05;
      pat2.escalat += 0.05;
      pat3.escalat += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      pat1.escalat -= 0.05;
      pat2.escalat -= 0.05;
      pat3.escalat -= 0.05;
      break;
    }
    case Qt::Key_R: { 
      anglegir += float(M_PI)/4.0f;
      pat1.angle += float(M_PI)/4.0f;
      pat2.angle += float(M_PI)/4.0f;
      pat3.angle += float(M_PI)/4.0f;
      break;
    } 
    case Qt::Key_Z: { 
      top = top * orthoZoomFactor;
      right = right * orthoZoomFactor;
      bottom = bottom * orthoZoomFactor;
      left = left * orthoZoomFactor;
      fov -= 0.1;
      break;
    }    
    case Qt::Key_X: { 
      top = top / orthoZoomFactor;
      right = right / orthoZoomFactor;
      bottom = bottom / orthoZoomFactor;
      left = left / orthoZoomFactor;
      fov += 0.1;
      break;
    }    
    case Qt::Key_O: { // canviar perspectiva
      /*if (ortho) {
        ortho = false;
      }
      else {
        ortho = true;
      }*/
      ortho = !ortho;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
  glm::vec2 nou;
  nou.x = event->y();
  nou.y = event->x();
  if (event->buttons() == Qt::LeftButton &&
    !(event->modifiers() & 
      (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier))) {
    anglePsi += (nou.x - posActual.x) * (float(M_PI) / 180);
    angleTheta += (nou.y - posActual.y) * (float(M_PI) / 180);
    
    posActual = nou;
  }
  viewTransform();
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

  glm::vec3 vertices[6] = {
    glm::vec3(2.5, 0, 2.5),
    glm::vec3(2.5, 0, -2.5),
    glm::vec3(-2.5, 0, -2.5),
    glm::vec3(2.5, 0, 2.5),
    glm::vec3(-2.5, 0, -2.5),
    glm::vec3(-2.5, 0, 2.5)
  }; 
  glm::vec3 color[6] = {
    glm::vec3(1.0, 0.6, 0.3),
    glm::vec3(1.0, 0.6, 0.3),
    glm::vec3(1.0, 0.6, 0.3),
    glm::vec3(1.0, 0.6, 0.3),
    glm::vec3(1.0, 0.6, 0.3),
    glm::vec3(1.0, 0.6, 0.3)
    };


  glGenVertexArrays(1, &VAO_terra);
  glBindVertexArray(VAO_terra);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
  glBufferData (GL_ARRAY_BUFFER ,sizeof(color), color, GL_STATIC_DRAW); // posició
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

glm::vec3 MyGLWidget::calculaCentre(glm::vec3 max, glm::vec3 min) {
  //return ((max*0.5f)+(min*0.5f));
  // return glm::vec3((max.x + min.x) / 2.0, (max.x + min.x) / 2.0, (max.x + min.x) / 2.0);
  return (max+min)/glm::vec3(2.0);
}

float MyGLWidget::calculaRadi(glm::vec3 min, glm::vec3 max) {
  return glm::distance(max,min)*0.5f;
}

void MyGLWidget::calculaCapsa(puntsModel &model) {
  //float min.x, max.x, min.y, max.y, min.z, max.z;
  //model var m
  /*for(unsigned int i = 0; i < m.vertices().size(); i+=3) {
    std::cout << "(x,y,z) = (" << m.vertices()[i] << ", "
                              << m.vertices()[i+1] << ", "
                              << m.vertices()[i+2] << ")" << std::endl;
  }*/
  model.min.x = model.max.x = m.vertices()[0];
  model.min.y = model.max.y = m.vertices()[1];
  model.min.z = model.max.z = m.vertices()[2];

  for(unsigned int i = 3; i < m.vertices().size(); i+=3) {
    if (m.vertices()[i] < model.min.x) model.min.x = m.vertices()[i];
    else if (m.vertices()[i] > model.max.x) model.max.x = m.vertices()[i];

    if (m.vertices()[i+1] < model.min.y) model.min.y = m.vertices()[i+1];
    else if (m.vertices()[i+1] > model.max.y) model.max.y = m.vertices()[i+1];

    if (m.vertices()[i+2] < model.min.z) model.min.z = m.vertices()[i+2];
    else if (m.vertices()[i+2] > model.max.z) model.max.z = m.vertices()[i+2];
  }
  
  model.centreBase = glm::vec3((model.max.x + model.min.x)/2.0, model.min.y, (model.max.z + model.min.z)/2.0);
  model.radi = glm::distance(glm::vec3(model.min.x, model.min.y, model.min.z), glm::vec3(model.max.x, model.max.y, model.max.z))/2.0;
  //model.centre = glm::vec3((model.min.x + model.max.x)/2, (model.min.y + model.max.y)/2, (model.min.z + model.max.z)/2);
  model.centre = calculaCentre(model.max, model.min);
  model.escalat = 1.0f/(model.max.y - model.min.y);

}

void MyGLWidget::calculaCapsaEscena(puntsEscena &esc) {
  esc.max.x = 2.5;
  esc.max.y = 1;
  esc.max.z = 2.5;
  esc.min.x = -2.5;
  esc.min.y = pat1.min.y;
  esc.min.z = -2.5;
  esc.centre = esc.max + esc.min;
  esc.centre = esc.centre / glm::vec3(2.0);
  esc.radi = calculaRadi(esc.min, esc.max);
}