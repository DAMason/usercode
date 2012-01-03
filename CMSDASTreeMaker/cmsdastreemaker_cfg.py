import FWCore.ParameterSet.Config as cms

process = cms.Process("Tuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


# calculate rho & jetArea
process.load('RecoJets.Configuration.RecoPFJets_cff')
process.kt6PFJets.doRhoFastjet = True
#process.ak5PFJets.doAreaFastjet = True


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/data/Run2011A/Photon/AOD/PromptReco-v6/000/173/692/74D4CEDE-B2CE-E011-94C3-0030487A17B8.root',
        '/store/data/Run2011B/Photon/AOD/PromptReco-v1/000/178/724/8433EE5E-9CF9-E011-AFEE-BCAEC5329714.root'
#         'file:///uscmst1b_scratch/lpc1/old_scratch/lpceg/yurii/iraklis/CMSDAS2012/multiphoton-Mpp200.root'
    )
)
process.TFileService = cms.Service("TFileService",fileName = cms.string('TestTreephoton20.root'))

process.GlobalTag.globaltag = 'GR_R_42_V21A::All'

process.tuple = cms.EDAnalyzer('CMSDASTreeMaker',
     TreeName      =   cms.untracked.string('DoesntMatterYet'),
#     IsMonteCarlo  =   cms.untracked.bool(True),
     IsMonteCarlo  =   cms.untracked.bool(False),
     TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
     L1GTReadoutTag = cms.untracked.InputTag('gtDigis'),
     L1GTObjectMapTag = cms.untracked.InputTag('hltL1GtObjectMap','','HLT'),
     L1Triggers =   cms.untracked.vstring(),
     HLTTriggers  =   cms.untracked.vstring('HLT_Photon30_CaloIdVL','HLT_Photon50_CaloIdVL','HLT_Photon75_CaloIdVL','HLT_Photon90_CaloIdVL','HLT_Photon135'),
     PhotonTag   =   cms.untracked.string('photons'),
     PhotonDetails   =   cms.untracked.bool(True),
     PhotonThresh=   cms.untracked.double(20.0),
     PFCandidateTag = cms.untracked.string('particleFlow'),
     PFCandidateThresh = cms.untracked.double(15.0),
     VertexTag = cms.untracked.string('offlinePrimaryVertices')
)



process.p = cms.Path(process.kt6PFJets * process.tuple)


