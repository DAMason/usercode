import FWCore.ParameterSet.Config as cms

process = cms.Process("Dave")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/data/Run2010B/Jet/RECO/Dec22ReReco_v1//0046/F2B43CBF-B51A-E011-AE67-003048C692B4.root'
    )
)


process.GlobalTag.globaltag = 'GR_R_311_V1::All'
#process.GlobalTag.globaltag = 'GR_R_38X_V15::All'


process.TFileService = cms.Service("TFileService",fileName = cms.string('TestTree.root'))

process.dave = cms.EDAnalyzer('TreeMaker',
     TreeName      =   cms.untracked.string('DoesntMatterYet'),
     IsMonteCarlo  =   cms.untracked.bool(False),
     CaloJetTag    =   cms.untracked.string('ak5CaloJets'),
     CaloJECServiceName = cms.untracked.string('ak5CaloL2L3Residual'),
     #CaloJECL2Tag  =   cms.untracked.string('Spring10_L2_Relative_AK5Calo'),
     #CaloJECL3Tag  =   cms.untracked.string('Spring10_L2_Absolute_AK5Calo'),
     #CaloJECResTag =   cms.untracked.string('Spring10DataV2_L2L3Residual_AK5Calo'),
     #CaloJECUncertTag =   cms.untracked.string('Spring10DataV2_Uncertainty_AK5Calo'),
     CaloJetThresh =   cms.untracked.double(10.0),
     PFJetTag    =   cms.untracked.string('ak5PFJets'),
     #PFJECL2Tag  =   cms.untracked.string('Spring10_L2_Relative_AK5PF'),
     #PFJECL3Tag  =   cms.untracked.string('Spring10_L2_Absolute_AK5PF'),
     #PFJECResTag =   cms.untracked.string('Spring10DataV2_L2L3Residual_AK5PF'),
     #PFJECUncertTag =   cms.untracked.string('Spring10DataV2_Uncertainty_AK5PF'),
     PFJECServiceName = cms.untracked.string('ak5PFL2L3Residual'),
     PFJetThresh =   cms.untracked.double(15.0),

     HLTTriggers =   cms.untracked.vstring(),
     L1Triggers  =   cms.untracked.vstring() 

)

process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.p = cms.Path(process.dave)
