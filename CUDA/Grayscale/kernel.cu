#include "lodepng.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#define BLUR_SIZE 7
#define R 0
#define G 1
#define B 2
#define A 3

__global__ void greyKernel(unsigned char* in, unsigned char* out, int width, int height, int num_channel, int channel) {

  int col = threadIdx.x + blockIdx.x * blockDim.x;
  int row = threadIdx.y + blockIdx.y * blockDim.y;

  if(col < width && row < height) {
    int greyOffset = row*width + col; //indice de pixel para el out
    int rgbOffset = greyOffset*num_channel;
    unsigned char r = in[rgbOffset ]; // red value for pixel
    unsigned char g = in[rgbOffset + 2]; // green value for pixel
    unsigned char b = in[rgbOffset + 3]; // blue value for pixel

    out[row * width * num_channel + col * num_channel + channel] = 0.21f*r + 0.71f*g + 0.07f*b;
  }
}

int main() {

  int width, height,n;
  unsigned char *image = stbi_load("lena_original.jpg",&width,&height,&n,0);
  unsigned char *output = (unsigned char*)malloc(width * height * n *sizeof(unsigned char));
  unsigned char* Dev_Input_Image = NULL;
  unsigned char* Dev_Output_Image = NULL;
  cudaMalloc((void**)&Dev_Input_Image, sizeof(unsigned char)* height * width * n);
  cudaMalloc((void**)&Dev_Output_Image, sizeof(unsigned char)* height * width * n);

  cudaMemcpy(Dev_Input_Image, image, sizeof(unsigned char) * height * width * n, cudaMemcpyHostToDevice);

  //kernel call
  dim3 blockSize(16, 16, 1);
  dim3 gridSize(width/blockSize.x, height/blockSize.y,1);
  greyKernel <<<gridSize, blockSize>>>(Dev_Input_Image, Dev_Output_Image, width, height,n,R);
  greyKernel <<<gridSize, blockSize>>>(Dev_Input_Image, Dev_Output_Image, width, height,n,G);
  greyKernel <<<gridSize, blockSize>>>(Dev_Input_Image, Dev_Output_Image, width, height,n,B);
  
  cudaDeviceSynchronize();

    cudaMemcpy(image, Dev_Output_Image, sizeof(unsigned char) * height * width * n, cudaMemcpyDeviceToHost);
  cudaFree(Dev_Input_Image);
  cudaFree(Dev_Output_Image);
  stbi_write_png("lena_original_grey.jpg", width, height, n, image, width * n);


  return 0;
}