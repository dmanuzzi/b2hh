inputs = {
    'data'       : {},
    'effPID'     : {},
    'mass'       : { 'cross' : {}, 'bkg' : {}},
    'time'       : { 'bkg' : {}, 'phys' : {}},
    'tagging'    : {},
    'acceptance' : {},
    'fitParams'  : {},
    'outParams' : {},
}

import os
outPath= os.environ.get('B2HH_OUT')
confPath= os.environ.get('B2HH_CONFIG')

# Baseline
inputs['data']['path']          = outPath+'/Reduce/'
inputs['effPID']['path']        = outPath+'/PID/effB2HH/'
inputs['mass']['cross']['path'] = outPath+'/MassModels/CrossFeed/'
inputs['mass']['bkg']['path']   = outPath+'/TimeModels/params/'
inputs['time']['path']          = outPath+'/TimeModels/templateFiles/'
inputs['tagging']['path']       = outPath+'/Tagging/templates/'
inputs['acceptance']['path']    = outPath+'/AccSignal/acceptances/'
#inputs['fitParams']['path']     = confPath+'/{outdir}/'
inputs['fitParams']['path']     = confPath+'/{bdtName}_{bdtCut}_{year}_{magnet}/'
inputs['outParams']['path']     = outPath+'/FitTotal/{outdir}/'
inputs['outParams']['pathPlots']= inputs['outParams']['path']+'/plots/'



inputs['data']['file']          = inputs['data']['path']         +'b2hh_{bdtName}_{bdtCut}_{year}_{magnet}.root'
inputs['effPID']['file']        = inputs['effPID']['path']       +'pidEffs.db'
inputs['mass']['cross']['file'] = inputs['mass']['cross']['path']+'{fState}_{bdtName}_{bdtCut}_{pid}_{magnet}_{year}.root'
inputs['mass']['bkg']['file']   = inputs['mass']['bkg']['path']  +'params_bkg_{fState}_{bdtName}_{bdtCut}_{year}_{magnet}.txt'
inputs['time']['bkg']['file']   = inputs['time']['path']         +'templates_{fState}_{bdtName}_{bdtCut}_{year}_{magnet}.root'
inputs['time']['phys']['file']  = inputs['time']['path']         +'templatesPhys_{fState}_{bdtName}_{bdtCut}_{year}_{magnet}.root'
inputs['tagging']['file']       = inputs['tagging']['path']      +'{fState}_{bdtName}_{bdtCut}_{year}_{magnet}.root'
inputs['acceptance']['file']    = inputs['acceptance']['path']   +'acceptancesNew_{bdtName}_{bdtCut}_{year}_{magnet}_{channel}_{suffix}.root'
inputs['fitParams']['file']     = inputs['fitParams']['path']    +'input_params_{bdtName}_{bdtCut}_{taggers}_{magnet}.txt.{blindState}'
inputs['outParams']['filePar']  = inputs['outParams']['path']    +'params_{bdtName}_{bdtCut}_{taggers}_{magnet}.txt.{blindState}'
inputs['outParams']['fileRes']  = inputs['outParams']['path']    +'params_{bdtName}_{bdtCut}_{taggers}_{magnet}.{blindState}.root'
inputs['outParams']['plot']     = inputs['outParams']['pathPlots']+'{var}_{rangePlot}_{state}_{bdtName}_{bdtCut}_{Btag}_{Ftag}_{Atag}.root'

