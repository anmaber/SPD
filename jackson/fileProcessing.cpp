#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

std::vector<double> processFile(int columns, std::string fileName){
	std::ifstream file;
	file.open(fileName);
	std::istream_iterator<double> start(file), end;
	std::vector<double> values(start, end);

	//std::cout << "Val::";
	//std::copy(values.begin(), values.end(),
	//	std::ostream_iterator<double>(std::cout, " "));
	//std::cout<<std::endl;

	std::vector<double> valuesProcessed;
	for(unsigned int i=0; i<values.size(); ++i){
		if(i%columns==1)
			valuesProcessed.push_back(values[i]);
	}
	//std::cout<<"Val::";
	//for(double d : valuesProcessed){
	//	std::cout<<d<<" ";
	//}
	//std::cout<<std::endl;
	return valuesProcessed;
}
