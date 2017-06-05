#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;

//Smooth
int MinsmoothValue = 0;
int MaxsmoothValue = 7;
//Smooth

//Erode/Dilate
IplImage* erode = 0;
IplImage* dilate = 0;

int radius = 1;
int radius_max=10;

int iterations = 1;
int iterations_max = 10;
//Erode/Dilate


void SmoothTrackbar(int pos)
{
    MinsmoothValue = pos;
}

//Erode
void myTrackbarRadius(int pos) {
    radius = pos;
}

//Dilate
void myTrackbarIterations(int pos) {
    iterations = pos;
}

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    const char* filename = argc == 2 ? argv[1] : "Image0.jpg";
    // получаем картинку
    image = cvLoadImage(filename,1);
    // клонируем картинку
    dst = cvCloneImage(image);
    
    printf("[i] image: %s\n", filename);
    assert( image != 0 );
    
    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("changed",CV_WINDOW_AUTOSIZE);
    
    cvCreateTrackbar("radius(Erode)", "changed", &radius, radius_max, myTrackbarRadius);
    cvCreateTrackbar("iterations(Dilate)", "changed", &iterations, iterations_max, myTrackbarIterations);
    cvCreateTrackbar("Smooth", "changed", &MinsmoothValue, MaxsmoothValue, SmoothTrackbar);
    
        while(1)
        {
            // показываем картинку
            cvShowImage("original",image);
            
            // создаём ядро Erode/Dilate
            IplConvKernel* Kern = cvCreateStructuringElementEx(radius*2+1, radius*2+1, radius, radius, CV_SHAPE_ELLIPSE);

            // изменяем исходную картинку
            cvSmooth(image, dst, CV_BLUR, MinsmoothValue+1, MinsmoothValue+1);
            cvErode(image, dst, Kern, iterations);
            cvDilate(image, dst, Kern, iterations);
            
            // показываем результат
            cvShowImage("changed",dst);
            
            cvReleaseStructuringElement(&Kern);
            
            // ждём нажатия клавиши
            int с = cvWaitKey(33);
            if(с == 27) break;
          
        }
    
    
    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&dst);
    
    // удаляем окно
    cvDestroyWindow("original");
    cvDestroyWindow("changed");
    return 0;
}

   