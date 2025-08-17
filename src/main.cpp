#include "RMS.h"

int main(){
    
    RMS rms;
    rms.PrintHello();
    rms.GetTaskSet();
    rms.computeUtilFactor();
    if(rms.CheckSceduleGuarantee())
        std::cout << "Provided task set is schedulable by RM\n";
    else
        std::cout << "Provided task set is not schedulable by RM\n";
    
    rms.SortAndAssignPriOrder();
    rms.ResponseTimeAnalysis();

    return EXIT_SUCCESS;

}