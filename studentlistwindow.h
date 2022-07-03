#ifndef STUDENTLISTWINDOW_H
#define STUDENTLISTWINDOW_H

#include <QDialog>

namespace Ui {
class StudentListWindow;
}

class Exam;

class StudentListWindow : public QDialog
{
    Q_OBJECT
    public:
        explicit StudentListWindow(QWidget *parent = nullptr, Exam* e = nullptr);
        ~StudentListWindow();
    public slots:
        void show_student_names(const QStringList& names);
    signals:
        void request_student_names();
        void send_student_index(int student_index);
private slots:
        void on_buttonBox_accepted();

private:
        Ui::StudentListWindow *ui;
        Exam* e;
};

#endif // STUDENTLISTWINDOW_H
