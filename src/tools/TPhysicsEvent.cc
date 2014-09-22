/**
* Autogenerated Source File for TPhysicsEvent
* \\file TPhysicsEvent.cc
* \\author G.Gavalian
* \\date 2013-10-28
*/
#include "TPhysicsEvent.h"

TDatabasePDG  *gPDGDatabase = new  TDatabasePDG();

ClassImp(TPhysicsEvent)

TPhysicsEvent::TPhysicsEvent()
{
  particleBuffer = new  TObjArray(); 
}
/* 
TPhysicsEvent::TPhysicsEvent(const TPhysicsEvent &obj)
{
}
*/
TPhysicsEvent::~TPhysicsEvent()
{
  if(gPDGDatabase!=NULL) delete gPDGDatabase;
  if(particleBuffer!=NULL) delete particleBuffer;
}

/* const TPhysicsEvent &TPhysicsEvent::operator=(const TPhysicsEvent &obj){} */
 void TPhysicsEvent::Clear()
 {
   if(particleBuffer!=NULL) particleBuffer->Delete();
 }

double     TPhysicsEvent::Match(TParticle *p, int index)
{
  TVector3  vecRef(p->Px(),p->Py(),p->Pz());
  TVector3  partVec;
  TParticle *part = static_cast<TParticle *>(particleBuffer->At(index));
  partVec.SetXYZ(part->Px(),part->Py(),part->Pz());
  double cos_th = vecRef.Dot(partVec)/(vecRef.Mag()*partVec.Mag());
  return cos_th;
}

int        TPhysicsEvent::BestMatch(TParticle *p)
{
  int index = -1;
  double bestcos = -1.0;
  for(int loop = 0; loop < particleBuffer->GetEntries();loop++)
    {
      double costh = Match(p,loop);
      if(costh>bestcos){
	index = loop;
	bestcos = costh;
      }
    } 
  return index;
}

void TPhysicsEvent::AddParticle(int pid, double px, double py, double pz, double vx, double vy, double vz, double time)
{
  if(gPDGDatabase==NULL){
    cout << "***** PDG ERROR **** : PDG Database is not instantiated..." << endl;
  }
  TParticlePDG *p_part = gPDGDatabase->GetParticle(pid);
  if(p_part==NULL)
    {
      cout << "*** PDG ERROR *** Particle with PID = " << pid << "  not found " << endl;
      return;
    }
  TParticle *particle = new TParticle();
  double m2  = px*px + py*py + pz*pz;
  double en2 = m2 + p_part->Mass()*p_part->Mass();
  particle->SetPdgCode(pid);
  particle->SetMomentum(px,py,pz,TMath::Sqrt(en2));
  particle->SetProductionVertex(vx,vy,vz,time);
  particleBuffer->Add(particle);
}

TLorentzVector TPhysicsEvent::getParticle(const char *formula)
{
  TEventOperation oper;
  oper.Parse(formula);
  ApplyOperation(oper);
  return oper.getVector();
}

TLorentzVector TPhysicsEvent::getParticle(const char *parent, const char *formula)
{
  TEventOperation oper_p;
  TEventOperation oper_c;
  oper_p.Parse(parent);
  oper_c.Parse(formula);
  ApplyOperation(oper_p);
  ApplyOperation(oper_c);
  TLorentzVector child = oper_c.getVector();
  TVector3 boost = oper_p.getVector().BoostVector();
  child.Boost(-boost);
  return child;
}

void TPhysicsEvent::Print()
{
  int nparticles = particleBuffer->GetEntries();
  TString header;
  header.Form("%8d %12.5f %12.5f %12.5f %12.5f",
	      nparticles,beamParticle.Px(),beamParticle.Py(),beamParticle.Pz(),
	      targetParticle.GetMass());
  cout << header << endl;
  for(int loop = 0; loop < particleBuffer->GetEntries();loop++)
    {
      TString partLine = ParticleToString((TParticle *) particleBuffer->At(loop));
      cout << partLine << endl;
    }
}

void       TPhysicsEvent::ApplyOperation(TEventOperation &oper)
{
  create_particle(oper.GetParticle(),oper.GetSigns(),oper.GetPids(),oper.GetOrders());
}

int      TPhysicsEvent::GetCountByPid(int pid)
{
  int counter = 0;
   for(int loop = 0; loop < particleBuffer->GetEntries();loop++)
    {
      TParticle *part = static_cast<TParticle *>(particleBuffer->At(loop));
      if(part->GetPdgCode()==pid) counter++;
    }
   return counter;
}

TParticle *TPhysicsEvent::FindParticle(int pid, int order)
{
  if(pid==50001) return &beamParticle;
  if(pid==50002) return &targetParticle;
  int skip = 0;
  for(int loop = 0; loop < particleBuffer->GetEntries();loop++)
    {
      TParticle *part = static_cast<TParticle *>(particleBuffer->At(loop));
      if(part->GetPdgCode()==pid){
	if(skip==order){
	  return part;
	} else { skip++; }
      }
    }
  return NULL;
}

TParticle *TPhysicsEvent::GetParticle(int index){
  return static_cast<TParticle *>(particleBuffer->At(index));
}

int       TPhysicsEvent::GetCount(){
  return particleBuffer->GetEntries();
}

void       TPhysicsEvent::SetTarget(int pid, double px, double py,double pz)
{
  TParticlePDG *p_part = gPDGDatabase->GetParticle(pid);
  if(p_part==NULL)
    {
      cout << "*** PDG ERROR *** Particle with PID = " << pid << "  not found " << endl;
      return;
    } 
  targetParticle.SetPdgCode(pid);
  targetParticle.SetMomentum(px,py,pz,TMath::Sqrt(px*px + py*py + pz*pz + p_part->Mass()*p_part->Mass()));
}

void       TPhysicsEvent::SetPhotonBeam(double px, double py, double pz)
{
  beamParticle.SetPdgCode(22);
  beamParticle.SetMomentum(px,py,pz,TMath::Sqrt(px*px+py*py+pz*pz));
  beamParticle.SetProductionVertex(-100.0,0.0,0.0,0.0);
}

void       TPhysicsEvent::SetElectronBeam(double px, double py, double pz)
{
  beamParticle.SetPdgCode(1);
  beamParticle.SetMomentum(px,py,pz,TMath::Sqrt(px*px+py*py+pz*pz + 0.000511*0.000511));
  beamParticle.SetProductionVertex(-100.0,0.0,0.0,0.0);
}

void       TPhysicsEvent::SetPhotonBeam(double energy)
{
  SetPhotonBeam(0.0,0.0,energy);
}

void    TPhysicsEvent::create_particle(TParticle *pp, vector<int> signs, vector<int> pids,
				       vector<int> order)
{
  pp->SetPdgCode(0);
  pp->SetMomentum(0.0,0.0,0.0,0.0);
  pp->SetProductionVertex(0.0,0.0,0.0,0.0);
  for(int loop = 0; loop < signs.size();loop++)
    {
      //cout << " evaluating loop = " << loop << "  " << signs[loop] << "  " << pids[loop] << " " << order[loop] << endl;
      if(FindParticle(pids[loop],order[loop])!=NULL)
	{
	  if(signs[loop]<0){
	    sub_particle(pp,FindParticle(pids[loop],order[loop]));
	  } else {
	    add_particle(pp,FindParticle(pids[loop],order[loop]));
	  }
	  //cout << " found the particle for LOOP = " << loop << "  " << pp->Px() << "  "  << pp->GetMass() << endl; 
	}
    }
}

void    TPhysicsEvent::add_particle(TParticle *pp, TParticle *pc)
{
  pp->SetMomentum(
		  pp->Px()+pc->Px(),
		  pp->Py()+pc->Py(),
		  pp->Pz()+pc->Pz(),
		  pp->Energy()+pc->Energy()
		  );
}

void    TPhysicsEvent::sub_particle(TParticle *pp, TParticle *pc)
{
  pp->SetMomentum(
		  pp->Px()-pc->Px(),
		  pp->Py()-pc->Py(),
		  pp->Pz()-pc->Pz(),
		  pp->Energy()-pc->Energy()
		  );
}

TString TPhysicsEvent::ParticleToString(TParticle *pref)
{
  TString sline;
  char    cline[128];
  sprintf(cline,"%8d %12.5f %12.5f %12.5f %12.5f %12.5f %12.5f",
	   pref->GetPdgCode(),
	  pref->Px(),pref->Py(),pref->Pz(),
	  pref->Vx(),pref->Vy(),pref->Vz());
  sline.Form("%s",cline);
  return sline;
}
