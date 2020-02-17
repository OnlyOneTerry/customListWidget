
#ifndef __ProgressDialog_h
#define __ProgressDialog_h

#include <QDialog>
#include <QString>

#include "ui_ProgressDialog.h"

class DarkeningWidget;


class ProgressDialog: public QDialog, public Ui::ProgressDialog
{
    Q_OBJECT

public:
    static ProgressDialog& getGlobalDialog();
    //Construction, destruction
    ProgressDialog(QWidget *parent = 0);
    virtual ~ProgressDialog();

    //configurable text
    void setMessage(const QString& text, const QString& time = QString(), const QString& speed = QString());

    void safeCloseDialog(int num = 1);

    virtual QPaintEngine * paintEngine() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void show();

    void setValue(int min, int max, int current);
    void setValue(int current);
    void setAutoMode();

protected:
    void showEvent(QShowEvent* show);
    void hideEvent(QHideEvent* hide);
    void keyPressEvent(QKeyEvent* event);


    virtual void closeEvent(QCloseEvent *) override;

private:
    static ProgressDialog		*_globalDialog;
    bool						_canClose = true;
    int							_openNum = 0;
};

#endif
