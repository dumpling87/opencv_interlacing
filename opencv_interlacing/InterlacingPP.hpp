//
//  InterlacingPP.hpp
//  Created by Thomas Hill on 10/25/18.
//  Copyright © 2018 Thomas Hill. All rights reserved.

/* implementation of interlacing videos using opencv's VideoCapture class
* the minimum number of frames from all the source videos is found
* and each source video contributes that amount of frames to the output
* parameters of the ouput video can be determined by the user
*/

#ifndef InterlacingPP_hpp
#define InterlacingPP_hpp

#include<opencv2/opencv.hpp>

class InterlacingPP
{
private:
    
    
    
    /* number of input videos */
    int num_sources;
    
    /* Params for output video writer
    *size: width and height of output frames
    *fps : frames per second
    *fourcc: video codecs
    */
    cv::Size size;
    double fps;
    int fourcc;
    
    /*** Helper functions for create_interlacing_videos ***/
    
    
    /**
    * function performs pixel by pixel color inversion on an image
    * @param image - the image to be inverted
    */
    void invert_img(cv::Mat& image);
    
    /**
    * function reads input from video capture source inverts and resizes it then writes it to output. run by multiple threads
    * @param vc_vector - vector storing all VideoCapture objects for all source files
    * @param output_writer - VideoWriter to write to output file
    * @param invert_frames - boolean determining whether the frames should be inverted
    */
    void interlace(std::vector<cv::VideoCapture>& vc_vector, cv::VideoWriter &output_writer,    bool invert_frames);
   
public:
    /**
     * constructor for InterlacingPP class
     * Initializes size to  550x550, fps =30 and fourcc to m4v format
    */
    InterlacingPP()
    {
        size = cv::Size(550,550);
        fps = 30.0;
        fourcc = CV_FOURCC('m', 'p', '4', 'v');
    }
    
    /**
    * constructor for InterlacingPP class with user given parameters for output video
    * @param fourcc - video codec for output
    * @param size - width and height of output frames stored in cv::Size
    * @param fps - frames per second of output video
    */
    InterlacingPP(int fourcc, cv::Size size, double fps )
    {
        this->size = size;
        this->fps = fps;
        this->fourcc = fourcc;
    }
    
    /**
    * function for creating interlaced video returns true on success and false on failure
    * @param video_names - vector of filenames for videos to interlace
    * @param output_name - string file name of output video
    * @param invert_frames - boolean indicating whether color of frames should be inverted true by default
    */
    bool create_interlacing_video(const std::vector<std::string> & video_names, const std::string & output_name, bool invert_frames = true);
    
    /**
    * functions getters and setters for ouput video params fps, fourcc, and size
    */
    void set_params(cv::Size size, int fourcc ,double fps)
    {
        this->size = size;
        this->fourcc = fourcc;
        this->fps = fps;
    }
    void set_fps(double fps){this->fps = fps;}
    double get_fps(){return this->fps;}
    void set_fourcc( int fourcc){this->fourcc = fourcc;}
    int get_fourcc () {return fourcc;}
    void set_size(cv::Size size){this->size = size;}
    cv::Size get_size(){return size;}

    
    
};

#endif /* InterlacingPP_hpp */
