#include "mainwindow.h"

#include <QApplication>

#include <QString>
#include <QTime>
#include <QDebug>
#include <QSettings>

const uint16_t key_val = 0x0000000000000010;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("GrapeRain", "Garden");
    QList<QVariant> list;
    QVariant path = a.applicationFilePath();
    if(!settings.contains(app_setting))
    {
        list.push_back(path);
        settings.setValue(app_setting, list);
    }
    else
    {
        list = settings.value(app_setting).toList();
        if(!list.contains(path))
        {
            list.push_back(path);
            settings.setValue(app_setting, list);
        }
    }
    settings.sync();

    MainWindow w;
    w.show();
    return a.exec();
}
