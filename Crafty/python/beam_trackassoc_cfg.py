import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

#process.Tracer = cms.Service("Tracer",
#      sourceSeed = cms.untracked.string("$$")
#   )

SimpleMemoryCheck = cms.Service("SimpleMemoryCheck", ignoreTotal = cms.untracked.int32(1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.TFileService = cms.Service("TFileService", fileName = cms.string("BeamTuple.root"))
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


#############   Jet - tracks association #############
from TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi import *
from RecoJets.JetAssociationProducers.j2tParametersVX_cfi import *
from RecoJets.JetAssociationProducers.j2tParametersCALO_cfi import *   
 
process.ak5JTAVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
     j2tParametersVX,
     jets         = cms.InputTag("iterativeCone5CaloJets")
)
process.ak5JTACalo = cms.EDProducer("JetTracksAssociatorAtCaloFace",
     j2tParametersCALO,
     jets         = cms.InputTag("iterativeCone5CaloJets")
)
process.JetExtender = cms.EDProducer("JetExtender",
     jets             = cms.InputTag("iterativeCone5CaloJets"), 
     jet2TracksAtCALO = cms.InputTag("ak5JTACalo"),
     jet2TracksAtVX   = cms.InputTag("ak5JTAVertex"),
     coneSize         = cms.double(0.5)

)


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        '/store/data/CRAFT09/Calo/RECO/v1/000/111/023/AC66AA31-278C-DE11-9D18-000423D98950.root'
#'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/960/385887B0-8EDC-DE11-ABEC-000423D98FBC.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/02E8544C-70D8-DE11-85CF-001617C3B66C.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/4CAB3B6C-6BD8-DE11-845C-000423D9890C.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/7C7495C2-71D8-DE11-ACF2-001D09F248F8.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/9264A28F-87D8-DE11-83A1-001D09F24763.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/EE7B1AC4-6CD8-DE11-97BB-0030487A1FEC.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/F4387297-74D8-DE11-996C-001D09F24F1F.root',
'/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/F62B040F-6CD8-DE11-9007-001D09F24664.root',

    )
)


process.demo = cms.EDAnalyzer('Beam',
triggerResults = cms.InputTag("TriggerResults","","HLT"),
alternateTriggerResults = cms.InputTag("TriggerResults","","HLT")

)


process.hltrep = cms.EDAnalyzer("HLTrigReport")
process.hltrep.HLTriggerResults = cms.InputTag("TriggerResults","","HLT")

process.p = cms.Path(process.ak5JTAVertex * process.ak5JTACalo * process.JetExtender * process.demo)

process.hltsum = cms.Path(process.hltrep)

