#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/// Global variables
const string file_name = ("../data/sunflower.jpg");
Mat img, hsv, test_img;
vector<Mat> hsv_split, bgr_split, image_split;
vector<int> compression_params;

void BGR_to_HSV();
void BGR();
void print_image();
void Blue();
void Green();
void Red();
void Test();



int main(void)
{

	img = imread(file_name);

	if (img.empty())
	{
		cout << "Nie znaleziono pliku " << file_name << endl;
		return -1;
	}

	//BGR_to_HSV();
	//BGR();

	//Test();
	
	waitKey(0);
	return 0;
}

//Konwersja przestrzeni barw w OpenCV
void BGR_to_HSV()
{
	///Stworzenie okien
	const string named_window[] = { "BGR", "HSV", "HUE", "SAT", "VAL" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);    //Utworzenie okien 
	namedWindow(named_window[1], CV_WINDOW_AUTOSIZE);
	namedWindow(named_window[2], CV_WINDOW_AUTOSIZE);
	namedWindow(named_window[3], CV_WINDOW_AUTOSIZE);
	namedWindow(named_window[4], CV_WINDOW_AUTOSIZE);

	cvtColor(img, hsv, CV_BGR2HSV);								//Konwersja BGR->HSV
	split(hsv, hsv_split);										//Rozdzielenie HSV na poszczeg�lne kana�y 

	///Wyswietlenie poszczegolnych obrazow
	imshow(named_window[0], img);								//Obraz oryginalny 
	imshow(named_window[1], hsv);								//Obraz w wersji HSV 
	imshow(named_window[2], hsv_split[0]);						//Barwa
	imshow(named_window[3], hsv_split[1]);						//Nasycenie 
	imshow(named_window[4], hsv_split[2]);						//Wartosc 

	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);		//Konwersja jpg 
	compression_params.push_back(100);							//Jakosc 100 
	
	///Zapis poszczegolnych obrazow 
	imwrite("../data/hsv.jpg", hsv, compression_params);   
	imwrite("../data/hue.jpg", hsv_split[0], compression_params);
	imwrite("../data/sat.jpg", hsv_split[1], compression_params);
	imwrite("../data/val.jpg", hsv_split[2], compression_params);

}

void BGR()
{
	///Stworzenie okien
	const string named_window[] = {"B", "G", "R"};
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);    //Utworzenie okien 
	namedWindow(named_window[1], CV_WINDOW_AUTOSIZE);
	namedWindow(named_window[2], CV_WINDOW_AUTOSIZE);

	split(img, bgr_split);

	imshow(named_window[0], bgr_split[0]);						//B
	Blue();

	imshow(named_window[1], bgr_split[1]);						//G
	Green();

	imshow(named_window[2], bgr_split[2]);						//R
	Red();

	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);		//Konwersja jpg 
	compression_params.push_back(100);							//Jakosc 100 

	imwrite("../data/Blue.jpg", bgr_split[0], compression_params);
	imwrite("../data/Green.jpg", bgr_split[1], compression_params);
	imwrite("../data/Red.jpg", bgr_split[2], compression_params);
}

void Blue()
{
	vector<Mat>  test_split;
	split(img, test_split);

	test_split[1] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	test_split[2] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	merge(test_split, test_img);
	
	const string named_window[] = { "Blue" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], test_img);						//G+R

	imwrite("../data/img_Blue.jpg", test_img, compression_params);
}

void Green()
{
	vector<Mat>  test_split;
	split(img, test_split);

	test_split[0] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	test_split[2] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	merge(test_split, test_img);

	const string named_window[] = { "Green" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], test_img);						//G+R

	imwrite("../data/img_Green.jpg", test_img, compression_params);
}

void Red()
{
	vector<Mat>  test_split;
	split(img, test_split);

	test_split[0] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	test_split[1] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	merge(test_split, test_img);

	const string named_window[] = { "Red" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], test_img);						//G+R

	imwrite("../data/img_Red.jpg", test_img, compression_params);
}


void print_image()
{

}

void Test()
{

}