#ifndef QUESTIONS_HPP
#define QUESTIONS_HPP

#include "utils.hpp"

#include <vector>
#include <string>
#include <memory>
#include "mainwindow.h"

class topic
{
	public :
		std::string draw_question();
		void reset_question_cnt() { m_questions_cnt = m_question_table.size(); };
        GET(get_topic_id, m_topic_id);
		GET(get_topic_name, m_topic_name);
        GET(get_level, m_level);
        GET_NUMBER(get_question_number, m_question_table.size());
        topic(int topic_id, std::string n_topic_name, int n_level, std::vector<std::string> n_question_table);
	private:
        int m_topic_id;
		std::string m_topic_name;
		int m_level;
		std::vector<std::string> m_question_table;
		size_t m_questions_cnt;
};

class questions
{
	public:
		void reset_questions_base();
        GET_CONTAINER_MEMBER(get_topic_from_index, m_topic_list, topic_id);
        GET_NUMBER(get_topic_number, m_topic_list.size());
        const topic& get_topic(int topic_id);
        GET(get_topic_list, m_topic_list);
        std::string draw_question(int topic_id);
        void load_questions(std::string q_directory);
		questions();
	private:
		std::vector<topic> m_topic_list;
};

#endif
