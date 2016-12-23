#include "webpage.h"

WebPage::WebPage(QWebEngineProfile *profile, QObject *parent)
{
}

bool WebPage::certificateError(const QWebEngineCertificateError &error)
{
    return true;
}

