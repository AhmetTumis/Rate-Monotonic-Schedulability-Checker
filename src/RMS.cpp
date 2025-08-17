#include "RMS.h"

void RMS::GetTaskSet()
{

    taskSetSize = 0;

    std::cout << "Please enter the number of tasks: ";
    std::cin >> taskSetSize;

    for(int i=1; i<taskSetSize+1; i++){
        Task newTask;
        newTask.taskNum = i;
        newTask.taskName = "P_" + std::to_string(newTask.taskNum); 
        std::cout << "C_" << i << ": ";
        std::cin >> newTask.C_i;
        std::cout << "T_" << i << ": " ;
        std::cin >> newTask.T_i;
    
        std::cout << "Adding task " << newTask.taskName 
                    << " with C_" << i << ": " << newTask.C_i 
                    << " and T_" << i << ": "
                    << newTask.T_i << " to the task set!\n";  
        taskSet.push_back(newTask);
    }

}

void RMS::computeUtilFactor()
{
    for(int i = 0; i < taskSet.size(); i++){
        utilFactor += float(taskSet[i].C_i) / float(taskSet[i].T_i);
    }
    std::cout << "Util Factor is: " << utilFactor << "\n";
}

void RMS::PrintHello()
{
        std::cout << "Hello\n";

}

bool RMS::CheckSceduleGuarantee()
{
    
    float limit = taskSetSize * (std::pow(2, 1.0/taskSetSize) - 1.0);
    
    std::cout << "Task set size: " << taskSetSize << "\n";
    std::cout << "Task set utilization factor: " << utilFactor << "\n";
    std::cout << "Value the ufactor should be bigger than: " << limit << "\n";

    if(utilFactor <= limit)
        return true;
    
    return false;
}

void RMS::SortAndAssignPriOrder()
{
    
    std::sort(taskSet.begin(), taskSet.end(), [](const Task &a, const Task &b) {
        return a.T_i < b.T_i;
    });

    for (const auto &t : taskSet) {
        std::cout << "pri(" << t.taskName << ",1/" << t.T_i << ")";  
        if (&t != &taskSet.back()) {
            std::cout << " > ";
        }
    }
    std::cout << "\n";
}

bool RMS::ResponseTimeAnalysis()
{
    bool isSchedulable = true;

    for(const auto &t : taskSet){
        
        if(&t == &taskSet.front()){
            std::cout << t.taskName << "^0 = C_0 = " << t.C_i << "<=" << t.T_i << "? ";
            if(t.C_i <= t.T_i){
                std::cout << "√\n";
            } else {
                std::cout << "X\n";
                isSchedulable = false;
                break;
            }
        }    
        
        int counter = 0;
        // ⌈x⌉
        while(true){
            std::string temp = t.taskName 
            std::cout << 
        }

    }

    return isSchedulable;
}