
#include <QDesktopWidget>
#include <QThread>
#include "ProgressDialog.h"
#include <QKeyEvent>
#include <QProgressBar>

ProgressDialog* ProgressDialog::_globalDialog = NULL;

ProgressDialog& ProgressDialog::getGlobalDialog()
{
    if(_globalDialog == NULL)
        _globalDialog = new ProgressDialog();

    return *_globalDialog;
}

/**
 * Default constructor
 */
ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint)
{
    setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setModal(true);
    _canClose = true;
}


/**
 * Virtual destructor
 */
ProgressDialog::~ProgressDialog()
{

}

/**
 * Sets the message area text and updates the size of the dialog
 * @param text The text for the message area (translated)
 */
void ProgressDialog::setMessage(const QString& text, const QString& time, const QString& speed)
{
    progressLabel->setText(text);

    if(time.isEmpty() && speed.isEmpty())
    {
        dWidget->hide();
    }
    else
    {
        dWidget->show();
        labelTime->setText(time);
        labelSpeed->setText(speed);
    }
    QApplication::processEvents();
}

void ProgressDialog::safeCloseDialog(int num)
{
    if(num <= 0)
    {
        _openNum = 0;
    }
    else
    {
        _openNum -= num;
    }

    if(_openNum <= 0)
    {
        _openNum = 0;
        _canClose = true;
        close();
    }
}

void ProgressDialog::show()
{
    ++_openNum;
    QDialog::show();
}

void ProgressDialog::setValue(int min, int max, int current)
{
    progressBar->setMinimum(min);
    progressBar->setMaximum(max);
    progressBar->setValue(current);
}

void ProgressDialog::setValue(int current)
{
    progressBar->setValue(current);
}

void ProgressDialog::setAutoMode()
{
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    progressBar->setValue(0);
}

/**
 * Re-implemented to dim the screen behind the dialog
 */
void ProgressDialog::showEvent(QShowEvent* event)
{
    //int screen = QApplication::desktop()->screenNumber(FFRCommon::getInstance().getMainWindow());
    QPoint globalCursorPos = QCursor::pos();
    int screenNum = qApp->desktop()->screenNumber(globalCursorPos);

    QRect screenGeometry = QApplication::desktop()->availableGeometry(screenNum);
    int x = screenGeometry.left() + (screenGeometry.width() - width()) / 2;
    int y = screenGeometry.top() + (screenGeometry.height() - height()) / 2;
    this->move(x, y);

    _canClose = false;
    progressBar->setFocus();
    QDialog::showEvent(event);
}

/**
 * Re-implemented to dim the screen behind the dialog
 */
void ProgressDialog::hideEvent(QHideEvent* event)
{
    QDialog::hideEvent(event);
}

/**
 * Reimplemented to catch the key presses
 * @param event key event
 */
void ProgressDialog::keyPressEvent(QKeyEvent* event)
{
}

void ProgressDialog::closeEvent(QCloseEvent *event)
{
    if(!_canClose)
        event->ignore();
    else
        event->accept();
}
