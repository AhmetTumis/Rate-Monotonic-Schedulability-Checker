#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cmath>


struct Task{
    int taskNum;
    std::string taskName;
    int C_i;
    int T_i;
};

class RMS{

public:

    float utilFactor;
    std::vector<Task> taskSet;
    int taskSetSize;
    bool isRMGuaranteed = false;

    void GetTaskSet();
    void computeUtilFactor();
    
    void PrintHello();

    bool CheckSceduleGuarantee();
    bool ResponseTimeAnalysis();
    void SortAndAssignPriOrder();

};


