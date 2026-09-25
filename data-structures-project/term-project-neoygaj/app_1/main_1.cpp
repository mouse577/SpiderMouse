
#include "../code_1/SpiderMouse.h"
#include "../code_1/SpiderMouse.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <array>


using namespace std;

int main()
{
    SpiderMouse testObject;

    testObject.BuildWeb();
    
    //vector<shared_ptr<spiderNode>> mouse_date = testObject.findMouseStartDate(20230409);
    
    testObject.master();

    return 0;
}