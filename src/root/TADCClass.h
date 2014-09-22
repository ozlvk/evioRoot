/**
* Autogenerated Header File for TADCClass
* \\file TADCClass.h
* \\author G.Gavalian
* \\date 2013-11-13
*/
#ifndef __TADCCLASS__
#define __TADCCLASS__
#include "TROOT.h"
#include "TObject.h"
#include "TArrayS.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>


using namespace std;
//! A Brief Description
/*
 * A detailed description
 */
class TADCClass : public TObject {

private:

  Int_t slot_number;
  Int_t channel_number;
  TArrayS adcValue;

public:

/** Default Constructor */
TADCClass();
TADCClass(int nrows);
TADCClass(int slot, int channel,int nrows);
//TADCClass(int slot, int channel,TArrayS *array);
/** Default Destructor */
~TADCClass();
/** Copy Constructor if one is needed */
TADCClass( const TADCClass &obj);

 Int_t     GetSlot(){ return slot_number;}
 Int_t     GetChannel(){ return channel_number;}
 Int_t     GetRows(){ return adcValue.GetSize();}
 void      SetValue(int row, int value);
 Short_t   GetValue(int row);
 void      Init(int nrows);
 void      SetSlotChannel(int slot, int channel);
 void      Init(int slot, int channel, int nrows);
 TArrayS  &Data(){ return adcValue;};
/** An operator = if one is needed */
/* const TADCClass &operator=(const TADCClass &obj); */

 ClassDef(TADCClass,1)
};
#endif