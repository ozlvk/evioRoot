/**
* Autogenerated Source File for TTreeEvio
* \\file TTreeEvio.cc
* \\author G.Gavalian
* \\date 2014-09-25
*/
#include "TTreeEvio.h"

ClassImp(TTreeEvio)

TTreeEvio::TTreeEvio() : TTree("CLAS12Tree","CLAS 12 Evio Tree")
{
  //variable = 2.5;
  //TBranch *branch = new TBranch(this,"DC",NULL,"time:energy:wire");
  //AddBranchToCache(branch);
  TBranch *branchPCAL =  Branch("/CLAS12Tree/PCAL",&variableI,"time:path:energy");
  TBranch *branchFTOF =  Branch("/FTOF",&variableI,"energy");
  //TBasket *energy  = new TBasket("energy","PCAL energy",branchFTOF);
  //branchPCAL->AddBasket(*energy,false,0);
}

TTreeEvio::TTreeEvio(const char *filename, bool debug) : TTree("CLAS12Tree","CLAS 12 Evio Tree")
{
    evioReader = new EvioFileReader();
    evioReader->open(filename);
    kDebugMode = debug;
    //evioReader->readEvent(5);
    //InitDescriptors();
    LoadDictionary();
    InitBranches();
}

TTreeEvio::TTreeEvio(const char *filename, const char *mode) : TTree("CLAS12Tree","CLAS 12 Evio Tree")
{
    evioReader = new EvioFileReader();
    evioReader->open(filename);
    kDebugMode = false;
    //evioReader->readEvent(5);
    //InitDescriptors();
    LoadDictionary6();
    InitBranches();
}
/* 
TTreeEvio::TTreeEvio(const TTreeEvio &obj)
{
}
*/
TTreeEvio::~TTreeEvio()
{
}

Int_t       TTreeEvio::GetNRows(const char *branch){
  TLeafI *leaf = (TLeafI *) GetLeaf(branch,"entries");
  if(leaf==NULL) return 0;
  return leaf->GetValue(0);
}

Double_t    TTreeEvio::GetValue(int row, const char *branch, const char *leaf){
if(GetNRows(branch)<=row){
    cout << "TTreeEvio::GetValueI:: Warning : Requested row " << row << " for branch " 
    << branch << " which has " << GetNRows(branch) << " entries" << endl;
    return 0;
  }
  TLeafD *leafp = (TLeafD *) GetLeaf(branch,leaf);
  if(leafp==NULL){
    cout << "TTreeEvio::GetValueI:: ERROR : invalid leaf " << branch << " " << leaf << endl;
    return 0;
  }

  return leafp->GetValue(row);
}


Int_t       TTreeEvio::GetValueI(int row,const char *branch, const char *leaf){
  if(GetNRows(branch)<=row){
    cout << "TTreeEvio::GetValueI:: Warning : Requested row " << row << " for branch " 
    << branch << " which has " << GetNRows(branch) << " entries" << endl;
    return 0;
  }
  TLeafI *leafp = (TLeafI *) GetLeaf(branch,leaf);
  if(leafp==NULL){
    cout << "TTreeEvio::GetValueI:: ERROR : invalid leaf " << branch << " " << leaf << endl;
    return 0;
  }

  return leafp->GetValue(row);
}

Float_t       TTreeEvio::GetValueF(int row,const char *branch, const char *leaf){
  if(GetNRows(branch)<=row){
    cout << "TTreeEvio::GetValueI:: Warning : Requested row " << row << " for branch " 
    << branch << " which has " << GetNRows(branch) << " entries" << endl;
    return 0;
  }
  TLeafF *leafp = (TLeafF *) GetLeaf(branch,leaf);
  if(leafp==NULL){
    cout << "TTreeEvio::GetValueI:: ERROR : invalid leaf " << branch << " " << leaf << endl;
    return 0;
  }

  return leafp->GetValue(row);
}

Double_t       TTreeEvio::GetValueD(int row,const char *branch, const char *leaf){
  if(GetNRows(branch)<=row){
    cout << "TTreeEvio::GetValueD:: Warning : Requested row " << row << " for branch " 
    << branch << " which has " << GetNRows(branch) << " entries" << endl;
    return 0;
  }
  TLeafD *leafp = (TLeafD *) GetLeaf(branch,leaf);
  if(leafp==NULL){
    cout << "TTreeEvio::GetValueI:: ERROR : invalid leaf " << branch << " " << leaf << endl;
    return 0;
  }

  return leafp->GetValue(row);
}

void        TTreeEvio::TestLoop(int nentries)
{
    evioReader->readEvent(5);
    int len;
    int32_t *buffer = evioReader->getEvent().geti32(1102,2,&len);
    cout << "  Length = " << len << endl;
  for(int loop = 0; loop < nentries; loop++){
    evioReader->readEvent(loop);
    //evioReader->getEvent().getList();
    //int len;
    //int32_t *buffer = evioReader->getEvent().geti32(1102,2,&len);
     //evioReader->getEvent().runIndexing();
     /*
    for(int ic = 0; ic < 20; ic++){

      //int32_t *data = new int32_t[len];
      //memcpy(data,buffer,len*sizeof(int32_t));
    }*/
  }
}

Long64_t    TTreeEvio::GetEntries() const
{
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}

Long64_t    TTreeEvio::GetEntries(const char* selection)
{
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}

Long64_t    TTreeEvio::GetEntriesFast() const
{
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}

Long64_t  TTreeEvio::GetEntriesFriend() const {
  if(evioReader!=NULL){
    return evioReader->getEntries();
  }
  return 0;
}

Long64_t    TTreeEvio::LoadTree(Long64_t entry)
{


  evioReader->readEvent(entry);
  if(kDebugMode==true){
    cout << "TTreeEvio::LoadEntry : ---->  loading entry : " << entry << endl;
  }

  LoadBranches();
  //LoadBranch(bankEvnt);
  /*
  //cout << "-----> load tree function called" << endl;
  TBranch  *EVHB = GetBranch("EVNTHB::particle");
  TLeafI   *entLeaf = (TLeafI *) EVHB->GetLeaf("entries");
  entLeaf->SetMinimum(0);
  entLeaf->SetMaximum(100);
  TLeafF   *pxLeaf = (TLeafF *)  EVHB->GetLeaf("px");
  int *counter = new int[1];
  
  int len;
  float *bufferPx = evioReader->getEvent().getf(4601,7,&len);
  if(len==0){
    counter[0] = 0;
    valueI = 0;
    entLeaf->SetLen(1);
    entLeaf->SetAddress(&counter[0]);
  } else {
    counter[0] = len;
    entLeaf->SetLen(1);
    entLeaf->SetAddress(&counter[0]);
    valueI = len;
    pxLeaf->SetLen(len);
    pxLeaf->SetAddress(bufferPx);
  }*/
  //cout << " Reading PX LENGTH = " << len << "  counter = " << entLeaf->GetValue() 
  //<< "  " << entLeaf->GetNdata() << "  " << entLeaf->GetMinimum() << "  " << entLeaf->GetMaximum()
  // << endl; 
}

void        TTreeEvio::InitBranches()
{
  //InitDescriptors();
  cout << "-> Initializing branches for the Tree " << endl;
   int nSize = bankList.GetSize();
     cout << "-> Total number of branches = " << nSize << endl;
    for(int loop = 0; loop < nSize; loop++){
      InitBranch( *static_cast<TBankDescriptor *> (bankList.At(loop)));
    }
  //InitBranch(bankEvnt);
  //Branch("entries",&valueI,"entries[10]/I");
  //Branch("EVNTHB::particle",&variableD,"entries/I:status[entries]/I:charge[entries]/I:pid[entries]/I:mass[entries]/F:beta[entries]/F:px[entries]/F:pz[entries]/F:py[entries]/F");
  //InitBranch(bankEvnt);
}

/**
* Initializes a branch for give bank descriptor. Called from InitDescriptors() function for each
* entry in the descriptors map.
*/
void        TTreeEvio::InitBranch(TBankDescriptor &desc)
{
  TBranch  *branch = Branch(desc.GetName(),NULL,desc.GetFormatString().c_str());
  TLeafI   *counterLeaf = (TLeafI *) branch->GetLeaf("entries");
  counterLeaf->SetMaximum(200);
}

void        TTreeEvio::LoadBranches(){
  
  int nSize = bankList.GetSize();
  
  if(kDebugMode == true ){
    cout << "TTreeEvio::LoadBranches : ---->  loading branches  count =  " << nSize << endl;
  }

    for(int loop = 0; loop < nSize; loop++){
      TBankDescriptor *desc = static_cast<TBankDescriptor *> (bankList.At(loop));
      if(kDebugMode==true){
      cout << "TTreeEvio::LoadBranches : ---->  loading branch with name =  " 
          << desc->GetName() << endl;
      }
      LoadBranch(*desc,loop);
    }
}
/**
* Load the branch with given descriptor. Called from LoadTree routine for each descriptor.
* If the branch is disabled, it will not be processed, this will speed up the drawing.
* This routine also checks if all the leafs read from evio have the same length. If not,
* then the entries leaf value will be set to 0, so there is nothing read from the leaf
* by TreePlayer.
*/
void        TTreeEvio::LoadBranch(TBankDescriptor &desc, int entry)
{

  TBranch *branch = GetBranch(desc.GetName());
  
  //if(branch!=NULL) cout << " branch is OK " << endl;
  //evioReader->getEvent().getList();
  
//int tbl;
//float *data = evioReader->getEvent().getf(21,3,&tbl);
//cout << "  bank length (21,3) = " << tbl << endl;
  //cout << " Loading branch " << desc.GetName() << endl;
  //desc.Print();
  int bankLenght = 0;
  bool bankExists = true;
  for(int loop = 0; loop < desc.GetEntries(); loop++){
    //cout << " Looking for " << desc.GetEntryName(loop) << "  " << desc.GetEntryType(loop)
    //<< "  " << desc.GetTag(loop) << "  " << desc.GetNum(loop) << endl;
    if(desc.isFloat(loop)==true){
      const float *bufferF = reinterpret_cast<const float *> (
        evioReader->getEvent().getBankIndex().getBank(desc.GetTag(loop),desc.GetNum(loop),&bankLenght));
      if(bankLenght==0 || bufferF==NULL){
        bankExists = false;
        break;
      } else {
        //cout << " FLOAT ----> Returned length for " << desc.GetEntryName(loop) << " = " << bankLenght 
        //  << " first value = " << bufferF[0] << "  " << bufferF[1] << endl;
      //cout << " Returned length for " << desc.GetEntryName(loop) << " = " << bankLenght << endl;
        TLeafF *leafF  = (TLeafF *) branch->GetLeaf(desc.GetEntryName(loop));
        leafF->SetLen(bankLenght);
        leafF->SetAddress(const_cast<void *> (reinterpret_cast<const void *> (bufferF)));
      }
    }
   
   if(desc.isDouble(loop)==true){
      const double *bufferD = reinterpret_cast<const double *> (
        evioReader->getEvent().getBankIndex().getBank(desc.GetTag(loop),desc.GetNum(loop),&bankLenght));
      if(bankLenght==0 || bufferD==NULL){
        bankExists = false;
        break;
      } else {
        //cout << " DOUBLE ----> Returned length for " << desc.GetEntryName(loop) << " = " << bankLenght 
        //<< " first value = " << bufferD[0] << "  " << bufferD[1] << endl;
        TLeafD *leafD  = (TLeafD *) branch->GetLeaf(desc.GetEntryName(loop));
        leafD->SetLen(bankLenght);
        leafD->SetAddress(const_cast<void *> (reinterpret_cast<const void *> (bufferD)));
      }
    }
   if(desc.isInt32(loop)==true){
      const int32_t *bufferI32 = reinterpret_cast<const int32_t *> 
        (evioReader->getEvent().getBankIndex().getBank(desc.GetTag(loop),desc.GetNum(loop),&bankLenght));
        if(bankLenght==0 || bufferI32==NULL){
          bankExists = false;
          break;
        } else {
          //cout << " Returned length for " << desc.GetEntryName(loop) << " = " << bankLenght 
          //<< " first value = " << bufferI32[0] << "  " << bufferI32[1] << endl;
          TLeafI *leafI  = (TLeafI *) branch->GetLeaf(desc.GetEntryName(loop));
          leafI->SetLen(bankLenght);
          leafI->SetAddress( const_cast<void *> (reinterpret_cast<const void *> (bufferI32)));
        }
      //cout << " Returned length for " << desc.GetEntryName(loop) << " = " << bankLenght << endl;
      //if(bankLenght>0) cout << "  EVENT has a bank length > 0 " << endl;
      /*

      if(bankLenght==0){
        leafI->SetLen(1);
        leafI->SetAddress(&variableI);
      } else {
        leafI->SetLen(bankLenght);
        leafI->SetAddress(bufferI32);
      }*/
    }
  }
  //cout << " setting entries to 0" << endl;
  //int *counter = new int[1]; counter[0] = bankLenght;
  //int *counter = new int[1]; counter[0] = 0;
  //  cout << " bank Length = " << bankLenght << endl;

  TLeafI *entries = (TLeafI *) branch->GetLeaf("entries");
  if(bankExists==false){
    bankSizes[entry] = 0;
  } else {
    bankSizes[entry] = bankLenght;
  }
  if(kDebugMode==true){
      cout << "TTreeEvio::LoadBranch(b,e) : ---->  branch  " 
          << desc.GetName() << " loaded entries = " << bankLenght << endl;
  }
  entries->SetLen(1);
  entries->SetAddress(&bankSizes[entry]);
  //cout << "-> Loading branch : " << desc.GetName() << " size = " << bankLenght << endl;
}

/**
* Initialize descriptos for the Library.
*/
void        TTreeEvio::InitDescriptors()
{
  
  bankEvnt.SetName("FTOF1B");
  bankEvnt.AddEntry("sector"  ,"I", 1102, 1  );
  bankEvnt.AddEntry("paddle"  ,"I", 1102, 2  );
  bankEvnt.AddEntry("ADCL"    ,"I", 1102, 3  );
  bankEvnt.AddEntry("ADCR"    ,"I", 1102, 4  );
  bankEvnt.AddEntry("TDCL"    ,"I", 1102, 5  );
  bankEvnt.AddEntry("TDCR"    ,"I", 1102, 6  );
  
  
  TBankDescriptor *bankFTOF1A = new TBankDescriptor("FTOF1A::dgtz");
  bankFTOF1A->AddEntry("sector"  ,"I", 1002, 1  );
  bankFTOF1A->AddEntry("paddle"  ,"I", 1002, 2  );
  bankFTOF1A->AddEntry("ADCL"    ,"I", 1002, 3  );
  bankFTOF1A->AddEntry("ADCR"    ,"I", 1002, 4  );
  bankFTOF1A->AddEntry("TDCL"    ,"I", 1002, 5  );
  bankFTOF1A->AddEntry("TDCR"    ,"I", 1002, 6  );

  TBankDescriptor *bankFTOF1B = new TBankDescriptor("FTOF1B::dgtz"); 
  bankFTOF1B->Copy("FTOF1B::dgtz",1102, *bankFTOF1A);

  bankList.Add(bankFTOF1A);
  bankList.Add(bankFTOF1B);
  bankSizes.resize(bankList.GetSize());
  //cout << " EVNT : " << bankEvnt.GetFormatString().c_str() << endl;
}

void        TTreeEvio::LoadDictionary6()
{
  vector<string>  banknames;
  banknames.push_back("etc/bankdefs/CLAS6BANKS.xml");
  bankList.Delete();
  TXMLBankDictionary parser;
  for(int loop = 0; loop < banknames.size(); loop++){
    parser.ParseFile("CLASROOT",banknames[loop].c_str());
    for(int ik = 0; ik < parser.GetList().GetEntries();ik++){
      TBankDescriptor *bank = new TBankDescriptor();
      bank->Copy(*(static_cast<TBankDescriptor *> (parser.GetList().At(ik))));
      bankList.Add(bank);
    }
  }
  //int nSize = bankList.GetEntries();
  bankSizes.resize(bankList.GetSize());
}

void        TTreeEvio::LoadDictionary()
{
  vector<string>  banknames;
  banknames.push_back("etc/bankdefs/DC.xml");
  banknames.push_back("etc/bankdefs/FTOF.xml");
  banknames.push_back("etc/bankdefs/EC.xml");
  banknames.push_back("etc/bankdefs/SEB.xml");
  banknames.push_back("etc/bankdefs/BST.xml");
  banknames.push_back("etc/bankdefs/GenPart.xml");
  banknames.push_back("etc/bankdefs/RECEVENT.xml");
  bankList.Delete();
  TXMLBankDictionary parser;
  for(int loop = 0; loop < banknames.size(); loop++){
    parser.ParseFile("CLASROOT",banknames[loop].c_str());
    for(int ik = 0; ik < parser.GetList().GetEntries();ik++){
      TBankDescriptor *bank = new TBankDescriptor();
      bank->Copy(*(static_cast<TBankDescriptor *> (parser.GetList().At(ik))));
      bankList.Add(bank);
    }
  }
  //int nSize = bankList.GetEntries();
  bankSizes.resize(bankList.GetSize());
}
/*
Long64_t TTreeEvio::Draw(const char* varexp, const char* selection, Option_t* option, Long64_t nentries, Long64_t firstentry){
  cout << "  Tree Drawing is called variable [" << varexp << "]  selection [" << selection << "]" <<  endl;

  //TH1D *tmp = (TH1D *) gDirectory->Get();
  //if(tmp!=NULL){
  //  cout << " Deleting histogram " << endl;
  //}
  if(gDirectory->FindObject(varexp)!=NULL){
    cout << " Deleting histogram " << varexp << endl;
    gDirectory->Delete(varexp);
  }
  
  TH1D *H = new TH1D(varexp,varexp,100,0.0,1.0);
  H->Draw();
}
*/
/* const TTreeEvio &TTreeEvio::operator=(const TTreeEvio &obj){} */
