#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  cv::Mat image;
  cv::Vec3b val;

  int P1, P2;

  image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
  if (!image.data) std::cout << "nao abriu o arquivo.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  std::cout << "Diga um valor para P1:" ;
  std::cin >> P1;
  std::cout << "Diga um valor para P2:" ;
  std::cin >> P2;

  for (int i = P1; i < P2; i++) {
    for (int j = P1; j < P2; j++) {
        image.at<uchar>(i, j) = 255 - image.at<uchar>(i,j);
    }
  }

  cv::imshow("janela", image);
  cv::waitKey();
  return 0;
}
