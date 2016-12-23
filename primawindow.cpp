#include "primawindow.h"

PrimaWindow::PrimaWindow() : QWebEngineView()
{
    this->setWindowIcon(QIcon(":/icons/main-icon.png"));
    this->resize(800, 600);
//    this->showFullScreen();

    webPage = new WebPage(QWebEngineProfile::defaultProfile(), this);
    this->setPage(webPage);

//    this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
//    this->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    //Setup Event Handlers for Page
    connect(this->page(),
            SIGNAL(featurePermissionRequested(const QUrl&, QWebEnginePage::Feature)),
            SLOT(featurePermissionRequested(const QUrl&, QWebEnginePage::Feature)));

    connect(this->page(),
            SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)),
            SLOT(fullScreenRequested(QWebEngineFullScreenRequest)));

    connect(this, SIGNAL(renderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus, int)),
            this, SLOT(renderProcessTerminationHandler(QWebEnginePage::RenderProcessTerminationStatus, int)));

    this->setUrl(QUrl("https://www.primevideo.com"));
    this->show();
}

PrimaWindow::~PrimaWindow()
{

}


void PrimaWindow::featurePermissionRequested(const QUrl &securityOrigin,
                                               QWebEnginePage::Feature feature)
{
    // Grant permission
//    qDebug() << securityOrigin << feature;
    switch (feature) {
    case QWebEnginePage::MediaAudioCapture:
    case QWebEnginePage::MediaVideoCapture:
    case QWebEnginePage::Notifications:
    case QWebEnginePage::MediaAudioVideoCapture:
        this->page()->setFeaturePermission(securityOrigin,
                                           feature, QWebEnginePage::PermissionGrantedByUser);
        break;
    default:
        qDebug() << securityOrigin << feature;
    }
}

void PrimaWindow::fullScreenRequested(QWebEngineFullScreenRequest request)
{
    // Grant permission
//    qDebug() << "FullScreen Requested!";
    request.accept();
    if(request.toggleOn())
    {
        this->showFullScreen();
    } else {
        this->showNormal();
    }
}

void PrimaWindow::renderProcessTerminationHandler(QWebEnginePage::RenderProcessTerminationStatus termStatus,
                                                    int statusCode)
{
    qDebug() << "Render Process Terminated" << termStatus << statusCode;
    bool reloadProcess = false;

    switch (termStatus)
    {
        case QWebEnginePage::AbnormalTerminationStatus:
        case QWebEnginePage::CrashedTerminationStatus:
        case QWebEnginePage::KilledTerminationStatus:
            reloadProcess = true;
            break;
        default:
            qDebug() << "Render Process Terminated Normally" << termStatus << statusCode;
            break;
    }

    if (reloadProcess == true)
    {
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setAttribute(Qt::WA_DeleteOnClose);
        QString a = QString("Render Process Terminated. ");
        a.append(QString("Termination Status: "));
        a.append(QString::number(termStatus));
        a.append(QString(" Status Code: "));
        a.append(QString::number(statusCode));
        msgBox->setText(a);
        msgBox->show();

        QTimer::singleShot(0, [this] { reload(); });
    }
}

