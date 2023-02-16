#include <iostream>
#include <vector>
#include <string>
using namespace std;

const char TIME_DELIMITER=':';
const string DAILY_MEETING_END="#";
const char START_END_DELIMITER='-';
const string START_TIME="00:00-12:00";
const string STOP_TIME="20:00-00:00";

struct meeting_work
{
    vector <string> daily_meeting; 
    vector <vector <string>> daily_work;
};

int stoi_times(string str, int start_index, int stop_index)
{
    string wanted_time;
    wanted_time.push_back(str[start_index]);
    wanted_time.push_back(str[stop_index]);
    return stoi(wanted_time);
}

vector <string> determine_free_times(vector <string> meetings)
{
    vector <string> free_time;
    string index_of_free_time;
    int free_time_num=0;

    for (int meet_num=0; meet_num<meetings.size()-1; meet_num++)
    {
        if ((stoi_times(meetings[meet_num],6,7)<stoi_times(meetings[meet_num+1],0,1)) ||
            (stoi_times(meetings[meet_num],6,7)==stoi_times(meetings[meet_num+1],0,1)&&
             stoi_times(meetings[meet_num],9,10)<stoi_times(meetings[meet_num+1],3,4)))
            {
                for (int char_num1=0; char_num1<5;char_num1++)
                    index_of_free_time.push_back(meetings[meet_num][char_num1+6]);

                index_of_free_time.push_back(START_END_DELIMITER);

                for (int char_num2=0; char_num2<5;char_num2++)
                    index_of_free_time.push_back(meetings[meet_num+1][char_num2]);

                index_of_free_time.push_back(START_END_DELIMITER);
                index_of_free_time+=to_string(free_time_num+1);

                free_time.push_back(index_of_free_time);

                index_of_free_time.clear();

                free_time_num++;
            }
    }
    return free_time;
}

string time_sum(int hour, int min, int duration)
{
    string fin_time;
    int minute= min+duration;
    int fin_hour=hour+(minute/60);
    minute=minute%60;

    fin_time+=to_string(fin_hour);
    fin_time.push_back(TIME_DELIMITER);
    if(minute<10)
        fin_time.push_back('0');
    fin_time+=to_string(minute);

    return fin_time;
}

vector <vector <string>> scheduling (vector <vector <string>> daily_work, 
                                     vector <string> free_times)
{
    string time_end;
    string time_save; 
    int schedule_count=0;
    vector <vector <string>> schedule;
    vector <string> updated_time;

      for(int work_count=0; work_count<daily_work.size(); work_count++)
    {
       for(int free_time_id=0; free_time_id<free_times.size(); free_time_id++)
        {
            if (stoi(daily_work[work_count][1])== int(free_times[free_time_id][12])-48)
            {
                time_end= time_sum(stoi_times(free_times[free_time_id],0,1),
                                   stoi_times(free_times[free_time_id],3,4),
                                   stoi(daily_work[work_count][0]));

                for(int count=0; count<6; count++)
                    time_save.push_back(free_times[free_time_id][count]);

                time_save +=time_end;
                updated_time.push_back(time_save);

                schedule.push_back(updated_time);

                time_save.clear();
                updated_time.clear();

                schedule[schedule_count].push_back(daily_work[work_count][2]);
                schedule_count++;

                for(int update=0; update<time_end.size(); update++)
                    free_times[free_time_id][update]=time_end[update];

                break;
            }
        }
    }
    return schedule;
}

struct meeting_work take_and_arrange_inputs()
{
    struct meeting_work plans;
    vector <string> daily_work_index;
    string input; 
    int daily_meeting_end_check=0; 
    int index_length_is_2=0; 

    plans.daily_meeting.push_back(START_TIME);

    while (cin >> input)
    {
        if (input == DAILY_MEETING_END)
            daily_meeting_end_check=1;

        else
        {
            if (input != DAILY_MEETING_END && daily_meeting_end_check==0)
                plans.daily_meeting.push_back(input);

            else if (input != DAILY_MEETING_END && daily_meeting_end_check==1)
            {
                index_length_is_2 ++;
                daily_work_index.push_back(input);

                if(index_length_is_2 ==2)
                {
                    plans.daily_work.push_back(daily_work_index);
                    daily_work_index.clear();
                    index_length_is_2 =0;
                }
            }
        } 
    }
    
    plans.daily_meeting.push_back(STOP_TIME);

    for (int work_id=1;work_id<=plans.daily_work.size();work_id++)
        plans.daily_work[work_id-1].push_back(to_string(work_id));
    
    return plans;
}

int main()
{
    struct meeting_work daily_plans;
    vector <string> free_times;
    vector <vector <string>> scheduled_plan;

    daily_plans=take_and_arrange_inputs();

    free_times=determine_free_times(daily_plans.daily_meeting);

    scheduled_plan=scheduling(daily_plans.daily_work,free_times);

    for (int row=0;row<scheduled_plan.size();row++){
        for (int element=0;element<scheduled_plan[row].size()-1;element++)
        {
            cout <<scheduled_plan[row][1]<<' ';
            cout <<scheduled_plan[row][element]<<' ';
        }
        cout << '\n';
    }
    return 0;
}