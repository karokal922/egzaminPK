#include "tests.h"
#include "questions.hpp"
#include "student_list.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
/*
void draw_question_test1(int topic_id)
{
    std::cout << "draw question test 1 (drawing to much questions from one topic): ";
    questions q;
    auto t = q.get_topic_from_index(topic_id);
    try
    {
        for (size_t i = 0; i < t.get_question_number() + 1; ++i)
            t.draw_question();
        std::cerr << "FAIL!\n";
    }
    catch (...)
    {
        std::cout<<"OK!\n";
    }
}

void draw_question_test2(int topic_id)
{
    questions q;
    auto t = q.get_topic_from_index(topic_id);
    std::vector<std::string> questions_tab;
    questions_tab.clear();
    for (size_t i = 0; i < t.get_question_number(); ++i)
        questions_tab.emplace_back(t.draw_question());
    std::unique(questions_tab.begin(), questions_tab.end());
    std::cout << "draw question test 2: ";
    try
    {
        if (t.get_question_number() != questions_tab.size())
            throw std::runtime_error{"Drawing not working!"};
        std::cout << "OK!\n";
    }
    catch (...)
    {
        std::cerr<<"FAIL!\n";
    }
}

void additional_questions_test1()
{
    std::cout << "additional questions test 1: ";
    try
    {
        student_list sl;                  // call of load_student_list() in constructor
        std::cerr << "FAIL!\n";
    }
    catch (...)
    {
        std::cout << "OK!\n";
    }
}

void data_saving_test1()
{
    student_list sl;

	sl.add_points(0,2.0);
	sl.end_student_session(0);

    sl.save_ratings_as_json();
    sl.load_student_list("./exam_data/exam_grades.json");
    try
    {
        for (size_t i = 0; i < sl.get_student_list().size(); ++i)
        {
            if (sl.get_student_from_index(i) != sl.get_student_after_exam_from_index(i))
                throw std::runtime_error{"Saving data as json not working!"};
        }
        std::cout << "OK!\n";
    }
    catch(...)
    {
        std::cerr << "FAIL!\n";
    }
    
}*/

