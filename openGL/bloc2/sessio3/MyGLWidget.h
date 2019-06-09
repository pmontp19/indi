#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:
    void creaBuffers ();
    void carregaShaders ();
    void modelTransform ();
    void modelTransformTerra();
    void modelTransform1();
    void modelTransform2();
    void modelTransform3();
    void projectTransform();
    void viewTransform();
    void ini_camera();
    float calculaRadi(glm::vec3 min, glm::vec3 max);
    glm::vec3 calculaCentre(glm::vec3 max, glm::vec3 min);

    // attribute locations
    GLuint vertexLoc, colorLoc, projLoc, viewLoc;
    // uniform locations
    GLuint transLoc;
    // VAO i VBO names
    GLuint VAO, VAO_terra;
    // Program
    QOpenGLShaderProgram *program;
    // Viewport
    GLint ample, alt;
    // Internal vars
    float scale, anglegir;
    glm::vec3 pos;

    glm::vec3 obs,vrp,up;
    float fov,ra,znear,zfar;
    float fov_original;
    Model m;

    bool ortho;
    float orthoZoomFactor;
    float top, bottom, right, left;
    float anglePsi, angleTheta;


    struct puntsModel
    {
      glm::vec3 min, max;
      float radi;
      float escalat, angle;
      glm::vec3 centre, centreBase;
    };
    
    puntsModel pat1, pat2, pat3;

    struct puntsEscena {
      glm::vec3 min, max;
      glm::vec3 centre;
      float radi;
    };

    puntsEscena escena;

    void calculaCapsa(puntsModel &model);
    void calculaCapsaEscena(puntsEscena &esc);
    
    glm::vec2 posActual;
};

