// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
//#include "../code_1/<HEADER FILE>.hpp"
#include "../code_1/SpiderMouse.cpp"
#include "../code_1/SpiderMouse.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_SpiderMouse : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
	}
	
};

//double test_x::total_grade = 0;
//double test_x::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////



std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
    

    
/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

// tests initMouseNode
TEST_F(test_SpiderMouse, TestinitMouseNode){
    SpiderMouse myobj;
    shared_ptr<spiderNode> mouse;
    mouse = myobj.initMouseNode(20230401, "V2000", 20230201, "M", true, "Opn4cre-GCaMP", "AAV intravitreal injections", "normal mouse", "good injections");
    
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230401, mouse->startDate);
    ASSERT_EQ("V2000", mouse->IDtag);
    ASSERT_EQ(20230201, mouse->DOB);
    ASSERT_EQ("M", mouse->gender);
    ASSERT_TRUE(mouse->alive);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("normal mouse", mouse->notes);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("-1", mouse->projTitle);
    
    int SIZE = mouse->projectExpList.size();
    ASSERT_EQ(0, SIZE);
    SIZE = mouse->mouseExpList.size();
    ASSERT_EQ(1, SIZE);
    SIZE = mouse->expProjList.size();
    ASSERT_EQ(0, SIZE);
    
    shared_ptr<spiderNode> exp;
    exp = mouse->mouseExpList[0];
    
    ASSERT_EQ(2, exp->nodeType);
    ASSERT_EQ(20230401, exp->startDate);
    ASSERT_EQ("V2000", exp->IDtag);
    ASSERT_EQ("AAV intravitreal injections", exp->expType);
    ASSERT_EQ("good injections", exp->notes);
    ASSERT_EQ(-1, exp->DOB);
    ASSERT_EQ("-1", exp->gender);
    ASSERT_EQ("-1", exp->genotype);
    ASSERT_TRUE(exp->alive);
    ASSERT_EQ("-1", exp->projTitle);
    
    SIZE  = exp->projectExpList.size();
    ASSERT_EQ(0, SIZE);
    SIZE = exp->mouseExpList.size();
    ASSERT_EQ(0, SIZE);
    SIZE = exp->expProjList.size();
    ASSERT_EQ(0, SIZE);
    
    vector<shared_ptr<spiderNode>> MOUSELIST = myobj.getMouseList();
    SIZE = MOUSELIST.size();
    ASSERT_EQ(1, SIZE);
    
    vector<shared_ptr<spiderNode>> PROJLIST = myobj.getProjectList();
    SIZE = PROJLIST.size();
    ASSERT_EQ(0, SIZE);
}

// tests initExpNode
TEST_F(test_SpiderMouse, TestinitExpNode){
    SpiderMouse myobj;
    shared_ptr<spiderNode> experiment;
    experiment = myobj.initExpNode(20230102, "V1999", "PC", "2 good cells", false);
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230102, experiment->startDate);
    ASSERT_EQ("V1999", experiment->IDtag);
    ASSERT_EQ("PC", experiment->expType);
    ASSERT_EQ("2 good cells", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
}

// tests initProjNode
TEST_F(test_SpiderMouse, TestinitProjNode){
    SpiderMouse myobj;
    shared_ptr<spiderNode> project;
    project = myobj.initProjNode(20230401, "Injury Physiology Manuscript", "Experiment phase");
    
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("Injury Physiology Manuscript", project->projTitle);
    ASSERT_EQ("Experiment phase", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    int SIZE  = project->projectExpList.size();
    ASSERT_EQ(0, SIZE);
    SIZE = project->mouseExpList.size();
    ASSERT_EQ(0, SIZE);
    SIZE = project->expProjList.size();
    ASSERT_EQ(0, SIZE);
    
    vector<shared_ptr<spiderNode>> PROJLIST = myobj.getProjectList();
    SIZE = PROJLIST.size();
    ASSERT_EQ(1, SIZE);
    
    vector<shared_ptr<spiderNode>> MOUSELIST = myobj.getMouseList();
    SIZE = MOUSELIST.size();
    ASSERT_EQ(0, SIZE);
}

// tests findMouseID
TEST_F(test_SpiderMouse, TestfindMouseID){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    shared_ptr<spiderNode> mouse;
    mouse = myobj.findMouseID("V2007");
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230408, mouse->startDate);
    ASSERT_EQ(20230208, mouse->DOB);
    ASSERT_EQ("F", mouse->gender);
    ASSERT_EQ("Oxtrcre-GCaMP", mouse->genotype);
    ASSERT_EQ("normal", mouse->notes);
    ASSERT_FALSE(mouse->alive);
    int Size = mouse->mouseExpList.size();
    ASSERT_EQ(7,Size);
}

// tests findMouseStartDate
TEST_F(test_SpiderMouse, TestfindMouseStartDate){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    vector<shared_ptr<spiderNode>> mouse;
    mouse = myobj.findMouseStartDate(20230408);
    int Size = mouse.size();
    ASSERT_EQ(1, Size);
    shared_ptr<spiderNode> curMouse = mouse[0];
    curMouse = myobj.findMouseID("V2007");
    ASSERT_EQ(1, curMouse->nodeType);
    ASSERT_EQ(20230408, curMouse->startDate);
    ASSERT_EQ(20230208, curMouse->DOB);
    ASSERT_EQ("F", curMouse->gender);
    ASSERT_EQ("Oxtrcre-GCaMP", curMouse->genotype);
    ASSERT_EQ("normal", curMouse->notes);
    ASSERT_FALSE(curMouse->alive);
    Size = curMouse->mouseExpList.size();
    ASSERT_EQ(7,Size);
}

// tests findExp
TEST_F(test_SpiderMouse, TestfindExp){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    shared_ptr<spiderNode> experiment;
    experiment = myobj.findExp(20230409, "V2007", "VEP");
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude", experiment->notes);
    ASSERT_EQ("V2007", experiment->IDtag);
    int Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
}

// tests findProj
TEST_F(test_SpiderMouse, TestfindProj){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    shared_ptr<spiderNode> project;
    project = myobj.findProj("Motion Paper");
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230410, project->startDate);
    ASSERT_EQ("Motion Paper", project->projTitle);
    ASSERT_EQ("manuscript to submit for peer-review", project->notes);
    int Size = project->projectExpList.size();
    ASSERT_EQ(2, Size);
}

// tests addExp2Proj and removeExpFromProj
TEST_F(test_SpiderMouse, Test_addExp2Proj_and_Test_removeExpFromProj){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    shared_ptr<spiderNode> project;
    project = myobj.findProj("Injury Paper");
    myobj.addExp2Proj(20230428, "V2007", "2p", "Injury Paper");
    int LENGTH = project->projectExpList.size();
    ASSERT_EQ(13, LENGTH);
    shared_ptr<spiderNode> experiment;
    experiment = project->projectExpList[12];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230428, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    int Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    
    myobj.removeExpFromProj(20230428, "V2007", "2p", "Injury Paper");
    LENGTH = project->projectExpList.size();
    ASSERT_EQ(12, LENGTH);
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
}

// tests addExp2Mouse
TEST_F(test_SpiderMouse, TestaddExp2Mouse){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    shared_ptr<spiderNode> mouse;
    myobj.addExp2Mouse(20230601, "PC", "V2007", "Not good, no cells", false);
    mouse = myobj.findMouseID("V2007");
    int Size = mouse->mouseExpList.size();
    ASSERT_EQ(8, Size);
    shared_ptr<spiderNode> experiment;
    experiment = mouse->mouseExpList[7];
    ASSERT_EQ(20230601, experiment->startDate);
    ASSERT_EQ("PC", experiment->expType);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("Not good, no cells", experiment->notes);
    ASSERT_FALSE(experiment->alive);
}

// tests getMouseList
TEST_F(test_SpiderMouse, TestgetMouseList){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    vector<shared_ptr<spiderNode>> mice;
    mice = myobj.getMouseList();
    int Size = mice.size();
    ASSERT_EQ(10, Size);
}

// tests getProjList
TEST_F(test_SpiderMouse, TestgetProjectList){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    vector<shared_ptr<spiderNode>> projects;
    projects = myobj.getProjectList();
    int Size = projects.size();
    ASSERT_EQ(3, Size);
}

// tests initProjNode2, initMouseNode2, addExp2Proj, addExp2Mouse and removeExpFromProj
TEST_F(test_SpiderMouse, TestBuildWeb){
    
    SpiderMouse myobj;
    myobj.BuildWeb();
    vector<shared_ptr<spiderNode>> MOUSE;
    MOUSE = myobj.getMouseList();
    int LENGTH = MOUSE.size();
    ASSERT_EQ(10, LENGTH);
    
    
    shared_ptr<spiderNode> mouse;
    mouse = MOUSE[0];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230401, mouse->startDate);
    ASSERT_EQ("V2000", mouse->IDtag);
    ASSERT_EQ(20230201, mouse->DOB);
    ASSERT_EQ("Wild-type", mouse->genotype);
    ASSERT_EQ("M", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    shared_ptr<spiderNode> experiment;
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230401, experiment->startDate);
    ASSERT_EQ("V2000", experiment->IDtag);
    ASSERT_EQ("AAV intravitreal injections", experiment->expType);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    ASSERT_EQ("good injections, reg glusnfr", experiment->notes);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230415, experiment->startDate);
    ASSERT_EQ("V2000", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 10 regions", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    shared_ptr<spiderNode> project;
    project = experiment->expProjList[0];
    int Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230410, project->startDate);
    ASSERT_EQ("Motion Paper", project->projTitle);
    ASSERT_EQ("manuscript to submit for peer-review", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    mouse = MOUSE[1];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230402, mouse->startDate);
    ASSERT_EQ("V2001", mouse->IDtag);
    ASSERT_EQ(20230202, mouse->DOB);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("F", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230402, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recordings", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230404, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("ONC", experiment->expType);
    ASSERT_EQ("Good left eye ONC", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230418, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, 14 dpi, left eye no signal", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230420, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good reponses, 7 regions ONC, 3 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[4];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230429, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, from 20230420, spinningdisc", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    mouse = MOUSE[2];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230403, mouse->startDate);
    ASSERT_EQ("V2002", mouse->IDtag);
    ASSERT_EQ(20230203, mouse->DOB);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("M", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230403, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("poor signal left eye", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230405, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("ONC", experiment->expType);
    ASSERT_EQ("Good left eye ONC, minor bleed", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230419, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, 14 dpi, left eye some signal", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    
    experiment = mouse->mouseExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230421, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 8 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[4];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230430, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, from 20230421, spiinningdisc", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    mouse = MOUSE[3];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230404, mouse->startDate);
    ASSERT_EQ("V2003", mouse->IDtag);
    ASSERT_EQ(20230204, mouse->DOB);
    ASSERT_EQ("Wild-type", mouse->genotype);
    ASSERT_EQ("F", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230404, experiment->startDate);
    ASSERT_EQ("V2003", experiment->IDtag);
    ASSERT_EQ("AAV intravitreal injections", experiment->expType);
    ASSERT_EQ("good injections, reg glusnfr, right eye bleeding", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230418, experiment->startDate);
    ASSERT_EQ("V2003", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 8 regions", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230410, project->startDate);
    ASSERT_EQ("Motion Paper", project->projTitle);
    ASSERT_EQ("manuscript to submit for peer-review", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    mouse = MOUSE[4];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230405, mouse->startDate);
    ASSERT_EQ("V2004", mouse->IDtag);
    ASSERT_EQ(20230205, mouse->DOB);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("M", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230405, experiment->startDate);
    ASSERT_EQ("V2004", experiment->IDtag);
    ASSERT_EQ("AAV intravitreal injections", experiment->expType);
    ASSERT_EQ("good injections, left eye, AAV TM", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230504, experiment->startDate);
    ASSERT_EQ("V2004", experiment->IDtag);
    ASSERT_EQ("ONC", experiment->expType);
    ASSERT_EQ("Good bilateral ONC", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230518, experiment->startDate);
    ASSERT_EQ("V2004", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 10 regions ONC, 5 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230526, experiment->startDate);
    ASSERT_EQ("V2004", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, staining started 20230505, slide scanner", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    mouse = MOUSE[5];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230406, mouse->startDate);
    ASSERT_EQ("V2005", mouse->IDtag);
    ASSERT_EQ(20230206, mouse->DOB);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("F", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230406, experiment->startDate);
    ASSERT_EQ("V2005", experiment->IDtag);
    ASSERT_EQ("AAV intravitreal injections", experiment->expType);
    ASSERT_EQ("good injections, left eye, AAV TM", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230505, experiment->startDate);
    ASSERT_EQ("V2005", experiment->IDtag);
    ASSERT_EQ("ONC", experiment->expType);
    ASSERT_EQ("Good left ONC, right moderate bleed", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230519, experiment->startDate);
    ASSERT_EQ("V2005", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 12 regions ONC, 3 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230527, experiment->startDate);
    ASSERT_EQ("V2005", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, staining started 20230505, slide scanner", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    
    mouse = MOUSE[6];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230407, mouse->startDate);
    ASSERT_EQ("V2006", mouse->IDtag);
    ASSERT_EQ(20230207, mouse->DOB);
    ASSERT_EQ("Oxtrcre-GCaMP", mouse->genotype);
    ASSERT_EQ("M", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230407, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recodings, not great", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, right side noisy", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230411, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("ONC", experiment->expType);
    ASSERT_EQ("Good left eye ONC", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230423, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, left eye, 13 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[4];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230425, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, right eye noisy, 15 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[5];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230427, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 9 ONC regions, 10 control regions, 17 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[6];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230504, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("GFP, rbpms, iba1, staining started 20230427, spinning disc", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(1, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    mouse = MOUSE[7];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230408, mouse->startDate);
    ASSERT_EQ("V2007", mouse->IDtag);
    ASSERT_EQ(20230208, mouse->DOB);
    ASSERT_EQ("Oxtrcre-GCaMP", mouse->genotype);
    ASSERT_EQ("F", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230408, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recodings, huge amplitude", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230412, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("ONC", experiment->expType);
    ASSERT_EQ("Good left eye ONC, minor bleed after", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = mouse->mouseExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230423, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude, 12 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[4];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230425, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude, 14 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(2, Size);
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    project = experiment->expProjList[1];
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230530, project->startDate);
    ASSERT_EQ("Injury Paper", project->projTitle);
    ASSERT_EQ("TBI paper (collaboration)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[5];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230428, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, some rundown, 5 ONC regions, 5 control regions, 17 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    experiment = mouse->mouseExpList[6];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230510, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("GFP, rbpms, iba1, staining started 20230428, slide scanner", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
     
    mouse = MOUSE[8];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230409, mouse->startDate);
    ASSERT_EQ("V2008", mouse->IDtag);
    ASSERT_EQ(20230209, mouse->DOB);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("M", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("left eye microphthalmia", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2008", experiment->IDtag);
    ASSERT_EQ("PC", experiment->expType);
    ASSERT_EQ("3 good cells", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    
    mouse = MOUSE[9];
    ASSERT_EQ(1, mouse->nodeType);
    ASSERT_EQ(20230410, mouse->startDate);
    ASSERT_EQ("V2009", mouse->IDtag);
    ASSERT_EQ(20230210, mouse->DOB);
    ASSERT_EQ("Opn4cre-GCaMP", mouse->genotype);
    ASSERT_EQ("F", mouse->gender);
    ASSERT_FALSE(mouse->alive);
    ASSERT_EQ("-1", mouse->expType);
    ASSERT_EQ("normal", mouse->notes);
    
    experiment = mouse->mouseExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230410, experiment->startDate);
    ASSERT_EQ("V2009", experiment->IDtag);
    ASSERT_EQ("PC", experiment->expType);
    ASSERT_EQ("1 good cell, 1 reconstructed, no recordings", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    project = experiment->expProjList[0];
    Size = experiment->expProjList.size();
    ASSERT_EQ(3, project->nodeType);
    ASSERT_EQ(20230401, project->startDate);
    ASSERT_EQ("R01 Injury Physiology", project->projTitle);
    ASSERT_EQ("preliminary data for new R01 submission (December)", project->notes);
    ASSERT_EQ("-1", project->IDtag);
    ASSERT_EQ(-1, project->DOB);
    ASSERT_EQ("-1", project->genotype);
    ASSERT_EQ("-1", project->gender);
    ASSERT_TRUE(project->alive);
    ASSERT_EQ("-1", project->expType);
    
    
    
    vector<shared_ptr<spiderNode>> PROJECT;
    PROJECT = myobj.getProjectList();
    LENGTH = PROJECT.size();
    ASSERT_EQ(3, LENGTH);
    
    project = PROJECT[0];
    string TITLE = project->projTitle;
    ASSERT_EQ("R01 Injury Physiology", TITLE);
    LENGTH = project->projectExpList.size();
    ASSERT_EQ(26, LENGTH);
    
    experiment = project->projectExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230402, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recordings", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230403, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("poor signal left eye", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230407, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recodings, not great", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230408, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recodings, huge amplitude", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[4];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2008", experiment->IDtag);
    ASSERT_EQ("PC", experiment->expType);
    ASSERT_EQ("3 good cells", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[5];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, right side noisy", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[6];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[7];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230410, experiment->startDate);
    ASSERT_EQ("V2009", experiment->IDtag);
    ASSERT_EQ("PC", experiment->expType);
    ASSERT_EQ("1 good cell, 1 reconstructed, no recordings", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[8];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230418, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, 14 dpi, left eye no signal", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[9];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230419, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, 14 dpi, left eye some signal", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[10];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230420, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good reponses, 7 regions ONC, 3 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[11];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230421, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 8 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[12];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230423, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, left eye, 13 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[13];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230423, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude, 12 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[14];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230425, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, right eye noisy, 15 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[15];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230425, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude, 14 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[16];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230427, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 9 ONC regions, 10 control regions, 17 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[17];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230428, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, some rundown, 5 ONC regions, 5 control regions, 17 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[18];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230429, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, from 20230420, spinningdisc", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[19];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230430, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, from 20230421, spiinningdisc", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[20];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230504, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("GFP, rbpms, iba1, staining started 20230427, spinning disc", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[21];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230510, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("GFP, rbpms, iba1, staining started 20230428, slide scanner", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[22];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230518, experiment->startDate);
    ASSERT_EQ("V2004", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 10 regions ONC, 5 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[23];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230519, experiment->startDate);
    ASSERT_EQ("V2005", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 12 regions ONC, 3 regions control", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[24];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230526, experiment->startDate);
    ASSERT_EQ("V2004", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, staining started 20230505, slide scanner", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[25];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230527, experiment->startDate);
    ASSERT_EQ("V2005", experiment->IDtag);
    ASSERT_EQ("Histology", experiment->expType);
    ASSERT_EQ("gfp, rbpms, staining started 20230505, slide scanner", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    
    
    
    project = PROJECT[1];
    TITLE = project->projTitle;
    ASSERT_EQ("Motion Paper", TITLE);
    LENGTH = project->projectExpList.size();
    ASSERT_EQ(2, LENGTH);
    string NOTES = project->notes;
    ASSERT_EQ("manuscript to submit for peer-review", NOTES);
    
    experiment = project->projectExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230415, experiment->startDate);
    ASSERT_EQ("V2000", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 10 regions", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230418, experiment->startDate);
    ASSERT_EQ("V2003", experiment->IDtag);
    ASSERT_EQ("2p", experiment->expType);
    ASSERT_EQ("Good responses, 8 regions", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_FALSE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    
    project = PROJECT[2];
    TITLE = project->projTitle;
    LENGTH = project->projectExpList.size();
    ASSERT_EQ(12, LENGTH);
    NOTES = project->notes;
    ASSERT_EQ("TBI paper (collaboration)", NOTES);
    
    experiment = project->projectExpList[0];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230402, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recordings", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[1];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230403, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("poor signal left eye", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[2];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230407, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recodings, not great", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[3];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230408, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("good recodings, huge amplitude", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[4];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, right side noisy", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[5];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230409, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[6];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230418, experiment->startDate);
    ASSERT_EQ("V2001", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, 14 dpi, left eye no signal", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[7];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230419, experiment->startDate);
    ASSERT_EQ("V2002", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, 14 dpi, left eye some signal", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[8];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230423, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, left eye, 13 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[9];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230423, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("pERG", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude, 12 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[10];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230425, experiment->startDate);
    ASSERT_EQ("V2006", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, right eye noisy, 15 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    experiment = project->projectExpList[11];
    ASSERT_EQ(2, experiment->nodeType);
    ASSERT_EQ(20230425, experiment->startDate);
    ASSERT_EQ("V2007", experiment->IDtag);
    ASSERT_EQ("VEP", experiment->expType);
    ASSERT_EQ("Good recordings, huge amplitude, 14 dpi", experiment->notes);
    ASSERT_EQ(-1, experiment->DOB);
    ASSERT_EQ("-1", experiment->gender);
    ASSERT_EQ("-1", experiment->genotype);
    ASSERT_TRUE(experiment->alive);
    ASSERT_EQ("-1", experiment->projTitle);
    
    
    myobj.addExp2Proj(20230428, "V2007", "2p", "Injury Paper");
    LENGTH = project->projectExpList.size();
    ASSERT_EQ(13, LENGTH);
    myobj.removeExpFromProj(20230428, "V2007", "2p", "Injury Paper");
    LENGTH = project->projectExpList.size();
    ASSERT_EQ(12, LENGTH);
    
    
    
    
}
    
    
    
    

