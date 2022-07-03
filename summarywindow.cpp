#include "summarywindow.h"
#include "ui_summarywindow.h"
#include "exam.h"

SummaryWindow::SummaryWindow(QWidget *parent, Exam* exam) :
    QDialog(parent),
    ui(new Ui::SummaryWindow),
    e(exam)
{
    ui->setupUi(this);
    this->setWindowTitle("StudentFailer++ Summary Window");
    connect(e, &Exam::show_student_result_data, this, &SummaryWindow::recive_student_result_data);
    connect( this, &SummaryWindow::request_exam_end ,e, &Exam::end_exam);
}

SummaryWindow::~SummaryWindow()
{
    delete ui;
}
void SummaryWindow::recive_student_result_data(QString name, QString surname, double grade){
    ui->nameLabel->setText(name);
    ui->surnameLabel->setText(surname);
    ui->gradeLabel->setText(QString::number(grade));
}

void SummaryWindow::on_endExamButton_clicked()
{
    emit request_exam_end();
    this->hide();
}

