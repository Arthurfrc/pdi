#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{
  cv::Mat1s image, realce;
  int width, height;
  int nobjects;

  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (!image.data)
  {
    std::cout << "Imagem não carregou corretamente\n";
    return (-1);
  }

  width = image.cols;
  height = image.rows;
  std::cout << width << "x" << height << std::endl;

  // Inicializando a imagem com zeros para o resultado
  realce = Mat1s::zeros(height, width);

  // busca objetos presentes
  nobjects = 0;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (image.at(i, j) == 255 && isValidObject(image, j, i))
      {
        // achou um objeto
        nobjects++;
        // para o floodfill as coordenadas
        // preenche o objeto com o contador
        cv::floodFill(image, Point(j, i), nobjects, 0, realce, Scalar(255));
      }
    }
  }
  std::cout << "a figura tem " << nobjects << " bolhas\n";
  cv::imshow("image", image);
  cv::imwrite("labeling.png", image);
  cv::waitKey();
  return 0;
}

// Função para verificar se objeto é válido
bool isValidObject(const Mat1s &image, int x, int y)
{
  // Objeto nas bordas
  if (x < 1 || x >= image.cols - 1 || y < 1 || y >= image.rows - 1)
  {
    return false;
  }
  // Objeto fora das bordas e sem vizinhos
  if (image(y, x - 1) == 0 && image(y, x + 1) == 0 && image(y - 1, x) == 0 && image(y + 1, x) == 0)
  {
    return true;
  }
  return false;
}