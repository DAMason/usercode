import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

#process.Tracer = cms.Service("Tracer",
#      sourceSeed = cms.untracked.string("$$")
#   )

SimpleMemoryCheck = cms.Service("SimpleMemoryCheck", ignoreTotal = cms.untracked.int32(1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.TFileService = cms.Service("TFileService", fileName = cms.string("Test.root"))
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/data/CRAFT09/Calo/RECO/v1/000/111/023/AC66AA31-278C-DE11-9D18-000423D98950.root'
    )
)

#process.demo = cms.EDAnalyzer('Crafty'
#)

#process.demo = cms.EDAnalyzer('Craft',
process.demo = cms.EDAnalyzer('Cruzet',
triggerResults = cms.InputTag("TriggerResults","","HLT"),
alternateTriggerResults = cms.InputTag("TriggerResults","","HLT")

)


process.hltrep = cms.EDAnalyzer("HLTrigReport")
process.hltrep.HLTriggerResults = cms.InputTag("TriggerResults","","HLT")

process.p = cms.Path(process.demo)

process.hltsum = cms.Path(process.hltrep)

