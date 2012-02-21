extern "C" {
    #include "StructureReader.h"
    #include "RNAScoring.h"
    #include "TreeScoring.h"    
}
//#include <ctype.h>
//#include <limits.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "loader.h"
//#include "data.h"
//#include "constants.h"
#include <cstdlib>
#include <iostream>
#include "LoopScoring.h"
#include "options.h"
#include <math.h>
#include<string.h>

using namespace std;
void PFtest();
double getScore(string seqfilepath, int mode);
string summary_file_path;
string output_file_path;
string error_file_path;
bool is_dS=true;

int PFtest(int argc, char* argv[])
{
    if (argc < 5)
    {
		fprintf(stderr, "USAGE: RNAScore --pf_test <summary_file_path> <output_file_path> <error_file_path> [-dS|-d2]\n");
		exit(-1);
		//help();
		//return 1;
    }
    
    summary_file_path = argv[2];
    output_file_path = argv[3];
    error_file_path = argv[4];
if(argc==6) {string dangle = argv[5];
	if(dangle.compare("-d2")==0) is_dS=false;
}
    PFtest();
    return 0;
}
double getScore(string seqfilepath, int pfmode, int nodanglemode, int d2mode, int defaultmode){
	PFMODE = pfmode;
	NODANGLEMODE = nodanglemode;
	D2MODE=d2mode;
	DEFAULTMODE=defaultmode;

	char seqfileTmp[1000];strcpy(seqfileTmp, seqfilepath.c_str());
    strcpy(seqfile,seqfileTmp);
	printf("Inside getScore() function: seqfile=%s\n",seqfile);
	char bases[16] = {0, 'A', 'C', 'M', 'G', 'R', 'S', 'V', 'U',
                      'W', 'Y', 'H', 'K', 'D', 'B', 'N'};
    ResultBundle* resultBundle = CreateFromFile(seqfile);
    int length = resultBundle->length;
    TreeNode* tree = resultBundle->treenode;
    int* RNA = resultBundle->RNA_seq;

         nndb_constants* param = populate("data/Turner99", 1);

        int one; int two; int three; int four; int score;

        int tree_score = ScoreNode(tree, resultBundle->RNA_seq, param, length);
	return (double)tree_score/100;
}
void PFtest(){
	string summaryfile = summary_file_path;//"/home/users/msoni/Desktop/manoj_gatech/research/gtfold/git_code/gtfold/gtfold-mfe/src/stochaSampleSummery.txt";
	ifstream summaryinfile;
        summaryinfile.open(summaryfile.c_str());
        
	string outfilepath = output_file_path;//"/home/users/msoni/Desktop/manoj_gatech/research/gtfold/scoring_code_shel/shelswenson-gtfold-cdc688c/rna-scoring/scoreSummary.txt";
	ofstream outfile;
	outfile.open(outfilepath.c_str());

	ofstream errfile;
        errfile.open(error_file_path.c_str());

	string seqfilepath, ensemble;
	double pfEnergy;
	while(summaryinfile>>seqfilepath>>ensemble>>pfEnergy){
		cout<<seqfilepath<<" "<<ensemble<<" "<<pfEnergy<<" "<<endl;
                double dSModeScore = getScore(seqfilepath, 1,0,0,0);
                double noDangleModeScore = getScore(seqfilepath, 0,1,0,0);
                double d2ModeScore = getScore(seqfilepath, 0,0,1,0);
		double defaultModeScore = getScore(seqfilepath, 0,0,0,1);//cout<<"manoj="<<defaultModeScore<<"\n";
	
		outfile<<seqfilepath<<" "<<ensemble<<" "<<pfEnergy<<" "<<defaultModeScore<<" "<<dSModeScore<<" "<<noDangleModeScore<<" "<<d2ModeScore<<endl;
		if(is_dS){
if(pfEnergy!=dSModeScore) errfile<<seqfilepath<<" "<<ensemble<<" "<<pfEnergy<<" "<<defaultModeScore<<" "<<dSModeScore<<" "<<noDangleModeScore<<" "<<d2ModeScore<<endl;
}
else{
		if(pfEnergy!=dSModeScore) errfile<<seqfilepath<<" "<<ensemble<<" "<<pfEnergy<<" "<<defaultModeScore<<" "<<dSModeScore<<" "<<noDangleModeScore<<" "<<d2ModeScore<<endl;
}
	}
	summaryinfile.close();	
	outfile.close();
	errfile.close();
}
