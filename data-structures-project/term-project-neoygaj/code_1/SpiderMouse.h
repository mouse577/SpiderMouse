#ifndef SPIDERMOUSE_H__
#define SPIDERMOUSE_H__

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include <array>

//#define MOUSE_NODE 1
//#define EXPERIMENT_NODE 2
//#define PROJECT_NODE 3

using namespace std;

struct spiderNode {
    int nodeType;  // "1-mouse", "2-experiment", "3-project"
    int startDate; // FOR ALL TYPES: YYYYMMDD
    string IDtag; // FOR TYPES: mouse and experiment: V2093
    int DOB; // FOR TYPES: mouse: YYYYMMDD
    string genotype; //FOR TYPE: mouse: "Opn4cre/gcamp", "Oxtrcre/gcamp", "WT", "ChatCre"
    string gender; // FOR TYPE: mouse: "M" or "F"
    bool alive; // FOR TYPE: mouse
    string expType; // FOR TYPE: mouse and experiment: "AAVinj", "pERG", "VEP", "ONC", "TBI", "2p-gcamp", "2p-glusnfr", "PC", "Histology" 
    string notes; // FOR ALL TYPES
    string projTitle; //  FOR TYPE: project
    vector<shared_ptr<spiderNode>> projectExpList; // FOR TYPE: project
    vector<shared_ptr<spiderNode>> mouseExpList; // FOR TYPE: mouse
    vector<shared_ptr<spiderNode>> expProjList; // FOR TYPE: experiment
};

class SpiderMouse {
    
public:
    
    // SpiderMouse class constructor
    SpiderMouse();
    
    // SpiderMouse class destructor
    ~SpiderMouse();
    
    // Prints options for selections for user input to create and initialize a new node interactively (mouse, experiment or project), and adds a pointer to the node to the corresponding vector of pointers (mouse-1 addes to mouseList, experiment-2 adds to mouseExpList for corresponding mouse with IDtag parameter, project-3 adds to ProjList), includes errors and prompt for re-entry for invalid entries, and option for user to quit by entering "Q". 
    void initNode();
    
    // Creates and initializes a new mouse node (nodeType 1), add an experiments to the mouseExpList, add a pointer to the node to private member mouseList and returns a pointer to the node
    shared_ptr<spiderNode> initMouseNode(int start_date, string id, int dob, string gend, bool Alive, string Geno, string exp_type, string mouseNotes, string expNotes);
    
    // Same as initMouseNode, except void, for use in BuildWeb() member function
    void initMouseNode2(int start_date, string id, int dob, string gend, bool Alive, string Geno, string exp_type, string mouseNotes, string expNotes);
    
    // Creates and initializes a new experiment node (nodeType 2) and returns a ponter to the node
    shared_ptr<spiderNode> initExpNode(int start_date, string id, string exp_type, string Notes, bool Alive);
    
    // Creates and initializes a new project node (nodeType 3) and returns a pointer to the node
    shared_ptr<spiderNode> initProjNode(int start_date, string proj_title, string Notes);
    
    // Same as initProjNode(), except void, for use in BuildWeb() member function
    void initProjNode2(int start_date, string proj_title, string Notes);
    
    // Finds a mouse node with IDtag matching the input paramter, by searching mouseList until the mouse is found and a pointer to the mouse node is returned, or nullptr if mouse is not found
    shared_ptr<spiderNode> findMouseID(string id_tag);
    
    // Finds a mouse node with startDate matching the input parameter, in a vector of pointers, in case more than one mouse was started on the same date
    vector<shared_ptr<spiderNode>> findMouseStartDate(int start_date);
    
    // Finds an experiment node with startDate, IDtag and expType matching the input parameters, and returns a pointer to the experiment node, or nullprt if the experiment is not found
    shared_ptr<spiderNode> findExp(int start_date, string id, string exp_type);
    
    // Finds a project node with projTitle that matches the input parameter, and returns a pointer to the project node, which is null if a matching project node is not found
    shared_ptr<spiderNode> findProj(string proj_title);
    
    // Adds an existing experiment to an existing project by calling the findExp function, calling the findProj function, adding a pointer to the experiment node to projectExpList vector of the project node, and also adds the project node to expProjList vector of the experiment node
    void addExp2Proj(int Exp_start, string id, string exp_type, string proj_title);
    
    // Removes an experiment from a project by calling the findProj function, finding and removing the experiment in projectExperimentList and also removing the project from expProjList for the experiment
    void removeExpFromProj(int Exp_start, string id, string exp_type, string proj_title);
    
    // Creates and adds a new experiment node by calling the initExpNode member function, finds an existing mouse by calling the findMouseID member function, adds the experiment to mouseExpList for the mouse and updates mouse->alive if needed based on the input parameter
    void addExp2Mouse(int Exp_start, string exp_type, string id, string Notes, bool Alive);
    
    // Copies and returns all mice in mouseList
    vector<shared_ptr<spiderNode>> getMouseList();
    
    // Copies and returns projList
    vector<shared_ptr<spiderNode>> getProjectList();
    
    // Prints out all projects, asks user to input selection for a project and then prints out details for all experiments in ProjectExpList for selected project, loops until "Q" selection is entered by user, and includes error statement and prompt for re-entry for invalid entry
    void printAllProjects();
    
    // Prints out all mice, asks user to input selection to see all experiment details for a particular mouse and then prints out details for all experiments in mouseExpList for selected mouse, loops until "Q" selection is entered by user, and includes error statement and prompt for re-entry for invalid entry
    void printAllMice();
    
    // Builds a SpiderMouse structure for testing
    void BuildWeb();
    
    // Interactively prints out options and reads inputs from user to add new nodes, add existing experiment to existing project, remove experiment from project, add new experiment to exisiting mouse, print all projects, print all mice, and loop until "Q" selection is entered to quit.  This function calls other member functions
    void master();


private:
    
    // Holds pointers for all mouse nodes
    vector<shared_ptr<spiderNode>> mouseList;
    
    // Holds pointers for all project nodes
    vector<shared_ptr<spiderNode>> projList;
};

#endif  // SPIDERMOUSE_H__
    