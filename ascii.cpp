#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

String chardensity{"@\"$B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "};
char look_uptable[256];

void initialize_lookuptable(int pixel){
  for(int i=0;i<256;i++){
    int index = min(static_cast<int>((i/255.0)*(chardensity.size()-1)),chardensity.size()-1);
    look_uptable[i] = chardensity[index];
  }
}
int main(){
  
  initialize_lookuptable();

  Mat image = cv::imread("image_path",IMREAD_GRAYSCALE);
  if(image.empty()){
    cout<<"Error opening the file"<<endl;
    return -1;
  }

  Size size = image.size();
  int height = size.height;
  int width = size.width;
  int new_width = 200;
  int new_height = height * (new_width / float(width))*0.5;
  resize(image, image, Size(new_width, new_height));

  ofstream file("../art.txt");
  for(int row=0;row<new_height;row++){
    for(int col=0;col<new_width;col++){
      unsigned char pixel_value = image.at<uchar>(row, col);
      cout<<look_uptable[pixel_value];
      file<<look_uptable[pixel_value];
    }
    cout<<"\n";
    file<<"\n";
  }
  file.close(); 
}
