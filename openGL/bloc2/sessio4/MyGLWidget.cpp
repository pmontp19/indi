#include "MyGLWidget.h"

#include <iostream>

/*
 * problemes
 * loop entre actualizatzacions de valor ratoli/teclat a widgets
 * color fa coses rares
 * factor d'escala, s'ha de canviar la capsa cada cop?
 * zoom fov fatal, retreballar
 * zoom ortho amb slider per fer
 * */

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
    scale = 1.0f;
    ortho = false;
    posActual = glm::vec2(0);
    orthoZoomFactor = 0.9f;
    anglePsi = 0;
    angleTheta = 0;

    pat[0].angle = lego[0].angle = 0;
    pat[1].angle = lego[1].angle = 90 * float(M_PI)/180;
    pat[2].angle = lego[2].angle = 180 * float(M_PI)/180;

    pat[0].posicio = lego[0].posicio = glm::vec3(2,0,2);
    pat[1].posicio = lego[1].posicio = glm::vec3(0,0,0);
    pat[2].posicio = lego[2].posicio = glm::vec3(-2,0,-2);
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

    float r = 0.5;
    float g = 0.7;
    float b = 1.0;
    glClearColor(r, g, b, 1.0); // defineix color de fons (d'esborrat)
    emit enviaIniColor(int(r*255), int(g*255), int(b*255));
    carregaShaders();
    m_patricio.load("../models/Patricio.obj");
    m_lego.load("../models/legoman.obj");
    creaBuffers();

    calculaCapsa(pat[0], m_patricio);
    calculaCapsa(pat[1], m_patricio);
    calculaCapsa(pat[2], m_patricio);
    calculaCapsa(lego[0], m_lego);
    calculaCapsa(lego[1], m_lego);
    calculaCapsa(lego[2], m_lego);
    calculaCapsaEscena(escena);

    ini_camera();

    projectTransform();
    viewTransform();
}

void MyGLWidget::paintTerra() {
    // Carreguem la transformació de model
    modelTransformTerra();

    glBindVertexArray(VAO_terra);
    glDrawArrays (GL_TRIANGLES, 0, 6);
}

void MyGLWidget::paintLego() {
    // Carreguem la transformació de model

    modelTransform(lego[0]);
    glBindVertexArray (VAO_lego);  // activar vao lego
    glDrawArrays(GL_TRIANGLES, 0, m_lego.faces().size()*3);  //pintar patricio

    modelTransform(lego[1]);
    glBindVertexArray (VAO_lego);  // activar vao lego
    glDrawArrays(GL_TRIANGLES, 0, m_lego.faces().size()*3);  //pintar patricio

    modelTransform(lego[2]);
    glBindVertexArray (VAO_lego);  // activar vao lego
    glDrawArrays(GL_TRIANGLES, 0, m_lego.faces().size()*3);  //pintar patricio
}

void MyGLWidget::paintPatricio() {
    // Carreguem la transformació de model

    modelTransform(pat[0]);
    glBindVertexArray (VAO_patricio);  // activar vao patricio
    glDrawArrays(GL_TRIANGLES, 0, m_patricio.faces().size()*3);  //pintar patricio

    modelTransform(pat[1]);
    glBindVertexArray (VAO_patricio);  // activar vao patricio
    glDrawArrays(GL_TRIANGLES, 0, m_patricio.faces().size()*3);  //pintar patricio

    modelTransform(pat[2]);
    glBindVertexArray (VAO_patricio);  // activar vao patricio
    glDrawArrays(GL_TRIANGLES, 0, m_patricio.faces().size()*3);  //pintar patricio
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

    if (person == Patricio) {
        paintPatricio();
    }
    else if (person == Lego) {
        paintLego();
    }

    paintTerra();

    glBindVertexArray (0);
}


void MyGLWidget::modelTransform ()
{
    // Matriu de transformació de model
    glm::mat4 transform (1.0f);
    transform = glm::scale(transform, glm::vec3(scale));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform (const puntsModel m)
{
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, m.posicio);
    transform = glm::scale(transform, glm::vec3(m.escalat));
    transform = glm::rotate(transform, m.angle, glm::vec3(0,1,0));
    transform = glm::translate(transform, -m.centreBase);
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
    transform = glm::scale(transform, glm::vec3(pat[0].escalat));
    transform = glm::rotate(transform, pat[0].angle, glm::vec3(0,1,0));
    transform = glm::translate(transform, -pat[0].centreBase);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform2() {
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(0,0,0));
    transform = glm::scale(transform, glm::vec3(pat[1].escalat));
    transform = glm::rotate(transform, pat[1].angle, glm::vec3(0,1,0));
    transform = glm::translate(transform, -pat[1].centreBase);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform3() {
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(-2,0,-2));
    transform = glm::scale(transform, glm::vec3(pat[2].escalat));
    transform = glm::rotate(transform, pat[2].angle, glm::vec3(0,1,0));
    transform = glm::translate(transform, -pat[2].centreBase);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::setPersonatgePat() {
    makeCurrent();
    person = Patricio;
    update();
}

void MyGLWidget::setPersonatgeLego() {
    makeCurrent();
    person = Lego;
    update();
}

void MyGLWidget::setProjectionPersp() {
    QKeyEvent *key_press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_O, Qt::NoModifier, "O");
    keyPressEvent(key_press);
}
void MyGLWidget::setProjectionOrtho() {
    QKeyEvent *key_press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_O, Qt::NoModifier, "O");
    keyPressEvent(key_press);

}

void MyGLWidget::setScale(double valor) {
    scale = valor;
    for (GLuint i=0; i < 3; i++) {
        pat[i].escalat = (1.0f + scale - 1) / (pat[i].max.y - pat[i].min.y);
        lego[i].escalat = (1.0f + scale - 1) / (lego[i].max.y - lego[i].min.y);
    }
    update();
}

void MyGLWidget::setColor(int r, int g, int b) {
    makeCurrent();
    glClearColor(float(r)/255, float(g)/255, float(b)/255, 1.0); // defineix color de fons (d'esborrat)
    update();
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
    std::cout << ortho << std::endl;
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
    dist = escena.radi * 2.0f;
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
            fov = 2.f * glm::atan(glm::tan(fov_original/2.f)/ra);  //revisar que sigui 0.5
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
        scale += 0.05f;
        for (GLuint i=0; i < 3; i++) {
            pat[i].escalat = (1.0f + scale - 1) / (pat[i].max.y - pat[i].min.y);
            lego[i].escalat = (1.0f + scale - 1) / (lego[i].max.y - lego[i].min.y);
        }
        emit enviaScale(scale);
        break;
    }
    case Qt::Key_D: { // escalar a més petit
        if (scale >= 0) {
            scale -= 0.05f;
            for (GLuint i=0; i < 3; i++) {
                pat[i].escalat = (1.0f + scale - 1) / (pat[i].max.y - pat[i].min.y);
                lego[i].escalat = (1.0f + scale - 1) / (lego[i].max.y - lego[i].min.y);
            }
            emit enviaScale(scale);
        }
        break;
    }
    case Qt::Key_R: {
        anglegir += float(M_PI)/4.0f;
        for (GLuint i=0; i < 3; i++) {
            pat[i].angle += float(M_PI)/4.0f;
            lego[i].angle += float(M_PI)/4.0f;
        }
        break;
    }
    case Qt::Key_Z: {
        if (fov >= 0.2) {
            fov -= 0.1f;
            projectTransform();
            emit enviaZoom(calculaValorZoom(fov/2.f));
        }
        top = top * orthoZoomFactor;
        right = right * orthoZoomFactor;
        bottom = bottom * orthoZoomFactor;
        left = left * orthoZoomFactor;
        break;
    }
    case Qt::Key_X: {
        if (fov <= (float(M_PI) - 0.1f) ) {
            fov += 0.1f;
            projectTransform();
            emit enviaZoom(calculaValorZoom(fov/2.f));
        }
        top = top / orthoZoomFactor;
        right = right / orthoZoomFactor;
        bottom = bottom / orthoZoomFactor;
        left = left / orthoZoomFactor;
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
        projectTransform();
        if (ortho) emit enviaProjectionOrtho(ortho);
        if (!ortho) emit enviaProjectionPersp(!ortho);
        break;
    }
    default: event->ignore(); break;
    }
    update();
}

float MyGLWidget::calculaValorZoom(float alpha) {
    float valor;
    valor = alpha /  ((M_PI/2 - .2f)/99);
    valor = valor - 0.1f;
    return valor;
}

void MyGLWidget::setZoom(int valor) {
    makeCurrent();
    float temp = 0.1f + valor * ((M_PI/2-0.2f)/99);
    fov = temp * 2.f;
    projectTransform();
    update();
}

void MyGLWidget::setPsi(int angle) {
    makeCurrent();
    anglePsi = angle * (M_PI/180);
    viewTransform();
    update();
}

void MyGLWidget::setTheta(int angle) {
    makeCurrent();
    angleTheta = angle * (M_PI/180);
    viewTransform();
    update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
    glm::vec2 nou;
    glm::vec2 angle;
    makeCurrent();
    nou.x = event->y();
    nou.y = event->x();
    if (event->buttons() == Qt::LeftButton &&
            !(event->modifiers() &
              (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier))) {
        //anglePsi += (nou.x - posActual.x) * (float(M_PI) / 180);
        //angleTheta += (nou.y - posActual.y) * (float(M_PI) / 180);
        if (nou.x > posActual.x) {
            angle.x = anglePsi * (180/float(M_PI)) + 4;
            anglePsi = angle.x * (float(M_PI)/180);
            emit enviaPsi(angle.x);
        } else if (nou.x < posActual.x) {
            angle.x = anglePsi * (180/float(M_PI)) - 4;
            anglePsi = angle.x * (float(M_PI)/180);
            emit enviaPsi(angle.x);
        }
        if (nou.y > posActual.y) {
            angle.y = angleTheta * (180/float(M_PI)) + 4;
            angleTheta = angle.y * (float(M_PI)/180);
            emit enviaTheta(angle.y);
        } else if (nou.y < posActual.y) {
            angle.y = angleTheta * (180/float(M_PI)) - 4;
            angleTheta = angle.y * (float(M_PI)/180);
            emit enviaTheta(angle.y);
        }
        posActual = nou;
    }
    viewTransform();
    update();
}

void MyGLWidget::creaBuffers ()
{

    glGenVertexArrays(1, &VAO_patricio);
    glBindVertexArray(VAO_patricio);

    GLuint VBO[6];
    glGenBuffers(6, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_patricio.faces().size() * 3 * 3, m_patricio.VBO_vertices(), GL_STATIC_DRAW); // posicio
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_patricio.faces().size() * 3 * 3, m_patricio.VBO_matdiff(), GL_STATIC_DRAW); // color
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

    glGenVertexArrays(1, &VAO_lego);
    glBindVertexArray(VAO_lego);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_lego.faces().size() * 3 * 3, m_lego.VBO_vertices(), GL_STATIC_DRAW); // posicio
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_lego.faces().size() * 3 * 3, m_lego.VBO_matdiff(), GL_STATIC_DRAW); // color
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

void MyGLWidget::calculaCapsa(puntsModel &model, const Model &m) {
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

    model.centreBase = glm::vec3((model.max.x + model.min.x)/2.0f, model.min.y, (model.max.z + model.min.z)/ 2.0f );
    model.radi = glm::distance(glm::vec3(model.min.x, model.min.y, model.min.z), glm::vec3(model.max.x, model.max.y, model.max.z)) / 2.0f;
    //model.centre = glm::vec3((model.min.x + model.max.x)/2, (model.min.y + model.max.y)/2, (model.min.z + model.max.z)/2);
    model.centre = calculaCentre(model.max, model.min);
    model.escalat = 1.0f/(model.max.y - model.min.y);

}

void MyGLWidget::calculaCapsaEscena(puntsEscena &esc) {
    esc.max.x = 2.5;
    esc.max.y = 1;
    esc.max.z = 2.5;
    esc.min.x = -2.5;
    esc.min.y = 0.0;
    esc.min.z = -2.5;
    esc.centre = esc.max + esc.min;
    esc.centre = esc.centre / glm::vec3(2.0);
    esc.radi = calculaRadi(esc.min, esc.max);
}
