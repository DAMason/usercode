import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

#process.Tracer = cms.Service("Tracer",
#      sourceSeed = cms.untracked.string("$$")
#   )

SimpleMemoryCheck = cms.Service("SimpleMemoryCheck", ignoreTotal = cms.untracked.int32(1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.TFileService = cms.Service("TFileService", fileName = cms.string("CRAFTuple.CaloReRecoRun109524b.root"))
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/data/CRAFT09/Calo/RECO/CRAFT09_R_V4_CosmicsSeq_v2/0056/C865151D-DFBC-DE11-B895-0018F3D095EE.root'
    )
)


process.demo = cms.EDAnalyzer('Craft',
triggerResults = cms.InputTag("TriggerResults","","HLT"),
alternateTriggerResults = cms.InputTag("TriggerResults","","HLT")

)


process.hltrep = cms.EDAnalyzer("HLTrigReport")
process.hltrep.HLTriggerResults = cms.InputTag("TriggerResults","","HLT")

process.p = cms.Path(process.demo)

process.hltsum = cms.Path(process.hltrep)

