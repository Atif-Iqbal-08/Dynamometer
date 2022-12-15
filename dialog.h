#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


    void updatecombo();
private slots:


    void on_deleteProfile_clicked();

    void on_addProfile_clicked();



    void on_combo_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;

 bool vok=false;
 bool vwok = false;
 float vwheeldia;
};

#endif // DIALOG_H
