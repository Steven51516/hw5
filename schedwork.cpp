

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool valid(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::map<int, int>& shifts,
    int row,
    int col);

bool solve_helper(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::map<int, int>& shifts,
    int row,
    int col);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
    std::map<int, int> shifts;
    int days = avail.size();
    int n_nurse = avail[0].size();
		//shifts[i] means the total shifts for nurse i
    for(int i = 0; i<n_nurse; i++) shifts[i]=0;
		//initialize the sched matrix
    for(int i = 0; i<days; i++)
    {
        std::vector<Worker_T> temp;
        for(int j = 0; j<int(dailyNeed); j++) temp.push_back(0);
        sched.push_back(temp);
    }
    AvailabilityMatrix A = avail;
    return solve_helper(A, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool solve_helper(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::map<int, int>& shifts,
    int row,
    int col)
{
    int n_nurse = avail[0].size();
    for(int i = 0; i<int(n_nurse); i++)
    {
        sched[row][col]=i;
  
        if(valid(avail, dailyNeed, maxShifts, sched, shifts, row, col))
        { 
            shifts[i]+=1;
            avail[row][i]=0;
            if(row==int(avail.size()-1) && col==int(dailyNeed-1))  return true;
            else if((col==int(dailyNeed-1))&&solve_helper(avail, dailyNeed, maxShifts, sched, shifts, row+1, 0)) return true;
            else if(col!=int(dailyNeed-1)&&solve_helper(avail, dailyNeed, maxShifts, sched, shifts, row, col+1))  return true;
            //backtrack if fails
						shifts[i]-=1;
            avail[row][i]=1;
        }
    }
    return false;
}

//a helper function to determine whether the current sched matrix is valid
bool valid(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::map<int, int>& shifts,
    int row,
    int col)
{
    int id = sched[row][col];
    if(avail[row][id]==0) return false;
    if(shifts[id]+1 > int(maxShifts)) return false;
    return true;
}

