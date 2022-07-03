#include "exam.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

Exam::Exam(QObject *parent)
    : QObject{parent}
{}

void Exam::student_names_requested()
{
    QStringList names;
    names.clear();
    for (const auto &s : m_sl.get_student_list())
    {
        names.emplace_back(QString::fromStdString(s.get_name() + " " + s.get_surname()));
    }
    emit send_student_names(names);
}

void Exam::set_current_student(int student_index)
{
    m_current_student = &m_sl.get_student_from_index(student_index);
    emit request_display_student_data(m_current_student);
    emit request_display_questions(draw_questions(1,1,1,2));
}

QStringList Exam::draw_questions(size_t topic0_cnt, size_t topic1_cnt, size_t topic2_cnt, size_t topic3_cnt)
{
    QStringList questions;
    questions.clear();
    QString topic0_questions = "";
    for (size_t i = 0; i < topic0_cnt; i++)
        topic0_questions += QString::fromStdString(m_q.draw_question(0) + "\n\n");
    questions.push_back(topic0_questions);
    QString topic1_questions = "";
    for (size_t i = 0; i < topic1_cnt; i++)
        topic1_questions += QString::fromStdString(m_q.draw_question(1) + "\n\n");
    questions.push_back(topic1_questions);
    QString topic2_questions = "";
    for (size_t i = 0; i < topic2_cnt; i++)
        topic2_questions += QString::fromStdString(m_q.draw_question(2) + "\n\n");
    questions.push_back(topic2_questions);
    QString topic3_questions = "";
    for (size_t i = 0; i < topic3_cnt; i++)
        topic3_questions += QString::fromStdString(m_q.draw_question(3) + "\n\n");
    questions.push_back(topic3_questions);
    return questions;
}

void Exam::draw_additional_questions(size_t topic0_cnt, size_t topic1_cnt, size_t topic2_cnt, size_t topic3_cnt)
{
    emit request_display_questions(draw_questions(topic0_cnt,topic1_cnt,topic2_cnt,topic3_cnt));
}

void Exam::question_cnt_change(size_t cnt, size_t index)
{
    additional_quesstion_cnts[index] = cnt;
    size_t sum = 0;
    for (auto cnt : additional_quesstion_cnts)
        sum += cnt;
    emit send_additional_questions_cnt(m_current_student->get_additional_questions_cnt() - sum);
}
void Exam::calculate_rating(bool t0_good,bool t0_bad,bool t1_good,bool t1_bad,bool t2_good,bool t2_bad,
                            bool t3_q1_good,bool t3_q1_average,bool t3_q1_bad,bool t3_q2_good,bool t3_q2_average,bool t3_q2_bad){
    m_sl.add_points(m_current_student->get_id(),m_current_student->get_exam_rating()*-1);
    if(t0_bad==true||t1_bad==true||t2_bad==true){

       m_sl.add_points(m_current_student->get_id(),2.0);
    }
    if(t0_good==true&&t1_good==true&&t2_good==true){

       m_sl.add_points(m_current_student->get_id(),3.0);
       if(t3_q1_average==true){

           m_sl.add_points(m_current_student->get_id(),0.5);
       }
       if(t3_q2_average==true){

           m_sl.add_points(m_current_student->get_id(),0.5);
       }

       if(t3_q1_good==true){

           m_sl.add_points(m_current_student->get_id(),1.0);
       }
       if(t3_q2_good==true){

           m_sl.add_points(m_current_student->get_id(),1.0);
       }
    }
}
void Exam::check_advanced_level_access(bool t0_good,bool t0_bad,bool t1_good,bool t1_bad,bool t2_good,bool t2_bad){
    if(t0_bad==true||t1_bad==true||t2_bad==true){
       emit send_advanced_level_avible(false);
    }
    if(t0_good==true&&t1_good==true&&t2_good==true)
       emit send_advanced_level_avible(true);
}
void Exam::exam_type_change(int type){
    if(type==0){
        m_q.load_questions("../exam_data/pk_questions.json");
        m_q.reset_questions_base();
    }
    if(type==1){
        m_q.load_questions("../exam_data/ppk_questions.json");
        m_q.reset_questions_base();
    }
}
void Exam::save_ratings(){
    m_sl.save_ratings_as_json();
}
void Exam::recive_student_result_data(){
    emit show_student_result_data(QString::fromStdString(m_current_student->get_name()),
                                  QString::fromStdString(m_current_student->get_surname()),
                                  m_current_student->get_exam_rating());
}
void Exam::change_question_base(QString filepath){
    if(filepath!="")
        m_q.load_questions(filepath.toStdString());
}
void Exam::change_students_base(QString filepath){
    if(filepath!="")
        m_sl.load_student_list(filepath.toStdString());
}
void Exam::end_exam(){
    m_sl.end_student_session(m_current_student->get_id());
    m_q.reset_questions_base();
    emit request_clear_all();
}
