#include "../code_1/SpiderMouse.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <array>


SpiderMouse::SpiderMouse(){
    // not used
}

SpiderMouse::~SpiderMouse(){
    // not used, using shared pointers
}

void SpiderMouse::initNode(){
    
    // Asks user for input for which nodeType to add, or "Q" to quit
    std::cout << "Which would you like to add?" << endl;
    std::cout << "Enter 1 to add a new mouse" << endl;
    std::cout << "Enter 2 to add a new experiment to an existing mouse" << endl;
    std::cout << "Enter 3 to add a new project" <<endl;
    std::cout << "Enter Q to Quit" << endl;
    std::cout << endl;
    string type;
    std::cin >> type;
    std::cout << endl;
    
    // Create new node 
    shared_ptr<spiderNode> ret(new spiderNode);
    
    // If user input is invalid, display error message and prompt to re-enter, loops until user entry is valid
    while (type != "1" && type != "2" && type != "3" && type != "Q"){
        std::cout << "!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
        std::cout << endl;
        std::cout << "Which would you like to add?" << endl;
        std::cout << "Enter 1 to add a new mouse" << endl;
        std::cout << "Enter 2 to add a new experiment to an existing mouse" << endl;
        std::cout << "Enter 3 to add a new project" <<endl;
        std::cout << "Enter Q to Quit" << endl;
        std::cout << endl;
        std::cin >> type;
        std::cout << endl;
    }
    
    // Selection "1" to add a new mouse, asks for user input for input parameters
    if (type == "1"){
        
        //  convert input string to int, set nodeType based on user input
        int TYPE = stoi(type);
        ret->nodeType = TYPE;
        
        // enter start date of first experiment with mouse, set startDate
        int start_date;
        std::cout << "Enter the start date (YYYYMMDD, ex. 20230430 for April 30th, 2023)" << endl;
        std::cout << endl;
        std::cin >> start_date;
        std::cout << endl;
        ret->startDate = start_date;
        
        // enter mouse ID tag number, set IDtag
        string id;
        std::cout << "Enter the mouse ID" << endl;
        std::cout << endl;
        std::cin >> id;
        std::cout << endl;
        ret->IDtag = id;
        
        //  enter mouse date of birth, set DOB 
        int dob;
        std::cout << "Enter the date of birth (YYYYMMDD, ex. 20230430 for April 30th, 2023)" << endl;
        std::cout << endl;
        cin >> dob;
        std::cout << endl;
        ret->DOB = dob;
        
        // Select genotype of mouse
        int Geno;
        std::cout << "Enter the genotype: " << endl;
        std::cout << "1 - Wild-Type" << endl;
        std::cout << "2 - Opn4cre-GCaMP" << endl;
        std::cout << "3 - Oxtrcre-GCaMP" << endl;
        std::cout << "4 - Chatcre" << endl;
        std::cout << endl;
        std::cin >> Geno;
        std::cout << endl;
        
        // If input is invalid, loop through error message and prompt to re-enter until input is valid
        while (Geno != 1 && Geno != 2 && Geno != 3 && Geno != 4){
            std::cout << "!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            std::cout << "Enter the genotype: " << endl;
            std::cout << "1 - Wild-Type" << endl;
            std::cout << "2 - Opn4cre-GCaMP" << endl;
            std::cout << "3 - Oxtrcre-GCaMP" << endl;
            std::cout << "4 - Chatcre" << endl;
            std::cout << endl;
            std::cin >> Geno;
            std::cout << endl;
        }
        
        // Set genotype based on user input
        if (Geno == 1){
            ret->genotype = "Wild-Type";
        }
        else if (Geno == 2){
            ret->genotype = "Opn4cre-GCaMP";
        }
        else if (Geno == 3){
            ret->genotype = "Oxtrcre-GCaMP";
        }
        else if (Geno == 4){
            ret->genotype = "Chatcre";
        }
        
        // Select mouse gender
        int gend;
        std::cout << "Enter the gender: " << endl;
        std::cout << endl;
        std::cout << "1 - Male" << endl;
        std::cout << "2 - Female" << endl;
        std::cin >> gend;
        
        // If input is invalid, loop through error message and prompt to re-enter until input is valid
        while (gend != 1 && gend != 2){
            std::cout <<"!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            std::cout << "Enter the gender: " << endl;
            std::cout << "1 - Male" << endl;
            std::cout << "2 - Female" << endl;
            std::cout << endl;
            std::cin >> gend;
            std::cout << endl;
        }
        
        // Set gender based on user input
        if (gend == 1){
            ret->gender = "Male";
        }
        else if (gend == 2){
            ret->gender = "Female";
        }
        
        // Select whether mouse is alive or not
        int Alive;
        std::cout << "Is the mouse alive?" << endl;
        std::cout << endl;
        std::cout << "1 - YES" << endl;
        std::cout << "2 - NO" << endl;
        std::cout << endl;
        std::cin >> Alive;
        std::cout << endl;
        
        // If input is invalid, loop through error message and prompt to re-enter until input is valid
        while (Alive != 1 && Alive != 2){
            std::cout << "!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            std::cout << "Is the mouse alive?" << endl;
            std::cout << endl;
            std::cout << "1 - YES" << endl;
            std::cout << "2 - NO" << endl;
            std::cout << endl;
            std::cin >> Alive;
            std::cout << endl;
        }
        
        // set alive based on user input
        if (Alive == 1){
            ret->alive = true;
        }
        else if (Alive == 2){
            ret->alive = false;
        }
        
        // Select experiment type for first experiment for the mouse
        int exp_type;
        std::cout << "What type of experiment was performed on this mouse today?" << endl;
        cout << endl;
        std::cout << "1 - AAV intravitreal injection" << endl;
        std::cout << "2 - pERG" << endl;
        std::cout << "3 - VEP" << endl;
        std::cout << "4 - ERG" << endl;
        std::cout << "5 - ONC" << endl;
        std::cout << "6 - 2p" << endl;
        std::cout << "7 - PC" << endl;
        std::cout << "8 - Histology" << endl;
        std::cout << endl;
        std::cin >> exp_type;
        std::cout << endl;
        
        // If input is invalid, loop through error message and prompt to re-enter until input is valid
        while (exp_type != 1 && exp_type != 2 && exp_type != 3 && exp_type != 4 && exp_type != 4 && exp_type != 5 && exp_type != 6 && exp_type != 7&& exp_type != 8){
            cout << "!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
            cout << endl;
            cout << "What type of experiment was performed on this mouse today?" << endl;
            cout << endl;
            cout << "1 - AAV intravitreal injection" << endl;
            cout << "2 - pERG" << endl;
            cout << "3 - VEP" << endl;
            cout << "4 - ERG" << endl;
            cout << "5 - ONC" << endl;
            cout << "6 - 2p" << endl;
            cout << "7 - PC" << endl;
            cout << "8 - Histology" << endl;
            cout << endl;
            cin >> exp_type;
            cout << endl;
        }
        
        // Set the expType based on user input
        if (exp_type == 1){
            ret->expType = "AAV intravitreal injection";
        }
        else if (exp_type == 2){
            ret->expType = "pERG";
        }
        else if (exp_type == 3){
            ret->expType = "VEP";
        }
        else if (exp_type == 4){
            ret->expType = "ERG";
        }
        else if (exp_type == 5){
            ret->expType = "ONC";
        }
        else if (exp_type == 6){
            ret->expType = "2p";
        }
        else if (exp_type == 7){
            ret->expType = "PC";
        }
        else if (exp_type == 8){
            ret->expType = "Histology";
        }
        
        // Enter notes for experiment
        string expNotes;
        std::cout << "Notes for experiment: " << endl;
        std::cout << endl;
        std::cin >> expNotes;
        std::cout << endl;
        
        // Set alive based on user input
        bool ALIVE;
        if (Alive == 1){
            ALIVE = true;
        }
        else if (Alive == 2){
            ALIVE = false;
        }
        
        // Enter notes for the mouse
        string Notes;
        std::cout << "Notes for mouse: " << endl;
        std::cout << endl;
        std::cin >> Notes;
        std::cout << endl;
        ret->notes = Notes;
        
        // Set projTitle to "-1" for mouse node
        string proj_title = "-1";
        ret->projTitle = proj_title;
        
        // Create new experiment node and add to mouseExpList for mouse
        shared_ptr<spiderNode> retExp;
        string Exp_Type = ret->expType;
        retExp = initExpNode(start_date, id, Exp_Type, expNotes, ALIVE);
        ret->mouseExpList.push_back(retExp);
        
        // add mouse node to mouseList
        mouseList.push_back(ret);
    }
    
    // Selection "2" to add a new experiment, asks for user input for input parameters
    else if (type == "2"){
        
        // convert input string to int, set nodeType 
        int TYPE = stoi(type);
        ret->nodeType = TYPE;
        
        // enter experiment start date, set to startDate
        int start_date;
        std::cout << "Enter the start date (YYYYMMDD, ex. 20230430 for April 30th, 2023)" << endl;
        std::cout << endl;
        std::cin >> start_date;
        std::cout << endl;
        ret->startDate = start_date;
        
        // enter mouse ID, set to IDtag
        string id;
        std::cout << "Enter the mouse ID" << endl;
        std::cout << endl;
        std::cin >> id;
        std::cout << endl;
        ret->IDtag = id;
        
        // Select experiment type
        int exp_type;
        std::cout << "What type of experiment was performed on this mouse today?" << endl;
        std::cout << endl;
        std::cout << "1 - AAV intravitreal injection" << endl;
        std::cout << "2 - pERG" << endl;
        std::cout << "3 - VEP" << endl;
        std::cout << "4 - ERG" << endl;
        std::cout << "5 - ONC" << endl;
        std::cout << "6 - 2p" << endl;
        std::cout << "7 - PC" << endl;
        std::cout << "8 - Histology" << endl;
        std::cout << endl;
        std::cin >> exp_type;
        std::cout << endl;
        
        // If input is invalid, loop through error message and prompt to re-enter until input is valid
        while (exp_type != 1 && exp_type != 2 && exp_type != 3 && exp_type != 4 && exp_type != 5 && exp_type != 6 && exp_type != 7 && exp_type > 8){
            cout << "!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            std::cout << "What type of experiment was performed on this mouse today?" << endl;
            std::cout << endl;
            std::cout << "1 - AAV intravitreal injection" << endl;
            std::cout << "2 - pERG" << endl;
            std::cout << "3 - VEP" << endl;
            std::cout << "4 - ERG" << endl;
            std::cout << "5 - ONC" << endl;
            std::cout << "6 - 2p" << endl;
            std::cout << "7 - PC" << endl;
            std::cout << "8 - Histology" << endl;
            std::cout << endl;
            cin >> exp_type;
            std::cout << endl;
        }
        
        // Set the expType based on user input
        if (exp_type == 1){
            ret->expType = "AAV intravitreal injection";
        }
        else if (exp_type == 2){
            ret->expType = "pERG";
        }
        else if (exp_type == 3){
            ret->expType = "VEP";
        }
        else if (exp_type == 4){
            ret->expType = "ERG";
        }
        else if (exp_type == 5){
            ret->expType = "ONC";
        }
        else if (exp_type == 6){
            ret->expType = "2p";
        }
        else if (exp_type == 7){
            ret->expType = "PC";
        }
        else if (exp_type == 8){
            ret->expType = "Histology";
        }
        
        // Select whether mouse is alive or not after the experiment
        int Alive;
        std::cout << "Is the mouse alive?" << endl;
        std::cout << endl;
        std::cout << "1 - YES" << endl;
        std::cout << "2 - NO" << endl;
        std::cout <<endl;
        std::cin >> Alive;
        std::cout << endl;
        
        // If input is invalid, loop through error message and prompt to re-enter until input is valid
        while (Alive != 1 && Alive != 2){
            std::cout << "!!! THE ENTRY WAS NOT VALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            std::cout << "Is the mouse alive?" << endl;
            std::cout << "1 - YES" << endl;
            std::cout << "2 - NO" << endl;
            std::cout << endl;
            std::cin >> Alive;
            std::cout << endl;
        }
        
        // set alive based on user input
        if (Alive == 1){
            ret->alive = true;
        }
        else if (Alive == 2){
            ret->alive = false;
        }
        
        // enter notes for experiment, set notes based on user input
        string Notes;
        std::cout << "Notes for experiment: " << endl;
        std::cout << endl;
        std::cin >> Notes;
        std::cout << endl;
        ret->notes = Notes;
        
        // find mouse that experiment was performed on, add experiment to mouseExpList
        shared_ptr<spiderNode> curMouse;
        curMouse = findMouseID(id);
        curMouse->mouseExpList.push_back(ret);
    }
    
    // Selection 3 to add a new project, asks for user input for input parameters
    else if (type == "3"){
        
        // convert input string to int, set type based on user input
        int TYPE = stoi(type);
        ret->nodeType = TYPE;
        
        // enter start date for project, set startDate based on user input
        int start_date;
        std::cout << "Enter the start date (YYYYMMDD, ex. 20230430 for April 30th, 2023)" << endl;
        std::cout << endl;
        std::cin >> start_date;
        std::cout << endl;
        ret->startDate = start_date;
        
        // enter project title, set projTitle based on user input
        string proj_title;
        std::cout << "Enter the project title" << endl;
        std::cout << endl;
        std::cin >> proj_title;
        std::cout << endl;
        ret->projTitle = proj_title;
        
        // enter notes for project, set notes based on user input
        string Notes;
        std::cout << "Notes for project: " << endl;
        std::cout << endl;
        std::cin >> Notes;
        std::cout << endl;
        ret->notes = Notes;
        
        // set unused variables in node for project node to "-1", alive = true
        ret->IDtag = "-1";
        ret->DOB = -1;
        ret->genotype = "-1";
        ret->gender = "-1";
        ret->alive = true;
        ret->expType = "-1";
        
        // add project node to projList
        projList.push_back(ret);
    }
}
        
            
        
shared_ptr<spiderNode> SpiderMouse::initMouseNode(int start_date, string id, int dob, string gend, bool Alive, string Geno, string exp_type, string mouseNotes, string expNotes){
    
    // create new mouse node, set node variables based on input parameters, or "-1" for unused variables for mouse node
    shared_ptr<spiderNode> ret(new spiderNode);
    ret->nodeType = 1;
    ret->startDate = start_date;
    ret->IDtag = id;
    ret->DOB = dob;
    ret->gender = gend;
    ret->alive = Alive;
    ret->genotype = Geno;
    ret->expType = "-1";
    ret->notes = mouseNotes;
    ret->projTitle = "-1";
    
    // create new experiment node based on input parameters, add to mouseExpList for mouse node, update alive for mouse node based on user input
    shared_ptr<spiderNode> retExp;
    if (Alive == true){
        retExp = initExpNode(start_date, id, exp_type, expNotes, true);
    }
    else {
        retExp = initExpNode(start_date, id, exp_type, expNotes, false);
    }
    
    // add experiment node to mouseExpList
    ret->mouseExpList.push_back(retExp);
    
    // add mouse node to mouseList
    mouseList.push_back(ret);
    
    return ret;
}

void SpiderMouse::initMouseNode2(int start_date, string id, int dob, string gend, bool Alive, string Geno, string exp_type, string mouseNotes, string expNotes){
    
    // create new mouse node, set node variables based on input parameters, or "-1" for unused variables for mouse node
    shared_ptr<spiderNode> ret(new spiderNode);
    ret->nodeType = 1;
    ret->startDate = start_date;
    ret->IDtag = id;
    ret->DOB = dob;
    ret->gender = gend;
    ret->alive = Alive;
    ret->genotype = Geno;
    ret->expType = "-1";
    ret->notes = mouseNotes;
    ret->projTitle = "-1";
    
    // create new experiment node based on input parameters, add to mouseExpList for mouse node, update alive for mouse node based on user input
    shared_ptr<spiderNode> retExp;
    if (Alive == true){
        retExp = initExpNode(start_date, id, exp_type, expNotes, true);
    }
    else {
        retExp = initExpNode(start_date, id, exp_type, expNotes, false);
    }
    
    // add experiment node to mouseExpList
    ret->mouseExpList.push_back(retExp);
    
    // add mouse node to mouseList
    mouseList.push_back(ret);
}

shared_ptr<spiderNode> SpiderMouse::initExpNode(int start_date, string id, string exp_type, string Notes, bool Alive){
    
    // create new experiment node, set node variables based on input parameters, or "-1" for unused variables for experiment node
    shared_ptr<spiderNode> retExp(new spiderNode);
    retExp->nodeType = 2;
    retExp->startDate = start_date;
    retExp->IDtag = id;
    retExp->expType = exp_type;
    retExp->notes = Notes;
    retExp->DOB = -1;
    retExp->gender = "-1";
    retExp->genotype = "-1";
    retExp->alive = Alive;
    retExp->projTitle = "-1";
    
    return retExp;
}

shared_ptr<spiderNode> SpiderMouse::initProjNode(int start_date, string proj_title, string Notes){
    
    // create a new project node, set node variables based on input parameters, or"-1" for unused variables for project node
    shared_ptr<spiderNode> ret(new spiderNode);
    ret->nodeType = 3;
    ret->startDate = start_date;
    ret->projTitle = proj_title;
    ret->notes = Notes;
    ret->IDtag = "-1";
    ret->DOB = -1;
    ret->genotype = "-1";
    ret->gender = "-1";
    ret->alive = true;
    ret-> expType = "-1";
    
    // add project node to projList
    projList.push_back(ret);
    
    return ret;
}

void SpiderMouse::initProjNode2(int start_date, string proj_title, string Notes){
    
    // create a new project node, set node variables based on input parameters, or"-1" for unused variables for project node
    shared_ptr<spiderNode> ret(new spiderNode);
    ret->nodeType = 3;
    ret->startDate = start_date;
    ret->projTitle = proj_title;
    ret->notes = Notes;
    ret->IDtag = "-1";
    ret->DOB = -1;
    ret->genotype = "-1";
    ret->gender = "-1";
    ret->alive = true;
    ret-> expType = "-1";
    
    // add project node to projList
    projList.push_back(ret);
}
    
shared_ptr<spiderNode> SpiderMouse::findMouseID(string id_tag){
    
    int length = mouseList.size();
    string id;
    shared_ptr<spiderNode> cur;
    
    // visit each node in mouseList until matching IDtag is found, then return pointer to discovered mouse node
    for (int i = 0; i < length; i++){
        cur = mouseList[i];
        id = cur->IDtag;
        if (id == id_tag){
            //std::cout << "A MOUSE WITH THE ENTERED ID TAG HAS BEEN FOUND: " << endl;
            //std::cout << "ID: " << cur->IDtag << ", Start Date: " << cur->startDate << endl;
            //std::cout << "Genotype: " << cur->genotype << endl;
            //std::cout << "Gender: " << cur->gender << endl;
            //std::cout << "Alive?: ";
            //if (cur->alive == true){
            //    std::cout << "YES" << endl;
            //}
            //else {
            //    std::cout << "NO" << endl;
            //}
            //std::cout << "Note: " << cur->notes << endl;
            //std::cout << endl;
            return cur;
        }
    }
    //std::cout << "NO MOUSE WITH THE ENTERED ID WAS FOUND" << endl;
    //std::cout << endl;
    return nullptr;
}

vector<shared_ptr<spiderNode>> SpiderMouse::findMouseStartDate(int start_date){
    
    int length = mouseList.size();
    int Start;
    shared_ptr<spiderNode> cur;
    vector<shared_ptr<spiderNode>> search;
    
    // visit each node in mouseList and for each node with matching startDate (could be >1 for a single start date), add pointer to search vector, then return vector
    for (int i = 0; i < length; i++){
        cur = mouseList[i];
        Start = cur->startDate;
        if (Start == start_date){
            search.push_back(cur);
        }
    }
    //length = search.size();
    //if (length == 0){
    //    std::cout << "NO MOUSE FOUND FOR THAT DATE" << endl;
    //}
    //else if (length == 1){
    //    std::cout << "THERE IS ONE MOUSE FROM THE ENTERED DATE: ";
    //}
    //else if (length > 1){
    //    std::cout << "THERE IS MORE THAN ONE MOUSE FROM THE ENTERED DATE: ";
    //}
    //for (int i = 0; i < length; i++){
    //    int selection = i+1;
    //    std::cout << selection << " - ID: " << search[i]->IDtag << ", Start Date: " << search[i]->startDate << endl;
    //    std::cout << "DOB: " << search[i]->DOB << endl;
    //    std::cout << "Genotype: " << search[i]->genotype << endl;
    //    std::cout << "Gender: " <<search[i]->gender << endl;
    //    std::cout << "Alive?: ";
    //    if (search[i]->alive == true){
    //        std::cout << "YES" << endl;
    //    }
    //    else {
    //        std::cout << "NO" << endl;
    //    }
    //    std::cout << "Notes: " << search[i]->notes << endl;
    //    return search;
    //}
    //cout << endl;
    return search;
}

shared_ptr<spiderNode> SpiderMouse::findExp(int start_date, string id, string exp_type){
    
    shared_ptr<spiderNode> cur;
    int length = mouseList.size();
    
    // visit each node in mouseList until node with matching IDtag is found
    for (int i = 0; i < length; i++){
        shared_ptr<spiderNode> temp;
        temp = mouseList[i];
        if (temp->IDtag == id){
            int tempLength = temp->mouseExpList.size();
            
            // visit each node in mouseExpList until node with matching startDate and expType is found, return pointer to experiment node
            for (int j = 0; j < tempLength; j++){
                shared_ptr<spiderNode> temp2;
                temp2 = temp->mouseExpList[j];
                if (temp2->startDate == start_date && temp2->expType == exp_type){
                    return temp2;
                }
            }
        }
    }
    return nullptr;
}

shared_ptr<spiderNode> SpiderMouse::findProj(string proj_title){
    int length = projList.size();
    shared_ptr<spiderNode> cur;
    
    // visit each node in projList until node with matching projTitle is found, return pointer to project node
    for (int i = 0;  i < length; i++){
        cur = projList[i];
        if (cur->projTitle == proj_title){
            return cur;
        }
    }
    return cur;
}
    

void SpiderMouse::addExp2Proj(int Exp_start, string id, string exp_type, string proj_title){
    
    // find experiment node by calling findExp member function
    shared_ptr<spiderNode> Exp;
    Exp = findExp(Exp_start, id, exp_type);
    shared_ptr<spiderNode> Proj;
    
    // find project node by calling findProj member function
    Proj = findProj(proj_title);
    Exp->expProjList.push_back(Proj);
    Proj->projectExpList.push_back(Exp);
}


void SpiderMouse::removeExpFromProj(int Exp_start, string id, string exp_type, string proj_title){
    
    // find project node by calling findProj member function, assign projectExpList to projExps vector
    shared_ptr<spiderNode> proj = findProj(proj_title);
    vector<shared_ptr<spiderNode>> projExps;
    projExps = proj->projectExpList;
    int length = projExps.size();
    shared_ptr<spiderNode> temp;
    
    // visit each node in projExps for project node until experiment node with matching startDate and expType is found and erase, then break
    for (int i = 0; i < length; i++){
        temp = projExps[i];
        if (temp->startDate == Exp_start && temp->expType == exp_type){
            proj->projectExpList.erase(proj->projectExpList.begin() + i);
            break;
        }
    }
    
    // visit each node in projExps for experiment node until project node with matching projTitle is found and erase, then break
    int Length = temp->expProjList.size();
    for (int j = 0; j < Length; j++){
        shared_ptr<spiderNode> temp2 = temp->expProjList[j];
        if (temp2->projTitle == proj_title){
            temp->expProjList.erase(temp->expProjList.begin() + j);
            break;
        }
    }
}

void SpiderMouse::addExp2Mouse(int Exp_start, string exp_type, string id, string Notes, bool Alive){
    
    // create a new experiment node based on input parameters
    shared_ptr<spiderNode> cur = initExpNode(Exp_start, id, exp_type, Notes, Alive);
    
    // find existing mouse node by calling findMouseID by calling findMouseID member function, update alive for mouse node based on input parameter
    shared_ptr<spiderNode> mouse = findMouseID(id);
    if (Alive == true){
        mouse->alive = true;
    }
    else if (Alive == false){
        mouse->alive = false;
    }
    
    // add new experiment node to mouseExpList for mouse node
    mouse->mouseExpList.push_back(cur);    
}

vector<shared_ptr<spiderNode>> SpiderMouse::getMouseList(){
    
    // create vector and copy each element from mouseList
    vector<shared_ptr<spiderNode>> copy;
    shared_ptr<spiderNode> cur;
    int length = mouseList.size();
    for (int i = 0; i < length; i++){
        cur = mouseList[i];
        copy.push_back(cur);
    }
    return copy;
}

vector<shared_ptr<spiderNode>> SpiderMouse::getProjectList(){
    
    // create vector and copy each element from projList
    vector<shared_ptr<spiderNode>> copy;
    shared_ptr<spiderNode> cur;
    int length = projList.size();
    for (int i = 0; i < length; i++){
        cur = projList[i];
        copy.push_back(cur);
    }
    return copy;
}

void SpiderMouse::printAllProjects(){
    
    // print out all project titles in projList and prompt user to enter a selection
    std::cout << "ALL PROJECTS: " << endl;
    std::cout << endl;
    int length = projList.size();
    vector<string> q;
    for (int i = 0; i < length; i++){
        int selection = i+1;
        auto s = to_string(selection);
        q.push_back(s);
        std::cout << selection << " - Project Title: " << projList[i]->projTitle << ", Project Start Date: " << projList[i]->startDate << endl;
    }
    std::cout << "Q - Quit" << endl;
    std::cout << endl;
    std::cout << "Please select a project to print out experiments or Q to quit" << endl;
    std::cout << endl;
    
    string SELECTION;
    std::cin >> SELECTION;
    
    int l = q.size();
    bool contains = false;
    
    if (SELECTION == "Q" || l == 0){
        contains = true;
    }
    else {
        for (int i = 0; i < l; i++){
            if (q[i] == SELECTION){
                contains = true;
            }
        }
    }
    
    // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
    while (contains == false){
        std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
        std::cout << endl;
        for (int j = 0; j < l; j++){
            int selection = j+1;
            std::cout << selection << " - Project Title: " << projList[j]->projTitle << ", Project Start Date: " << projList[j]->startDate << endl;
        }
        std::cout << "Q - Quit" << endl;
        std::cout << endl;
        std::cout << "Please select a project to print out experiments or Q to quit" << endl;
        std::cout << endl;
        
        std::cin >> SELECTION;
        
        int l = q.size();
        if (SELECTION == "Q" || l == 0){
            contains = true;
        }
        else {
            for (int i = 0; i < l; i++){
                if (q[i] == SELECTION){
                    contains = true;
                }
            }
        }
    }
    
    // return of "Q" is selected to quit
    if (SELECTION == "Q"){
        return;
    }
    
    // print out details for all experiments in projectExpList for selected project, loop until "Q" is entered by user
    while (SELECTION != "Q"){
    
        int select = stoi(SELECTION);
        int idx = select - 1;
        shared_ptr<spiderNode> temp;
        temp = projList[idx];
        std::cout << "Project " << temp->projTitle << " Experiments: " << endl;
        std::cout << endl;
        int Length = temp->projectExpList.size();
        for (int j = 0; j < Length; j++){
            std::cout << "Experiment " << j+1 << ": " << endl;
            std::cout << "Start Date: " << temp->projectExpList[j]->startDate << endl;
            std::cout << "Animal ID: " << temp->projectExpList[j]->IDtag << endl;
            std::cout << "Experiment Type: " << temp->projectExpList[j]->expType << endl;
            std::cout << "Notes: " << temp->projectExpList[j]->notes  << endl;
            std::cout << endl;
        }
        std::cout << endl;
        std::cout << "ALL PROJECTS: " << endl;
        std::cout << endl;
        for (int i = 0; i < length; i++){
            int selection = i+1;
            std::cout << selection << " - Project Title: " << projList[i]->projTitle << ", Project Start Date: " << projList[i]->startDate << endl;
        }
        std::cout << endl;
        std::cout << "Please select a project to print out experiments or Q to quit" << endl;
        std::cout << endl;
        std::cin >> SELECTION;
        if (SELECTION == "Q"){
            return;
        }
    }
}


void SpiderMouse::printAllMice(){
    
    // print out startDate and IDtag for all mouse in mouseList and prompt user to enter selection
    std::cout << "ALL MICE: " << endl;
    std::cout << endl;
    int length = mouseList.size();
    vector<string> q;
    for (int i = 0; i < length; i++){
        int selection = i+1;
        auto s = to_string(selection);
        q.push_back(s);
        if (selection < 10){
            std::cout << selection << "  - Mouse ID: " << mouseList[i]->IDtag << ", Mouse Start Date: " << mouseList[i]->startDate << endl;
        }
        else {
            std::cout << selection << " - Mouse ID: " << mouseList[i]->IDtag << ", Mouse Start Date: " << mouseList[i]->startDate << endl;
        }
    }
    std::cout << "Q  - Quit" << endl;
    std::cout << endl;
    std::cout << "Please select a mouse to print out details and experiments or Q to quit" << endl;
    std::cout << endl;
    
    string SELECTION;
    std::cin >> SELECTION;
    
    int l = q.size();
    bool contains = false;
    
    // if "Q" is selected or mouselist is empty, or if user selection is valid, skip error message
    if (SELECTION == "Q" || l == 0){
        contains = true;
    }
    else {
        for (int i = 0; i < l; i++){
            if (q[i] == SELECTION){
                contains = true;
            }
        }
    }
    
    // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
    while (contains == false){
        std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
        std::cout << endl;
        for (int j = 0; j < l; j++){
            int selection = j+1;
            if (selection < 10){
                std::cout << selection << "  - Mouse ID: " << mouseList[j]->IDtag << ", Mouse Start Date: " << mouseList[j]->startDate << endl;
            }
            else {
                std::cout << selection << " - Mouse ID: " << mouseList[j]->IDtag << ", Mouse Start Date: " << mouseList[j]->startDate << endl;
            }
        }
        std::cout << "Q - Quit" << endl;
        std::cout << endl;
        std::cout << "Please select a mouse to print out details and experiments of Q to quit" << endl;
        std::cout << endl;
        
        std::cin >> SELECTION;
        
        int l = q.size();
        if (SELECTION == "Q" || l == 0){
            contains = true;
        }
        else {
            for (int j = 0; j < l; j++){
                if (q[j] == SELECTION){
                    contains = true;
                }
            }
        }
    }
    
    // print out mouse details for user selection and print out details for all experiments in mouseExpList for selected mouse, loop until user selects "Q" to quit
    while (SELECTION != "Q"){
        
        // print details for selected mouse and experiments in mouseExpList
        int select = stoi(SELECTION);    
        int idx = select - 1;
        shared_ptr<spiderNode> temp = mouseList[idx];
        cout << endl;
        std::cout << "Mouse: " << temp->IDtag << ", Start Date: " << temp->startDate << endl;
        std::cout << "DOB: " << temp->DOB << endl;
        std::cout << "Genotype: " << temp->genotype << endl;
        std::cout << "Gender: " << temp->gender << endl;
        std::cout << "Alive?: ";
        if (temp->alive == true){
            std::cout << "Yes" << endl;
        }
        else {
            std::cout << "No" << endl;
        }
        std::cout << "Notes: " << temp->notes << endl;
        std::cout << endl;    
        std::cout << "Experiments: " << endl;
        int Length = temp->mouseExpList.size();
        for (int k = 0; k < Length; k++){
            std::cout << "Experiment: " << k+1 << ", " << "Start Date: " << temp->mouseExpList[k]->startDate << endl;
            std::cout << "Experiment Type: " << temp->mouseExpList[k]->expType << endl;
            std::cout << "Notes: " <<temp->mouseExpList[k]->notes << endl;
            std::cout << endl;
        }
        std::cout << endl;    
        
        // re-print list of all mice in mouseList
        std::cout << "ALL MICE: " << endl;
        int length = mouseList.size();
        for (int i = 0; i < length; i++){
            int selection = i+1;
            if (selection < 10){
                std::cout << selection << "  - Mouse ID: " << mouseList[i]->IDtag << ", Start Date: " << mouseList[i]->startDate << endl;
            }
            else {
                std::cout << selection << " - Mouse ID: " << mouseList[i]->IDtag << ", Start Date: " << mouseList[i]->startDate << endl;
            }
        }
        std::cout << endl;
        
        // prompt user to select a mouse for input
        std::cout << "Please select a mouse to print out details and experiments or Q to quit" << endl;
        std::cin >> SELECTION;
        
        // if user input is valid, skip error message
        int l = q.size();
        bool contains = false;
        for (int i = 0; i < l; i++){
            if (q[i] == SELECTION || SELECTION == "Q" || l == 0){
                contains = true;
            }
        }
    
        // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
        while (contains == false){
            std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            for (int j = 0; j < l; j++){
                int selection = j+1;
                if (selection < 10){
                    std::cout << selection << "  - Mouse ID: " << mouseList[j]->IDtag << ", Mouse Start Date: " << mouseList[j]->startDate << endl;
                }
                else {
                    std::cout << selection << " - Mouse ID: " << mouseList[j]->IDtag << ", Mouse Start Date: " << mouseList[j]->startDate << endl;
                }
            }
            std::cout << "Q  - Quit" << endl;
            std::cout << endl;
            std::cout << "Please select a mouse to print out details and experiments of Q to quit" << endl;
            std::cout << endl;
        
            std::cin >> SELECTION;
        
            int l = q.size();
            contains = false;
            for (int j = 0; j < l; j++){
                if (q[j] == SELECTION){
                    contains = true;
                }
                else if (l == 0){
                    contains = true;
                }
            }
        }  
    }
}

void SpiderMouse::BuildWeb(){
    
    // build spiderNode object using initProjNode2, initMouseNode2, addExp2Proj and addExp2Mouse member functions for testing
    initProjNode2(20230401, "R01 Injury Physiology", "preliminary data for new R01 submission (December)");
    initMouseNode2(20230401, "V2000", 20230201, "M", true, "Wild-type", "AAV intravitreal injections", "normal", "good injections, reg glusnfr");
    initMouseNode2(20230402, "V2001", 20230202, "F", true, "Opn4cre-GCaMP", "pERG", "normal", "good recordings");
    addExp2Proj(20230402, "V2001", "pERG", "R01 Injury Physiology");
    initMouseNode2(20230403, "V2002", 20230203, "M", true, "Opn4cre-GCaMP", "pERG", "normal", "poor signal left eye");
    addExp2Proj(20230403, "V2002", "pERG", "R01 Injury Physiology"); 
    initMouseNode2(20230404, "V2003", 20230204, "F", true, "Wild-type", "AAV intravitreal injections", "normal", "good injections, reg glusnfr, right eye bleeding");
    addExp2Mouse(20230404, "ONC", "V2001", "Good left eye ONC", true);
    initMouseNode2(20230405, "V2004", 20230205, "M", true, "Opn4cre-GCaMP", "AAV intravitreal injections", "normal", "good injections, left eye, AAV TM");
    addExp2Mouse(20230405, "ONC", "V2002", "Good left eye ONC, minor bleed", true);
    initMouseNode2(20230406, "V2005", 20230206, "F", true, "Opn4cre-GCaMP", "AAV intravitreal injections", "normal", "good injections, left eye, AAV TM");
    initMouseNode2(20230407, "V2006", 20230207, "M", true, "Oxtrcre-GCaMP", "pERG", "normal", "good recodings, not great");
    addExp2Proj(20230407, "V2006", "pERG", "R01 Injury Physiology");
    initMouseNode2(20230408, "V2007", 20230208, "F", true, "Oxtrcre-GCaMP", "pERG", "normal", "good recodings, huge amplitude");
    addExp2Proj(20230408, "V2007", "pERG", "R01 Injury Physiology");
    initMouseNode2(20230409, "V2008", 20230209, "M", false, "Opn4cre-GCaMP", "PC", "left eye microphthalmia", "3 good cells");
    addExp2Proj(20230409, "V2008", "PC", "R01 Injury Physiology");
    addExp2Mouse(20230409, "VEP", "V2006", "Good recordings, right side noisy", true);
    addExp2Proj(20230409, "V2006", "VEP", "R01 Injury Physiology"); 
    addExp2Mouse(20230409, "VEP", "V2007", "Good recordings, huge amplitude", true);
    addExp2Proj(20230409, "V2007", "VEP", "R01 Injury Physiology");                 
    initProjNode2(20230410, "Motion Paper", "manuscript to submit for peer-review"); 
    initMouseNode2(20230410, "V2009", 20230210, "F", false, "Opn4cre-GCaMP", "PC", "normal", "1 good cell, 1 reconstructed, no recordings");
    addExp2Proj(20230410, "V2009", "PC", "R01 Injury Physiology");  
    addExp2Mouse(20230411, "ONC", "V2006", "Good left eye ONC", true);
    addExp2Mouse(20230412, "ONC", "V2007", "Good left eye ONC, minor bleed after", true);
    addExp2Mouse(20230415, "2p", "V2000", "Good responses, 10 regions", false);
    addExp2Proj(20230415, "V2000", "2p", "Motion Paper"); 
    addExp2Mouse(20230418, "pERG", "V2001", "Good recordings, 14 dpi, left eye no signal", true);
    addExp2Proj(20230418, "V2001", "pERG", "R01 Injury Physiology"); 
    addExp2Mouse(20230418, "2p", "V2003", "Good responses, 8 regions", false);
    addExp2Proj(20230418, "V2003", "2p", "Motion Paper"); //
    addExp2Mouse(20230419, "pERG", "V2002", "Good recordings, 14 dpi, left eye some signal", true);
    addExp2Proj(20230419, "V2002", "pERG", "R01 Injury Physiology");                
    addExp2Mouse(20230420, "2p", "V2001", "Good reponses, 7 regions ONC, 3 regions control", false);
    addExp2Proj(20230420, "V2001", "2p", "R01 Injury Physiology"); 
    addExp2Mouse(20230421, "2p", "V2002", "Good responses, 8 regions control", false);
    addExp2Proj(20230421, "V2002", "2p", "R01 Injury Physiology"); 
    addExp2Mouse(20230423, "pERG", "V2006", "Good recordings, left eye, 13 dpi", true);
    addExp2Proj(20230423, "V2006", "pERG", "R01 Injury Physiology");                   
    addExp2Mouse(20230423, "pERG", "V2007", "Good recordings, huge amplitude, 12 dpi", true);
    addExp2Proj(20230423, "V2007", "pERG", "R01 Injury Physiology"); 
    addExp2Mouse(20230425, "VEP", "V2006", "Good recordings, right eye noisy, 15 dpi", true);
    addExp2Proj(20230425, "V2006", "VEP", "R01 Injury Physiology"); 
    addExp2Mouse(20230425, "VEP", "V2007", "Good recordings, huge amplitude, 14 dpi", true);
    addExp2Proj(20230425, "V2007", "VEP", "R01 Injury Physiology"); 
    addExp2Mouse(20230427, "2p", "V2006", "Good responses, 9 ONC regions, 10 control regions, 17 dpi", false);
    addExp2Proj(20230427, "V2006", "2p", "R01 Injury Physiology"); 
    addExp2Mouse(20230428, "2p", "V2007", "Good responses, some rundown, 5 ONC regions, 5 control regions, 17 dpi", false);
    addExp2Proj(20230428, "V2007", "2p", "R01 Injury Physiology"); 
    addExp2Mouse(20230429, "Histology", "V2001", "gfp, rbpms, from 20230420, spinningdisc", false);
    addExp2Proj(20230429, "V2001", "Histology", "R01 Injury Physiology"); 
    addExp2Mouse(20230430, "Histology", "V2002", "gfp, rbpms, from 20230421, spiinningdisc", false);
    addExp2Proj(20230430, "V2002", "Histology", "R01 Injury Physiology"); 
    addExp2Mouse(20230504, "ONC", "V2004", "Good bilateral ONC", true);
    addExp2Mouse(20230504, "Histology", "V2006", "GFP, rbpms, iba1, staining started 20230427, spinning disc", false);
    addExp2Proj(20230504, "V2006", "Histology", "R01 Injury Physiology"); 
    addExp2Mouse(20230505, "ONC", "V2005", "Good left ONC, right moderate bleed", true);
    addExp2Mouse(20230510, "Histology", "V2007", "GFP, rbpms, iba1, staining started 20230428, slide scanner", false);
    addExp2Proj(20230510, "V2007", "Histology", "R01 Injury Physiology"); 
    addExp2Mouse(20230518, "2p", "V2004", "Good responses, 10 regions ONC, 5 regions control", false);
    addExp2Proj(20230518, "V2004", "2p", "R01 Injury Physiology"); 
    addExp2Mouse(20230519, "2p", "V2005", "Good responses, 12 regions ONC, 3 regions control", false);
    addExp2Proj(20230519, "V2005", "2p", "R01 Injury Physiology"); 
    addExp2Mouse(20230526, "Histology", "V2004", "gfp, rbpms, staining started 20230505, slide scanner", false);
    addExp2Proj(20230526, "V2004", "Histology", "R01 Injury Physiology"); 
    addExp2Mouse(20230527, "Histology", "V2005", "gfp, rbpms, staining started 20230505, slide scanner", false);
    addExp2Proj(20230527, "V2005", "Histology", "R01 Injury Physiology");
    initProjNode2(20230530, "Injury Paper", "TBI paper (collaboration)");
    addExp2Proj(20230402, "V2001", "pERG", "Injury Paper");
    addExp2Proj(20230403, "V2002", "pERG", "Injury Paper");
    addExp2Proj(20230407, "V2006", "pERG", "Injury Paper"); 
    addExp2Proj(20230408, "V2007", "pERG", "Injury Paper"); 
    addExp2Proj(20230409, "V2006", "VEP", "Injury Paper"); 
    addExp2Proj(20230409, "V2007", "VEP", "Injury Paper"); 
    addExp2Proj(20230418, "V2001", "pERG", "Injury Paper"); 
    addExp2Proj(20230419, "V2002", "pERG", "Injury Paper"); 
    addExp2Proj(20230423, "V2006", "pERG", "Injury Paper"); 
    addExp2Proj(20230423, "V2007", "pERG", "Injury Paper"); 
    addExp2Proj(20230425, "V2006", "VEP", "Injury Paper");
    addExp2Proj(20230425, "V2007", "VEP", "Injury Paper");
}


void SpiderMouse::master(){
    
    // !!! THIS FUNCTION MANAGES ALL ACTIONS TO BUILD OR MODIFY A SPIDERNODE OBJECT BASED ON USER INPUT AND CALLING MEMBER FUNCTIONS !!!
    
    // initNode(), printAllProjects(), addExp2Proj(), removeExpFromProj(), addExp2Mouse(), printAllMice();
    
    string SELECTION;

    // print out selection menu and prompt user to enter selection
    std::cout << "SELECT OPTION" << endl;
    std::cout << "1 - Add New MOUSE, Add New EXPERIMENT To Existing MOUSE, OR Add New PROJECT" << endl;
    std::cout << "2 - Add EXPERIMENT To PROJECT" << endl;
    std::cout << "3 - Remove EXPERIMENT From PROJECT" << endl;
    std::cout << "4 - Add EXPERIMENT To Existing MOUSE" << endl;
    std::cout << "5 - Print Projects" << endl;
    std::cout << "6 - Print Mice" << endl;
    std::cout << "Q - Quit" << endl;
    std::cout << endl;

    std::cin >> SELECTION;
    std::cout << endl;
    
    // prompt user for input based on selection for input parameters for corresponding member functions, loop until "Q" is entered to quit
    while (SELECTION != "Q"){
        
        // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
        while (SELECTION != "1" && SELECTION != "2" && SELECTION != "3" && SELECTION != "4" && SELECTION != "5" && SELECTION != "6" && SELECTION != "Q"){
            
            std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << "SELECT OPTION" << endl;
            std::cout << "1 - Add New MOUSE, Add New EXPERIMENT To Existing MOUSE, OR Add New PROJECT" << endl;
            std::cout << "2 - Add EXPERIMENT To PROJECT" << endl;
            std::cout << "3 - Remove EXPERIMENT From PROJECT" << endl;
            std::cout << "4 - Add EXPERIMENT To Existing MOUSE" << endl;
            std::cout << "5 - Print Projects" << endl;
            std::cout << "6 - Print Mice" << endl;
            std::cout << "Q - Quit" << endl;
            std::cout << endl;

            std::cin >> SELECTION;
            std::cout << endl;
        }
        
        // for selection "1", initNode() for new mouse, experiment or project node
        if (SELECTION == "1"){
            initNode();
        }
        
        // for selection "2", add new experiment to existing project
        else if (SELECTION == "2"){
            
            // print list of all projects in projList, to look at details and experiments in projectExpList, used for user upcoming user input
            std::cout << "Look through projects and then enter Q when finished" << endl;
            std::cout << endl;
            
            printAllProjects();
            
            // prompt user to enter information for experiment node variables
            int EXP_START;
            std::cout << "Enter experiment start date (YYYYMMDD)" << endl;
            std::cout << endl;
            std::cin >> EXP_START;
            std::cout << endl;
            
            string ID;
            std::cout << "ENTER mouse ID tag#" << endl;
            std::cout << endl;
            std::cin >> ID;
            std::cout << endl;
            
            int EXP_TYPE;
            string EXP_type;
            
            std::cout << "Enter experiment type: " << endl;
            std::cout << "1 - AAV intravitreal injection" << endl;
            std::cout << "2 - pERG" << endl;
            std::cout << "3 - VEP" << endl;
            std::cout << "4 - ERG" << endl;
            std::cout << "5 - ONC" << endl;
            std::cout << "6 - 2p" << endl;
            std::cout << "7 - PC" << endl;
            std::cout << "8 - Histology" << endl;
            std::cout << endl;
            std::cin >> EXP_TYPE;
            std::cout << endl;
            
            // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
            while (EXP_TYPE != 1 && EXP_TYPE != 2 && EXP_TYPE != 3 && EXP_TYPE != 4 && EXP_TYPE != 5 && EXP_TYPE != 6 && EXP_TYPE != 7 && EXP_TYPE != 8){
                std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
                std::cout << endl;
                std::cout << "Enter experiment type: " << endl;
                std::cout << "1 - AAV intravitreal injection" << endl;
                std::cout << "2 - pERG" << endl;
                std::cout << "3 - VEP" << endl;
                std::cout << "4 - ERG" << endl;
                std::cout << "5 - ONC" << endl;
                std::cout << "6 - 2p" << endl;
                std::cout << "7 - PC" << endl;
                std::cout << "8 - Histology" << endl;
                std::cout << endl;
                std::cin >> EXP_TYPE;
                std::cout << endl;
            }
                
                
            if (EXP_TYPE == 1){
                EXP_type = "AAV intravitreal injection";
            }
            else if (EXP_TYPE == 2){
                EXP_type = "pERG";
            }
            else if (EXP_TYPE == 3){
                EXP_type = "VEP";
            }
            else if (EXP_TYPE == 4){
                EXP_type = "ERG";
            }
            else if (EXP_TYPE== 5){
                EXP_type = "ONC";
            }
            else if (EXP_TYPE == 6){
                EXP_type = "2p";
            }
            else if (EXP_TYPE == 7){
                EXP_type = "PC";
            }
            else if (EXP_TYPE == 8){
                EXP_type = "Histology";
            }
            
            // prompt user to enter selection for project to add experiment to
            string in;
            string ProjTitle;
            printAllProjects();
            std::cout << "Select Project To Add Experiment To" << endl;
            std::cout << endl;
            std::cin >> in;
            std::cout << endl;
            
            //if (in == "Q"){
            //    continue;
            //}
            //else {
                
            // assign get projTitle based on user input, use member function addExp2Proj to add new experiment to exisiting project node
            int IN = stoi(in);
                int length = projList.size();
                for (int i = 0; i < length; i++){
                    if (IN-1 == i){
                        ProjTitle = projList[i]-> projTitle;
                    }
                }
                std::cout << ProjTitle;
                std::cout << endl;

                addExp2Proj(EXP_START, ID, EXP_type, ProjTitle);
            //}
        }
        
        // for selection "3" remove experiment from exisiting project
        else if (SELECTION == "3"){
            
            // print list of all projects in projList, to look at details and experiments in projectExpList, used for user upcoming user input
            std::cout << "Look through projects and then enter Q when finished" << endl;
            std::cout << endl;
            
            printAllProjects();

            // prompt user to enter information for experiment node variables
            int EXP_START;
            std::cout << "Enter experiment start date (YYYYMMDD)" << endl;
            std::cout << endl;
            std::cin >> EXP_START;
            std::cout << endl;
            
            string ID;
            std::cout << "ENTER mouse ID tag#" << endl;
            std::cout << endl;
            std::cin >> ID;
            std::cout << endl;
            
            int EXP_TYPE;
            string EXP_type;
            
            std::cout << "Enter experiment type: " << endl;
            std::cout << "1 - AAV intravitreal injection" << endl;
            std::cout << "2 - pERG" << endl;
            std::cout << "3 - VEP" << endl;
            std::cout << "4 - ERG" << endl;
            std::cout << "5 - ONC" << endl;
            std::cout << "6 - 2p" << endl;
            std::cout << "7 - PC" << endl;
            std::cout << "8 - Histology" << endl;
            std::cout << endl;
            std::cin >> EXP_TYPE;
            std::cout << endl;
            
            // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
            while (EXP_TYPE != 1 && EXP_TYPE != 2 && EXP_TYPE != 3 && EXP_TYPE != 4 && EXP_TYPE != 5 && EXP_TYPE != 6 && EXP_TYPE != 7 && EXP_TYPE != 8){
                std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
                std::cout << endl;
                std::cout << "Enter experiment type: " << endl;
                std::cout << "1 - AAV intravitreal injection" << endl;
                std::cout << "2 - pERG" << endl;
                std::cout << "3 - VEP" << endl;
                std::cout << "4 - ERG" << endl;
                std::cout << "5 - ONC" << endl;
                std::cout << "6 - 2p" << endl;
                std::cout << "7 - PC" << endl;
                std::cout << "8 - Histology" << endl;
                std::cout << endl;
                std::cin >> EXP_TYPE;
                std::cout << endl;
            }

            if (EXP_TYPE == 1){
                EXP_type = "AAV intravitreal injection";
            }
            else if (EXP_TYPE == 2){
                EXP_type = "pERG";
            }
            else if (EXP_TYPE == 3){
                EXP_type = "VEP";
            }
            else if (EXP_TYPE == 4){
                EXP_type = "ERG";
            }
            else if (EXP_TYPE == 5){
                EXP_type = "ONC";
            }
            else if (EXP_TYPE == 6){
                EXP_type = "2p";
            }
            else if (EXP_TYPE == 7){
                EXP_type = "PC";
            }
            else if (EXP_TYPE == 8){
                EXP_type = "Histology";
            }

            // assign get projTitle based on user input, use member function removeExpFromProj to add new experiment to exisiting project node
            int in;
            printAllProjects();
            std::cout << "Select Project To Remove Experiment From" << endl;
            //std::cout << endl;
            std::cin >> in;
            int length = projList.size();
            string ProjTitle;
            for (int i = 0; i < length; i++){
                if (in-1 == i){
                    ProjTitle = projList[i]-> projTitle;
                }
            }
            std::cout << ProjTitle;
            std::cout << endl;

            removeExpFromProj(EXP_START, ID, EXP_type, ProjTitle);
        }

        // for selection "4", add experiment from exisiting mouse
        else if (SELECTION == "4"){
            
            // prompt user to enter information for input variables for new experiment
            int EXP_START;
            std::cout << "Enter experiment start date (YYYYMMDD)" << endl;
            std::cout << endl;
            std::cin >> EXP_START;
            std::cout << endl;
            
            int EXP_TYPE;
            string EXP_type;
            
            std::cout << "Enter experiment type: " << endl;
            std::cout << "1 - AAV intravitreal injection" << endl;
            std::cout << "2 - pERG" << endl;
            std::cout << "3 - VEP" << endl;
            std::cout << "4 - ERG" << endl;
            std::cout << "5 - ONC" << endl;
            std::cout << "6 - 2p" << endl;
            std::cout << "7 - PC" << endl;
            std::cout << "8 - Histology" << endl;
            std::cout << endl;
            std::cin >> EXP_TYPE;
            std::cout << endl;
            
            // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
            while (EXP_TYPE != 1 && EXP_TYPE != 2 && EXP_TYPE != 3 && EXP_TYPE != 4 && EXP_TYPE != 5 && EXP_TYPE != 6 && EXP_TYPE != 7 && EXP_TYPE != 8){
                std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
                std::cout << endl;
                std::cout << "Enter experiment type: " << endl;
                std::cout << "1 - AAV intravitreal injection" << endl;
                std::cout << "2 - pERG" << endl;
                std::cout << "3 - VEP" << endl;
                std::cout << "4 - ERG" << endl;
                std::cout << "5 - ONC" << endl;
                std::cout << "6 - 2p" << endl;
                std::cout << "7 - PC" << endl;
                std::cout << "8 - Histology" << endl;
                std::cout << endl;
                std::cin >> EXP_TYPE;
                std::cout << endl;
            }

            if (EXP_TYPE == 1){
                EXP_type = "AAV intravitreal injection";
            }
            else if (EXP_TYPE == 2){
                EXP_type = "pERG";
            }
            else if (EXP_TYPE == 3){
                EXP_type = "VEP";
            }
            else if (EXP_TYPE == 4){
                EXP_type = "ERG";
            }
            else if (EXP_TYPE == 5){
                EXP_type = "ONC";
            }
            else if (EXP_TYPE == 6){
                EXP_type = "2p";
            }
            else if (EXP_TYPE == 7){
                EXP_type = "PC";
            }
            else if (EXP_TYPE == 8){
                EXP_type = "Histology";
            }

            // prompt user to enter information for existing mouse to add new experiment to, call member function addExp2Mouse with input parameters based on user input
            string id;
            std::cout << "Enter The Existing Mouse ID" << endl;
            std::cout << endl;
            std::cin >> id;
            std::cout << endl;

            bool ALIVE;
            int Alive;
            std::cout << "Is the mouse alive?" << endl;
            std::cout << "1 - YES" << endl;
            std::cout << "2 - NO" << endl;
            std::cout << endl;
            std::cin >> Alive;
            std::cout << endl;
            
            while (Alive != 1 && Alive != 2){
                std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
                std::cout << endl;
                std::cout << "Is the mouse alive?" << endl;
                std::cout << "1 - YES" << endl;
                std::cout << "2 - NO" << endl;
                std::cout << endl;
                std::cin >> Alive;
                std::cout << endl;
            }
            if (Alive == 1){
                ALIVE = true;
            }
            else if (Alive == 2){
                ALIVE = false;
            }
            
            string Notes;
            std::cout << "Enter Notes For Experiment" << endl;
            std::cout << endl;
            std::cin >> Notes;
            std::cout << endl;
            
            addExp2Mouse(EXP_START, EXP_type, id, Notes, ALIVE);
        }

        else if (SELECTION == "5"){
            printAllProjects();
        }

        else if (SELECTION == "6"){
            printAllMice();
        }

        // re-print list of selection options, prompt user to enter selection, loop until "Q" is entered to quit
        SELECTION.clear();
        std::cout << "SELECT OPTION" << endl;
        std::cout << "1 - Add New MOUSE, Add New EXPERIMENT To Existing MOUSE, OR Add New PROJECT" << endl;
        std::cout << "2 - Add EXPERIMENT To PROJECT" << endl;
        std::cout << "3 - Remove EXPERIMENT From PROJECT" << endl;
        std::cout << "4 - Add EXPERIMENT To Existing MOUSE" << endl;
        std::cout << "5 - Print Projects" << endl;
        std::cout << "6 - Print Mice" << endl;
        std::cout << "Q - Quit" << endl;
        std::cout << endl;

        std::cin >> SELECTION;
        std::cout << endl;
        
        // if the entry is invalid, print error message and prompt user to re-enter a selection, loop until input is valid
        while (SELECTION != "1" && SELECTION != "2" && SELECTION != "3" && SELECTION != "4" && SELECTION != "5" && SELECTION != "6" && SELECTION != "Q"){
            std::cout << "!!! THE ENTRY IS INVALID, PLEASE TRY AGAIN !!!" << endl;
            std::cout << endl;
            std::cout << "SELECT OPTION" << endl;
            std::cout << "1 - Add New MOUSE, Add New EXPERIMENT To Existing MOUSE, OR Add New PROJECT" << endl;
            std::cout << "2 - Add EXPERIMENT To PROJECT" << endl;
            std::cout << "3 - Remove EXPERIMENT From PROJECT" << endl;
            std::cout << "4 - Add EXPERIMENT To Existing MOUSE" << endl;
            std::cout << "5 - Print Projects" << endl;
            std::cout << "6 - Print Mice" << endl;
            std::cout << "Q - Quit" << endl;
            std::cout << endl;
            std::cin >> SELECTION;
            std::cout << endl;
        } 
    }
}