#ifndef PRIMAWINDOW_H
#define PRIMAWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebEngineFullScreenRequest>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QIcon>
#include <webpage.h>

class PrimaWindow : public QWebEngineView
{
    Q_OBJECT
private:
    WebPage *webPage;
public:
    PrimaWindow();
    ~PrimaWindow();

signals:

private slots:
    void renderProcessTerminationHandler(QWebEnginePage::RenderProcessTerminationStatus termStatus,
                                             int statusCode);
    void featurePermissionRequested(const QUrl & securityOrigin,
                                    QWebEnginePage::Feature feature);
    void fullScreenRequested(QWebEngineFullScreenRequest request);
};

#endif // PRIMAWINDOW_H
