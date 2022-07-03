#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QDialog>

namespace Ui {
class SummaryWindow;
}

class Exam;

class SummaryWindow : public QDialog
{
    Q_OBJECT
    public:
        explicit SummaryWindow(QWidget *parent = nullptr, Exam* exam = nullptr);
        ~SummaryWindow();
    signals:
        void request_exam_end();
    public slots:
        void recive_student_result_data(QString name,QString surname,double grade);
    private slots:
        void on_endExamButton_clicked();

    private:
        Ui::SummaryWindow *ui;
        Exam* e;
};

#endif // SUMMARYWINDOW_H
