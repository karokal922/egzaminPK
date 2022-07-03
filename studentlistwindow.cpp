#include "studentlistwindow.h"
#include "ui_studentlistwindow.h"
#include "exam.h"

StudentListWindow::StudentListWindow(QWidget *parent, Exam* exam) :
    QDialog(parent),
    ui(new Ui::StudentListWindow),
    e(exam)
{
    ui->setupUi(this);
    this->setWindowTitle("StudentFailer++ Student List Window");
    connect(this, &StudentListWindow::request_student_names, e, &Exam::student_names_requested);
    connect(e, &Exam::send_student_names, this, &StudentListWindow::show_student_names);
    connect(this, &StudentListWindow::send_student_index, e, &Exam::set_current_student);
    emit request_student_names();
}

void StudentListWindow::show_student_names(const QStringList& names)
{
    for (const auto &name : names)
        ui->studentListWidget->addItem(name);
}

StudentListWindow::~StudentListWindow()
{
    delete ui;
}

void StudentListWindow::on_buttonBox_accepted()
{
    if(ui->studentListWidget->currentRow()>=0)
        emit send_student_index(ui->studentListWidget->currentRow());
}

