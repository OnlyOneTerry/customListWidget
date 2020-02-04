#ifndef NAVIGATEWIDGET_H
#define NAVIGATEWIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class NavigateWidget;
}

class NavigateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavigateWidget(int amount ,QWidget *parent = nullptr);
    ~NavigateWidget();
    void initUI();
    void moveBtnDisplayTextNum(int moveStep);
    void setCurrentBtnHighLight(int currentIndex);
    void btn1Clicked();
    void btn2Clicked();
    void btn3Clicked();
    void btn4Clicked();
    void btn5Clicked();
    void btnHidesClicked();
    void btnLastClicked();
    void selectItemChanged(int idex,bool isScrollBarChange = false);
    void setCurrentPos(int index,bool isScrollBarChange);
private slots:
    void on_btnBefore_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btnHides_clicked();

    void on_btnLast_clicked();

    void on_btnNext_clicked();

signals:
    void signalClickeIndex(int idex);

private:
    Ui::NavigateWidget *ui;
    int _currentIndex = 0;//序号1-amount
    int _amount = 28;
    QList<QPushButton*> _pBtnList;
    int _currentPressIndex =1;//当前被点击的按钮index 1-7
    int _currentHighLightIndex = 1;//1-7
};

#endif // NAVIGATEWIDGET_H
