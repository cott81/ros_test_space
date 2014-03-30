/*
 * testSpace.h
 *
 * Copyright 2012 Carpe Noctem, Distributed Systems Group,
 * University of Kassel. All right reserved.
 *
 * The code is derived from the software contributed to Carpe Noctem by
 * the Carpe Noctem Team.
 *
 * The code is licensed under the Carpe Noctem Userfriendly BSD-Based
 * License (CNUBBL). Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided that the
 * conditions of the CNUBBL are met.
 *
 * You should have received a copy of the CNUBBL along with this
 * software. The license is also available on our website:
 * http://carpenoctem.das-lab.net/license.txt
 *  Created on: Oct 26, 2012		1:12:55 PM
 *      Author: Dominik Kirchner
 */

#ifndef TESTSPACE_H_
#define TESTSPACE_H_

using namespace std;

void testSpace(void) {
    std::cout << "test" << std::endl;

    /*
    DSL_doubleArray dArray;
    dArray.Add(1.0);
    dArray.Add(2.0);
    double var1 = dArray[3];
    int len = dArray.GetSize();
    std::cout << "test out:" << var1 << std::endl;
    std::cout << "test out len:" << len << std::endl;
    */

    /*
    DSL_idArray idArray;
    idArray.Add("das");
    idArray.Add("haus");
    idArray.Add("garten");
    idArray.Add("kind");
    char* var1 = idArray[10];
    int len = idArray.GetSize();suspious
    for (int i = 0; i< idArray.GetSize(); i++){
      std::cout << "test out: "<< i << " val: " << idArray[i] << std::endl;
    }
    */
}

void BuildDBN(){
  /*
  DSL_network theNet;
  theNet.ReadFile("test.xdsl");
  int success= theNet.FindNode("Success");
  theNet.SetTemporalType( success, dsl_plateNode);

  theNet.SetTemporalType(success, dsl_plateNode);
  theNet.AddTemporalArc(success, success, 1);
  theProbs.SetSize(4);
  theProbs[0] = 0.9;
  theProbs[1] = 0.1;
  theProbs[2] = 0.4;
  theProbs[3] = 0.6;
  */

  //perhaps from file
  DSL_network myNet;
  myNet.SetNumberOfSlices(100);
  int node1 = myNet.AddNode(DSL_CPT, "Node1"); //cause
  cout << "handle node1: " << node1 << endl;
  myNet.GetNode(node1)->SetId("Id_Node1");



  int tType = 99;
  tType = myNet.GetTemporalType(node1);
  cout << "temporal type : " << tType << endl;

  myNet.SetTemporalType(node1, dsl_plateNode);
  tType = myNet.GetTemporalType(node1);
  cout << "temporal type : " << tType << endl;

  int test = myNet.FindNode("Id_Node1");
  cout << "node1 handle " << test << endl;

  DSL_idArray outNames;
  outNames.Add("das");
  outNames.Add("jenes");
  myNet.GetNode(node1)->Definition()->SetNumberOfOutcomes(outNames);

  int node2 = myNet.AddNode(DSL_CPT, "Node2"); //observatoin
  cout << "handle node2: " << node2 << endl;
  myNet.SetTemporalType(node2, dsl_plateNode);

  int nodeInit = myNet.AddNode(DSL_CPT, "Node_Init"); //cause
  cout << "handle node1: " << nodeInit << endl;
  myNet.SetTemporalType(nodeInit, dsl_anchorNode);

  int nodeTerm = myNet.AddNode(DSL_CPT, "Node_Term"); //cause
  cout << "handle node1: " << nodeTerm << endl;
  myNet.SetTemporalType(nodeTerm, dsl_terminalNode);

  //DSL_idArray outNames;
  outNames.Flush();
  outNames.Add("das2");
  outNames.Add("jenes2");

  myNet.AddArc(node1, node2);
  myNet.AddArc(nodeInit, node1);
  myNet.AddArc(node1, nodeTerm);
  myNet.AddTemporalArc(node1, node1, 1);

  //temp cpt definition
  DSL_doubleArray probs;
  probs.Add(0.2);
  probs.Add(0.8);
  probs.Add(0.6);
  probs.Add(0.4);
  myNet.GetNode(node1)->Definition()->SetDefinition(probs);

  DSL_doubleArray tProbs;
  tProbs.Add(0.2);
  tProbs.Add(0.8);
  tProbs.Add(0.1);
  tProbs.Add(0.9);
  myNet.GetNode(node1)->Definition()->SetTemporalDefinition(1, tProbs);

  myNet.WriteFile("myDBN.xdsl");
}

void InferDBN(){

  DSL_network myNet;
  myNet.ReadFile("Tutorial17.xdsl");
  /*
  DSL_intArray handles;
  for (int i = 0; i<theNet.GetNumberOfNodes(); i++){
    cout << "node: " << theNet.GetNode(handles[i])->GetId() << endl;
  }
  */
  if (myNet.UpdateBeliefs() != DSL_OKAY) {
    cout << "error in UpdateBelief()" << endl;
  }

  //ifno id is set ... Id_"name"
  int node1 = myNet.FindNode("A");
  cout << "node handle Node1: " << node1 << endl;

  myNet.UpdateBeliefs();



  DSL_Dmatrix* matrix;
  matrix = myNet.GetNode(node1)->Value()->GetMatrix();
  cout << "last dim: " << matrix->GetLastDimension() << endl;
  cout << "dims: " << matrix->GetNumberOfDimensions() << endl;
  cout << "size: " << matrix->GetSize() << endl;
  //t=0
  cout << "dims: " << (*matrix)[0] << endl;
  cout << "dims: " << (*matrix)[1] << endl;
  //t=1
  cout << "dims: " << (*matrix)[2] << endl;
  cout << "dims: " << (*matrix)[3] << endl;
  //t= ...
  cout << "dims: " << (*matrix)[4] << endl;
  cout << "dims: " << (*matrix)[5] << endl;

  cout << "dims: " << (*matrix)[6] << endl;
  cout << "dims: " << (*matrix)[7] << endl;

  // t=3 out=2 -> ((t-1) * totalOutNum + (out-1) ... zählung ab null
  for (int i= 0; i<matrix->GetSize(); i++){
    cout << "dims: " << (*matrix)[i] << endl;
  }



  //how to set the evidence ... everything starts with 0!
  myNet.GetNode(node1)->Value()->SetTemporalEvidence(2, 1);
  myNet.UpdateBeliefs();
  for (int i= 0; i<matrix->GetSize(); i++){
    cout << "value with evidence: " << (*matrix)[i] << endl;
  }

  return;

}

void BuildLearnNet() {

  //biuld sample net ...
}


void PrintDataset(const DSL_dataset &d)
{
  int v,r;
  cout << " ===================" << endl;
  cout << " -- variable info --" << endl;
  cout << "number of variables = " << d.GetNumberOfVariables() << endl;
  for (v=0;v<d.GetNumberOfVariables();v++)
  {
  DSL_datasetVarInfo vi;
  vi = d.GetVariableInfo(v);
  cout << " Variable " << v << endl;
  cout << "\tid: " << vi.id << endl;
  cout << "\t";
  if (vi.discrete)
  cout << "is discrete";
  else
  cout << "is continuous";
  cout << endl;
  cout << "\tMissing element value: ";
  if (vi.discrete)
  {
  cout << vi.missingInt << endl;
  cout << "\tState names: ";
  for (unsigned s=0;s<vi.stateNames.size();s++)
  cout << vi.stateNames[s] << " ";
  cout << endl;
  }
  else
  cout << vi.missingFloat << endl;
  }

  cout << " -- data records --" << endl;
  cout << "number of records = " << d.GetNumberOfRecords() << endl;
  for (r=0;r<d.GetNumberOfRecords();r++)
  {
  for (v=0;v<d.GetNumberOfVariables();v++)
  {
  if (d.IsMissing(v,r))
  cout << "*";
  else
  {
  if (d.IsDiscrete(v))
  cout << d.GetInt(v,r);
  else
  cout << d.GetFloat(v,r);
  }
  cout << "\t" ;
  }
  cout << endl;
  }
  cout << endl;
}

void NaiveBayes() {
  DSL_dataset d;
  if(d.ReadFile("naive_simple.txt") != DSL_OKAY) {
        cout << "Cannot read data file... exiting." << endl;
        exit(1);
  }
  DSL_network result;
  DSL_naiveBayes naive;
  naive.classVariableId = "c"; //???
  if (naive.Learn(d,result)!=DSL_OKAY)
  {
        cout << "Learning failed." << endl;
        return;
  }
  PrintDataset(d);

  int nodeCHandle = result.FindNode("c");
  DSL_Dmatrix* values;
  values = result.GetNode(nodeCHandle)->Value()->GetMatrix();
  values = result.GetNode(nodeCHandle)->Definition()->GetMatrix();
  for (int i= 0; i<values->GetSize(); i++) {
    cout << "value " << i << " : " << (*values)[i] << endl;
  }
  result.WriteFile("naivebayes.xdsl");


}

void staticEM() {
   // open the data set:
   DSL_dataset ds;
   if (ds.ReadFile("ds_tut_5.txt") != DSL_OKAY) {
      cout << "Cannot read data file... exiting." << endl;
      exit(1);
   }

   // open the network:
   DSL_network net;
   if (net.ReadFile("net_tut_5.xdsl", DSL_XDSL_FORMAT) != DSL_OKAY) {
      cout << "Cannot read network... exiting." << endl;
      exit(1);
   }

   //check if something is in the net
   DSL_intArray nodeHandles;
   int result = net.GetAllNodes(nodeHandles);

   for (int i = 0; i < net.GetNumberOfNodes(); i++) {
     cout << "integrate node: " << net.GetNode(nodeHandles[i])->GetId() << endl;
   }


   // match the data set and the network:
   vector<DSL_datasetMatch> matches;
   string err;
   if (ds.MatchNetwork(net, matches, err) != DSL_OKAY) {
      cout << "Cannot match network... exiting." << endl;
      //exit(1);
      cout << "continue anyway" << endl;
   }

   // learn parameters:
   DSL_em em;
   if (em.Learn(ds, net, matches) != DSL_OKAY) {
      cout << "Cannot learn parameters... exiting." << endl;
      exit(1);
   }
   net.WriteFile("res_tut_5.xdsl", DSL_XDSL_FORMAT);
}


void IntegrateSubModel(DSL_network* originalNet, DSL_network* subModelNet ){

  //Integrates a subnet in a given original net ... no connection yet declared
  cout<< "Integration started" << endl;

  //create nodes in original net
  DSL_intArray nodeHandles;
  int result = subModelNet->GetAllNodes(nodeHandles);

  for (int i = 0; i < subModelNet->GetNumberOfNodes(); i++) {
    cout << "integrate node: " << subModelNet->GetNode(nodeHandles[i])->GetId() << endl;

    //create new node with the old id ... Type can be infered frim Definition.GetType()
    //TODO: get type ...
    int node3 =  originalNet->AddNode(DSL_CPT, subModelNet->GetNode(nodeHandles[i])->GetId()); //store node handle?

    //get outcomes from subModel
    DSL_idArray *outNames3 = subModelNet->GetNode(nodeHandles[i])->Definition()->GetOutcomesNames();

    //write outcomes to created node in the original network
    originalNet->GetNode(node3)->Definition()->SetNumberOfOutcomes(*outNames3);
  }

  //arc creation loop
  for (int i = 0; i < subModelNet->GetNumberOfNodes(); i++) {

    //identfy node in original Net
    int currentNode = originalNet->FindNode(subModelNet->GetNode(nodeHandles[i])->GetId());

    DSL_intArray parents = subModelNet->GetParents(nodeHandles[i]);

    for (int ii = 0; ii < parents.NumItems(); ii++){

      //identify the parent node in the original Net
      int parentNode = originalNet->FindNode(subModelNet->GetNode(parents[ii])->GetId());

      cout << "\t add arc between: parent node " << subModelNet->GetNode(parents[ii])->GetId() <<
          ";\t child :" << subModelNet->GetNode(nodeHandles[i])->GetId() << endl;
      originalNet->AddArc(parentNode, currentNode); //found parents to current node
    }

  }

  //set cpt for the nodes (needs already established connections)
  for(int i = 0; i < subModelNet->GetNumberOfNodes(); i++) {

    //get the prob table
    DSL_doubleArray *p;
    subModelNet->GetNode(nodeHandles[i])->Definition()->GetDefinition(&p);
    cout << "num prob elements: " << p->NumItems() << endl;
    for (int count = 0; count < p->NumItems(); count++) {
      cout << "probs from sub net node: " << (*p)[count] << endl;
    }

    //identfy node in original Net and set definition (cpt)
    int currentNode = originalNet->FindNode(subModelNet->GetNode(nodeHandles[i])->GetId());
    originalNet->GetNode(currentNode)->Definition()->SetDefinition(*p);
  }

  cout<< "Integration finished" << endl;
  return;
}

void testNetwork(void) {
  std::cout << "test network" << std::endl;

  //perhaps from file
  DSL_network myNet;
  int node1 = myNet.AddNode(DSL_CPT, "Node1"); //cause
  cout << "handle node1: " << node1 << endl;
  myNet.GetNode(node1)->SetId("Id_Node1");

  int tType = 99;
  tType = myNet.GetTemporalType(node1);
  cout << "temporal type : " << tType << endl;

  myNet.SetTemporalType(node1, dsl_plateNode);

  tType = myNet.GetTemporalType(node1);
  cout << "temporal type : " << tType << endl;

  DSL_idArray outNames;
  outNames.Add("das");
  outNames.Add("jenes");
  myNet.GetNode(node1)->Definition()->SetNumberOfOutcomes(outNames);

  int node2 = myNet.AddNode(DSL_CPT, "Node2"); //observatoin
  cout << "handle node2: " << node2 << endl;

  //DSL_idArray outNames;
  outNames.Flush();
  outNames.Add("das2");
  outNames.Add("jenes2");
  /*
  myNet.GetNode(node2)->Definition()->SetNumberOfOutcomes(outNames);
  DSL_idArray* a = myNet.GetNode(node2)->Definition()->GetOutcomesNames();
  char* b = (*a)[0];
  for (int c = 0; c < a->NumItems(); c++) {
    cout << "test id array access: " << (*a)[c] << endl;
  }
  */


  //TODO: try to read file with part of the net and add it to the complete model
  DSL_network subpartNet;
  //subpartNet.ReadFile("SingleNode3.xdsl"); // test ... one single node
  subpartNet.ReadFile("MultiNodes.xdsl"); // test ... parse complete network

  //testSpace();
  IntegrateSubModel(&myNet, &subpartNet);

  //get that node and bring it to the other model
  //DSL_intArray nodeHandles;
  int node3Handle = subpartNet.FindNode("Node3");
  //subpartNet.GetNode(node3Handle)->SetNetwork(&myNet);

  /*
  //create new node with the old id ... Type can be infered frim Definition.GetType()
  int node3 =  myNet.AddNode(DSL_CPT, subpartNet.GetNode(node3Handle)->GetId());

  DSL_idArray *outNames3 = subpartNet.GetNode(node3Handle)->Definition()->GetOutcomesNames();
  myNet.GetNode(node3)->Definition()->SetNumberOfOutcomes(*outNames3);

  //probs
  DSL_doubleArray *p;
  subpartNet.GetNode(node3Handle)->Definition()->GetDefinition(&p);
  cout << "num elements: " << p->NumItems() << endl;
  for (int count = 0; count < p->NumItems(); count++) {
    cout << "probs from sub net node: " << (*p)[count] << endl;
  }

  myNet.GetNode(node3)->Definition()->SetDefinition(*p);

*/
  /*
  //check if the values are in the node
  DSL_doubleArray *pp;
  myNet.GetNode(node3)->Definition()->GetDefinition(&pp);
  cout << "num elements: " << pp->GetSize() << endl;
  //pp->UseAsList();
  cout << "num elements: " << pp->NumItems() << endl; // needs us as list before the correct size culd be asked!
  for (int count2 = 0; count2 < pp->GetSize(); count2++) {
    cout << "probs from sub net node: " << (*pp)[count2] << endl;
  }
  */

  //int node333 = myNet.FindNode("Node3");
  //cout << "found " << node3 << endl;


  // get Type of Node ... PROBLEM! woher das bekommen
  // get Definition Outcommes ... check
  // get Definition Probabilities ... check
  //myNet.AddNode()

  //int node3 = myNet.AddNode(DSL_CPT, "Node33"); //observatoin
  //cout << "handle node3: " << node3 << endl;

  //DSL_idArray outNames;
  //outNames.Flush();
  //outNames.Add("das3");
  //outNames.Add("jenes3");
  //myNet.GetNode(node3)->Definition()->SetNumberOfOutcomes(outNames);


  //TODO: how to know waht note to connect to the original network
  //myNet.AddArc(node3, node2);

  //connect the nodes
  myNet.AddArc(node1, node2);
  //cout << "\tbefore double add arc" << endl; //... doesnt seems to be a problem
  myNet.AddArc(node1, node2);

  //Fill the cpt s
  DSL_doubleArray probs;
  probs.Add(0.2);
  probs.Add(0.8);
  myNet.GetNode(node1)->Definition()->SetDefinition(probs);

  //DSL_doubleArray probs;

  /*
  probs.Flush();
  probs.Add(0.01);
  probs.Add(0.99);
  myNet.GetNode(node3)->Definition()->SetDefinition(probs);
  */

  DSL_sysCoordinates theCoordinates (*myNet.GetNode(node2)->Definition());

  theCoordinates.UncheckedValue() = 0.4;
  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.6;
  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.2;
  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.8;

  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.04;
  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.96;
  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.02;
  theCoordinates.Next();
  cout << theCoordinates[0] <<theCoordinates[1] <<theCoordinates[2] << endl;
  theCoordinates.UncheckedValue() = 0.98;

  //binäre zählweise von hinten  [0][1][2]... 000 001 010 ... baum entlang der blätter von 1.parent 2.parent own state!

  theCoordinates[0] = 0; //parents first state
  theCoordinates[1] = 0; //own states
  theCoordinates[2] = 0; //own states
  theCoordinates.GoToCurrentPosition();
  cout << "prob in index 0 0 0 " << theCoordinates.UncheckedValue() << endl;

  theCoordinates[0] = 1; // 1.parent
  theCoordinates[1] = 0; //2.parent
  // ... more parents to come
  theCoordinates[2] = 0; //own ... Last!
  theCoordinates.GoToCurrentPosition();
  cout << "prob in index 0 0 1 " << theCoordinates.UncheckedValue() << endl;



  /*
  //inspect the network
  int nodeHandles[8];
  nodeHandles[0] = myNet.GetFirstNode();
  cout << myNet.GetNode(nodeHandles[0])->GetId() << endl;
  cout << "handle first node: " << nodeHandles[0] << endl;

  nodeHandles[1] = myNet.GetNextNode(nodeHandles[0]);
  cout << "handle next node: " << nodeHandles[1] << endl;

*/

  DSL_intArray nodeIntArray; //class automatisch pointer?
  //nodeIntArray.Add(0);
  myNet.GetAllNodes(nodeIntArray);

  cout << nodeIntArray.NumItems() << endl;
  for(int i=0; i< nodeIntArray.NumItems(); i++) {
    cout << "handle : " << nodeIntArray[i] << " " << myNet.GetNode(nodeIntArray[i])->GetId() << endl;
  }

  //set evidence of e.g. Node2
  int searchedHandle;
  searchedHandle = myNet.FindNode("Node2");

  //myNet.GetNode(node3)->Value()->SetEvidence(1); //update the net with observations ... no save of the evidence ... first state

  myNet.UpdateBeliefs();
  DSL_sysCoordinates theCoord(*myNet.GetNode(searchedHandle)->Value());

  DSL_idArray *theNames;
  theNames = myNet.GetNode(searchedHandle)->Definition()->GetOutcomesNames();
  int moderateIndex = theNames->FindPosition("das2"); // should be 1
  theCoord[0] = moderateIndex; // the odometer? ... here only 1 dimension? because only discrete states for that node independant from dependencies
  theCoord.GoToCurrentPosition();

  double P = theCoord.UncheckedValue();
   printf("P(\"Node2\" = das2 ) = ");
   printf("%f\n",P);




   //wie composition bekommen? ... zusammensetzung mehrerer Teilmodelle.

  /*
  DSL_network theNet;
  theNet.ReadFile("MyBooster_FuncCNKicker.xdsl");
  theNet.ReadFile("MyBooster_FuncCNUsbCanProxy.xdsl", ); // überschreibt es!


  */
   myNet.WriteFile("myNetTest2.xdsl");
  cout << "end test" << endl;
}


#endif /* TESTSPACE_H_ */
