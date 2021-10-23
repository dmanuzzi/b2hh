int findOption(int argc, char * argv[], TString option) {

  for(int i = 1; i<argc; i++)
   if(option==argv[i]) return i;
  return -1; 

}

bool getBooleanOption(int argc, char * argv[], TString option, bool default_value) {

  int iOption = findOption(argc,argv,option);
  if(iOption > 0 && iOption < argc)
    return true;
  return default_value;

}

const char * getOption(int argc, char * argv[], TString option, TString default_value) {

  int iOption = findOption(argc,argv,option);
  if(iOption>0 && iOption < argc-1)
    return argv[iOption+1];
  return default_value.Data();

}
