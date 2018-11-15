//
//
//  interlacingpp_demo
//
//  Created by Thomas Hill on 10/23/18.
//  Copyright © 2018 Thomas Hill. All rights reserved.
//

#include <iostream>
#include<opencv2/opencv.hpp>
#include "InterlacingPP.hpp"

/**
* input and output file names entered as command line arguments in the format
* inputfile_1 inputfile_2 .... inputfile_n outputfile
*/
int main(int argc, char * argv[]) {
    if(argc > 3)
    {
        InterlacingPP ipp;
        ipp.set_fps(60.0);
        std::vector<std::string> input_names;
        input_names.assign(argv + 1, argv + argc -1 );
        std::string output_name = argv[argc -1];
        ipp.create_interlacing_video(input_names, output_name);
    }
    else
    {
        std::cerr<< "Input error: not enough arguments"<< std::endl;
    }
    return 0;
}

