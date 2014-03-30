  void InferenceWithInfluenceDiagram(void) {
    DSL_network theNet;
    theNet.ReadFile("tutorial.dsl");
    
    // update the network
    theNet.UpdateBeliefs();
    
    // get the resulting value
    int gain = theNet.FindNode("Gain");
    DSL_sysCoordinates theCoordinates(*theNet.GetNode(gain)->Value());
    printf("\nThese are the expected utilities:\n\n");
    DSL_idArray *theOutcomesNames;
    DSL_intArray theIndexingParents;
    DSL_nodeDefinition *theDefinition;
    char *hisOutcomeName;
    char *hisName;
    double ExpectedUtility;
    int aParent;
    int hisOutcome;
    int x;
    int result = DSL_OKAY;
    theIndexingParents = theNet.GetNode(gain)->Value()->GetIndexingParents();
    theCoordinates.GoFirst(); // goes to (0,0)
    
    /* print the expected utility of each choice */
    while (result != DSL_OUT_OF_RANGE) {
      printf("Policy:\n");
      for (x=0; x<theIndexingParents.NumItems(); x++) {
        aParent = theIndexingParents[x];
        theDefinition = theNet.GetNode(aParent)->Definition();
        theOutcomesNames = theDefinition->GetOutcomesNames();
    
        // get the name of the current outcome for this node
        // the current outcome is in the coordinates
        hisOutcome = theCoordinates[x];
        hisOutcomeName = (*theOutcomesNames)[hisOutcome];
        hisName = theNet.GetNode(aParent)->Info().Header().GetId();
        printf(" Node \"%s\" = %s\n",hisName,hisOutcomeName);
      };
      ExpectedUtility = theCoordinates.UncheckedValue();
      printf(" Expected Utility = %f\n\n",ExpectedUtility);
      result = theCoordinates.Next();
    };
  };