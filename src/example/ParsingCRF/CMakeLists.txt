cmake_minimum_required(VERSION 3.5)
add_executable(parsing_crf parsing_crf_main.cpp binarytree.cpp evaluate.h node.cpp ptb_reader.h rule.h parsing_crf_feature_manager.cpp parsing_crf_instance.h
        parsing_crf_network.h parsing_crf_network_compiler.cpp)
target_link_libraries(parsing_crf statnlp_hypernetworks_lib statnlp_neural_lib statnlp_opt_lib statnlp_type_lib dynet)