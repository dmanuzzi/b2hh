static int callback(void * NotUsed,
                    int argc, char * argv[], char * azColName[]) {

  int i;
  for(i=0;i<argc;i++) {
    printf("%s = %s\n",azColName[i],argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;

}

bool createDB(sqlite3 * db,TString name) {

  char * zErrMsg = 0;
  TString command;
  command.Form("create table if not exists %s \
               (decay varchar(7),finalState varchar(5), name varchar(10), bdtConfig varchar(7),\
                bdtCUT float,plusCUT1 integer,plusCUT2 integer,minusCUT1 integer,minusCUT2 integer,\
                magnet varchar(5),year varchar(4), splotFlag integer,\
                eff double,effErr double,\
                fracFiducialPlus double,   effFiducialPlus double,   effFiducialPlusMC double,\
                fracNoFiducialPlus double, effNoFiducialPlus double, effNoFiducialPlusMC double,\
                fracFiducialMinus double,  effFiducialMinus double,  effFiducialMinusMC double,\
                fracNoFiducialMinus double,effNoFiducialMinus double,effNoFiducialMinusMC double,\
                primary key (decay,finalState,name,plusCUT1,plusCUT2,minusCUT1,minusCUT2,\
                bdtConfig,bdtCUT,magnet,year,splotFlag));",name.Data());

  int rc = sqlite3_exec(db,command.Data(),callback,0,&zErrMsg);
  while(rc==SQLITE_BUSY) { sleep(1); rc = sqlite3_exec(db,command.Data(),callback,0,&zErrMsg); }

  if(rc != SQLITE_OK) return false;
  else return true;


}

bool fillDB(sqlite3 * db,
            TString &decay, TString &finalState, TString &name, TString &bdtConfig,
            TString &bdtCUT, TString &cuts,bool splotFlag, TString &magnet, TString &year,
            double &eff, double &effErr,
            double &fracFiducialPlus,   double &effFiducialPlus,   double &effFiducialPlusMC,
            double &fracNoFiducialPlus, double &effNoFiducialPlus, double &effNoFiducialPlusMC,
            double &fracFiducialMinus,  double &effFiducialMinus,  double &effFiducialMinusMC,
            double &fracNoFiducialMinus,double &effNoFiducialMinus,double &effNoFiducialMinusMC){

  TString plusCUT1  = ((TObjString *)cuts.Tokenize('.')->At(0))->String();
  TString plusCUT2  = ((TObjString *)cuts.Tokenize('.')->At(1))->String();
  TString minusCUT1 = ((TObjString *)cuts.Tokenize('.')->At(2))->String();
  TString minusCUT2 = ((TObjString *)cuts.Tokenize('.')->At(3))->String();

  char * zErrMsg = 0;
  TString command;
  command.Form("insert or replace into pidEffs \
                (decay,finalState,name,bdtConfig,\
                 bdtCUT,plusCUT1,plusCUT2,minusCUT1,minusCUT2,\
                 magnet,year,splotFlag,\
                 eff,effErr,\
                 fracFiducialPlus,   effFiducialPlus,   effFiducialPlusMC,\
                 fracNoFiducialPlus, effNoFiducialPlus, effNoFiducialPlusMC, \
                 fracFiducialMinus,  effFiducialMinus,  effFiducialMinusMC,\
                 fracNoFiducialMinus,effNoFiducialMinus,effNoFiducialMinusMC) \
                values \
                (\"%s\",\"%s\",\"%s\",\"%s\",%s,%s,%s,%s,%s,\"%s\",\"%s\",%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf);",
               decay.Data(),finalState.Data(),name.Data(),bdtConfig.Data(),
               bdtCUT.Data(),plusCUT1.Data(),plusCUT2.Data(),minusCUT1.Data(),minusCUT2.Data(),
               magnet.Data(),year.Data(),splotFlag,eff,effErr,
               fracFiducialPlus,   effFiducialPlus,   effFiducialPlusMC,
               fracNoFiducialPlus, effNoFiducialPlus, effNoFiducialPlusMC,
               fracFiducialMinus,  effFiducialMinus,  effFiducialMinusMC,
               fracNoFiducialMinus,effNoFiducialMinus,effNoFiducialMinusMC);

  int rc = sqlite3_exec(db,command.Data(),callback,0,&zErrMsg);
  while(rc==SQLITE_BUSY) { sleep(1); rc = sqlite3_exec(db,command.Data(),callback,0,&zErrMsg); }
  if(rc != SQLITE_OK) return false;
  else return true;

}

