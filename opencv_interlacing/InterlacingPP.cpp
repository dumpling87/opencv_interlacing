//
//  InterlacingPP.cpp
//  Created by Thomas Hill on 10/25/18.
//  Copyright © 2018 Thomas Hill. All rights reserved.
//

#include "InterlacingPP.hpp"
#include <algorithm>
bool InterlacingPP::create_interlacing_video(const std::vector <std::string> & video_names,
                                             const std::string & output_name,
                                             bool invert_frames)
{
    num_sources = (int) video_names.size();
    std::vector<cv::VideoCapture> video_capture_container(num_sources);
    for(int i = 0; i < num_sources ; i++)
    {
        video_capture_container[i].open(video_names[i]);
        if(!video_capture_container[i].isOpened())
        {
            std::cerr<< "File " << video_names[i] <<"could not be opened"<<std::endl;
            return false;
        }
    }
    //sort based on estimated framecount. Generally allows each video to get the same amount of frames
    std::sort(video_capture_container.begin(), video_capture_container.end(),
              [](const cv::VideoCapture&  a,const  cv::VideoCapture& b)
              {
                  return a.get(CV_CAP_PROP_FRAME_COUNT) < b.get(CV_CAP_PROP_FRAME_COUNT);
              }
              );
    cv:: VideoWriter output_writer(output_name, fourcc, fps, size);
    if(!output_writer.isOpened())
    {
        std::cerr<< " Video writer failed to open with file: " << output_name << " fourcc: "<< fourcc << " fps: " << fps << " height "<<size.height << " and width: "<< size.width << std::endl;
        
    }
    interlace(video_capture_container, output_writer, invert_frames);
    return true;
}
/*** Helper functions for create_interlacing_videos ***/
void InterlacingPP:: interlace(std::vector<cv::VideoCapture>& vc_vector, cv::VideoWriter& output_writer, bool invert_frames)
{
    
    cv::namedWindow("interlaced");
    while(true)
    {
        for(int i = 0; i < num_sources; i++ )
        {
            cv::Mat original_frame;
            vc_vector[i] >> original_frame;
            if(original_frame.empty())
            {
                cv::destroyWindow("interlaced");
                return;
            }
            cv::Mat modified_frame;
            cv::resize(original_frame, modified_frame,size);
            if(invert_frames)
            {
                invert_img(modified_frame);
            }
            cv::imshow("interlaced", modified_frame);
            cv::waitKey(10);
            output_writer << modified_frame;
           
        }
    }
  
}

void InterlacingPP::invert_img(cv::Mat& img)
{
    for(int i = 0; i< img.rows; i++)
    {
        for(int j = 0; j < img.cols; j++)
        {
            img.at<cv::Vec3b>(i,j)[0] = 255 - img.at<cv::Vec3b>(i,j)[0];
            img.at<cv::Vec3b>(i,j)[1] = 255 - img.at<cv::Vec3b>(i,j)[1];
            img.at<cv::Vec3b>(i,j)[2] = 255 - img.at<cv::Vec3b>(i,j)[2];
        }
    }
}
