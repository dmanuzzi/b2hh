config = {
    'generate' : { 
        'flag' : True,
        'NToys' : 10 
    },
    'blind'    : {
        'bdpipi_C_201516'  : 'B2hhLegacy_Cpipi',
        'bdpipi_S_201516'  : 'B2hhLegacy_Spipi',
        'bskk_C_201516'    : 'B2hhLegacy_CKK',
        'bskk_S_201516'    : 'B2hhLegacy_SKK',
        'bskk_D_201516'    : 'B2hhLegacy_ADGKK',
        'bdkpi_ACP_20151618' : 'B2hhLegacy_ACPBd',
        'bdkpi_ACP_201516' : 'B2hhLegacy_ACPBd',
        'bdkpi_ACP_2017' : 'B2hhLegacy_ACPBd',
        'bdkpi_ACP_2017s29r2p2' : 'B2hhLegacy_ACPBd',
        'bdkpi_ACP_2018'  : 'B2hhLegacy_ACPBd',
        'bskpi_ACP_20151618' : 'B2hhLegacy_ACPBs',
        'bskpi_ACP_201516' : 'B2hhLegacy_ACPBs',
        'bskpi_ACP_2017' : 'B2hhLegacy_ACPBs',
        'bskpi_ACP_2017s29r2p2' : 'B2hhLegacy_ACPBs',
        'bskpi_ACP_2018'  : 'B2hhLegacy_ACPBs' 
    },
    'observables' : { 
        'mass'    : { 
            'range' : [5.0,6.2], 'binnings' : { 'cache' : 10000 },
            'units' : 'GeV/#it{c}^{2}' 
        },
        'time'    : { 
            'range' : [0.2,2.2], 'binnings' : {},
#            'range' : [0.2,10.2], 'binnings' : {},
            #'range' : [1.2,14.2], 'binnings' : {},
            #'range' : [1.5,14.2], 'binnings' : {},
            'units' : 'ps' },
        'etaOS'   : { 
            'range' : [0,0.5], 'binnings' : {} 
        },
        'etaSSk'  : { 
            'range' : [0,0.5], 'binnings' : {} 
        },
        'etaSS'   : { 
            'range' : [0,0.5], 'binnings' : {} 
        },
        'qOS'     : { 'types' : [ ('B',1), ('Bbar',-1), ('Untag',0)           ] },
        'qSSk'    : { 'types' : [ ('B',1), ('Bbar',-1), ('Untag',0)           ] },
        'qSS'     : { 'types' : [ ('B',1), ('Bbar',-1), ('Untag',0)           ] },
        'p'       : { 'types' : [ ('kpi',1), ('pik',-1), ('pipi',0), ('kk',2) ] },
        'fState'  : { 'types' : [] },
    }
}

def mergeDictionaries(dA, dB):
    import copy
    d = copy.deepcopy(dA)
    d2 = copy.deepcopy(dB)    
    for k in d2.keys():
        if k not in d.keys():
            d[k] = copy.deepcopy(d2[k])
        else:
            if type(d[k]) != type(d2[k]):
                print('configuration: mergeDictionaries: ERROR!\n'
                      '    different types for analogous dict values')
            if type(d2[k]) != dict:
                d[k] += d2[k]
            else:
                d[k] = copy.deepcopy(mergeDictionaries(d[k], d2[k]))
    return d 

from configuration20151618 import config as config20151618
from configuration201516 import config as config201516
from configuration2017 import config as config2017
from configuration2018alone import config as config2018
from configuration2017s29r2p2alone import config as config2017s29r2p2

def getConfigs(splitConf):
    tmpD_201516 = mergeDictionaries(config, config201516)
    tmpD_2018 = mergeDictionaries(config, config2018)
    tmpD_2017s29r2p2 = mergeDictionaries(config, config2017s29r2p2)
    if splitConf == '201516': 
        return tmpD_201516
    elif splitConf == '2018': 
        return tmpD_2018
    elif splitConf == '2017s29r2p2':
        return tmpD_2017s29r2p2
    elif splitConf == '201516_2017':
        return mergeDictionaries(tmpD_201516, config2017)
    elif splitConf == '201516_2018':
        return mergeDictionaries(tmpD_201516, config2018)
    elif splitConf == '2017':
        outD = mergeDictionaries(tmpD_201516, config2017)
        outD['observables']['fState']['types'] = [ t for t in outD['observables']['fState']['types'] if '_2017' in t[0] ]
        return outD
    # elif splitConf == '2018':
    #     outD = mergeDictionaries(tmpD_201516, config2018)
    #     outD['observables']['fState']['types'] = [ t for t in outD['observables']['fState']['types'] if '_2018' in t[0] ]
    #     return outD
    elif splitConf == '20151618':
        outD = mergeDictionaries(tmpD_201516, config20151618)
        outD['observables']['fState']['types'] = [ t for t in outD['observables']['fState']['types'] if '_20151618' in t[0] ]
        return outD
    elif splitConf == '20151618_2017':
        tmpDD = mergeDictionaries(tmpD_201516, config20151618)
        outD = mergeDictionaries(tmpDD, config2017)
        outD['observables']['fState']['types'] = [ t for t in outD['observables']['fState']['types'] if t[0].__contains__('_20151618') or t[0].__contains__('_2017') ]
        return outD
    else : 
        return None
    
    
    
        
        
         
