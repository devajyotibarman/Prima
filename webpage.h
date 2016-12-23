#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QObject>
#include <QWebEnginePage>
#include <QWebEngineProfile>


class WebPage : public QWebEnginePage
{
public:
    WebPage(QWebEngineProfile *profile, QObject *parent = nullptr);
protected:
    bool certificateError(const QWebEngineCertificateError &error) override;

};

#endif // WEBPAGE_H
