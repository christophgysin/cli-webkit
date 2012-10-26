#include <QtGui>

class QWebView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);

protected slots:
    void updateLocation(const QUrl& url);
    void changeLocation();

    void viewSource();
    void slotSourceDownloaded();

private:
    QString jQuery;
    QWebView *view;
    QLineEdit *locationEdit;
};
