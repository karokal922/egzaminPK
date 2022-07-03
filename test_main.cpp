#include <iostream>

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "questions.hpp"
#include "student_list.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	fs::current_path((fs::current_path()/
		fs::path(argv[0])).parent_path());

	questions q;
	std::cout << q.get_topic(0).get_topic_name() << std::endl;
	for (int i = 0; i < 12; i++)
	{
		std::cout << q.draw_question(0) << std::endl;
	}
	std::cout << std::endl;
	std::cout << q.get_topic(1).get_topic_name() << std::endl;
	for (int i = 0; i < 12; i++)
	{
		std::cout << q.draw_question(1) << std::endl;
	}
	std::cout << std::endl;
	std::cout << q.get_topic(2).get_topic_name() << std::endl;
	for (int i = 0; i < 12; i++)
	{
		std::cout << q.draw_question(2) << std::endl;
	}
	std::cout << std::endl;
	std::cout << q.get_topic(3).get_topic_name() << std::endl;
	for (int i = 0; i < 22; i++)
	{
		std::cout << q.draw_question(3) << std::endl;
	}
	std::cout << std::endl;
	q.reset_questions_base();
	std::cout << q.get_topic(0).get_topic_name() << std::endl;
	for (int i = 0; i < 12; i++)
	{
		std::cout << q.draw_question(0) << std::endl;
	}
	std::cout << std::endl;
	student_list sl;
	for (int i = 0; i < 6; i++)
	{
		std::cout << sl.get_student(i).get_id() << std::endl;
		std::cout << sl.get_student(i).get_name() << std::endl;
		std::cout << sl.get_student(i).get_surname() << std::endl;
		std::cout << sl.get_student(i).get_average_rating() << std::endl;
		std::cout << sl.get_student(i).get_exam_rating() << std::endl;
		std::cout << sl.get_student(i).get_additional_questions_cnt() << std::endl;
		std::cout << std::endl;
	}
	std::cout << sl.get_student(230).get_id() << std::endl;
	std::cout << sl.get_student(230).get_name() << std::endl;
	std::cout << sl.get_student(230).get_surname() << std::endl;		
	std::cout << sl.get_student(230).get_average_rating() << std::endl;
	std::cout << sl.get_student(230).get_exam_rating() << std::endl;		
	std::cout << sl.get_student(230).get_additional_questions_cnt() << std::endl;
	std::cout << std::endl;

	std::cout << sl.get_number_of_students();

	sl.add_points(0,1.0);
	sl.add_points(0,1.0);
	sl.end_student_session(0);
	sl.add_points(1,3.0);
	sl.end_student_session(1);
	sl.add_points(230, 5.0);
	sl.end_student_session(230);
	
	sl.save_ratings_as_json();
}

// std::cout << "\n";
