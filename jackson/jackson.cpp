#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <algorithm>

using TaskFeatures = std::pair<std::vector<int>,std::vector<int>>;

TaskFeatures fileHandling(const std::string& fileName)
{
    std::fstream file;
    file.open(fileName);
    std::vector<int> availbilityDates;
    std::vector<int> timesOfHandling;

    if(file.good())
    {
        int numberOfTasks;
        int availbilityDate;
        int timeOfHandling;

        file >> numberOfTasks;
        for(int i = 0; i < numberOfTasks; ++i)
        {
            file >> availbilityDate;
            file >> timeOfHandling;

            availbilityDates.push_back(availbilityDate);
            timesOfHandling.push_back(timeOfHandling);
        }
    }

    file.close();
    return std::make_pair(availbilityDates, timesOfHandling);
}

int JacksonRule(TaskFeatures& taskFeatures)
{
    int numberOfTasks = taskFeatures.first.size();

    for (int i = 0; i<numberOfTasks; i++)
    {
        for(int j=1; j<numberOfTasks; j++)
        {
            if(taskFeatures.first.at(j-1) > taskFeatures.first.at(j))
            {
                std::swap(taskFeatures.first.at(j-1), taskFeatures.first.at(j));
                std::swap(taskFeatures.second.at(j-1), taskFeatures.second.at(j));
            }
        }
    }

    std::vector<int> C;
    C.resize(numberOfTasks,0);
    for (int i=1; i< numberOfTasks; i++)
        C.at(i)=std::max(taskFeatures.first.at(i), C.at(i-1)) + taskFeatures.second.at(i);

    return C.at(numberOfTasks-1);
}


int main()
{
    TaskFeatures taskFeatures = fileHandling("JACK3.DAT");
    std::cout << JacksonRule(taskFeatures);

    return 0;
}
