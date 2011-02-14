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

'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_0.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_100.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1000.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1100.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1200.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1300.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1400.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1500.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1600.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1700.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1800.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_1900.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_200.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_2000.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_2100.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_2200.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_2300.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_2400.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_300.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_400.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_500.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_600.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_700.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_800.root',
'dcap:///pnfs/cms/WAX/resilient/dmason/fifthgrid_noPU/winoNLSPout_/reco/800_700_300/reco_800_700_300_900.root'

    )
)


#process.GlobalTag.globaltag = 'GR_R_311_V1::All'
#process.GlobalTag.globaltag = 'GR_R_38X_V15::All'
process.GlobalTag.globaltag = 'L1HLTST311_V0::All'


process.TFileService = cms.Service("TFileService",fileName = cms.string('TestTree.root'))

process.dave = cms.EDAnalyzer('TreeMaker',
     TreeName      =   cms.untracked.string('DoesntMatterYet'),
     IsMonteCarlo  =   cms.untracked.bool(False),
     CaloJetTag    =   cms.untracked.string('ak5CaloJets'),
     CaloJetIDTag  =   cms.untracked.string('ak5JetID'),
     CaloJetExtenderTag = cms.untracked.string('ak5JetExtender'),
     CaloJECServiceName = cms.untracked.string('ak5CaloL2L3Residual'),
     CaloJetDetails   =   cms.untracked.bool(True),
     CaloJetThresh =   cms.untracked.double(10.0),
     PFJetTag    =   cms.untracked.string('ak5PFJets'),
     PFJECServiceName = cms.untracked.string('ak5PFL2L3Residual'),
     PFJetThresh =   cms.untracked.double(15.0),
     TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
     L1GTReadoutTag = cms.untracked.InputTag('gtDigis'),
     L1GTObjectMapTag = cms.untracked.InputTag('hltL1GtObjectMap','','HLT'),
     L1Triggers =   cms.untracked.vstring(),
     HLTTriggers  =   cms.untracked.vstring('HLT_Photon30_CaloIdVL_v1', 'HLT_Photon30_CaloIdVL_IsoL_v1', 'HLT_Photon75_CaloIdVL_v1', 'HLT_Photon75_CaloIdVL_IsoL_v1', 'HLT_Photon125_NoSpikeFilter_v1', 'HLT_DoublePhoton5_IsoVL_CEP_v1', 'HLT_DoublePhoton32_CaloIdL_v1', 'HLT_DoublePhoton33_v1,HLT_Photon26_Photon18_v1', 'HLT_Photon26_IsoL_Photon18_v1', 'HLT_Photon26_IsoVL_Photon18_v1', 'HLT_Photon26_IsoVL_Photon18_IsoVL_v1', 'HLT_Photon26_CaloIdL_IsoVL_Photon18_v1', 'HLT_Photon26_CaloIdL_IsoVL_Photon18_CaloIdL_IsoVL_v1', 'HLT_Photon32_Photon26_CaloIdL_v1', 'HLT_Photon32_CaloIdL_Photon26_CaloIdL_v1','HLT_HT160_v1', 'HLT_HT240_v1', 'HLT_HT260_MHT60_v1', 'HLT_HT300_v1', 'HLT_HT300_MHT75_v1', 'HLT_HT360_v1', 'HLT_HT440_v1', 'HLT_HT520_v1', 'HLT_PFMHT80_v1', 'HLT_PFMHT150_v1', 'HLT_MET100_v1', 'HLT_MET120_v1', 'HLT_MET200_v1'),

     PhotonTag   =   cms.untracked.string('photons'),
     PhotonDetails   =   cms.untracked.bool(True),
     PhotonThresh=   cms.untracked.double(10.0) 

)

process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.p = cms.Path(process.dave)
