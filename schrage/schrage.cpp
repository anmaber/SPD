#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <chrono>

struct Task
{
    int r,p,q;
};

auto availableComparator = [](const Task& lhs, const Task& rhs){return lhs.q < rhs.q;};
using availableQueue = std::priority_queue<Task, std::vector<Task>, decltype(availableComparator)>;

auto unavailableComparator = [](const auto& lhs,const auto& rhs){return lhs.r > rhs.r;};
using unavailableQueue = std::priority_queue<Task, std::vector<Task>, decltype(unavailableComparator)>;

std::vector<Task> readFile(const std::string& fileName)
{
    std::vector<Task> tasks;
    std::fstream file;
    int numOfTasks;

    file.open(fileName, std::ios::in);
    if(file.good())
    {
        Task tmp;
        file >> numOfTasks;
        for(int i = 0; i < numOfTasks; ++i)
        {
            file >> tmp.r;
            file >> tmp.p;
            file >> tmp.q;
            tasks.push_back(tmp);
        }
    }
    file.close();

    return tasks;
}

void fillQueue(const std::vector<Task>& tasks, unavailableQueue& queue)
{
    for(auto elem : tasks)
        {
            queue.push(elem);
        }
}

int schrage(availableQueue& available, unavailableQueue& unavailable)
{
    Task e;
    int time = 0;
    int cMax = 0;
    while(!available.empty() || !unavailable.empty())
		{
			
			while(!unavailable.empty() && unavailable.top().r<=time)
			{
				e=unavailable.top();
				available.push(e);
				unavailable.pop();
				
			}
			if(available.empty())
			{
				time=unavailable.top().r;
			}
			else
			{
				e=available.top();
				available.pop();

				time+=e.p;
				cMax=std::max(cMax,time+e.q);
				
			}
		}
    return cMax;    
}

int main()
{
    unavailableQueue unavailable(unavailableComparator);
    availableQueue available(availableComparator);

    std::fstream results;

    results.open("results.csv", std::ios::out);
    if(results.good())
    {
        for(int i = 1; i<=10; ++i)
        {
            std::string fileName = "SCHRAGE";
            fileName.append(std::to_string(i));
            fileName.append(".DAT");

            fillQueue(readFile(fileName),unavailable);
            results << unavailable.size() << ",";

            auto start = std::chrono::high_resolution_clock::now();
            int res = schrage(available,unavailable);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration =std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            results<< res << ","<< duration.count() << "\n";

        }
    }

    return 0;
}