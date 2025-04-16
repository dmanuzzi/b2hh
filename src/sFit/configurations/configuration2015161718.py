config = { 
  'observables' : { 
    'fState'  : { 
      #'types' : [ ('KPI_201516' ,201), ('PIPI_201516',200),  ('KK_201516'  ,202)] 
      'types' : [ ('KK_201516'  ,202), ('KK_2017s29r2p2'  ,22), ('KK_2018'  ,32)] 
    },
  },
  'bdkpi' : {
    'time' : { 
      '201516' : { 
        'G'  : [0.65417,1,10,False],
        'dM' : [0.50650,0.1,1,False],
        'dG' : [0,-1,1,True] 
      },
      '2017s29r2p2' : { 
        'G'  : 'bdkpi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },
      '2018' : { 
        'G'  : 'bdkpi_G_201516',
        'dM' : 'bdkpi_dM_201516',
        'dG' : 'bdkpi_dG_201516' 
      },
    },
    'timeErr' : { 
      '201516' : { 
        'mean'     : [-0.0036,-0.05,0.05,True],
        'sigma'    : [0.04326,0,5,True],
        'sf_mean'  : [1,0,10,True],
        'sf_sigma' : [1,0.01,5,True] 
      },
      '2017s29r2p2' : { 
        'mean'     : [-0.0036,-0.05,0.05,True],
        'sigma'    : [0.04326,0,5,True],
        'sf_mean'  : [1,0,10,True],
        'sf_sigma' : [1,0.01,5,True] 
      },
      '2018' : { 
        'mean'     : [-0.0036,-0.05,0.05,True],
        'sigma'    : [0.04326,0,5,True],
        'sf_mean'  : [1,0,10,True],
        'sf_sigma' : [1,0.01,5,True] 
      },
    },
    'tag'  : { 
      '201516' : { 
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
      '2017s29r2p2' : { 
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
      '2018' : { 
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
    'CP' : { 
      '201516' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : [0,-1,1,True],
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bd'] 
      },
      '2017s29r2p2' : { 
        'ACP' : 'bdkpi_ACP_201516',
        'Af'  : [0,-1,1,True],
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bd'] 
      },
      '2018' : { 
        'ACP' : 'bdkpi_ACP_201516',
        'Af'  : [0,-1,1,True],
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bd'] 
      },
    },
    'acc' : { 
      '201516' : [0.99,False],  
      '2017s29r2p2' : [0.99,False],  
      '2018' : [0.99,False],  
    },
  },
  'bskpi' : {
    'time' : { 
      '201516' : { 
        'G'  : [0.65620,0,10,True],
        'dM' : [17.757,0,30,True],
        'dG' : [0.081600,-1,1,True] 
      },
      '2017s29r2p2' : { 
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
      '2018' : { 
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
    },
    'timeErr' : { 
      '201516' : { 
        'mean'     : 'bdkpi_timeErr_mean_201516',
        'sigma'    : 'bdkpi_timeErr_sigma_201516',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
      '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_2017s29r2p2',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_2017s29r2p2', 
      },
      '2018' : { 
        'mean'     : 'bdkpi_timeErr_mean_2018',
        'sigma'    : 'bdkpi_timeErr_sigma_2018',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_2018',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_2018', 
      },
    },
    'tag'  : { 
      '201516' : { 
        'OS'   : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : 'bdkpi_p0OS_201516',
          'p1'      : 'bdkpi_p1OS_201516',
          'epsAsym' : 'bdkpi_epsAsymOS_201516',
          'deltap0' : 'bdkpi_deltap0OS_201516',
          'deltap1' : 'bdkpi_deltap1OS_201516',
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
      '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_2017s29r2p2', },
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
            'etaHat'  : 'bdkpi_etaHatSS_2017s29r2p2' 
          }
        },
      '2018' : { 
        'OS'   : { 
          'eps'     : [0.3,0,1,False],
          'p0'      : 'bdkpi_p0OS_2018',
          'p1'      : 'bdkpi_p1OS_2018',
          'epsAsym' : 'bdkpi_epsAsymOS_2018',
          'deltap0' : 'bdkpi_deltap0OS_2018',
          'deltap1' : 'bdkpi_deltap1OS_2018',
          'etaHat'  : 'bdkpi_etaHatOS_2018', },
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
            'etaHat'  : 'bdkpi_etaHatSS_2018' 
          }
        },
      },
    'CP' : { 
      '201516' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : 'bdkpi_Af_201516',
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bs'] 
      },
      '2017s29r2p2' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : 'bdkpi_Af_2017s29r2p2',
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bs'] 
      },        
      '2018' : { 
        'ACP' : [-0.0957262,-1,1,False],
        'Af'  : 'bdkpi_Af_2018',
        'AP'  : [-0.00525242,-0.1,0.1,False],
        'CPState' : ['FS','Bs'] 
      },
    },
    'acc' : { 
      '201516' : [0.99,False], 
      '2017s29r2p2' : [0.99,False],
      '2018' : [0.99,False] 
    },
  },
  'bskk' : {
    'time' : { 
      '201516' : { #'G'  : [1.5226,1,3,False],
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
      '2017s29r2p2' : { #'G'  : [1.5226,1,3,False],
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
      '2018' : { #'G'  : [1.5226,1,3,False],
        'G'  : 'bskpi_G_201516',
        'dM' : 'bskpi_dM_201516',
        'dG' : 'bskpi_dG_201516' 
      },
    },
    'timeErr' : { 
      '201516' : { 
        'mean'     : 'bdkpi_timeErr_mean_201516',
        'sigma'    : 'bdkpi_timeErr_sigma_201516',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_201516',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_201516', 
      },
      '2017s29r2p2' : { 
        'mean'     : 'bdkpi_timeErr_mean_2017s29r2p2',
        'sigma'    : 'bdkpi_timeErr_sigma_2017s29r2p2',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_2017s29r2p2',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_2017s29r2p2', 
      },
      '2018' : { 
        'mean'     : 'bdkpi_timeErr_mean_2018',
        'sigma'    : 'bdkpi_timeErr_sigma_2018',
        'sf_mean'  : 'bdkpi_timeErr_sf_mean_2018',
        'sf_sigma' : 'bdkpi_timeErr_sf_sigma_2018', 
      },
    },
    'tag'  : { 
      '201516' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_201516',
          'p1'      : 'bdkpi_p1OS_201516',
          'epsAsym' : 'bdkpi_epsAsymOS_201516',
          'deltap0' : 'bdkpi_deltap0OS_201516',
          'deltap1' : 'bdkpi_deltap1OS_201516',
          'etaHat'  : 'bdkpi_etaHatOS_201516', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_201516',
          'p1'      : 'bskpi_p1SSk_201516',
          'epsAsym' : [0,-1,1,False],
          'deltap0' : 'bskpi_deltap0SSk_201516',
          'deltap1' : 'bskpi_deltap1SSk_201516',
          'etaHat'  : 'bdkpi_etaHatSSk_201516', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SS_201516',
          'p1'      : 'bskpi_p1SS_201516',
          'epsAsym' : 'bskpi_epsAsymSS_201516',
          'deltap0' : 'bskpi_deltap0SS_201516',
          'deltap1' : 'bskpi_deltap1SS_201516',
          'etaHat'  : 'bdkpi_etaHatSS_201516', 
        },
      },
      '2017s29r2p2' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_2017s29r2p2',
          'p1'      : 'bdkpi_p1OS_2017s29r2p2',
          'epsAsym' : 'bdkpi_epsAsymOS_2017s29r2p2',
          'deltap0' : 'bdkpi_deltap0OS_2017s29r2p2',
          'deltap1' : 'bdkpi_deltap1OS_2017s29r2p2',
          'etaHat'  : 'bdkpi_etaHatOS_2017s29r2p2', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_2017s29r2p2',
          'p1'      : 'bskpi_p1SSk_2017s29r2p2',
          'epsAsym' : [0,-1,1,False],
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
          'etaHat'  : 'bdkpi_etaHatSS_2017s29r2p2', 
        },
      },
      '2018' : { 
        'OS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bdkpi_p0OS_2018',
          'p1'      : 'bdkpi_p1OS_2018',
          'epsAsym' : 'bdkpi_epsAsymOS_2018',
          'deltap0' : 'bdkpi_deltap0OS_2018',
          'deltap1' : 'bdkpi_deltap1OS_2018',
          'etaHat'  : 'bdkpi_etaHatOS_2018', 
        },
        'SSk'  : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SSk_2018',
          'p1'      : 'bskpi_p1SSk_2018',
          'epsAsym' : [0,-1,1,False],
          'deltap0' : 'bskpi_deltap0SSk_2018',
          'deltap1' : 'bskpi_deltap1SSk_2018',
          'etaHat'  : 'bdkpi_etaHatSSk_2018', 
        },
        'SS'   : { 
          'eps'     : [0.33097,0,1,False],
          'p0'      : 'bskpi_p0SS_2018',
          'p1'      : 'bskpi_p1SS_2018',
          'epsAsym' : 'bskpi_epsAsymSS_2018',
          'deltap0' : 'bskpi_deltap0SS_2018',
          'deltap1' : 'bskpi_deltap1SS_2018',
          'etaHat'  : 'bdkpi_etaHatSS_2018', 
        },
      },
    },
    'CP' : { 
      '201516' : { 
        # 'AMP'     : [0.5,0,1,False],
        # 'PHI'     : [3.14/4.,0,2*3.141592653589793, False],
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bskpi_AP_201516',
        'CPState' : ['CP','Bs'] 
      },
      '2017s29r2p2' : { 
        # 'AMP'     : 'bskk_AMP_201516',
        # 'PHI'     : 'bskk_PHI_201516',
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bskpi_AP_2017s29r2p2',
        'CPState' : ['CP','Bs'] 
      },
      '2018' : { 
        # 'AMP'     : 'bskk_AMP_201516',
        # 'PHI'     : 'bskk_PHI_201516',
        'C'       : [0.25,-1,1,False],
        'S'       : [0.25,-1,1,False],
        'D'       : [0.25,-1,1,False],
        'AP'      : 'bskpi_AP_2018',
        'CPState' : ['CP','Bs'] 
      },
    },
    'acc' : { 
      '201516' : [0.99,False], 
      '2017s29r2p2' : [0.99,False], 
      '2018' : [0.99,False], 
    },
  },
}

