import FWCore.ParameterSet.Config as cms

process = cms.Process("Dave")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        '/store/data/Run2010B/Jet/RECO/Dec22ReReco_v1//0046/F2B43CBF-B51A-E011-AE67-003048C692B4.root'
 
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_0.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1000.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_100.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1025.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1050.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1075.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1100.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1125.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1150.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1175.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1200.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1225.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1250.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_125.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1275.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1300.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1325.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1350.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1375.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1400.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1425.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1450.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1475.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1500.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_150.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1525.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1550.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1575.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1600.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1625.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1650.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1675.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1700.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1725.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1750.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_175.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1775.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1800.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1825.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1850.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1875.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1900.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1925.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1950.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_1975.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_2000.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_200.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_2025.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_2050.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_2075.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_2100.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_2125.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_225.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_250.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_25.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_275.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_300.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_325.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_350.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_375.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_400.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_425.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_450.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_475.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_500.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_50.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_525.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_550.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_575.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_600.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_625.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_650.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_675.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_700.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_725.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_750.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_75.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_775.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_800.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_825.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_850.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_875.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_900.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_925.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_950.root',
#'dcap:///pnfs/cms/WAX/resilient/dmason/try4_20PU/conlsp_/reco/reco_820_800_400_975.root'

'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_0.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_100.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1000.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1100.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1200.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1300.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1400.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1500.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1600.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1700.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1800.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_1900.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_200.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_2000.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_2100.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_300.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_400.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_500.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_600.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_700.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_800.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/try3/conlsp_/reco/reco_820_800_400_900.root'

    )
)


process.GlobalTag.globaltag = 'GR_R_311_V1::All'
#process.GlobalTag.globaltag = 'GR_R_38X_V15::All'


process.TFileService = cms.Service("TFileService",fileName = cms.string('TestTree.root'))

process.dave = cms.EDAnalyzer('TreeMaker',
     TreeName      =   cms.untracked.string('DoesntMatterYet'),
     IsMonteCarlo  =   cms.untracked.bool(False),
     CaloJetTag    =   cms.untracked.string('ak5CaloJets'),
     CaloJetIDTag  =   cms.untracked.string('ak5JetID'),
     CaloJetExtenderTag = cms.untracked.string('ak5JetExtender'),
     CaloJECServiceName = cms.untracked.string('ak5CaloL2L3Residual'),
     CaloJetDetails   =   cms.untracked.bool(True),
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
     L1Triggers  =   cms.untracked.vstring(),

     PhotonTag   =   cms.untracked.string('photons'),
     PhotonDetails   =   cms.untracked.bool(True),
     PhotonThresh=   cms.untracked.double(10.0) 

)

process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.p = cms.Path(process.dave)
