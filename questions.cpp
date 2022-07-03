#include "questions.hpp"
#include "json.hpp"

#include <fstream>
#include <random>
#include <iostream>

using json = nlohmann::json;

topic::topic(int topic_id, std::string n_topic_name, int n_level, std::vector<std::string> n_question_table) :
    m_topic_id(topic_id), m_topic_name(n_topic_name), m_level(n_level), m_question_table(n_question_table)
{
	reset_question_cnt();
}

questions::questions()
{
    load_questions("../exam_data/pk_questions.json");

	reset_questions_base();
}

std::string topic::draw_question()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<size_t> question_generator(0, m_questions_cnt - 1);
	std::string question = "";

	if (m_questions_cnt)
	{
		std::swap(m_question_table[question_generator(rng)],
			m_question_table[m_questions_cnt - 1]);
		question = m_question_table[m_questions_cnt-- - 1];
	}
	else
	{
		throw std::runtime_error{"Question base limit reached!"};
	}

	return question;
}

void questions::reset_questions_base()
{
	for (auto& topic : m_topic_list)
	{
		topic.reset_question_cnt();
	}		
}

void questions::load_questions(std::string q_directory)
{
    std::ifstream questions_file(q_directory);

    if (questions_file.is_open())
	{
		json data;
		questions_file >> data;

		size_t i = 0;
		m_topic_list.clear();
		for (const auto& topic : data)
		{
			auto question_set = topic["questions"];
            m_topic_list.emplace_back(topic["topic_id"], topic["topic"], topic["level"], question_set);
			++i;
        }
	}
	else
    {
        throw std::runtime_error("Could not open \"questions.json\"!");
    }
}

std::string questions::draw_question(int topic_id)
{
    size_t index = 0;
    for (auto& t : m_topic_list)
    {
        if (t.get_topic_id() == topic_id)
        {
            return t.draw_question();
        }
        ++index;
    }
    throw std::invalid_argument {"Topic is not in the topic list!"};
}

const topic& questions::get_topic(int topic_id)
{
    size_t index = 0;
    for (auto& t : m_topic_list)
    {
        if (t.get_topic_id() == topic_id)
        {
            return t;
        }
        ++index;
    }
    throw std::invalid_argument {"Topic is not in the topic list!"};
}

