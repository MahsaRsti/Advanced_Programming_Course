#include "input.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    Input input(argv[1]);
    input.take_commands();
    return 0;
}