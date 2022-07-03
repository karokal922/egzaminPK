
//#include "tests.h"
#include "student_list.hpp"
#include <filesystem>
#include "mainwindow.h"
#include <QApplication>
#include "exam.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(exam_data);
    fs::current_path((fs::current_path()/fs::path(argv[0])).parent_path());
    QApplication a(argc, argv);
    Exam exam;
    MainWindow w(nullptr, &exam);
    w.show();
    return a.exec();
}
