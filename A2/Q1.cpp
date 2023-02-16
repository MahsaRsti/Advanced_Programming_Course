#include <iostream>
#include <string>
using namespace std;

const string FIRST_STRING="0";
const int FIRST_STEP=1;

string read_num_k(string str,int n, int k, int step)
{
    string updated_str;
    if (step==n)
       return to_string(int(str[k-1])-48);
    else
    {
        for(int num=0; num<str.size(); num++)
        {
            if (str[num]=='0')
            {
                updated_str.push_back('0');
                updated_str.push_back('1');
            }
            else if(str[num]=='1')
            {
                updated_str.push_back('1');
                updated_str.push_back('0');
            }
        }
        step++;
        return read_num_k(updated_str,n,k,step);

    }

}
int main()
{
    int n;
    int k;
    cin >>n>>k;
    cout <<read_num_k(FIRST_STRING,n,k,FIRST_STEP)<<'\n';
    return 0;
}