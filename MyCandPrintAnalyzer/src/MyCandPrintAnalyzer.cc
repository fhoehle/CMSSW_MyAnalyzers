// -*- C++ -*-
//
// Package:    MyCandPrintAnalyzer
// Class:      MyCandPrintAnalyzer
// 
/**\class MyCandPrintAnalyzer MyCandPrintAnalyzer.cc MyAnalyzers/MyCandPrintAnalyzer/src/MyCandPrintAnalyzer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
 */
//
// Original Author:  Felix Hoehle
//         Created:  Fri Sep 28 18:46:24 CEST 2012
// $Id$
//
//


// system include files
#include <memory>
#include <string>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
//
// class declaration
//

class MyCandPrintAnalyzer : public edm::EDAnalyzer {
	public:
		explicit MyCandPrintAnalyzer(const edm::ParameterSet&);
		~MyCandPrintAnalyzer();

		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


	private:
		virtual void beginJob() ;
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob() ;

		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
		edm::InputTag src_;
		std::vector<std::string> quantity_;
		std::string prefix_;
		// ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyCandPrintAnalyzer::MyCandPrintAnalyzer(const edm::ParameterSet& iConfig):
	src_(iConfig.getParameter<edm::InputTag>("src")),
	quantity_(iConfig.getParameter<std::vector<std::string> >("quantity")),
	prefix_(iConfig.getParameter<std::string>("prefix"))
{
	//now do what ever initialization is needed

}


MyCandPrintAnalyzer::~MyCandPrintAnalyzer()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
	void
MyCandPrintAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	edm::Handle<edm::View<reco::Candidate> > coll;
	iEvent.getByLabel(src_,coll);
	std::cout<<prefix_.c_str()<<" print collection's quantities run "<<iEvent.id ().run()<<"  lumi "<< iEvent.id ().luminosityBlock ()<<" event "<<iEvent.id ().event()<<" collection "<<src_.label().c_str()<<" size "<<coll->size()<<std::endl;
	for (edm::View<reco::Candidate>::const_iterator it = coll->begin(); it != coll->end(); ++it){
		for (std::vector<std::string>::iterator str = quantity_.begin(); str != quantity_.end(); ++str){
			StringObjectFunction<reco::Candidate> f(str->c_str(),true);
			std::cout<<" "<<str->c_str()<<": "<<f(*it);
		}
		std::cout<<std::endl;
	}
}


// ------------ method called once each job just before starting event loop  ------------
	void 
MyCandPrintAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
	void 
MyCandPrintAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
	void 
MyCandPrintAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
	void 
MyCandPrintAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
	void 
MyCandPrintAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
	void 
MyCandPrintAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyCandPrintAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyCandPrintAnalyzer);
