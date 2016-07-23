#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include "camera.h"
#include "camerastatus.h"

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QPixmap>
#include <QImage>
#include <QMap>
#include <QList>

namespace hpis {

class DecoderThread;

class CameraThread : public QThread
{
    friend class DecoderThread;

    Q_OBJECT
public:
    enum CommandType {
        CommandStartLiveview,
        CommandStopLiveview,

        CommandIncreaseAperture,
        CommandDecreaseAperture,

        CommandIncreaseShutterSpeed,
        CommandDecreaseShutterSpeed,

        CommandIncreaseIso,
        CommandDecreaseIso,
        CommandSetIso,
        CommandEnableIsoAuto,
        CommandDisableIsoAuto,

        CommandIncreaseProgramShiftValue,
        CommandDecreaseProgramShiftValue,

        CommandIncreaseExposureCompensation,
        CommandDecreaseExposureCompensation,

        CommandExposureModePlus,
        CommandExposureModeMinus,
        CommandIncreaseLvZoomRatio,
        CommandDecreaseLvZoomRatio,
        CommandChangeAfArea,
        CommandPhotoMode,
        CommandVideoMode,
        CommandCapturePhoto,
        CommandEnableExposurePreview,
        CommandDisableExposurePreview,

        CommandToggleLiveview,
        CommandStartStopMovie,
        CommandStartMovie,
        CommandStopMovie,

        CommandAfDrive
    };

    class Command {
    public:
        Command();
        Command(CommandType commandType);
        static Command changeAfArea(int x, int y);
        static Command setIso(QString value);

        CommandType type();
        int x();
        int y();
        QString value();
    private:
        CommandType m_commandType;
        int m_x;
        int m_y;
        QString m_value;
    };

    explicit CameraThread(hpis::Camera* camera, QObject *parent = 0);
    void stop();
    void executeCommand(Command executeCommand);
    CameraStatus cameraStatus();

protected:
    // Thread main loop
    void run();

    // Init & Shutdown
    bool init();
    void shutdown();

    // Camera control
    hpis::CameraStatus doCommand(Command executeCommand) const;


    void doCapturePreview();

    // Image decoding
    void previewDecoded(QImage image);
private:
    hpis::Camera* m_camera;

    // Thread control
    bool m_stop;
    hpis::CameraStatus m_cameraStatus;

    int refreshTimeoutMs;


    // Thread synchronization
    QMutex m_mutex;
    QWaitCondition m_condition;

    // Thread commands
    QQueue<Command> m_commandQueue;

    // Decoder
    DecoderThread* m_decoderThread;


    // Camera infos
    QString m_cameraModel;
    QString m_cameraPort;

signals:
    void previewAvailable(CameraPreview::Format format, QByteArray bytes);
    void imageAvailable(QImage preview);
    void cameraStatusAvailable(hpis::CameraStatus cameraStatusAvailable);
public slots:
    void capturePreview();
};

}

#endif // CAMERATHREAD_H
