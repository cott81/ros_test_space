#include <iostream>

void CreateKickerBN(void) {

  DSL_network theNet;
  theNet.ReadFile("MyBooster_FuncCNKicker.xdsl");
  std::cout << "after importing the model" << std::endl;

  //calculate output and check if it is reight
  //set solver
  theNet.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);
  theNet.UpdateBeliefs();
  int kicker = theNet.FindNode("CNKicker");

  // get the result value
  DSL_sysCoordinates theCoordinates(*theNet.GetNode(kicker)->Value());
  DSL_idArray *theNames;
  theNames = theNet.GetNode(kicker)->Definition()->GetOutcomesNames();

  int okIndex = theNames->FindPosition("Ok"); // should be 1
  std::cout << "okIndex:" << okIndex << std::endl;

  theCoordinates[0] = okIndex;
  theCoordinates.GoToCurrentPosition();

  // get P("Forecast" = Moderate)
  double P_ForecastIsModerate = theCoordinates.UncheckedValue();
  printf("P(\"CNKicker\" = Ok) = %f\n",P_ForecastIsModerate);


  //second file
  DSL_network theNetUsbCan;
  theNetUsbCan.ReadFile("MyBooster_FuncCNUsbCanProxy.xdsl");
  std::cout << "after importing the 2 model" << std::endl;

  //calculate output and check if it is reight
  //set solver
  theNetUsbCan.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);
  theNetUsbCan.UpdateBeliefs();
  int usbCanProxy = theNetUsbCan.FindNode("CNUsbCanProxy");

  // get the result value
  DSL_sysCoordinates theCoordinatesUsb(*theNetUsbCan.GetNode(usbCanProxy)->Value());
  DSL_idArray *theNamesUsb;
  theNamesUsb = theNetUsbCan.GetNode(usbCanProxy)->Definition()->GetOutcomesNames();

  int okUsbIndex = theNamesUsb->FindPosition("Ok"); // should be 1
  std::cout << "okIndex:" << okUsbIndex << std::endl;

  theCoordinatesUsb[0] = okIndex;
  theCoordinatesUsb.GoToCurrentPosition();

  // get P("Forecast" = Moderate)
  double P_UsbCanIsOk = theCoordinatesUsb.UncheckedValue();
  printf("P(\"CNUsbCanProxy\" = Ok) = %f\n",P_UsbCanIsOk);



  //read another file and connect
  // check composition results! ...

  //integration of equations? ... lib extension?


}
