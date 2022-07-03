#ifndef STUDENT_LIST_HPP
#define STUDENT_LIST_HPP

#include "utils.hpp"

#include <string>
#include <vector>

class student
{
	public:
        void add_points(double points) { m_exam_rating += points; };
		GET(get_id, m_id);
		GET(get_name, m_name);
		GET(get_surname, m_surname);
		GET(get_average_rating, m_avreage_rating);
		GET(get_exam_rating, m_exam_rating);
		GET(get_additional_questions_cnt, m_additional_questions_cnt);
        student(int n_id, std::string n_name, std::string n_surname,
			double n_avreage_rating, size_t n_additional_questions_cnt) :
			m_id(n_id), m_name(n_name), m_surname(n_surname),
			m_avreage_rating(n_avreage_rating),
			m_additional_questions_cnt(n_additional_questions_cnt)
		{}
		student& operator=(const student& s2) = default;
	private:
		int m_id;
		std::string m_name;
		std::string m_surname;
		double m_avreage_rating;
		double m_exam_rating = 0.0;
		size_t m_additional_questions_cnt;
};

bool operator==(const student& s1, const student& s2);
bool operator!=(const student& s1, const student& s2);

class student_list
{
	public:
		void load_student_list(std::string sl_directory);
		void add_points(int id, double points);
        void end_student_session(int student_id);
		void save_ratings_as_json();
        const student& get_student(int student_id) const;
		GET_NUMBER(get_number_of_students, m_students.size());
		GET_NUMBER(get_number_of_students_after_exam, m_students_after_exam.size());
		GET(get_student_list, m_students);
		GET(get_student_list_after_exam, m_students_after_exam);
		GET_CONTAINER_MEMBER(get_student_from_index, m_students, student_index);
		GET_CONTAINER_MEMBER(get_student_after_exam_from_index, m_students_after_exam, student_index);
		student_list();
	private:
		std::vector<student> m_students;
		std::vector<student> m_students_after_exam;
		size_t evaluate_additional_questions_number(double avreage_rating);
};

#endif
