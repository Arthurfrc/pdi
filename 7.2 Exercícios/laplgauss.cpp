#include <opencv2/opencv.hpp>

using namespace cv;

float gauss[] = {0.0625, 0.125, 0.0625,
                 0.125, 0.25, 0.125,
                 0.0625, 0.125, 0.0625};

float laplace[] = {0, -1, 0,
                   -1, 4, -1,
                   0, -1, 0};

float laplace_gauss[] = {-0.125, 0.375, -0.125,
                         -0.25, 0.75, -0.25,
                         -0.125, 0.375, -0.125};

Mat convolve(const Mat &image, const float *filter, int filter_width, int filter_height)
{
  Mat result(image.rows, image.cols, CV_32F);

  for (int y = 0; y < image.rows; ++y)
  {
    const float *image_row = image.ptr<const float>(y);
    float *result_row = result.ptr<float>(y);
  }

  for (int x = 0; x < image.cols; ++x)
  {
    double sum = 0;
    const float *filter_ptr = filter;
    for (int ky = 0; ky < filter_height; ++ky)
    {
      const float *filter_ptr = filter_ptr;
      for (int kx = 0; kx < filter_width; ++kx)
      {
        if (x + kx >= 0 && x + kx < image.cols && y + ky >= 0 && y + ky < image.rows)
        {
          sum += image_row[x + kx] * filter_row[kx];
        }
        filter_row += filter_width;
      }
      filter_ptr += filter_width * filter_height;
    }
    result_row[x] = sum;
  }
}

int main()
{
  Mat image = imread("image.png", IMREAD_GRAYSCALE); // Trocar "image.png" pelo nome da sua imagem

  Mat gaussian = convolve(image, gauss, 3, 3);
  Mat laplace_image = convolve(image, laplace, 3, 3);
  Mat laplace_gauss_image = convolve(gaussian, laplace_gauss, 3, 3);

  imshow("Original", image);
  imshow("Gauss", gaussian);
  imshow("Laplace", laplace_image);
  imshow("Laplace da Gaussiana", laplace_gauss_image);

  waitKey(0);
  return 0;
}