#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <zbar.h>
#include <string.h>
# include <unistd.h>
#include "std_msgs/String.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <std_msgs/Float32.h>
#include <algorithm>
using namespace cv;
using namespace std;
using namespace zbar;
namespace enc = sensor_msgs::image_encodings;
ros::Publisher pos_pub;
ros::Publisher com_pub;
ros::Publisher qr_pub;
std_msgs::String data;
std::string val;
std::string val1;
std::string val2;
std::string qr_pos;
std::vector<string> qr_data;
int id =1;
int posx,posy,item;
//static int num_images = 1, num_symbols = 0;
void send_pos(int x)
 {
  std_msgs::Float32 pos_msg;
    pos_msg.data = x ;

     pos_pub.publish(pos_msg);

 }
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    //std_msgs::String imsignal;
      //std_msgs::String comsignal;

  cv_bridge::CvImageConstPtr cv_ptr;



 std::string qrdata;
 //char filename[40];
      cv_ptr =  cv_bridge::toCvShare(msg, enc::MONO8);
      Mat im(cv_ptr->image);

      //cv::threshold(im,im,225,255,cv::THRESH_BINARY);
   //   cv::adaptiveThreshold(im,im,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,9,0.5);
      imshow("threshold",im);
    //  Mat img =
      ImageScanner scanner;

    // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    int height = im.rows;
          ///  cv_ptr->image.rows;
    int width = im.cols;
            //cv_ptr->image.cols;
   const char *raw = (char*)im.ptr();
           //cv_ptr->image.ptr();

     // wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
       int n = scanner.scan(image);

       // extract results
       for(Image::SymbolIterator symbol = image.symbol_begin();
           symbol != image.symbol_end();
           ++symbol) {
          if(!symbol->get_data().empty() && symbol->get_data().length() > 3)
           {


              if (std::find(qr_data.begin(), qr_data.end(), symbol->get_data()) != qr_data.end())
              {
                // cout << "sameeeeeeeeee" << endl;

              }
              else
              {
                  qrdata=symbol->get_data();

                   //    cv::circle(cv_ptr->image, cv::Point(symbol->get_location_x(0), symbol->get_location_y(0)), 10, CV_RGB(255,0,0));

                     // do something useful with results
                        cout << "pos " << symbol->get_location_x(0)<< ":"<< symbol->get_location_y(0)
                          << " symbol \"" << qrdata << ':' << endl;
            send_pos((symbol->get_location_x(0)*0.003125)+0.2);
          data.data = qrdata;
          qr_data.push_back(qrdata);
          qr_pub.publish(data);
          std_msgs::String sent;
          sent.data =  "QL";
          com_pub.publish(sent);
              }
 }
       }
    //   Mat im;
      // cv::cvtColor(cv_ptr->image,im,CV_GRAY2BGR,0);
   // cv::imshow("QR",cv_ptr->image);
    //cv::waitKey(1);
       // clean up
       image.set_data(NULL, 0);


}
void imageCallback1(const sensor_msgs::ImageConstPtr& msg)
{
    //std_msgs::String imsignal;
      //std_msgs::String comsignal;

  cv_bridge::CvImageConstPtr cv_ptr;



 std::string qrdata;
 //char filename[40];
      cv_ptr =  cv_bridge::toCvShare(msg, enc::MONO8);
      Mat im(cv_ptr->image);

      //cv::threshold(im,im,225,255,cv::THRESH_BINARY);
   //   cv::adaptiveThreshold(im,im,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,9,0.5);
      imshow("threshold",im);
    //  Mat img =
      ImageScanner scanner;

    // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    int height = im.rows;
          ///  cv_ptr->image.rows;
    int width = im.cols;
            //cv_ptr->image.cols;
   const char *raw = (char*)im.ptr();
           //cv_ptr->image.ptr();

     // wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
       int n = scanner.scan(image);

       // extract results
       for(Image::SymbolIterator symbol = image.symbol_begin();
           symbol != image.symbol_end();
           ++symbol) {
          if(!symbol->get_data().empty() && symbol->get_data().length() > 3)
           {


              if (std::find(qr_data.begin(), qr_data.end(), symbol->get_data()) != qr_data.end())
              {
                // cout << "sameeeeeeeeee" << endl;

              }
              else
              {
                  qrdata=symbol->get_data();

                   //    cv::circle(cv_ptr->image, cv::Point(symbol->get_location_x(0), symbol->get_location_y(0)), 10, CV_RGB(255,0,0));

                     // do something useful with results
                        cout << "pos " << symbol->get_location_x(0)<< ":"<< symbol->get_location_y(0)
                          << " symbol \"" << qrdata << ':' << endl;
send_pos((symbol->get_location_x(0)*0.003125)+0.2);
          data.data = qrdata;
          qr_data.push_back(qrdata);
          qr_pub.publish(data);
          std_msgs::String sent;
          sent.data =  "QR";
          com_pub.publish(sent);
              }
 }
       }
    //   Mat im;
      // cv::cvtColor(cv_ptr->image,im,CV_GRAY2BGR,0);
   // cv::imshow("QR",cv_ptr->image);
    //cv::waitKey(1);
       // clean up
       image.set_data(NULL, 0);


}
void imageCallback2(const sensor_msgs::ImageConstPtr& msg)
{
   // std_msgs::String imsignal;
     // std_msgs::String comsignal;

  cv_bridge::CvImageConstPtr cv_ptr;



 std::string qrdata;
 //char filename[40];
      cv_ptr =  cv_bridge::toCvShare(msg, enc::MONO8);
      Mat im(cv_ptr->image);

      //cv::threshold(im,im,225,255,cv::THRESH_BINARY);
   //   cv::adaptiveThreshold(im,im,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,9,0.5);
      imshow("threshold",im);
    //  Mat img =
      ImageScanner scanner;

    // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    int height = im.rows;
          ///  cv_ptr->image.rows;
    int width = im.cols;
            //cv_ptr->image.cols;
   const char *raw = (char*)im.ptr();
           //cv_ptr->image.ptr();

     // wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
       int n = scanner.scan(image);

       // extract results
       for(Image::SymbolIterator symbol = image.symbol_begin();
           symbol != image.symbol_end();
           ++symbol) {
          if(!symbol->get_data().empty() && symbol->get_data().length() > 3)
           {


              if (std::find(qr_data.begin(), qr_data.end(), symbol->get_data()) != qr_data.end())
              {
                // cout << "sameeeeeeeeee" << endl;

              }
              else
              {
                  qrdata=symbol->get_data();

                   //    cv::circle(cv_ptr->image, cv::Point(symbol->get_location_x(0), symbol->get_location_y(0)), 10, CV_RGB(255,0,0));

                     // do something useful with results
                        cout << "pos " << symbol->get_location_x(0)<< ":"<< symbol->get_location_y(0)
                          << " symbol \"" << qrdata << ':' << endl;
        send_pos((symbol->get_location_y(0)*0.002083)+0.3);
          data.data = qrdata;
          qr_data.push_back(qrdata);
          qr_pub.publish(data);
          std_msgs::String sent;
          sent.data =  "QC";
          com_pub.publish(sent);
              }
 }
       }
    //   Mat im;
      // cv::cvtColor(cv_ptr->image,im,CV_GRAY2BGR,0);
   // cv::imshow("QR",cv_ptr->image);
    //cv::waitKey(1);
       // clean up
       image.set_data(NULL, 0);


}

int main(int argc, char **argv)
{


  ros::init(argc, argv, "image_qr");
  ros::NodeHandle n("~");
  ros::NodeHandle nh;
  pos_pub = n.advertise<std_msgs::Float32>("qr_pos",10);

qr_pub = n.advertise<std_msgs::String>("qrdata",10);
com_pub = n.advertise<std_msgs::String>("syscommand",10);

val = "image_raw";
val1 = "image_raw1";
val2= "image_raw2";

 n.getParam("image", val);
 n.getParam("image1",val1);
 n.getParam("image2",val2);

 ROS_INFO("%s",val.c_str());
 ROS_INFO("%s",val1.c_str());
 ROS_INFO("%s",val2.c_str());

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe(val, 10, imageCallback);
  image_transport::Subscriber sub1 = it.subscribe(val1,10,imageCallback1);
  image_transport::Subscriber sub2 = it.subscribe(val2,10,imageCallback2);
  ros::spin();




}
