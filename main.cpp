 #include <QtGui>
 #include "mainwindow.h"

 int main(int argc, char* argv[])
 {
    QApplication app(argc, argv);

    if(argc < 2)
    {
        printf("usage: %s <url>\n", argv[0]);
        exit(1);
    }

    QUrl url(argv[1]);
    MainWindow mainwindow(url);
    mainwindow.show();

    return app.exec();
 }
