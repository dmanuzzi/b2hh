#include <expandFileName.h>

struct binScheme { TString name;
                   double start;
                   double end;
                   std::vector<double> intervals; };

int findBin(double x, binScheme &binning) {

  unsigned int nBins = binning.intervals.size();
  unsigned int bin = 0, i = 0;
  double xlow = binning.start, xhigh = binning.start;
  for(i = 0; i < nBins; i++) {
    xlow   = xhigh;
    xhigh += binning.intervals.at(i);
    if(x >= xlow && x < xhigh ) {
      bin = i; break;
    }
  }
  return bin;
}

int createBinning(TString binName, binScheme &bin) {
  TString fileName = Form("${B2HH_SRC}/PID/effB2HH/binnings/%s.bin", binName.Data());
  expandFileName::expandFileName(fileName);
  // // Expand input file name
  // char tmp_buff[400];
  // FILE *tmp_f = popen(Form("echo ${B2HH_SRC}/PID/effB2HH/binnings/%s.bin",fileName.Data()), "r");
  // if (tmp_f == NULL){
  //   printf("ERROR not able to expand the input file name\n");
  //   return -1;
  // }
  // if ( fgets(tmp_buff, 400, tmp_f) == NULL){
  //   printf("ERROR not able to get the input file name\n");
  //   return -1;
  // };
  // fclose(tmp_f);
  // tmp_buff[strlen(tmp_buff)-1] = '\0';
  // printf("expandend input file name: %s\n", tmp_buff);
  
  FILE * schemeFile = fopen(fileName.Data(), "r");
  if(schemeFile == NULL) { 
    printf("File %s.bin does not exists\n",fileName.Data());
    return -1;
  }
  double max = 0, min = 0; int nBins = 0;
  double start = 0, end = 0;
  char name[200];
  int readFlag = 0, count = 0;
  fscanf(schemeFile,"%s",name); bin.name = name;
  printf("READING BINNING FOR VARIABLE %s from %s.bin\n",bin.name.Data(),fileName.Data());
  while(1) {

    readFlag = fscanf(schemeFile,"%d %lf %lf",&nBins,&min,&max);
    if(readFlag < 0) break;
    else if(readFlag != 3) {
      printf("Unexpected number of parameters\n");
      fclose(schemeFile);
      return -1;
    }
    if(!count) { start = min; count++; }
    bin.intervals.insert(bin.intervals.end(),nBins,(max-min)/nBins);
    end = max;
     
  }
  fclose(schemeFile);
  bin.start = start;
  bin.end = end;
  return 0;
}

double * histoBinning(binScheme &bin) {

  unsigned int nBins = bin.intervals.size();
  double xlow = bin.start;
  double * binning = new double[nBins+1];
  for(unsigned int count = 0; count < nBins; count++) {
    binning[count] = xlow;
    xlow += bin.intervals[count];
  }
  binning[nBins] = bin.end;

  return binning;

}

bool fiducialCut(double x, double y) {

  return true;

  double m1 = 0;                  double q1 = 2;
  double m2 = (3.75-2)/(120-25);  double q2 = 2 - m2*25;
  double m3 = (6-3.75)/(135-120); double q3 = 3.75 - m3*120;

  bool ret = (y > x*m1+q1 && x<=25)||
             (y > x*m2+q2 && x>25 && x<=120)||
             (y > x*m3+q3 && x>120);
  return ret;

}

