  void InfereceWithBayesNet(void) {
    DSL_network theNet;
    theNet.ReadFile("tutorial.dsl");  // could be used to get a graphicly created mdoel
    
    // use clustering algorithm
   theNet.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);
 
    
    /* say that we want to compute P("Forecast" = Moderate) */
    // update the network
    theNet.UpdateBeliefs();
    
    // get the handle of node "Forecast"
    int forecast = theNet.FindNode("Forecast");
 
    // get the result value
    DSL_sysCoordinates theCoordinates(*theNet.GetNode(forecast)->Value());
    DSL_idArray *theNames;
    theNames = theNet.GetNode(forecast)->Definition()->GetOutcomesNames();  
    int moderateIndex = theNames->FindPosition("Moderate"); // should be 1
    theCoordinates[0] = moderateIndex;
    theCoordinates.GoToCurrentPosition();
    
    // get P("Forecast" = Moderate)
    double P_ForecastIsModerate = theCoordinates.UncheckedValue();
    printf("P(\"Forecast\" = Moderate) = %f\n",P_ForecastIsModerate);
    
    
    /* now we want to compute P("Success" = Failure | "Forecast" = Good) */
    // first, introduce the evidence
    // 0 is the index of state [Good]
    theNet.GetNode(forecast)->Value()->SetEvidence(0);
 
    // update the network again
    theNet.UpdateBeliefs();
    
    // get the handle of node "Success"
    int success = theNet.FindNode("Success");
    
    // get the result value
    theCoordinates.LinkTo(*theNet.GetNode(success)->Value());
    theCoordinates[0] = 1; // 1 is the index of state [Failure]
    theCoordinates.GoToCurrentPosition();
   double P_SuccIsFailGivenForeIsGood = theCoordinates.UncheckedValue();
    printf("P(\"Success\" = Failure | \"Forecast\" = Good) = ");
    printf("%f\n",P_SuccIsFailGivenForeIsGood);
    
 
    /* now we want to compute P("Success" = Success | "Forecast" = Poor) */
    // first, clear the evidence in node "Forecast"
    theNet.GetNode(forecast)->Value()->ClearEvidence();
    
    // introduce the evidence in node "Success"
    // 2 is the index of state [Poor]
    theNet.GetNode(forecast)->Value()->SetEvidence(2);
    
    // update the network again
    theNet.UpdateBeliefs();
    
    // get the result value
    theCoordinates.LinkTo(*theNet.GetNode(success)->Value());
    theCoordinates[0] = 0; // 0 is the index of state [Success]
    theCoordinates.GoToCurrentPosition();
    double P_SuccIsSuccGivenForeIsPoor = theCoordinates.UncheckedValue();
    printf("P(\"Success\" = Success | \"Forecast\" = Poor) = ");
    printf("%f\n", P_SuccIsSuccGivenForeIsPoor);
  };
