#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Exam;
class StudentListWindow;
class SummaryWindow;
class student;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr, Exam* exam = nullptr);
        ~MainWindow();
    public slots:
        void on_selectStudentButton_clicked();
        void on_endExamButton_clicked();
        void display_current_student_data(const student* student);
        void display_questions(const QStringList& questions);
        void update_additional_questions_label(size_t aq_cnt);
        void set_additional_level_avible(bool enabled);
        void clear_all();

    signals:
        void request_cnt_change(size_t cnt, size_t index);
        void request_addintional_questions_draw(size_t topic0_cnt, size_t topic1_cnt, size_t topic2_cnt, size_t topic3_cnt);
        void request_raiting_calculate(bool t0_good,bool t0_bad,bool t1_good,bool t1_bad,bool t2_good,bool t2_bad,
                                       bool t3_q1_good,bool t3_q1_average,bool t3_q1_bad,bool t3_q2_good,bool t3_q2_average,bool t3_q2_bad);
        void request_check_advanced_level_access(bool t0_good,bool t0_bad,bool t1_good,bool t1_bad,bool t2_good,bool t2_bad);
        void request_exam_type_change(int type);
        void request_save_ratings();
        void send_student_result_data();
        void request_change_question_base(QString filepath);
        void request_change_students_base(QString filepath);

    private slots:
        void on_topic0SpinBox_valueChanged(int);
        void on_topic1SpinBox_valueChanged(int);
        void on_topic2SpinBox_valueChanged(int);
        void on_topic3SpinBox_valueChanged(int);
        void on_additonalQuestionsDrawButton_clicked();
        void on_topic0GoodButton_clicked();
        void on_topic0BadButton_clicked();
        void on_topic1GoodButton_clicked();
        void on_topic1BadButton_clicked();
        void on_topic2GoodButton_clicked();
        void on_topic2BadButton_clicked();
        void on_pkRadioButton_clicked();
        void on_ppkRadioButton_clicked();
        void on_saveRatingsButton_clicked();
        void on_loadQuestionsButton_clicked();
        void on_loadStudentsButton_clicked();

private:
        Ui::MainWindow *ui;
        StudentListWindow* slw;
        SummaryWindow* sw;
        Exam* e;
};
#endif // MAINWINDOW_H
