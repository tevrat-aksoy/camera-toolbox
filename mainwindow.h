#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QMap>

#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-port-info-list.h>

#define HPIS_CONFIG_KEY_VIEWFINDER "viewfinder"

namespace Ui {
class MainWindow;
}

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

protected:
    int findWidgets(CameraWidget* widget);

    int toggleWidget(QString widgetName, int toggleValue);


    // Events
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

private:
    QTimer*                 lookupCameraTimer;
    QTimer*                 liveviewTimer;

    GPContext*              context;
    CameraAbilitiesList*    abilitieslist;
    GPPortInfoList*         portinfolist;

    Camera*                 camera;
    CameraWidget*           cameraWindow;

    QMap<QString, CameraWidget*> widgets;

    QPixmap preview;
public slots:
    void lookupCamera();
    void capturePreview();
};

#endif // MAINWINDOW_H