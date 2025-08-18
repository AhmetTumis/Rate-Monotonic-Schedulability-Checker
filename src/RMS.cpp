#include "RMS.h"

void RMS::GetTaskSet()
{
    taskSetSize = 0;

    while (true) {
        std::cout << "Please enter the number of tasks (>0): ";
        if (std::cin >> taskSetSize && taskSetSize > 0) {
            break;
        } else {
            std::cout << "Invalid input. Number of tasks must be a positive integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    for (int i = 1; i <= taskSetSize; i++) {
        Task newTask;
        newTask.taskNum = i;
        newTask.taskName = "P_" + std::to_string(newTask.taskNum);

        while (true) {
            std::cout << "C_" << i << ": ";
            if (std::cin >> newTask.C_i && newTask.C_i > 0) {
                break;
            } else {
                std::cout << "Invalid input. C_" << i << " must be a positive integer.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        while (true) {
            std::cout << "T_" << i << ": ";
            if (std::cin >> newTask.T_i && newTask.T_i > 0) {
                break;
            } else {
                std::cout << "Invalid input. T_" << i << " must be a positive integer.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        std::cout << "Adding task " << newTask.taskName
                  << " with C_" << i << ": " << newTask.C_i
                  << " and T_" << i << ": " << newTask.T_i
                  << " to the task set!\n";

        taskSet.push_back(newTask);
    }

    std::cout << "\n";
}

void RMS::ComputeUtilFactor()
{
    for(int i = 0; i < taskSet.size(); i++){
        utilFactor += float(taskSet[i].C_i) / float(taskSet[i].T_i);
    }
}

void RMS::PrintHello()
{
    std::cout << "Hello\n";

}

bool RMS::CheckSceduleGuarantee()
{
    
    float limit = taskSetSize * (std::pow(2, 1.0/taskSetSize) - 1.0);
    
    std::cout << "Task set utilization factor: " << utilFactor << "\n";
    std::cout << "Task set size: " << taskSetSize << "\n";
    std::cout << "Value the ufactor should be bigger than: " << limit << "\n";

    if(utilFactor <= 1.0)
        isCheckable = true;

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
    int taskIndex = 0;
    for(const auto &t : taskSet){
        
        std::cout << "\n\n";

        if(&t == &taskSet.front()){
            std::cout << t.taskName << "^0 = C_0 = " << t.C_i << "<=" << t.T_i << "? ";
            if(t.C_i <= t.T_i){
                std::cout << "√\n";
            } else {
                std::cout << "X\n";
                return false;
            }
            taskIndex++;
            continue;
        }    
        
        int counter = 0;
        int prevR_i = 0;
        // ⌈x⌉
        bool resume = true;
        while(resume){

            std::string temp = t.taskName + "^" + std::to_string(counter);
            int curR_i = 0;

            if(counter == 0){
                std::cout << t.taskName << "^0 = C_0 = " << t.C_i << "<=" << t.T_i << "? ";
                if(t.C_i > t.T_i){
                    std::cout << "X\n";
                    return false;
                }
                std::cout << "√\n";
                prevR_i = t.C_i;
                counter++;
                continue;
            }
            
            curR_i += t.C_i;
            std::cout << temp << " = " << t.C_i; 
            for(int i=0; i<taskIndex; i++){
                std::cout << " + ⌈" << prevR_i << "/" << taskSet[i].T_i << "⌉ * " << taskSet[i].C_i;  
                curR_i += ((prevR_i + taskSet[i].T_i - 1) / taskSet[i].T_i)*taskSet[i].C_i;                
            }
            std::cout << " = " << curR_i << " <= " << t.T_i << "? ";
            if(curR_i > t.T_i){
                std::cout << "X\n";
                return false;
            }
            std::cout << "√\n";

            if(curR_i == prevR_i){
                std::cout << "\nFixed point detected\n";
                resume = false;
            }
            prevR_i = curR_i;
            counter++;

        }
        taskIndex++;
    }
    return true;
}