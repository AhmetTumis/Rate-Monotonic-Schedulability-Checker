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

    float utilFactor = 0.0;
    std::vector<Task> taskSet;
    int taskSetSize;
    bool isCheckable = false;
    bool isRMGuaranteed = false;

    void GetTaskSet();
    void ComputeUtilFactor();
    
    void PrintHello();

    bool CheckSceduleGuarantee();
    bool ResponseTimeAnalysis();
    void SortAndAssignPriOrder();

};


