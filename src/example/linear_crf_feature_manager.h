//
// Created by  ngs on 02/08/2018.
//

#ifndef STATNLP_LINEAR_CRF_LINEAR_FEATURE_MANAGER_H
#define STATNLP_LINEAR_CRF_LINEAR_FEATURE_MANAGER_H

#include "../hybridnetworks/feature_manager.h"

class LinearCRFFeatureManager: public FeatureManager{
public:
//    LinearCRFFeatureManager();
    LinearCRFFeatureManager(GlobalNetworkParam *ptr_param);
    ~LinearCRFFeatureManager();
    FeatureArray* ExtractHelper(Network *ptr, int parent, std::vector<int> *ptr_children);
};
#endif //STATNLP_LINEAR_CRF_LINEAR_FEATURE_MANAGER_H
