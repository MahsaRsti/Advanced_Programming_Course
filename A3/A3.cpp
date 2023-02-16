#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

const string ERROR= "Not Found";
const string DELIMITER=": ";
const string SPLIT_DELIMITER=" ";

struct language
{
    string language_name;
    string name_of_its_translator;
    int num_of_its_translators;
    int language_id;
};
typedef vector <language> event_languages;

struct translator
{
    string translator_name;
    vector <string> start_time;
    vector <string> end_time;
    vector <string> languages;
};
typedef vector <translator> translators;

struct event
{
    string event_name;
    string start_time;
    string end_time;
    vector <language> event_languages;
};
typedef vector <event> events;

struct input_info
{
    vector <event> events;
    vector <translator> translators;
};
 
vector <string> split_by_space(string line) 
{
    vector <string> results;
    int result_index=0;
    int space_index;
    while ( result_index<line.size()) 
    {
		space_index=line.find(SPLIT_DELIMITER,result_index);
		if (space_index==string::npos) 
        {
			results.push_back(line.substr(result_index));
			break;
		}
		results.push_back(line.substr(result_index,space_index-result_index));
		result_index=space_index+1;
	}
    return results;
}

struct translator read_translators(string input_line) 
{
    struct translator translator;
    vector <string> translator_info=split_by_space(input_line);
    translator.translator_name=translator_info[0];
    translator.start_time.push_back(translator_info[1]);
    translator.end_time.push_back(translator_info[2]);
    for (int language_count=3; language_count<translator_info.size(); language_count++)
        translator.languages.push_back(translator_info[language_count]);
    return translator;

}
struct event read_events(string input_line) 
{
    struct event event;
    struct language event_langs;
    vector <string> event_info=split_by_space(input_line);
    event.event_name=event_info[0];
    event.start_time=event_info[1];
    event.end_time=event_info[2];
    for (int language_count=3; language_count<event_info.size(); language_count++)
    {
        event_langs.language_name=event_info[language_count];
        event_langs.language_id=language_count-3;
        event.event_languages.push_back(event_langs);
    }
    return event;
}

struct input_info read_inputs(string file_name) 
{
    struct input_info inputs;
    string num_of_translators;
    string num_of_events;

    ifstream input_csv(file_name);
    string line;

    getline(input_csv,num_of_translators);
    for(int count=0; count<stoi(num_of_translators); count++)
    {
        getline(input_csv,line);
        inputs.translators.push_back(read_translators(line));
    }
    getline(input_csv,num_of_events);
    for(int count=0; count<stoi(num_of_events); count++)
    {
        getline(input_csv,line);
        inputs.events.push_back(read_events(line));
    }
    input_csv.close();
    return inputs;
}

event_languages sort_languages_base_on_num_of_trnaslators(struct event current_event,
                                                          translators translators) 
{
    for(int lan_count=0; lan_count<current_event.event_languages.size(); lan_count++)
    {
        current_event.event_languages[lan_count].num_of_its_translators=0;
        for(int trans_count=0; trans_count<translators.size(); trans_count++)
        {
            for(int lang_of_trans=0; lang_of_trans<translators[trans_count].languages.size(); 
                lang_of_trans++)
            {
                if(current_event.event_languages[lan_count].language_name==
                   translators[trans_count].languages[lang_of_trans])
                   current_event.event_languages[lan_count].num_of_its_translators++;
            }
        }
    }
    sort(current_event.event_languages.begin(),current_event.event_languages.end(),
         [](language a, language b)
    {
        return a.num_of_its_translators < b.num_of_its_translators;
    });
    return current_event.event_languages;
}

int stoi_times(string str, int start_index, int stop_index) 
{
    string wanted_time;
    if(str[start_index]==0)
        wanted_time.push_back(str[stop_index]);
    else
    {
        wanted_time.push_back(str[start_index]);
        wanted_time.push_back(str[stop_index]);
    }
    return stoi(wanted_time);
}

bool free_tanslator_conditon(int hour_start, int min_start, int hour_end,
                             int min_end, string trans_start, string trans_end) 
{
    int trans_hour_start=stoi_times(trans_start,0,1);
    int trans_min_start=stoi_times(trans_start,3,4);
    int trans_hour_end=stoi_times(trans_end,0,1);
    int trans_min_end=stoi_times(trans_end,3,4);

    if ((hour_start>trans_hour_start && hour_end<trans_hour_end) ||
        (hour_start==trans_hour_start && min_start>=trans_min_start && hour_end<trans_hour_end)||
        (hour_start>trans_hour_start && hour_end==trans_hour_end && min_end<=trans_min_end) ||
        (hour_start==trans_hour_start && min_start>=trans_min_start && hour_end==trans_hour_end &&
         min_end<=trans_min_end))
        return true;
    else
        return false;
}

translators find_free_translators(string Start, string End, translators all_translators) 
{
    int counting_translators=0;
    translators free_translators;
    translator none_translator;
    for(int trans_count=0; trans_count<all_translators.size(); trans_count++)
    {
        for(int start_count=0,end_count=0; 
            start_count<all_translators[trans_count].start_time.size() && 
            end_count<all_translators[trans_count].end_time.size(); start_count++, end_count++)
        {
            if(free_tanslator_conditon(stoi_times(Start,0,1),stoi_times(Start,3,4),
                                       stoi_times(End,0,1),stoi_times(End,3,4),
                                       all_translators[trans_count].start_time[start_count],
                                       all_translators[trans_count].end_time[end_count]))
            {
                free_translators.push_back(all_translators[trans_count]);
                counting_translators++;
                break;
            }
        }
    }
    if (counting_translators==0)
    {
        none_translator.translator_name=ERROR;
        free_translators.push_back(none_translator);
    }
    return free_translators;
}

translators detect_language_tranaslators(string language_name, translators free_translators)
{
    int counting_translators=0;
    translator none_translator;
    translators detected_translators;
    for(int trans_count=0; trans_count<free_translators.size(); trans_count++)
    {
        for (int lang_count=0; lang_count<free_translators[trans_count].languages.size();
             lang_count++)
        {
            if (free_translators[trans_count].languages[lang_count]==language_name)
            {
                detected_translators.push_back(free_translators[trans_count]);
                counting_translators++;
                break;
            }
        }
    }
    if (counting_translators==0)
    {
        none_translator.translator_name=ERROR;
        detected_translators.push_back(none_translator);
    }
    return detected_translators;
}

translator find_alphabetical_min_translator(translators same_translators)
{
    sort(same_translators.begin(),same_translators.end(),[](translator a, translator b)
    {
        return a.translator_name < b.translator_name;
    });
    return same_translators[0];
}

string find_suitable_translator(translators available_translators)
{
    int same_size_tranaslator_count=0;
    translators same_size_language_translators;
    translator chosen_translator;
    sort(available_translators.begin(),available_translators.end(),[](translator a, translator b)
    {
        return a.languages.size() < b.languages.size();
    });

    same_size_language_translators.push_back(available_translators[0]);
    for (int trans_count=1; trans_count<available_translators.size(); trans_count++)
    {
        if(available_translators[0].languages.size()== 
           available_translators[trans_count].languages.size())
        {
            same_size_tranaslator_count++;
            same_size_language_translators.push_back(available_translators[trans_count]);
        }
    }
    if (same_size_tranaslator_count==0)
        return available_translators[0].translator_name;
    else
    {
        chosen_translator=find_alphabetical_min_translator(same_size_language_translators);
        return chosen_translator.translator_name;
    }
}

string choose_translator(struct event current_event, struct language current_language,
                         translators all_translators)
{
    translators free_translators=find_free_translators(current_event.start_time,
                                                       current_event.end_time, all_translators);
    if (free_translators[0].translator_name==ERROR)
        current_language.name_of_its_translator=ERROR;
    else
    {
        translators this_language_translators=detect_language_tranaslators
                                              (current_language.language_name, free_translators);
        if (this_language_translators[0].translator_name==ERROR)
            current_language.name_of_its_translator=ERROR;

        else if(this_language_translators.size()==1)
            current_language.name_of_its_translator=this_language_translators[0].translator_name;
        else
            current_language.name_of_its_translator=find_suitable_translator
                                                    (this_language_translators);
    }
    return current_language.name_of_its_translator;
}

void update_times_of_chosen_translator(string chosen_translator, translators &all_translators,
                                       string Start, string End)
{
    for (int trans_count=0; trans_count<all_translators.size(); trans_count++)
    {
        if (all_translators[trans_count].translator_name==chosen_translator)
        {
            for(int start_count=0,end_count=0; 
                start_count<all_translators[trans_count].start_time.size() && 
                end_count<all_translators[trans_count].end_time.size(); start_count++, end_count++)
            {
                if (free_tanslator_conditon(stoi_times(Start,0,1),stoi_times(Start,3,4),
                                            stoi_times(End,0,1),stoi_times(End,3,4),
                                            all_translators[trans_count].start_time[start_count],
                                            all_translators[trans_count].end_time[end_count]))
                {
                   if (Start==all_translators[trans_count].start_time[start_count] &&
                       End==all_translators[trans_count].end_time[end_count])
                    {
                        all_translators[trans_count].start_time.erase(all_translators[trans_count].
                                                                      start_time.begin()+start_count);
                        all_translators[trans_count].end_time.erase(all_translators[trans_count].
                                                                    end_time.begin()+end_count); 
                    }
                    else if (Start==all_translators[trans_count].start_time[start_count])
                    {
                       all_translators[trans_count].start_time.erase(all_translators[trans_count].
                                                                     start_time.begin()+start_count);
                       all_translators[trans_count].start_time.insert(all_translators[trans_count].
                                                                      start_time.begin()+start_count,
                                                                      End);
                    }
                    else if (End==all_translators[trans_count].end_time[end_count])
                    {
                       all_translators[trans_count].end_time.erase(all_translators[trans_count].
                                                                   end_time.begin()+end_count);
                       all_translators[trans_count].end_time.insert(all_translators[trans_count].
                                                                    end_time.begin()+end_count,
                                                                    Start);
                    }
                    else
                    {
                        all_translators[trans_count].start_time.insert(all_translators[trans_count].
                                                                       start_time.begin()+start_count
                                                                       +1,End);
                        all_translators[trans_count].end_time.insert(all_translators[trans_count].
                                                                     end_time.begin()+end_count,
                                                                     Start);
                    }
                    break;
                }
            }
            break;
        }
    }
}

events arrangement(struct input_info Info)
{
    string chosen_translator;
    for(int num_of_event=0; num_of_event<Info.events.size();num_of_event++)
    {
        Info.events[num_of_event].event_languages=sort_languages_base_on_num_of_trnaslators(
                                                    Info.events[num_of_event],
                                                    Info.translators);
        for(int lang_count=0; lang_count<Info.events[num_of_event].event_languages.size();
            lang_count++)
        {
            Info.events[num_of_event].event_languages[lang_count].name_of_its_translator=
            choose_translator(Info.events[num_of_event],
                              Info.events[num_of_event].event_languages[lang_count],
                              Info.translators);
            chosen_translator=Info.events[num_of_event].event_languages[lang_count].
                              name_of_its_translator;
            if (chosen_translator != ERROR)
                update_times_of_chosen_translator(chosen_translator, Info.translators,
                                                  Info.events[num_of_event].start_time,
                                                  Info.events[num_of_event].end_time);
        }
    }
    return Info.events;
}

void print_output(events scheduled_events)
{
    for (int event_count=0; event_count<scheduled_events.size();event_count++)
    {
        sort(scheduled_events[event_count].event_languages.begin(),
                 scheduled_events[event_count].event_languages.end(),[](language a, language b)
        {
            return a.language_id < b.language_id;
        });
        cout<<scheduled_events[event_count].event_name<<'\n';
        for (int lang_count=0; lang_count<scheduled_events[event_count].event_languages.size();
             lang_count++)
        {
            cout<<scheduled_events[event_count].event_languages[lang_count].language_name<<DELIMITER;
            cout<<scheduled_events[event_count].event_languages[lang_count].name_of_its_translator;
            cout<<'\n';
        }
    }
}

int main(int argc, char* argv[])
{
    struct input_info trnaslators_events;
    events scheduled_events;
    trnaslators_events=read_inputs(argv[1]);
    scheduled_events=arrangement(trnaslators_events);
    print_output(scheduled_events);
    return 0;
}