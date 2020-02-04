#include "CustomListWidget.h"
#include <QApplication>
#include "LIstItemForm.h"
#include <QMessageBox>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DWORD pid = GetCurrentProcessId(); // 当前进程ID
    QString inform = QString("%1").arg(pid);
    QMessageBox::information(NULL,"","the client  PID is "+inform);

    HANDLE appLockMutex = CreateMutexA(NULL,FALSE,"CustomListWidget");
    if(ERROR_ALREADY_EXISTS == GetLastError())
    {
        CloseHandle(appLockMutex);
        QMessageBox::information(NULL,"","the client is already open");
        return a.exec();
    }
    CustomListWidget w;
    w.show();
    w.updateHeaderWid();
    return a.exec();
}
