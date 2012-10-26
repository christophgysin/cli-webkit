#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>
#include "mainwindow.h"

MainWindow::MainWindow(const QUrl& url)
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    view = new QWebView(this);
    connect(view, SIGNAL(linkClicked()), SLOT(updateLocation()));

    locationEdit = new QLineEdit(this);
    locationEdit->setText(url.toString());
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));


    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addWidget(locationEdit);

    showFullScreen();
    setCentralWidget(view);
    setUnifiedTitleAndToolBarOnMac(true);

    changeLocation();
}

void MainWindow::viewSource()
{
    QNetworkAccessManager* accessManager = view->page()->networkAccessManager();
    QNetworkRequest request(view->url());
    QNetworkReply* reply = accessManager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(slotSourceDownloaded()));
}

void MainWindow::slotSourceDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
    QTextEdit* textEdit = new QTextEdit(NULL);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->show();
    textEdit->setPlainText(reply->readAll());
    reply->deleteLater();
}

void MainWindow::updateLocation(const QUrl& url)
{
    locationEdit->setText(url.toString());
    setWindowTitle(view->title());
}

void MainWindow::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}
