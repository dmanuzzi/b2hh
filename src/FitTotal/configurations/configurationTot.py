config = {                                      
  'observables' : { 
    'fState'  : {
      'types' : [ ('KPI_Tot' ,101), ('PIPI_Tot',100),  ('KK_Tot'  ,102)] #is this right?         
#      'types' : [ ('KPI_Tot' ,31), ('PIPI_Tot',30),  ('KK_Tot'  ,32)] 
#      'types' : [ ('KPI_201516' ,201), ('PIPI_201516',200),  ('KK_201516'  ,202)]
    },
  },
  'bdkpi' : {
    'mass' : { 'Tot' : { 
        'delta'     : [0.00092968,-0.01,0.01,False],
        'mean'      : [5.2794,5.1,5.4,True],
        'sigma1'    : [0.018554,0.001,0.03,False],
        'sigma2'    : [0.030841,0.01,0.1,False],
        'alpha1'    : [0.70,0,5,True],
        'alpha2'    : [0.54,0,5,True],
        'frac'      : [0.77,0,1,True],
        'fracTail'  : [0.15,0,1,True] 
      },
    },
    'time' : { 'Tot' : { 
        'G'  : [0.65417,1,10,False],
        'dM' : [0.50650,0.1,1,False],
        'dG' : [0,-1,1,True] 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : [-0.0036,-0.05,0.05,True],
        'sigma'    : [0.04326,0,5,True],
        'sf_mean'  : [1,0,10,True],
        'sf_sigma' : [1,0.01,5,True] 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.37169,0,1,False],
          'p0'      : [0.39891,0.2,0.5,False],
          'p1'      : [0.92324,0.6,1.4,False],
          'epsAsym' : [-0.00833757,-1,1,False],
          'deltap0' : [0.014137,-0.5,0.5,False],
          'deltap1' : [0.020688,-0.5,0.5,False],
          'etaHat'  : [0.37,0,1,True] 
        },
        'SSk'  : { 
          'eps'     : [0.62690,0,2,False],
          'p0'      : [0.52941,0,1,False],
          'p1'      : [-0.339791,-2,2,False],
          'epsAsym' : [-0.000691886,-1,1,False],
          'deltap0' : [-0.0237541,-0.5,0.5,False],
          'deltap1' : [ 0.0054320,-0.1,0.1,False],
          'etaHat'  : [0.426449,0,1,True] 
        },
        'SS'   : { 
          'eps'     : [0.8,0,1,False],
          'p0'      : [0.48,0,1,False],
          'p1'      : [0.7,-3,3,False],
          'epsAsym' : [ -0.00229574,-1,1,False],
          'deltap0' : [0.0063415,-0.1,0.1,False],
          'deltap1' : [0.023247,-0.1,0.1,False],
          'etaHat'  : [0.44,0,1,True] 
        } 
      },
    },
    'CP' : { 'Tot' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : [0,-1,1,True],
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bd'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False]  },
  },
  'bskpi' : {
    'mass' : { 'Tot' : { 
        'delta'     : [0.0057,-0.007,0.007,True],
        'mean'      : [5.3669,5.1,5.4,True],
        'sigma1'    : 'bdkpi_mass_sigma1_Tot',
        'sigma2'    : 'bdkpi_mass_sigma2_Tot',
        'alpha1'    : [0.72,0,5,True],
        'alpha2'    : [0.53,0,5,True],
        'frac'      : 'bdkpi_mass_frac_Tot',
        'fracTail'  : [0.15,0,1,True] },
    },
    'time' : { 'Tot' : { 
        'G'  : [0.65620,0,10,True],
        'dM' : [17.757,0,30,True],
        'dG' : [0.081600,-1,1,True] 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', },
        'SSk'  : { 
          'eps'     : [0.2,0,1,False],
          'p0'      : [0.437,0,1,True],
          'p1'      : [0.66,-2,2,True],
          'epsAsym' : [0,-1,1,True],
          'deltap0' : [0,-0.1,0.1,True],
          'deltap1' : [0,-0.1,0.1,True],
          'etaHat'  : [0.426449,0,1,True] 
          },
          'SS'   : { 
            'eps'     : [0.8,0,1,False],
            'p0'      : [0.48,0,1,False],
            'p1'      : [0.7,-3,3,False],
            'epsAsym' : [0,-1,1,False],
            'deltap0' : [0,-0.1,0.1,False],
            'deltap1' : [0,-0.1,0.1,True],
            'etaHat'  : 'bdkpi_etaHatSS_Tot' 
          }
        },
      },
    'CP' : { 'Tot' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : 'bdkpi_Af_Tot',
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bs'] 
      },        
    },
    'acc' : { 'Tot' : [0.99,False] },
  },
  'bdpipi_kpi' : {
    'mass' : { 'Tot' : { 
        'resModel'  : 'bdkpi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 
        'G'  : 'bdpipi_G_Tot',
        'dM' : 'bdkpi_dM_Tot',
        'dG' : 'bdkpi_dG_Tot' 
      },        
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : 'bdpipi_epsOS_Tot',
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : 'bdpipi_epsSSk_Tot',
          'p0'      : 'bdkpi_p0SSk_Tot',
          'p1'      : 'bdkpi_p1SSk_Tot',
          'epsAsym' : 'bdkpi_epsAsymSSk_Tot',
          'deltap0' : 'bdkpi_deltap0SSk_Tot',
          'deltap1' : 'bdkpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : 'bdpipi_epsSS_Tot',
          'p0'      : 'bdkpi_p0SS_Tot',
          'p1'      : 'bdkpi_p1SS_Tot',
          'epsAsym' : 'bdkpi_epsAsymSS_Tot',
          'deltap0' : 'bdkpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 'C' : 'bdpipi_C_Tot',
                        'S'  : 'bdpipi_S_Tot',
                        'D'  : 'bdpipi_D_Tot',
                        'AP'  : 'bdkpi_AP_Tot',
                        'CPState' : ['CPtoFS','Bd'] },
          },
    'acc' : { 'Tot' : [0.99,False],
            },
  },
  'bskk_kpi' : {
    'mass' : { 'Tot' : { 
        'resModel'  : 'bdkpi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : {
        'G'  : 'bskpi_G_Tot',
        'dM' : 'bskpi_dM_Tot',
        'dG' : 'bskpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : 'bskk_epsOS_Tot',
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : 'bskk_epsSSk_Tot',
          'p0'      : 'bskpi_p0SSk_Tot',
          'p1'      : 'bskpi_p1SSk_Tot',
          'epsAsym' : 'bskpi_epsAsymSSk_Tot',
          'deltap0' : 'bskpi_deltap0SSk_Tot',
          'deltap1' : 'bskpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot' 
        },
        'SS'   : { 
          'eps'     : 'bskk_epsSS_Tot',
          'p0'      : 'bskpi_p0SS_Tot',
          'p1'      : 'bskpi_p1SS_Tot',
          'epsAsym' : 'bskpi_epsAsymSS_Tot',
          'deltap0' : 'bskpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot' 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'C' : 'bskk_C_Tot',
        'S'  : 'bskk_S_Tot',
        'D'  : 'bskk_D_Tot',
        'AP'  : 'bskpi_AP_Tot',
        'CPState' : ['CPtoFS','Bs'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False] },
  },
  'bdpipi' : {
    'mass' : { 'Tot' : { 
        'delta'     : [0.00092968,-0.01,0.01,False],#: 'bdkpi_mass_delta_Tot', ##modified
        'mean'      : 'bdkpi_mass_mean_Tot',
        'sigma1'    : [0.019,0.01,0.03,False],
        'sigma2'    : [0.035,0.01,0.05,False],
        'alpha1'    : [0.71,0,5,True],
        'alpha2'    : [0.54,0,5,True],
        'frac'      : [0.77,0,1,True],
        'fracTail'  : [0.16,0,1,True] 
      },
    },
    'time' : { 'Tot' : { #'G'  : 'bdkpi_G_Tot',
        'G'  : [0.6579,0.6,1,True],
        'dM' : 'bdkpi_dM_Tot',
        'dG' : 'bdkpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SSk_Tot',
          'p1'      : 'bdkpi_p1SSk_Tot',
          'epsAsym' : 'bdkpi_epsAsymSSk_Tot',
          'deltap0' : 'bdkpi_deltap0SSk_Tot',
          'deltap1' : 'bdkpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SS_Tot',
          'p1'      : 'bdkpi_p1SS_Tot',
          'epsAsym' : 'bdkpi_epsAsymSS_Tot',
          'deltap0' : 'bdkpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bdkpi_AP_Tot',
        'CPState' : ['CP','Bd'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False] },
  },
  'bspipi' : {
    'mass' : { 'Tot' : { 
        'delta'     : [0.00092968,-0.01,0.01,False],#: 'bskpi_mass_delta_Tot',##modified
        'mean'      : 'bskpi_mass_mean_Tot',
        'sigma1'    : 'bdpipi_mass_sigma1_Tot',
        'sigma2'    : 'bdpipi_mass_sigma2_Tot',
        'alpha1'    : [0.75,0,5,True],
        'alpha2'    : [0.54,0,5,True],
        'frac'      : 'bdpipi_mass_frac_Tot',
        'fracTail'  : [0.19,0,1,True] 
      },
    },
    'time' : { 'Tot' : { 
        'G'  : 'bskpi_G_Tot',
        'dM' : 'bskpi_dM_Tot',
        'dG' : 'bskpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : {  
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_Tot',
          'p1'      : 'bskpi_p1SSk_Tot',
          'epsAsym' : 'bskpi_epsAsymSSk_Tot',
          'deltap0' : 'bskpi_deltap0SSk_Tot',
          'deltap1' : 'bskpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SS_Tot',
          'p1'      : 'bskpi_p1SS_Tot',
          'epsAsym' : 'bskpi_epsAsymSS_Tot',
          'deltap0' : 'bskpi_deltap0SS_Tot',
          'deltap1' : 'bskpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bskpi_AP_Tot',
        'CPState' : ['CP','Bd'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False] },
  },
  'bdkpi_pipi' : {
    'mass' : { 'Tot' : { 
        'resModel'  : 'bdpipi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { #'G'  : 'bdkpi_G_Tot',
                          #'G'  : [0.65789,0,1,True],
        'G'  : 'bdpipi_G_Tot',
        'dM' : 'bdkpi_dM_Tot',
        'dG' : 'bdkpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      }, 
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.39,0,1,False],#'bdkpi_epsOS_Tot',
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : [0.6,0,1,False],#'bdkpi_epsSSk_Tot',
          'p0'      : 'bdkpi_p0SSk_Tot',
          'p1'      : 'bdkpi_p1SSk_Tot',
          'epsAsym' : 'bdkpi_epsAsymSSk_Tot',
          'deltap0' : 'bdkpi_deltap0SSk_Tot',
          'deltap1' : 'bdkpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : [0.8,0,1,False],#'bdkpi_epsSS_Tot',
          'p0'      : 'bdkpi_p0SS_Tot',
          'p1'      : 'bdkpi_p1SS_Tot',
          'epsAsym' : 'bdkpi_epsAsymSS_Tot',
          'deltap0' : 'bdkpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'ACP' : 'bdkpi_ACP_Tot',
        'Af'  : 'bdkpi_Af_Tot',
        'AP'  : 'bdkpi_AP_Tot',
        'CPState' : ['FStoCP','Bd'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False] },
  },
  'bskpi_pipi' : {
    'mass' : { 'Tot' : { 
        'resModel'  : 'bdpipi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { #'G'  : 'bdkpi_G_Tot',
                          #'G'  : [0.65789,0,1,True],
        'G'  : 'bskpi_G_Tot',
        'dM' : 'bskpi_dM_Tot',
        'dG' : 'bskpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      }, 
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.39,0,1,False],#'bdkpi_epsOS_Tot',
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : [0.6,0,1,False],#'bdkpi_epsSSk_Tot',
          'p0'      : 'bskpi_p0SSk_Tot',
          'p1'      : 'bskpi_p1SSk_Tot',
          'epsAsym' : 'bskpi_epsAsymSSk_Tot',
          'deltap0' : 'bskpi_deltap0SSk_Tot',
          'deltap1' : 'bskpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : [0.8,0,1,False],#'bdkpi_epsSS_Tot',
          'p0'      : 'bdkpi_p0SS_Tot',
          'p1'      : 'bdkpi_p1SS_Tot',
          'epsAsym' : 'bdkpi_epsAsymSS_Tot',
          'deltap0' : 'bdkpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'ACP' : 'bskpi_ACP_Tot',
        'Af'  : 'bdkpi_Af_Tot',
        'AP'  : 'bskpi_AP_Tot',
        'CPState' : ['FStoCP','Bd'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False] },
  },
  'bskk' : {
    'mass' : { 'Tot' : { 
        'delta'     : 'bskpi_mass_delta_Tot',##modified
        'mean'      : 'bskpi_mass_mean_Tot',
        'sigma1'    : [0.019,0.01,0.03,False],
        'sigma2'    : [0.019,0.01,0.03,False],
        'alpha1'    : [0.64,0,5,True],
        'alpha2'    : [0.51,0,5,True],
        'frac'      : [0.77,0,1,True],
        'fracTail'  : [0.12,0,1,True] 
      },
    },
    'time' : { 'Tot' : { #'G'  : [1.5226,1,3,False],
        'G'  : 'bskpi_G_Tot',
        'dM' : 'bskpi_dM_Tot',
        'dG' : 'bskpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_Tot',
          'p1'      : 'bskpi_p1SSk_Tot',
          'epsAsym' : [0,-1,1,False],
          'deltap0' : 'bskpi_deltap0SSk_Tot',
          'deltap1' : 'bskpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SS_Tot',
          'p1'      : 'bskpi_p1SS_Tot',
          'epsAsym' : 'bskpi_epsAsymSS_Tot',
          'deltap0' : 'bskpi_deltap0SS_Tot',
          'deltap1' : 'bskpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bskpi_AP_Tot',
        'CPState' : ['CP','Bs'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False], },
  },
  'bdkk' : {
    'mass' : { 'Tot' : { 
        'delta'     : 'bdkpi_mass_delta_Tot', ##modified
        'mean'      : 'bdkpi_mass_mean_Tot',
        'sigma1'    : 'bskk_mass_sigma1_Tot',
        'sigma2'    : 'bskk_mass_sigma2_Tot',
        'alpha1'    : [0.77,0,5,True],
        'alpha2'    : [0.53,0,5,True],
        'frac'      : 'bskk_mass_frac_Tot',
        'fracTail'  : 'bskk_mass_fracTail_Tot' },#[0.16,0,1,True] },
    },
    'time' : { 'Tot' : { 
        #'G'  : 'bdkpi_G_Tot',
        #'G'  : [0.65789,0,1,True],
        'G'  : 'bdpipi_G_Tot',
        'dM' : 'bdkpi_dM_Tot',
        'dG' : 'bdkpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : 'bdkpi_epsOS_Tot',#[0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', 
        },
        'SSk'  : { 
          'eps'     : 'bdkpi_epsSSk_Tot',#[0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SSk_Tot',
          'p1'      : 'bdkpi_p1SSk_Tot',
          'epsAsym' : 'bdkpi_epsAsymSSk_Tot',
          'deltap0' : 'bdkpi_deltap0SSk_Tot',
          'deltap1' : 'bdkpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', 
        },
        'SS'   : { 
          'eps'     : 'bdkpi_epsSS_Tot',#[0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SS_Tot',
          'p1'      : 'bdkpi_p1SS_Tot',
          'epsAsym' : 'bdkpi_epsAsymSS_Tot',
          'deltap0' : 'bdkpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', 
        },
      },
    },
    'CP' : { 'Tot' : { 
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bdkpi_AP_Tot',
        'CPState' : ['CP','Bs']
      },
    },
    'acc' : { 'Tot' : [0.99,False], },
  },
  'bdkpi_kk' : {
    'mass' : { 'Tot' : { 
        'resModel'  : 'bskk_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 
        #'G'  : 'bdkpi_G_Tot',
        #'G'  : [0.65789,0,1,True],
        'G'  : 'bdpipi_G_Tot',
        'dM' : 'bdkpi_dM_Tot',
        'dG' : 'bdkpi_dG_Tot' 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 
          'eps'     : [0.5,0,1,False],
          'p0'      : 'bdkpi_p0OS_Tot',
          'p1'      : 'bdkpi_p1OS_Tot',
          'epsAsym' : 'bdkpi_epsAsymOS_Tot',
          'deltap0' : 'bdkpi_deltap0OS_Tot',
          'deltap1' : 'bdkpi_deltap1OS_Tot',
          'etaHat'  : 'bdkpi_etaHatOS_Tot', },
        'SSk'  : { 
          'eps'     : [0.5,0,1,False],
          'p0'      : 'bdkpi_p0SSk_Tot',
          'p1'      : 'bdkpi_p1SSk_Tot',
          'epsAsym' : 'bdkpi_epsAsymSSk_Tot',
          'deltap0' : 'bdkpi_deltap0SSk_Tot',
          'deltap1' : 'bdkpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', },
        'SS'   : { 
          'eps'     : [0.5,0,1,False],
          'p0'      : 'bdkpi_p0SS_Tot',
          'p1'      : 'bdkpi_p1SS_Tot',
          'epsAsym' : 'bdkpi_epsAsymSS_Tot',
          'deltap0' : 'bdkpi_deltap0SS_Tot',
          'deltap1' : 'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', },
      },
    },
    'CP' : { 'Tot' : { 
        'ACP' : 'bdkpi_ACP_Tot',
        'Af'  : 'bdkpi_Af_Tot',
        'AP'  : 'bdkpi_AP_Tot',
        'CPState' : ['FStoCP','Bs'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False], },
  },
  'lbpk_kk' : {
    'mass' : { 'Tot' : { 
        'resModel'  : 'bskk_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 
        'G'  : [0.68210,0,1,True],
        'dM' : [0,-1,1,True],
        'dG' : [0,-1,1,True] 
      },
    },
    'timeErr' : { 'Tot' : { 
        'mean'     : 'bdkpi_timeErr_mean_Tot',
        'sigma'    : 'bdkpi_timeErr_sigma_Tot',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_Tot',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_Tot', 
      },
    },
    'tag'  : { 'Tot' : { 
        'OS'   : { 'eps'     : [0.37,0,1,False],
                    'p0'      : [0.5,0,1,True],#'bdkpi_p0OS_Tot',
                    'p1'      : [0,-1,1,True],#'bdkpi_p1OS_Tot',
                    'epsAsym' : [0,-1,1,True],#'bdkpi_epsAsymOS_Tot',
                    'deltap0' : [0,-1,1,True],#'bdkpi_deltap0OS_Tot',
                    'deltap1' : [0,-1,1,True],#'bdkpi_deltap1OS_Tot',
                    'etaHat'  : 'bdkpi_etaHatOS_Tot', },
        'SSk'  : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : [0.5,0,1,True],#'bdkpi_p0SSk_Tot',
          'p1'      : [0,-1,1,True],#'bdkpi_p1SSk_Tot',
          'epsAsym' : [0,-1,1,True],#'bdkpi_epsAsymSSk_Tot',
          'deltap0' : [0,-1,1,True],#'bdkpi_deltap0SSk_Tot',
          'deltap1' : [0,-1,1,True],#'bdkpi_deltap1SSk_Tot',
          'etaHat'  : 'bdkpi_etaHatSSk_Tot', },
        'SS'   : { 
          'eps'     : [0.8,0,1,False],
          'p0'      : [0.5,0,1,True],#'bdkpi_p0SS_Tot',
          'p1'      : [0,-1,1,True],#'bdkpi_p1SS_Tot',
          'epsAsym' : [0,-1,1,True],#'bdkpi_epsAsymSS_Tot',
          'deltap0' : [0,-1,1,True],#'bdkpi_deltap0SS_Tot',
          'deltap1' : [0,-1,1,True],#'bdkpi_deltap1SS_Tot',
          'etaHat'  : 'bdkpi_etaHatSS_Tot', },
      },
    },
    'CP' : { 'Tot' : { 
        'ACP' : [0,-1,1,True],
        'Af'  : [0,-1,1,True],
        'AP'  : [0,-1,1,True],
        'CPState' : ['FStoCP','Bs'] 
      },
    },
    'acc' : { 'Tot' : [0.99,False], },
  },
  'bkg_kpi' : {
    'mass' : { 'Tot' : { 
        'p0'      : [0,-100,100,False],
        'p1'      : [0,-100,100,False],
        'p2'      : [0,-100,100,False],
        'p0_11'   : [0,-100,100,False],
        'p1_11'   : [0,-100,100,False],
        'p2_11'   : [0,-100,100,False],
        'p0_10'   : [0,-100,100,False],
        'p1_10'   : [0,-100,100,False],
        'p2_10'   : [0,-100,100,False],
        'p0_01'   : [0,-100,100,False],
        'p1_01'   : [0,-100,100,False],
        'p2_01'   : [0,-100,100,False],
        'p0_00'   : [0,-100,100,False],
        'p1_00'   : [0,-100,100,False],
        'p2_00'   : [0,-100,100,False],
      },
    },
    'time' : { 'Tot' : { 
        #'frac11' : [-4.46323e-01,-10,1,False], 
        #'tau1_11' : [-4.46323e-01,-10,1,False],
        #'tau2_11' : [-1.79150e+00,-10,1,False],
        #'frac10' : [-4.46323e-01,-10,1,False], 
        #'tau1_10' : [-4.46323e-01,-10,1,False],
        #'tau2_10' : [-1.79150e+00,-10,1,False], 
        #'frac01' : [-4.46323e-01,-10,1,False], 
        #'tau1_01' : [-4.46323e-01,-10,1,False],
        #'tau2_01' : [-1.79150e+00,-10,1,False],
        #'frac00' : [-4.46323e-01,-10,1,False], 
        #'tau1_00' : [-4.46323e-01,-10,1,False],
        #'tau2_00' : [-1.79150e+00,-10,1,False],},
        'template' : True 
      },
    },
    'acc' : { 'Tot' : { 
        'c11' : [8.25233e-01,-10,10,False],
        'c10' : [5.38033e-01,-10,10,False],
        'c01' : [8.25233e-01,-10,10,False],
        'c00' : [5.38033e-01,-10,10,False],
      },
    },
    'tag' : { 'Tot' : { 
        'OS'  : { 
          'eps1' : [ 0.5,0,1,False],
          'epsAsym1' : [-0.01,-0.5,0.5,False],
          'eps0' : [ 0.5,0,1,False],
          'epsAsym0' : [-0.01,-0.5,0.5,False] 
        },
        'SSk' : { 
          'eps' : [0.57,0,1,False],
          'epsAsym' : [0.018,-0.5,0.5,False] 
        },
        'SS'  : { 
          'eps' : [0.57,0,1,False],
          'epsAsym' : [0.018,-0.5,0.5,False] 
        },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'bkg_pipi' : {
    'mass' : { 'Tot' : { 
        'p0'      : [0,-100,100,False],
        'p1'      : [0,-100,100,False],
        'p2'      : [0,-100,100,False],
        'p0_11'   : [0,-100,100,False],
        'p1_11'   : [0,-100,100,False],
        'p2_11'   : [0,-100,100,False],
        'p0_10'   : [0,-100,100,False],
        'p1_10'   : [0,-100,100,False],
        'p2_10'   : [0,-100,100,False],
        'p0_01'   : [0,-100,100,False],
        'p1_01'   : [0,-100,100,False],
        'p2_01'   : [0,-100,100,False],
        'p0_00'   : [0,-100,100,False],
        'p1_00'   : [0,-100,100,False],
        'p2_00'   : [0,-100,100,False],
      },
    },
    'time' : { 'Tot' : {
         #'frac11' : [-4.46323e-01,-10,1,False], 
        #'tau1_11' : [-4.46323e-01,-10,1,False],
        #'tau2_11' : [-1.79150e+00,-10,1,False],
        #'frac10' : [-4.46323e-01,-10,1,False], 
        #'tau1_10' : [-4.46323e-01,-10,1,False],
        #'tau2_10' : [-1.79150e+00,-10,1,False], 
        #'frac01' : [-4.46323e-01,-10,1,False], 
        #'tau1_01' : [-4.46323e-01,-10,1,False],
        #'tau2_01' : [-1.79150e+00,-10,1,False],
        #'frac00' : [-4.46323e-01,-10,1,False], 
        #'tau1_00' : [-4.46323e-01,-10,1,False],
        #'tau2_00' : [-1.79150e+00,-10,1,False],},
        'template' : True 
      },
    },
    'acc' : { 'Tot' : { 
        'c11' : [8.25233e-01,-10,10,False],
        'c10' : [5.38033e-01,-10,10,False],
        'c01' : [8.25233e-01,-10,10,False],
        'c00' : [5.38033e-01,-10,10,False],
      },
    },
    'tag' : { 'Tot' : { 
        'OS'  : { 
          'eps1' : [ 0.5,0,1,False],
          'epsAsym1' : [-0.01,-0.5,0.5,False],
          'eps0' : [ 0.5,0,1,False],
          'epsAsym0' : [-0.01,-0.5,0.5,False] 
        },
        'SSk' : { 
          'eps' : [0.57,0,1,False],
          'epsAsym' : [0.018,-0.5,0.5,False] 
        },
        'SS'  : { 
          'eps' : [0.57,0,1,False],
          'epsAsym' : [0.018,-0.5,0.5,False] 
        },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'bkg_kk' : {
    'mass' : { 'Tot' : { 
        'p0'      : [0,-100,100,False],
        'p1'      : [0,-100,100,False],
        'p2'      : [0,-100,100,False],
        'p0_11'   : [0,-100,100,False],
        'p1_11'   : [0,-100,100,False],
        'p2_11'   : [0,-100,100,False],
        'p0_10'   : [0,-100,100,False],
        'p1_10'   : [0,-100,100,False],
        'p2_10'   : [0,-100,100,False],
        'p0_01'   : [0,-100,100,False],
        'p1_01'   : [0,-100,100,False],
        'p2_01'   : [0,-100,100,False],
        'p0_00'   : [0,-100,100,False],
        'p1_00'   : [0,-100,100,False],
        'p2_00'   : [0,-100,100,False],
      },
    },
    'time' : { 'Tot' : {
         #'frac11' : [-4.46323e-01,-10,1,False], 
        #'tau1_11' : [-4.46323e-01,-10,1,False],
        #'tau2_11' : [-1.79150e+00,-10,1,False],
        #'frac10' : [-4.46323e-01,-10,1,False], 
        #'tau1_10' : [-4.46323e-01,-10,1,False],
        #'tau2_10' : [-1.79150e+00,-10,1,False], 
        #'frac01' : [-4.46323e-01,-10,1,False], 
        #'tau1_01' : [-4.46323e-01,-10,1,False],
        #'tau2_01' : [-1.79150e+00,-10,1,False],
        #'frac00' : [-4.46323e-01,-10,1,False], 
        #'tau1_00' : [-4.46323e-01,-10,1,False],
        #'tau2_00' : [-1.79150e+00,-10,1,False],},
        'template' : True 
      },
    },
    'acc' : { 'Tot' : { 
        'c11' : [8.25233e-01,-10,10,False],
        'c10' : [5.38033e-01,-10,10,False],
        'c01' : [8.25233e-01,-10,10,False],
        'c00' : [5.38033e-01,-10,10,False],
      },
    },
    'tag' : { 'Tot' : { 'OS'  : { 
          'eps1' : [ 0.5,0,1,False],
          'epsAsym1' : [-0.01,-0.5,0.5,False],
          'eps0' : [ 0.5,0,1,False],
          'epsAsym0' : [-0.01,-0.5,0.5,False] 
        },
        'SSk' : { 
          'eps' : [0.57,0,1,False],
          'epsAsym' : [0.018,-0.5,0.5,False] 
        },
        'SS'  : { 
          'eps' : [0.57,0,1,False],
          'epsAsym' : [0.018,-0.5,0.5,False] 
        },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'phys_kpi1' : {
    'mass' : { 'Tot' : { 
        'm0' : [5.1446,5,5.4,True],
        'cA' : [-20,-100,0,False],
        'resModel' : 'bdkpi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { 'Tot' : { 
        'a0' : [-4.46323e-01,-10,1,False],
        'b0' : [-1.79150e+00,-10,1,False],
        'c0'  : [-4.46323e-01,-10,1,False], 
        'a1' : [-4.46323e-01,-10,1,False],
        'b1' : [-1.79150e+00,-10,1,False],
        'c1'  : [-4.46323e-01,-10,1,False],
      },
    },
    'tag' : { 'Tot' : { 
        'OS'  : { 
          'eps'     : [ 0.5,0,1,False],
          'epsAsym' : [-0.01,-0.5,0.5,False],
        },
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym' : [-0.01,-0.5,0.5,False],
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym0' : [-0.01,-0.5,0.5,False] },
        'SSk' : { 
          'eps'      : [0.5,0,1,False],
          'epsAsym'  : [0.01,-0.5,0.5,False] 
        },
        'SS'  : { 
          'eps'      : [0.5,0,1,False],
          'epsAsym'  : [0.01,-0.5,0.5,False] 
        },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'phys_kpi2' : {
    'mass' : { 'Tot' : { 
        'm0' : [5.1446,5,5.4,True],
        'cA' : 'phys_kpi1_mass_cA_Tot',
        'resModel' : 'bskpi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { 'Tot' : { 
        'a0' : "phys_kpi1_a0_Tot",#[-4.46323e-01,-10,1,False],
        'b0' : "phys_kpi1_b0_Tot",#[-1.79150e+00,-10,1,False],
        'c0' : "phys_kpi1_c0_Tot",#[-4.46323e-01,-10,1,False], 
        'a1' : "phys_kpi1_a1_Tot",#[-4.46323e-01,-10,1,False],
        'b1' : "phys_kpi1_b1_Tot",#[-1.79150e+00,-10,1,False],
        'c1' : "phys_kpi1_c1_Tot",},#[-4.46323e-01,-10,1,False],},
    },
    'tag' : { 'Tot' : { 
        'OS'  : { 
          'eps'     : 'phys_kpi1_epsOS_Tot',#[ 0.5,0,1,False],
          'epsAsym' : 'phys_kpi1_epsAsymOS_Tot',},#[-0.01,-0.5,0.5,False],},
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym' : [-0.01,-0.5,0.5,False],
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym0' : [-0.01,-0.5,0.5,False] },
        'SSk' : { 
          'eps'      : 'phys_kpi1_epsSSk_Tot',#[0.5,0,1,False],
          'epsAsym'  : 'phys_kpi1_epsAsymSSk_Tot',},#[0.01,-0.5,0.5,False] },
        'SS'  : { 
          'eps'      : 'phys_kpi1_epsSS_Tot',#[0.5,0,1,False],
          'epsAsym'  : 'phys_kpi1_epsAsymSS_Tot',},#[0.01,-0.5,0.5,False] },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : 'phys_kpi1_ACP_Tot',
        'AtagOS' : 'phys_kpi1_AtagOS_Tot',
        'AtagSS' : 'phys_kpi1_AtagSS_Tot', 
      },
    },
  },
  'phys_pipi' : {
    'mass' : { 'Tot' : { 
        'm0' : 'phys_kpi1_mass_m0_Tot',
        'cA' : [-20,-100,0,False],
        'resModel' : 'bdpipi_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { 'Tot' : { 
        'a0' : [-4.46323e-01,-10,1,False],
        'b0' : [-1.79150e+00,-10,1,False],
        'c0'  : [-4.46323e-01,-10,1,False], 
        'a1' : [-4.46323e-01,-10,1,False],
        'b1' : [-1.79150e+00,-10,1,False],
        'c1'  : [-4.46323e-01,-10,1,False],
      },
    },
    'tag' : { 'Tot' : { 
        'OS'  : { 
          'eps'     : [ 0.5,0,1,False],
          'epsAsym' : [-0.01,-0.5,0.5,False],
        },
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym' : [-0.01,-0.5,0.5,False],
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym0' : [-0.01,-0.5,0.5,False] },
        'SSk' : { 
          'eps'      : [0.5,0,1,False],
          'epsAsym'  : [0.01,-0.5,0.5,False] 
        },
        'SS'  : { 
          'eps'      : [0.5,0,1,False],
          'epsAsym'  : [0.01,-0.5,0.5,False] 
        },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'phys_kk' : {
    'mass' : { 'Tot' : { 
        'm0' : 'phys_kpi2_mass_m0_Tot',
        'cA' : [-20,-100,0,False],
        'resModel' : 'bskk_mass_resModel_Tot' 
      },
    },
    'time' : { 'Tot' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { 'Tot' : { 
        'a0' : [-4.46323e-01,-10,1,False],
        'b0' : [-1.79150e+00,-10,1,False],
        'c0'  : [-4.46323e-01,-10,1,False], 
        'a1' : [-4.46323e-01,-10,1,False],
        'b1' : [-1.79150e+00,-10,1,False],
        'c1'  : [-4.46323e-01,-10,1,False],
      },
    },
    'tag' : { 'Tot' : { 
        'OS'  : { 
          'eps'     : [ 0.5,0,1,False],
          'epsAsym' : [-0.01,-0.5,0.5,False],
        },
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym' : [-0.01,-0.5,0.5,False],
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym0' : [-0.01,-0.5,0.5,False] },
        'SSk' : { 
          'eps'      : [0.5,0,1,False],
          'epsAsym'  : [0.01,-0.5,0.5,False] 
        },
        'SS'  : { 
          'eps'      : [0.5,0,1,False],
          'epsAsym'  : [0.01,-0.5,0.5,False] 
        },
      },
    },
    'CP'  : { 'Tot' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
}

