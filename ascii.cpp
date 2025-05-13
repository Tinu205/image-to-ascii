#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int return_index(int pixel){
  int index = min(static_cast<int>((pixel/255.0)*(69-1)),68);
  //int index = min(static_cast<int>((pixel/255.0)*(10-1)),9);
  return index;
}
int main(){
  Mat image = cv::imread("image_path",IMREAD_GRAYSCALE);
  String chardensity{"@\"$B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "};
  String dens{"@#*+=-:,. "};

  if(image.empty()){
    cout<<"Error opening the file"<<endl;
    return -1;
  }
  Size size = image.size();
  int height = size.height;
  int width = size.width;

  //cout<<height<<","<<width<<endl;
  int new_width = 200;
  int new_height = height * (new_width / float(width))*0.5;
  resize(image, image, Size(new_width, new_height));
  ofstream file("../art.txt");
  for(int row=0;row<new_height;row++){
    for(int col=0;col<new_width;col++){
      unsigned char pixel_value = image.at<uchar>(row, col);
      int index = return_index(pixel_value);
      cout<<chardensity[index];
      file<<chardensity[index];
      //cout<<dens[index];
      //file<<dens[index];
    }
    cout<<"\n";
    file<<"\n";
  }
  file.close(); 
}
