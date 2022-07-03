#ifndef EXAM_H
#define EXAM_H

#include <QObject>
#include "questions.hpp"
#include "student_list.hpp"

class MainWindow;

class Exam : public QObject
{
    Q_OBJECT
    public:
        explicit Exam(QObject *parent = nullptr);
        void set_gui(MainWindow* ui = nullptr) { m_gui = ui;};
        GET(get_current_student, m_current_student);
    signals:
        void send_student_names(const QStringList& names);
        void send_additional_questions_cnt(size_t aq_cnt);
        void send_advanced_level_avible(bool enabled);
        void request_display_student_data(const student* student);
        void request_display_questions(const QStringList& questions);
        void show_student_result_data(QString name,QString surname,double grade);
        void request_clear_all();

    public slots:
        void set_current_student(int student_index);
        void student_names_requested();
        QStringList draw_questions(size_t topic0_cnt, size_t topic1_cnt, size_t topic2_cnt, size_t topic3_cnt);
        void draw_additional_questions(size_t topic0_cnt, size_t topic1_cnt, size_t topic2_cnt, size_t topic3_cnt);
        void question_cnt_change(size_t cnt, size_t index);
        void calculate_rating(bool t0_good,bool t0_bad,bool t1_good,bool t1_bad,bool t2_good,bool t2_bad,
                              bool t3_q1_good,bool t3_q1_average,bool t3_q1_bad,bool t3_q2_good,bool t3_q2_average,bool t3_q2_bad);
        void check_advanced_level_access(bool t0_good,bool t0_bad,bool t1_good,bool t1_bad,bool t2_good,bool t2_bad);
        void exam_type_change(int type);
        void save_ratings();
        void recive_student_result_data();
        void change_question_base(QString filepath);
        void change_students_base(QString filepath);
        void end_exam();

    private:
        MainWindow* m_gui = nullptr;
        questions m_q;
        student_list m_sl;
        student const* m_current_student;
        size_t additional_quesstion_cnts[4] = {};
};

#endif // EXAM_H
