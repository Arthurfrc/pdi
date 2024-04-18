#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

int main(int argc, char** argv) {
  cv::Mat image;
  int width, height;
  int camera;
  cv::VideoCapture cap;
  cv::Mat hist;
  int nbins = 256;
  float range[] = {0, 256};
  const float *histrange = {range};
  bool uniform = true;
  bool acumular = false;
  int key;

  camera = cameraEnumerator();
  cap.open(camera);

  if(!cap.isOpened()) {
    std::cout << "Câmera indisponívela" << std::endl;;
    return -1;
  }

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "Largura (em px): " << width << std::endl;
  std::cout << "Altura (em px) : " << height << std::endl;

  while(1) {
    cap >> image;

    // Equalizar o histograma
    cv::equalizeHist(image, image);

    cv::imshow ("image", image);
    key = cv::waitKey(30);
    if(key == 27) break; // Pressione ESC para sair
  }
  return 0;
}