 #include <smile.h>
#include <smilearn.h>
#include <error.h>

#include "create_bn.h" 
#include "infer_bn.h"
#include "create_influence_bn.h" 
#include "infer_influence_bn.h"
#include "create_Kicker.h"
#include "testSpace.h"

#include <iostream>
#include <string>

//using namespace std;
 
  void CreateNetwork(void);
  void InfereceWithBayesNet(void);
  //void UpgradeToInfluenceDiagram(void);
  //void InferenceWithInfluenceDiagram(void);
  //void ComputeValueOfInformation(void);
  void CreateKickerBN(void);
  void testSpace(void);
  void testNetwork(void);
  void BuildDBN();
  void InferDBN();
  void NaiveBayes();
  void staticEM();
  
  int main()
  {  

    //testSpace();
    //testNetwork();
    //BuildDBN();
    InferDBN();
    //NaiveBayes();
    //staticEM();

     //CreateNetwork();
     //InfereceWithBayesNet();
     //CreateKickerBN();
     //UpgradeToInfluenceDiagram();
     //InferenceWithInfluenceDiagram();
     //ComputeValueOfInformation();  
     return(DSL_OKAY);
  };
