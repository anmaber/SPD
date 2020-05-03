#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <string>

using TaskFeatures = std::pair<std::vector<int>,std::vector<int>>;


std::vector<int> processFile(int columns, std::string fileName){
	std::ifstream file;
	file.open(fileName);
	std::istream_iterator<int> start(file), end;
	std::vector<int> values(start, end);

	std::vector<int> valuesProcessed;
	for(unsigned int i=0; i<values.size(); ++i){
		if(i%columns==1)
			valuesProcessed.push_back(values[i]);
	}

    // std::cout << "Val::";
	// std::copy(valuesProcessed.begin(), valuesProcessed.end(),
	// 	std::ostream_iterator<int>(std::cout, "\n"));
	return valuesProcessed;
}

TaskFeatures bindToTaskFeatures(const std::vector<int>& processedFile)
{

    std::vector<int> availbilityDates(processedFile.size(),0);
    return {availbilityDates, processedFile};
}

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
    TaskFeatures taskFeatures = bindToTaskFeatures(processFile(10,"20tllrd"));
    std::cout << JacksonRule(taskFeatures);

    std::vector<std::string> countOfElems = {"20","50","100","200"};
    std::vector<int> collumns = {10,10,10,40};

    std::string fileName;

    for(auto i=0u; i < countOfElems.size(); ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            std::string post = std::to_string(j);
            fileName.append(countOfElems.at(i));
            fileName.append("tllrd");
            fileName.append(post);
            std::cout<<fileName<<"\n";
            fileName.clear();
        }
    }

    return 0;
}
