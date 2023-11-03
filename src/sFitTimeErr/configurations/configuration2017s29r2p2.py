config = { 
  'observables' : { 
    'fState'  : { 
      'types' : [ ('KK_2017s29r2p2'  ,22)] 
    },
  },
  'bdkpi' : {
    'mass' : { '2017s29r2p2' : { 
        'delta'     : 'bdkpi_mass_delta_201516',
        'mean'      : 'bdkpi_mass_mean_201516',
        'sigma1'    : [0.018554,0.001,0.03,False],
        'sigma2'    : [0.030841,0.01,0.1,False],
        'alpha1'    : [0.70,0,5,True],
        'alpha2'    : [0.54,0,5,True],
        'frac'      : [0.77,0,1,True],
        'fracTail'  : [0.15,0,1,True] 
      },
    },
    'time' : { '2017s29r2p2' : { 
        'G'  : 'bdkpi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516',
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : [-0.0036,-0.05,0.05,True],
        'sigma'    : [0.04326,0,5,True],
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516',
      },
    },
    'tag'  : { '2017s29r2p2' : { 
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
    'CP' : { '2017s29r2p2' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : 'bdkpi_Af_201516',
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bd'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False]  },
  },
  'bskpi' : {
    'mass' : { '2017s29r2p2' : { 
        'delta'     : 'bskpi_mass_delta_201516',
        'mean'      : 'bskpi_mass_mean_201516',
        'sigma1'    : 'bdkpi_mass_sigma1_2017s29r2p2',
        'sigma2'    : 'bdkpi_mass_sigma2_2017s29r2p2',
        'alpha1'    : [0.72,0,5,True],
        'alpha2'    : [0.53,0,5,True],
        'frac'      : 'bdkpi_mass_frac_201516',
        'fracTail'  : [0.15,0,1,True] },
    },
    'time' : { '2017s29r2p2' : { 
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516', 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', },
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
            'etaHat'  : 'bdkpi_etaHatSS_201516' 
          }
        },
      },
    'CP' : { '2017s29r2p2' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : 'bdkpi_Af_201516',
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bs'] 
      },        
    },
    'acc' : { '2017s29r2p2' : [0.99,False] },
  },
  'bdpipi_kpi' : {
    'mass' : { '2017s29r2p2' : { 
        'resModel'  : 'bdkpi_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 
        'G'  : 'bdpipi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },        
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : 'bdpipi_epsOS_2017s29r2p2',
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : 'bdpipi_epsSSk_2017s29r2p2',
          'p0'      : 'bdkpi_p0SSk_2017s29r2p2',
          'p1'      : 'bdkpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', 
        },
        'SS'   : { 
          'eps'     : 'bdpipi_epsSS_2017s29r2p2',
          'p0'      : 'bdkpi_p0SS_2017s29r2p2',
          'p1'      : 'bdkpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 'C' : 'bdpipi_C_201516',
                        'S'  : 'bdpipi_S_201516',
                        'D'  : 'bdpipi_D_201516',
                        'AP'  : 'bdkpi_AP_2017s29r2p2',
                        'CPState' : ['CPtoFS','Bd'] },
          },
    'acc' : { '2017s29r2p2' : [0.99,False],
            },
  },
  'bskk_kpi' : {
    'mass' : { '2017s29r2p2' : { 
        'resModel'  : 'bdkpi_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : {
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : 'bskk_epsOS_2017s29r2p2',
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : 'bskk_epsSSk_2017s29r2p2',
          'p0'      : 'bskpi_p0SSk_2017s29r2p2',
          'p1'      : 'bskpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bskpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bskpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bskpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bskpi_etaHatSSk_2017s29r2p2' 
        },
        'SS'   : { 
          'eps'     : 'bskk_epsSS_2017s29r2p2',
          'p0'      : 'bskpi_p0SS_2017s29r2p2',
          'p1'      : 'bskpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bskpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bskpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516' 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'C' : 'bskk_C_201516',
        'S'  : 'bskk_S_201516',
        'D'  : 'bskk_D_201516',
        'AP'  : 'bskpi_AP_2017s29r2p2',
        'CPState' : ['CPtoFS','Bs'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False] },
  },
  'bdpipi' : {
    'mass' : { '2017s29r2p2' : { 
        'delta'     : 'bdkpi_mass_delta_201516',
        'mean'      : 'bdkpi_mass_mean_201516',
        'sigma1'    : [0.019,0.01,0.03,False],
        'sigma2'    : [0.035,0.01,0.05,False],
        'alpha1'    : [0.71,0,5,True],
        'alpha2'    : [0.54,0,5,True],
        'frac'      : 'bdkpi_mass_frac_201516',
        'fracTail'  : [0.16,0,1,True] 
      },
    },
    'time' : { '2017s29r2p2' : { #'G'  : 'bdkpi_G_201516',
        'G'  : 'bdpipi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SSk_2017s29r2p2',
          'p1'      : 'bdkpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SS_2017s29r2p2',
          'p1'      : 'bdkpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'C'       : 'bdpipi_C_201516',
        'S'       : 'bdpipi_S_201516',
        'D'       : 'bdpipi_D_201516',
        'AP'      : 'bdkpi_AP_2017s29r2p2',
        'CPState' : ['CP','Bd'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False] },
  },
  'bspipi' : {
    'mass' : { '2017s29r2p2' : { 
        'delta'     : 'bskpi_mass_delta_201516',
        'mean'      : 'bskpi_mass_mean_201516',
        'sigma1'    : 'bdpipi_mass_sigma1_2017s29r2p2',
        'sigma2'    : 'bdpipi_mass_sigma2_2017s29r2p2',
        'alpha1'    : [0.75,0,5,True],
        'alpha2'    : [0.54,0,5,True],
        'frac'      : 'bdkpi_mass_frac_201516',
        'fracTail'  : [0.19,0,1,True] 
      },
    },
    'time' : { '2017s29r2p2' : { 
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : {  
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_2017s29r2p2',
          'p1'      : 'bskpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bskpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bskpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bskpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SS_2017s29r2p2',
          'p1'      : 'bskpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bskpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bskpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bskpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'C'       : 'bspipi_C_201516',
        'S'       : 'bspipi_S_201516',
        'D'       : 'bspipi_D_201516',
        'AP'      : 'bskpi_AP_2017s29r2p2',
        'CPState' : ['CP','Bd'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False] },
  },
  'bdkpi_pipi' : {
    'mass' : { '2017s29r2p2' : { 
        'resModel'  : 'bdpipi_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { #'G'  : 'bdkpi_G_201516',
                          #'G'  : [0.65789,0,1,True],
        'G'  : 'bdpipi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      }, 
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.39,0,1,False],#'bdkpi_epsOS_2017s29r2p2',
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : [0.6,0,1,False],#'bdkpi_epsSSk_2017s29r2p2',
          'p0'      : 'bdkpi_p0SSk_2017s29r2p2',
          'p1'      : 'bdkpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', 
        },
        'SS'   : { 
          'eps'     : [0.8,0,1,False],#'bdkpi_epsSS_2017s29r2p2',
          'p0'      : 'bdkpi_p0SS_2017s29r2p2',
          'p1'      : 'bdkpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'ACP' : 'bdkpi_ACP_2017s29r2p2',
        'Af'  : 'bdkpi_Af_201516',
        'AP'  : 'bdkpi_AP_2017s29r2p2',
        'CPState' : ['FStoCP','Bd'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False] },
  },
  'bskk' : {
    'mass' : { '2017s29r2p2' : { 
        'delta'     : 'bskpi_mass_delta_201516',
        'mean'      : 'bskpi_mass_mean_201516',
        'sigma1'    : [0.019,0.01,0.03,False],
        'sigma2'    : [0.019,0.01,0.03,False],
        'alpha1'    : [0.64,0,5,True],
        'alpha2'    : [0.51,0,5,True],
        'frac'      : 'bdkpi_mass_frac_201516',
        'fracTail'  : [0.12,0,1,True] 
      },
    },
    'time' : { '2017s29r2p2' : { #'G'  : [1.5226,1,3,False],
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_2017s29r2p2',
          'p1'      : 'bskpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bskpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bskpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bskpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SS_2017s29r2p2',
          'p1'      : 'bskpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bskpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bskpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bskpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        # 'AMP'     : [0.5,0,1,False],
        'PHI'     : [3.14/4.,0,2*3.141592653589793, False],
        # 'C'       : [0.25,-1,1,False],
        # 'S'       : [0.25,-1,1,False],
        # 'D'       : [0.25,-1,1,False],
        'AMP'       : 'bskk_AMP_201516',
        # 'C'       : 'bskk_C_201516',
        # 'S'       : 'bskk_S_201516',
        'D'       : 'bskk_D_201516',
        'AP'      : 'bskpi_AP_2017s29r2p2',
        'CPState' : ['CP','Bs'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False], },
  },
  'bdkk' : {
    'mass' : { '2017s29r2p2' : { 
        'delta'     : 'bdkpi_mass_delta_201516',
        'mean'      : 'bdkpi_mass_mean_201516',
        'sigma1'    : 'bskk_mass_sigma1_2017s29r2p2',
        'sigma2'    : 'bskk_mass_sigma2_2017s29r2p2',
        'alpha1'    : [0.77,0,5,True],
        'alpha2'    : [0.53,0,5,True],
        'frac'      : 'bdkpi_mass_frac_201516',
        'fracTail'  : 'bskk_mass_fracTail_201516' },#[0.16,0,1,True] },
    },
    'time' : { '2017s29r2p2' : { 
        #'G'  : 'bdkpi_G_201516',
        #'G'  : [0.65789,0,1,True],
        'G'  : 'bdpipi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : 'bdkpi_epsOS_2017s29r2p2',#[0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : 'bdkpi_epsSSk_2017s29r2p2',#[0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SSk_2017s29r2p2',
          'p1'      : 'bdkpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', 
        },
        'SS'   : { 
          'eps'     : 'bdkpi_epsSS_2017s29r2p2',#[0.33097,0,1,False],
          'p0'      : 'bdkpi_p0SS_2017s29r2p2',
          'p1'      : 'bdkpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'C'       : 'bdkk_C_201516',
        'S'       : 'bdkk_S_201516',
        'D'       : 'bdkk_D_201516',
        'AP'      : 'bdkpi_AP_2017s29r2p2',
        'CPState' : ['CP','Bs']
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False], },
  },
  'bdkpi_kk' : {
    'mass' : { '2017s29r2p2' : { 
        'resModel'  : 'bskk_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 
        #'G'  : 'bdkpi_G_201516',
        #'G'  : [0.65789,0,1,True],
        'G'  : 'bdpipi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.5,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_201516', },
        'SSk'  : { 
          'eps'     : [0.5,0,1,False],
          'p0'      : 'bdkpi_p0SSk_2017s29r2p2',
          'p1'      : 'bdkpi_p1SSk_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SSk_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', },
        'SS'   : { 
          'eps'     : [0.5,0,1,False],
          'p0'      : 'bdkpi_p0SS_2017s29r2p2',
          'p1'      : 'bdkpi_p1SS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymSS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0SS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'ACP' : 'bdkpi_ACP_2017s29r2p2',
        'Af'  : 'bdkpi_Af_201516',
        'AP'  : 'bdkpi_AP_2017s29r2p2',
        'CPState' : ['FStoCP','Bs'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False], },
  },
  'lbpk_kk' : {
    'mass' : { '2017s29r2p2' : { 
        'resModel'  : 'bskk_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 
        'G'  : 'lbpk_kk_G_201516',
        'dM' : 'lbpk_kk_dM_201516',
        'dG' : 'lbpk_kk_dG_201516', 
      },
    },
    'timeErr' : { '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
    },
    'tag'  : { '2017s29r2p2' : { 
        'OS'   : { 'eps'     : [0.37,0,1,False],
                    'p0'      : [0.5,0,1,True],#'bdkpi_p0OS_2017s29r2p2',
                    'p1'      : [0,-1,1,True],#'bdkpi_p1OS_2017s29r2p2',
                    'epsAsym' : [0,-1,1,True],#'bdkpi_epsAsymOS_2017s29r2p2',
                    'deltap0' : [0,-1,1,True],#'bdkpi_deltap0OS_2017s29r2p2',
                    'deltap1' : [0,-1,1,True],#'bdkpi_deltap1OS_2017s29r2p2',
                    'etaHat'  : 'bdkpi_etaHatOS_201516', },
        'SSk'  : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : [0.5,0,1,True],#'bdkpi_p0SSk_2017s29r2p2',
          'p1'      : [0,-1,1,True],#'bdkpi_p1SSk_2017s29r2p2',
          'epsAsym' : [0,-1,1,True],#'bdkpi_epsAsymSSk_2017s29r2p2',
          'deltap0' : [0,-1,1,True],#'bdkpi_deltap0SSk_2017s29r2p2',
          'deltap1' : [0,-1,1,True],#'bdkpi_deltap1SSk_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSSk_2017s29r2p2', },
        'SS'   : { 
          'eps'     : [0.8,0,1,False],
          'p0'      : [0.5,0,1,True],#'bdkpi_p0SS_2017s29r2p2',
          'p1'      : [0,-1,1,True],#'bdkpi_p1SS_2017s29r2p2',
          'epsAsym' : [0,-1,1,True],#'bdkpi_epsAsymSS_2017s29r2p2',
          'deltap0' : [0,-1,1,True],#'bdkpi_deltap0SS_2017s29r2p2',
          'deltap1' : [0,-1,1,True],#'bdkpi_deltap1SS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatSS_201516', },
      },
    },
    'CP' : { '2017s29r2p2' : { 
        'ACP' : 'lbpk_kk_ACP_201516',
        'Af'  : 'lbpk_kk_Af_201516',
        'AP'  : 'lbpk_kk_AP_201516',
        'CPState' : ['FStoCP','Bs'] 
      },
    },
    'acc' : { '2017s29r2p2' : [0.99,False], },
  },
  'bkg_kpi' : {
    'mass' : { '2017s29r2p2' : { 
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
    'time' : { '2017s29r2p2' : { 
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
    'acc' : { '2017s29r2p2' : { 
        'c11' : [8.25233e-01,-10,10,False],
        'c10' : [5.38033e-01,-10,10,False],
        'c01' : [8.25233e-01,-10,10,False],
        'c00' : [5.38033e-01,-10,10,False],
      },
    },
    'tag' : { '2017s29r2p2' : { 
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
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'bkg_pipi' : {
    'mass' : { '2017s29r2p2' : { 
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
    'time' : { '2017s29r2p2' : {
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
    'acc' : { '2017s29r2p2' : { 
        'c11' : [8.25233e-01,-10,10,False],
        'c10' : [5.38033e-01,-10,10,False],
        'c01' : [8.25233e-01,-10,10,False],
        'c00' : [5.38033e-01,-10,10,False],
      },
    },
    'tag' : { '2017s29r2p2' : { 
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
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'bkg_kk' : {
    'mass' : { '2017s29r2p2' : { 
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
    'time' : { '2017s29r2p2' : {
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
    'acc' : { '2017s29r2p2' : { 
        'c11' : [8.25233e-01,-10,10,False],
        'c10' : [5.38033e-01,-10,10,False],
        'c01' : [8.25233e-01,-10,10,False],
        'c00' : [5.38033e-01,-10,10,False],
      },
    },
    'tag' : { '2017s29r2p2' : { 'OS'  : { 
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
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'phys_kpi1' : {
    'mass' : { '2017s29r2p2' : { 
        'm0' : 'phys_kpi1_mass_m0_201516',
        'cA' : [-20,-100,0,False],
        'resModel' : 'bdkpi_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { '2017s29r2p2' : { 
        'a0' : [-4.46323e-01,-10,1,False],
        'b0' : [-1.79150e+00,-10,1,False],
        'c0'  : [-4.46323e-01,-10,1,False], 
        'a1' : [-4.46323e-01,-10,1,False],
        'b1' : [-1.79150e+00,-10,1,False],
        'c1'  : [-4.46323e-01,-10,1,False],
      },
    },
    'tag' : { '2017s29r2p2' : { 
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
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'phys_kpi2' : {
    'mass' : { '2017s29r2p2' : { 
        'm0' : 'phys_kpi2_mass_m0_201516',
        'cA' : 'phys_kpi1_mass_cA_2017s29r2p2',
        'resModel' : 'bskpi_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { '2017s29r2p2' : { 
        'a0' : "phys_kpi1_a0_2017",#[-4.46323e-01,-10,1,False],
        'b0' : "phys_kpi1_b0_2017",#[-1.79150e+00,-10,1,False],
        'c0' : "phys_kpi1_c0_2017",#[-4.46323e-01,-10,1,False], 
        'a1' : "phys_kpi1_a1_2017",#[-4.46323e-01,-10,1,False],
        'b1' : "phys_kpi1_b1_2017",#[-1.79150e+00,-10,1,False],
        'c1' : "phys_kpi1_c1_2017",},#[-4.46323e-01,-10,1,False],},
    },
    'tag' : { '2017s29r2p2' : { 
        'OS'  : { 
          'eps'     : 'phys_kpi1_epsOS_2017s29r2p2',#[ 0.5,0,1,False],
          'epsAsym' : 'phys_kpi1_epsAsymOS_2017s29r2p2',},#[-0.01,-0.5,0.5,False],},
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym' : [-0.01,-0.5,0.5,False],
          #'eps'     : [ 0.5,0,1,False],
          #'epsAsym0' : [-0.01,-0.5,0.5,False] },
        'SSk' : { 
          'eps'      : 'phys_kpi1_epsSSk_2017s29r2p2',#[0.5,0,1,False],
          'epsAsym'  : 'phys_kpi1_epsAsymSSk_2017s29r2p2',},#[0.01,-0.5,0.5,False] },
        'SS'  : { 
          'eps'      : 'phys_kpi1_epsSS_2017s29r2p2',#[0.5,0,1,False],
          'epsAsym'  : 'phys_kpi1_epsAsymSS_2017s29r2p2',},#[0.01,-0.5,0.5,False] },
      },
    },
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : 'phys_kpi1_ACP_2017s29r2p2',
        'AtagOS' : 'phys_kpi1_AtagOS_2017s29r2p2',
        'AtagSS' : 'phys_kpi1_AtagSS_2017s29r2p2', 
      },
    },
  },
  'phys_pipi' : {
    'mass' : { '2017s29r2p2' : { 
        'm0' : 'phys_kpi1_mass_m0_201516',
        'cA' : [-20,-100,0,False],
        'resModel' : 'bdpipi_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { '2017s29r2p2' : { 
        'a0' : [-4.46323e-01,-10,1,False],
        'b0' : [-1.79150e+00,-10,1,False],
        'c0'  : [-4.46323e-01,-10,1,False], 
        'a1' : [-4.46323e-01,-10,1,False],
        'b1' : [-1.79150e+00,-10,1,False],
        'c1'  : [-4.46323e-01,-10,1,False],
      },
    },
    'tag' : { '2017s29r2p2' : { 
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
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
  'phys_kk' : {
    'mass' : { '2017s29r2p2' : { 
        'm0' : 'phys_kpi2_mass_m0_201516',
        'cA' : [-20,-100,0,False],
        'resModel' : 'bskk_mass_resModel_2017s29r2p2' 
      },
    },
    'time' : { '2017s29r2p2' : { 'template' : True },#'G'  : [-4.46323e-01,-10,1,False]},
            },
    'acc' : { '2017s29r2p2' : { 
        'a0' : [-4.46323e-01,-10,1,False],
        'b0' : [-1.79150e+00,-10,1,False],
        'c0'  : [-4.46323e-01,-10,1,False], 
        'a1' : [-4.46323e-01,-10,1,False],
        'b1' : [-1.79150e+00,-10,1,False],
        'c1'  : [-4.46323e-01,-10,1,False],
      },
    },
    'tag' : { '2017s29r2p2' : { 
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
    'CP'  : { '2017s29r2p2' : { 
        'ACP'    : [-0.02,-1,1,False],
        'AtagOS' : [0,-1,1,False],
        'AtagSS' : [0,-1,1,False], 
      },
    },
  },
}

