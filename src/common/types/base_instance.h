//
// Created by  ngs on 31/07/2018.
//

#ifndef STATNLP_BASE_INSTANCE_H
#define STATNLP_BASE_INSTANCE_H

#include "instance.h"
/**
 *
 * @tparam T0: its self type
 * @tparam T1: input type
 * @tparam T2: output type
 */

template <class SELF_TYPE, class INPUT_TYPE, class OUTPUT_TYPE>

class BaseInstance: public Instance{
public:
    BaseInstance(){

    }

    BaseInstance(SELF_TYPE *ptr_self, INPUT_TYPE *ptr_input, OUTPUT_TYPE *ptr_output){

    }

    BaseInstance(int id, double weight){
        Instance::Instance(id,weight);
    }

    BaseInstance(SELF_TYPE *ptr_self, INPUT_TYPE *ptr_input, OUTPUT_TYPE *ptr_output, int id, double weight){
        ptr_input_ = ptr_input;
        ptr_output_ = ptr_output;
        Instance::Instance(id,weight);
    }

    ~BaseInstance(){

    }

protected:
    INPUT_TYPE *ptr_input_;
    OUTPUT_TYPE *ptr_output_;
    OUTPUT_TYPE *ptr_prediction_;
};

#endif //STATNLP_BASE_INSTANCE_H
