#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores)
{
    // TODO: Implement round_down_scores
    std::vector<int> new_student_scores(student_scores.begin(), student_scores.end());
    return new_student_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores)
{
    // TODO: Implement count_failed_students
    int counted_failed_students{0};
    for (int grade : student_scores)
    {
        if (grade <= 40)
        {
            ++counted_failed_students;
        }
    }
    return counted_failed_students;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score)
{
    // TODO: Implement letter_grades
    int interval{(highest_score - 40) / 4};
    std::array<int, 4> letter_grade{
        41,
        41 + interval,
        41 + 2 * interval,
        41 + 3 * interval};
    return letter_grade;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(
    std::vector<int> student_scores, std::vector<std::string> student_names)
{
    // TODO: Implement student_ranking
    std::vector<std::string> student_ranks;
    for (int i{0}; i < student_scores.size(); ++i)
    {
        student_ranks.push_back(std::to_string(i + 1) + ". " + student_names.at(i) +
                                ": " +
                                std::to_string(student_scores.at(i)));
    }
    return {student_ranks};
}

// Create a string that contains the name of the first student to make a perfect
// score on the exam.
std::string perfect_score(std::vector<int> student_scores,
                          std::vector<std::string> student_names)
{
    // TODO: Implement perfect_score
    int grade{100};
    auto it = std::find(student_scores.begin(), student_scores.end(), grade);
    if (it != student_scores.end())
    {
        auto index = std::distance(student_scores.begin(), it);
        return student_names.at(index);
    }
    return "";
}
