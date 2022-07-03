#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentlistwindow.h"
#include "ui_studentlistwindow.h"
#include "summarywindow.h"
#include "ui_summarywindow.h"
#include "exam.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, Exam* exam)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      e(exam)
{
    e->set_gui(this);
    ui->setupUi(this);
    this->setWindowTitle("StudentFailer++");
    setStyleSheet("background-color:#022026;color:#42f5e3;");
    connect(e, &Exam::request_display_student_data, this, &MainWindow::display_current_student_data);
    connect(e, &Exam::request_display_questions, this, &MainWindow::display_questions);
    connect(e, &Exam::send_additional_questions_cnt, this, &MainWindow::update_additional_questions_label);
    connect(e, &Exam::send_advanced_level_avible, this, &MainWindow::set_additional_level_avible);
    connect(e, &Exam::request_clear_all, this, &MainWindow::clear_all);
    connect(this, &MainWindow::request_cnt_change, e, &Exam::question_cnt_change);
    connect(this, &MainWindow::request_addintional_questions_draw, e, &Exam::draw_additional_questions);
    connect(this, &MainWindow::request_raiting_calculate, e, &Exam::calculate_rating);
    connect(this, &MainWindow::request_check_advanced_level_access, e, &Exam::check_advanced_level_access);
    connect(this, &MainWindow::request_exam_type_change, e, &Exam::exam_type_change);
    connect(this, &MainWindow::request_save_ratings, e, &Exam::save_ratings);
    connect(this, &MainWindow::send_student_result_data, e, &Exam::recive_student_result_data);
    connect(this, &MainWindow::request_change_question_base, e, &Exam::change_question_base);
    connect(this, &MainWindow::request_change_students_base, e, &Exam::change_students_base);
    ui->topic0SpinBox->setDisabled(true);
    ui->topic1SpinBox->setDisabled(true);
    ui->topic2SpinBox->setDisabled(true);
    ui->topic3SpinBox->setDisabled(true);
}

MainWindow::~MainWindow()
{
    emit request_save_ratings();
    delete ui; 
}

void MainWindow::on_selectStudentButton_clicked()
{
    ui->topic0BadButton->setEnabled(true);
    ui->topic0GoodButton->setEnabled(true);
    ui->topic1BadButton->setEnabled(true);
    ui->topic1GoodButton->setEnabled(true);
    ui->topic2BadButton->setEnabled(true);
    ui->topic2GoodButton->setEnabled(true);
    ui->endExamButton->setEnabled(true);
    ui->loadQuestionsButton->setEnabled(false);
    ui->loadStudentsButton->setEnabled(false);
    ui->statusbar->clearMessage();
    slw = new StudentListWindow(this, e);
    slw->exec();
    slw->deleteLater();
}

void MainWindow::on_endExamButton_clicked()
{
    emit request_raiting_calculate(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked(),
                                   ui->topic3question1GoodButton->isChecked(),ui->topic3question1AverageButton->isChecked(),ui->topic3question1BadButton->isChecked(),
                                   ui->topic3question2GoodButton->isChecked(),ui->topic3question2AverageButton->isChecked(),ui->topic3question2BadButton->isChecked());
    sw = new SummaryWindow(this, e);
    emit send_student_result_data();
    sw->exec();
    sw->deleteLater();
}

void MainWindow::display_current_student_data(const student* student)
{
    ui->questionPlace0->setText("");
    ui->questionPlace1->setText("");
    ui->questionPlace2->setText("");
    ui->questionPlace3->setText("");
    ui->studentDataLabel->setText(QString::fromStdString("Student: " + student->get_name() + " " + student->get_surname()));
    ui->additionalQuestionsNumberLabel->setText(QString::number(student->get_additional_questions_cnt()));
    ui->topic0SpinBox->setMaximum(student->get_additional_questions_cnt());
    ui->topic1SpinBox->setMaximum(student->get_additional_questions_cnt());
    ui->topic2SpinBox->setMaximum(student->get_additional_questions_cnt());
    ui->topic3SpinBox->setMaximum(student->get_additional_questions_cnt());
    ui->topic0SpinBox->setDisabled(false);
    ui->topic1SpinBox->setDisabled(false);
    ui->topic2SpinBox->setDisabled(false);
    ui->topic3SpinBox->setDisabled(false);
    ui->topic0SpinBox->setValue(0);
    ui->topic1SpinBox->setValue(0);
    ui->topic2SpinBox->setValue(0);
    ui->topic3SpinBox->setValue(0);
    ui->additonalQuestionsDrawButton->setEnabled(true);
    ui->pkRadioButton->setEnabled(false);
    ui->ppkRadioButton->setEnabled(false);
}

void MainWindow::display_questions(const QStringList& questions)
{
    QString new_questions = ui->questionPlace0->toPlainText() + questions[0];
    ui->questionPlace0->setText(new_questions);
    new_questions = ui->questionPlace1->toPlainText() + questions[1];
    ui->questionPlace1->setText(new_questions);
    new_questions = ui->questionPlace2->toPlainText() + questions[2];
    ui->questionPlace2->setText(new_questions);
    new_questions = ui->questionPlace3->toPlainText() + questions[3];
    ui->questionPlace3->setText(new_questions);
}

void MainWindow::on_topic0SpinBox_valueChanged(int cnt0)
{
    emit request_cnt_change(cnt0, 0);
}

void MainWindow::on_topic1SpinBox_valueChanged(int cnt1)
{
    emit request_cnt_change(cnt1, 1);
}

void MainWindow::on_topic2SpinBox_valueChanged(int cnt2)
{
    emit request_cnt_change(cnt2, 2);
}

void MainWindow::on_topic3SpinBox_valueChanged(int cnt3)
{
    emit request_cnt_change(cnt3, 3);
}

void MainWindow::update_additional_questions_label(size_t aq_cnt)
{
    ui->additionalQuestionsNumberLabel->setText(QString::number(aq_cnt));
    ui->topic0SpinBox->setMaximum(ui->topic0SpinBox->value() + aq_cnt);
    ui->topic1SpinBox->setMaximum(ui->topic1SpinBox->value() + aq_cnt);
    ui->topic2SpinBox->setMaximum(ui->topic2SpinBox->value() + aq_cnt);
    ui->topic3SpinBox->setMaximum(ui->topic3SpinBox->value() + aq_cnt);
}

void MainWindow::on_additonalQuestionsDrawButton_clicked()
{
    if (!ui->additionalQuestionsNumberLabel->text().toInt())
    {
        emit request_addintional_questions_draw(ui->topic0SpinBox->value(),
                                                ui->topic1SpinBox->value(),
                                                ui->topic2SpinBox->value(),
                                                ui->topic3SpinBox->value());
        ui->additonalQuestionsDrawButton->setDisabled(true);
        ui->topic0SpinBox->setDisabled(true);
        ui->topic1SpinBox->setDisabled(true);
        ui->topic2SpinBox->setDisabled(true);
        ui->topic3SpinBox->setDisabled(true);
    }
}
void MainWindow::set_additional_level_avible(bool enabled){
    ui->topic3question1AverageButton->setEnabled(enabled);
    ui->topic3question1BadButton->setEnabled(enabled);
    ui->topic3question1GoodButton->setEnabled(enabled);
    ui->topic3question2AverageButton->setEnabled(enabled);
    ui->topic3question2BadButton->setEnabled(enabled);
    ui->topic3question2GoodButton->setEnabled(enabled);
}

void MainWindow::on_topic0GoodButton_clicked()
{
    emit request_check_advanced_level_access(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked());

}

void MainWindow::on_topic0BadButton_clicked()
{
    emit request_check_advanced_level_access(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked());
}

void MainWindow::on_topic1GoodButton_clicked()
{
    emit request_check_advanced_level_access(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked());
}

void MainWindow::on_topic1BadButton_clicked()
{
    emit request_check_advanced_level_access(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked());
}


void MainWindow::on_topic2GoodButton_clicked()
{
    emit request_check_advanced_level_access(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked());
}

void MainWindow::on_topic2BadButton_clicked()
{
    emit request_check_advanced_level_access(ui->topic0GoodButton->isChecked(),ui->topic0BadButton->isChecked(),
                                   ui->topic1GoodButton->isChecked(),ui->topic1BadButton->isChecked(),
                                   ui->topic2GoodButton->isChecked(),ui->topic2BadButton->isChecked());
}

void MainWindow::on_pkRadioButton_clicked()
{
    emit request_exam_type_change(0);
    ui->topic0Label->setText("Programowanie proceduralne, obsługa pamięci dynamicznej i złożone typy danych");
    ui->topic1Label->setText("Podstawy programowania obiektowego");
    ui->topic2Label->setText("Zarządzanie pamięcią w klasach, programowanie generyczne");
}

void MainWindow::on_ppkRadioButton_clicked()
{
    emit request_exam_type_change(1);
    ui->topic0Label->setText("Podstawy programowania i instrukcje sterujące");
    ui->topic1Label->setText("Operacje tablicowe i wskaźnikowe i funkcje");
    ui->topic2Label->setText("Debugowanie, testowanie kodu i obsługa wyjątków");
}

void MainWindow::on_saveRatingsButton_clicked()
{
    emit request_save_ratings();
    ui->statusbar->showMessage("Zapisano wyniki!");
}

void MainWindow::on_loadQuestionsButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"Wskaż plik","","Plik tekstowy (*.json)");
    emit request_change_question_base(filepath);
}

void MainWindow::on_loadStudentsButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"Wskaż plik","","Plik tekstowy (*.json)");
    emit request_change_students_base(filepath);
}
void MainWindow::clear_all()
{
    ui->questionPlace0->clear();
    ui->questionPlace1->clear();
    ui->questionPlace2->clear();
    ui->questionPlace3->clear();
    ui->studentDataLabel->clear();
    ui->topic0BadButton->setChecked(true);
    ui->topic1BadButton->setChecked(true);
    ui->topic2BadButton->setChecked(true);
    ui->topic3question1BadButton->setChecked(true);
    ui->topic3question2BadButton->setChecked(true);
    ui->topic3question1BadButton->setEnabled(false);
    ui->topic3question1AverageButton->setEnabled(false);
    ui->topic3question1GoodButton->setEnabled(false);
    ui->topic3question2BadButton->setEnabled(false);
    ui->topic3question2AverageButton->setEnabled(false);
    ui->topic3question2GoodButton->setEnabled(false);
    ui->endExamButton->setEnabled(false);
    ui->loadQuestionsButton->setEnabled(true);
    ui->loadStudentsButton->setEnabled(true);
    ui->additionalQuestionsNumberLabel->setText("0");
    ui->pkRadioButton->setEnabled(true);
    ui->ppkRadioButton->setEnabled(true);
}


