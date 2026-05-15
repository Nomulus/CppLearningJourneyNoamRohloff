#include <string>
#include <vector>

namespace election
{

    // The election result struct is already created for you:

    struct ElectionResult
    {
        // Name of the candidate
        std::string name{};
        // Number of votes the candidate has
        int votes{};
    };

    // TODO: Task 1
    // vote_count takes a reference to an `ElectionResult` as an argument and will
    // return the number of votes in the `ElectionResult.
    int vote_count(const ElectionResult &election)
    {
        return election.votes;
    }

    // TODO: Task 2
    // increment_vote_count takes a reference to an `ElectionResult` as an argument
    // and a number of votes (int), and will increment the `ElectionResult` by that
    // number of votes.

    void increment_vote_count(ElectionResult &election, int votes)
    {
        election.votes = election.votes + votes;
    }

    // TODO: Task 3
    // determine_result receives the reference to a final_count and returns a
    // reference to the `ElectionResult` of the new president. It also changes the
    // name of the winner by prefixing it with "President". The final count is given
    // in the form of a `reference` to `std::vector<ElectionResult>`, a vector with
    // `ElectionResults` of all the participating candidates.
    ElectionResult &determine_result(std::vector<ElectionResult> &result_vector)
    {
        int winner_index = 0;

        for (int i = 0; i < result_vector.size(); ++i)
        {
            if (result_vector.at(i).votes > result_vector.at(winner_index).votes)
            {
                winner_index = i;
            }
        }
        result_vector.at(winner_index).name = "President " + result_vector.at(winner_index).name;
        return result_vector.at(winner_index);
    }

} // namespace election
