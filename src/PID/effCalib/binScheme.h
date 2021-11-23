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
  TString fileName = Form("${B2HH_CONFIG}/PID_bins/%s.bin", binName.Data());
  expandFileName::expandFileName(fileName);

  FILE * schemeFile = fopen(fileName.Data(),"r");
  if(schemeFile == NULL) { 
    printf("File %s does not exists\n",fileName.Data());
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

