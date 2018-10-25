//
// Created by  ngs on 10/10/2018.
//

#ifndef STATNLP_EVALUATE_NER_H
#define STATNLP_EVALUATE_NER_H

#include <vector>
#include <src/common/types/instance.h>
#include <iostream>
#include <fstream>
#include "linear_ne_instance.h"
#include "evaluate_ner.h"

class EvaluateNER {
public:
    static int NUM_OF_ENTITY_TYPE;
    /**
     * Evaluate the prediciton results.
     *
     * @param ptr_inst
     * @param filename_ner_ouput
     */
    inline static void Evaluate(std::vector<Instance *> *ptr_inst, std::string filename_ner_ouput) {
        std::vector<ComType::Results> result_vec(NUM_OF_ENTITY_TYPE); /*LOC, MISC, ORG, PER*/
        for(auto it = result_vec.begin(); it != result_vec.end(); ++it){
            (*it).corr_ = 0;
            (*it).erro_ = 0;
            (*it).rest_ = 0;
        }
        int size = result_vec.size();
        std::ofstream ofs(filename_ner_ouput);
        int num_of_line = 0;
        int num_of_corr = 0;
        for (auto it = ptr_inst->begin(); it != ptr_inst->end(); ++it) {
            LinearNEInstance *ptr_ner_inst = (LinearNEInstance *) (*it);
            NER_OutPut_Type *ptr_predict = ptr_ner_inst->GetPrediction();
            NER_OutPut_Type *ptr_groudtrueth = ptr_ner_inst->GetOutPut();
            Sentence *ptr_sent = ptr_ner_inst->GetInput();
            for (int i = 0; i < ptr_sent->GetLength(); ++i) {
                std::string ground_truth_entity_str = (*ptr_groudtrueth)[i];
                std::string predict_entity_str = (*ptr_predict)[i];
                std::string line;
                if(true == Accumulate(ground_truth_entity_str, predict_entity_str, result_vec)){
                    ++num_of_corr;
                    line = ptr_sent->Get(i)->GetForm() + " " + ptr_sent->Get(i)->GetTag() + " " + ground_truth_entity_str +
                            " " + predict_entity_str;
                }else {
                    line = "erro "+ptr_sent->Get(i)->GetForm() + " " + ptr_sent->Get(i)->GetTag() + " " + ground_truth_entity_str +
                           " " + predict_entity_str;
                }
                num_of_line++;
                ofs << line ;
                ofs << std::endl;
            }
            ofs << std::endl;
        }
        CalcResult(num_of_corr,num_of_line,result_vec);
    }
    /**
     *
     * Compare the prediction entity with the groundtruth for each line.
     *
     * @param ground_truth_entity_str
     * @param predict_entity_str
     * @param result_vec
     * @return
     */
    inline static bool Accumulate(std::string ground_truth_entity_str, std::string predict_entity_str,
                                  std::vector<ComType::Results> &result_vec){
        int size = result_vec.size();
        if(0 == ground_truth_entity_str.compare(predict_entity_str)){
            if(0 == predict_entity_str.compare("O")){
                return true;
            }
            std::string sub_str = predict_entity_str.substr(2);
            if("LOC" == sub_str){
                result_vec[0].corr_++;
            } else if ("MISC" == sub_str){
                result_vec[1].corr_++;
            } else if("ORG" == sub_str){
                result_vec[2].corr_++;
            } else if("PER" == sub_str){
                result_vec[3].corr_++;
            }
            return true;
        } else{
            if(1 == predict_entity_str.compare("O")){
                std::string sub_str_err = predict_entity_str.substr(2);
                if("LOC" == sub_str_err){
                    result_vec[0].erro_++;
                } else if ("MISC" == sub_str_err){
                    result_vec[1].erro_++;
                } else if("ORG" == sub_str_err){
                    result_vec[2].erro_++;
                } else if("PER" == sub_str_err){
                    result_vec[3].erro_++;
                }
            }
            if(1 == ground_truth_entity_str.compare("O")){
                std::string sub_str_truth = ground_truth_entity_str.substr(2);
                if("LOC" == sub_str_truth){
                    result_vec[0].rest_++;
                } else if ("MISC" == sub_str_truth){
                    result_vec[1].rest_++;
                } else if("ORG" == sub_str_truth){
                    result_vec[2].rest_++;
                } else if("PER" == sub_str_truth){
                    result_vec[3].rest_++;
                }
            }
            return false;
        }
    }
    /***
     *
     * Calc the decoding results
     *
     * @param num_of_corr
     * @param num_of_line
     * @param reslut_vec
     */
    inline static void CalcResult(int num_of_corr, int num_of_line, std::vector<ComType::Results> &reslut_vec){
        double accuracy = (double) num_of_corr / (double) num_of_line;
        int prec_numerator = 0;
        int prec_denominator = 0;
        int recall_numberator = 0;
        int recall_denominator = 0;
        for(auto it = reslut_vec.begin(); it != reslut_vec.end(); ++it){
            prec_numerator += (*it).corr_;
            prec_denominator += (*it).erro_;
            recall_denominator += (*it).rest_;
        }
        recall_numberator = prec_numerator;
        double prec_overall = (double) prec_numerator / ((double) prec_denominator + (double) prec_numerator);
        double recall_overall = (double) recall_numberator / ((double) recall_denominator + (double) recall_numberator);
        double f1_b = (prec_overall * recall_overall * 2) / (prec_overall + recall_overall);
        std::cout<< "Accuracy: "<<accuracy<<"  Precision: "<<prec_overall<<" Recall: "<<recall_overall<< " F1: "<<f1_b<<std::endl;
    }
};

int EvaluateNER::NUM_OF_ENTITY_TYPE = 4;

#endif //STATNLP_EVALUATE_NER_H
