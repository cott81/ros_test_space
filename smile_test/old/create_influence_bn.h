  void UpgradeToInfluenceDiagram(void) {
    DSL_network theNet;
    theNet.ReadFile("tutorial.dsl");
    
    // create decision node "Invest"
    int invest = theNet.AddNode(DSL_LIST,"Invest");
    
    // setting number (and name) of choices
    DSL_stringArray someNames;
    someNames.Add("Invest");
    someNames.Add("DoNotInvest");
    theNet.GetNode(invest)->Definition()->SetNumberOfOutcomes(someNames);
    
    //theNet.AddNode()

    // create value node "Gain"
    int gain = theNet.AddNode(DSL_TABLE,"Gain");
    
    // add arc from "Invest" to "Gain"
    theNet.AddArc(invest,gain);
    
    // add arc from "Success" to "Gain"
    int success = theNet.FindNode("Success");
    theNet.AddArc(success,gain);
    
    // now fill in the utilities for the node "Gain"
    // The utilities are:
    // U("Invest" = Invest, "Success" = Success) = 10000
    // U("Invest" = Invest, "Success" = Failure) = -5000
    // U("Invest" = DoNotInvest, "Success" = Success) = 500
    // U("Invest" = DoNotInvest, "Success" = Failure) = 500
    // get the internal matrix of the definition of node "Gain"
    DSL_Dmatrix *theMatrix;

    theNet.GetNode(gain)->Definition()->GetDefinition(&theMatrix);
    
    // and set the values directly
    theMatrix->Subscript(0) = 10000;
    theMatrix->Subscript(1) = -5000;
    theMatrix->Subscript(2) = 500;
    theMatrix->Subscript(3) = 500;
    theNet.WriteFile("tutorial.dsl");
  };
