#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;


//info testowe
/// Global variables
const string file_name = ("test_color.jpg");
const string location = ("../data/") + file_name;
Mat img, hsv, test_img, binary;
vector<Mat> hsv_split, bgr_split, image_split;
vector<int> compression_params;
int alfa = 0, beta = 0;

void BGR_to_HSV();
void BGR();
void print_image();
void Blue();
void Green();
void Red();
void Test();
void zakres();
void range_img();
int alfa_range();
int beta_range();
//void HSV_to_BGR();

int main(void)
{

	img = imread(location);

	if (img.empty())
	{
		cout << "Nie znaleziono pliku " << file_name << endl;
		return -1;
	}
	else if (!img.empty())
	{
		cout << "Plik " << file_name << " zostal zaladowany. " << endl;
	}

	///wprowadzenie zakresu koloru;
	zakres();

	BGR_to_HSV();
	//BGR();

	Test();
	//range_img();
	//HSV_to_BGR();
	
	cout << "test#100" << endl;

	waitKey(0);
	return 0;
}

// funkcja zakres opcja 1
void zakres()
{
	int flaga_0 = 0;
	cout << "Wprowadz zakres oczekiwanego koloru: " << endl;

	do	
	{
		flaga_0 = alfa_range();
	}	while (flaga_0 != 1);
	
	do
	{ 
		flaga_0 = beta_range();
	}	while (flaga_0 != 0);

	cout << "Szukany kolor zawiera sie w: (" << alfa << ", " << beta << ")." << endl;
	
}
int alfa_range()
{
	cout << "dolna wartosc: \n";
	cin >> alfa;

	if (alfa >= 0 && alfa <= 255)
	{
		return 1;
	}
	else
	{
		cout << "Zla wartosc dolnego zakresy\n";
		return 0;
	}
}
int beta_range()
{
	cout << "gorna wartosc: \n";
	cin >> beta;

	if (beta >= 0 && beta <= 255)
	{
		return 0;
	}
	else
	{
		cout << "Zla wartosc gornego zakresy\n";
		return 1;
	}
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

void Test()
{

	Mat element(3, 3, CV_8U, cv::Scalar(1));						//Okreslenie opcji erozji 
	const string window_name[] = { "binary" };
	namedWindow(window_name[0], CV_WINDOW_AUTOSIZE);
	
	inRange(hsv_split[0], alfa, beta, binary);                      //Progowanie zgodnie z wartosciami lowerb, i upperb			//hsv_split[0] - HUE - barwa
	blur(binary, binary, cv::Size(3, 3));							//Rozmycie 
	erode(binary, binary, element);									//Erozja 
	imshow(window_name[0], binary);									//Obraz binarny 

}


//tworzenie obrazu zakresu
void range_img()
{
	///inicjalizacja zmiennych
	int step_size = 300;
	int range_size = beta - alfa + 1;
	int range_step_i = 255 / range_size;
	int range_step_j = 255 / step_size;
	
	///Utworzenie wstepnej macierzy zakresu
	Mat range_hue(step_size, range_size, CV_64F);
	Mat range_val(step_size, range_size, CV_64F);
	Mat range_sat(step_size, range_size, CV_64F);
		
	for (int j = 0; j < range_hue.cols; j++)
	{
		for (int i = 0; i < range_hue.rows; i++)
		{
			range_hue.at<double>(i, j) = alfa + j;
			range_val.at<double>(i, j) = range_step_i*(1 + j);
			range_sat.at<double>(i, j) = range_step_j*(1 + i);
		}
	}	
		
	//Wy�wietlenie macierzy range_...
	cout << range_hue << endl;
	cout << range_val << endl;
	cout << range_sat << endl;

	///utworzenie macierzy zakresu
	Mat range_hsv, range_bgr=img;
	vector<Mat> range_hsv_split = hsv_split;

	///zmiana rozmiaru macierzy.
	range_hsv_split[0].create(step_size, range_size, CV_64F);
	range_hsv_split[1].create(step_size, range_size, CV_64F);
	range_hsv_split[2].create(step_size, range_size, CV_64F);
	range_bgr.create(step_size, range_size, CV_64F);
	
	///zapisanie macierzy do kanalow
	range_hsv_split[0] = range_hue;
	range_hsv_split[1] = range_val;
	range_hsv_split[2] = range_sat;
			
	//Wy�wietlenie macierzy range_...
	/*cout << range_hue << endl;
	cout << range_val << endl;
	cout << range_sat << endl;*/


	merge(range_hsv_split, range_hsv);

	//cvtColor(range_hsv, range_bgr, COLOR_HSV2BGR);

	//const string named_window[] = { "zakres" };
	//namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	//imshow(named_window[0], range_bgr);						//G+R

	//imwrite("../data/range_hsv.jpg", range_bgr, compression_params);

	cout << "test#100" << endl;
		
}

// funkcja zakres opcja 2
//void zakres()
//{
//	Mat binary;
//	alfa = 0;		//inicjalizacja pocz�tkowego dolnego progu 
//	beta = 255;		//inicjalizacja pocz�tkowego g�rnego progu 
//
//	const string named_window[] = { "zakres","img"};
//	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
//	namedWindow(named_window[1], CV_WINDOW_AUTOSIZE);
//
//	createTrackbar("lower_border", named_window[0], &alfa, 255, NULL);
//	createTrackbar("upper_border", named_window[0], &beta, 255, NULL);
//
//	inRange(hsv_split[0], alfa, beta, binary);
//
//	inRange(hsv_split[0], alfa, beta, binary);			//okre�lenie parametr�w progowania
//	cv::Mat element(3, 3, CV_8U, cv::Scalar(1));
//	blur(binary, binary, cv::Size(3, 3));				//Rozmycie 
//	erode(binary, binary, element);						//Erozja 
//	imshow(named_window[0], img);				        //Obrazek Orginalny 
//	imshow(named_window[1], binary);					//Obraz binarny 
//}

// funkcja zakres opcja 3
//void zakres()
//{
//	alfa = 0;		//inicjalizacja pocz�tkowego dolnego progu 
//	beta = 255;		//inicjalizacja pocz�tkowego g�rnego progu 
//	
//	const string named_window[] = { "zakres","img" };
//	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
//	namedWindow(named_window[1], CV_WINDOW_AUTOSIZE);
//
//	createTrackbar("lower_border", named_window[0], &alfa, 255, NULL);
//	createTrackbar("upper_border", named_window[0], &beta, 255, NULL);
//
//	while (cin.get() != '\n');
//
//	int sizes[] = { 3, 255, 255 };
//	Mat Pixel = Mat::zeros(3, sizes, CV_8UC3);
//
//
//}

//funkcja zakres opcja 4 (1+3)
//void zakres()
//{
//	alfa = 0;		//inicjalizacja pocz�tkowego dolnego progu 
//	beta = 255;		//inicjalizacja pocz�tkowego g�rnego progu 
//
//	cout << "Wprowadz zakres oczekiwanego koloru: " << endl;
//	cout << "dolna wartosc: ";
//	cin >> alfa;
//	cout << "gorna wartosc: ";
//	cin >> beta;
//
//	while (cin.get() != '\n');
//
//	int range_size = beta - alfa;
//	Mat range_colour(30,range_size,CV_64F);
//		
//	for (int i = 0; i < range_colour.rows; i++)
//	{
//		for (int j = 0; j < range_colour.cols; j++)
//		{
//			range_colour.at<double>(i, j) = alfa + i;
//		}
//	}	
//	
//	vector<Mat> test_vec;
//	split(range_colour, test_vec);
//
//
//
//
//	cout << "test" << endl;
//
//
//	while (cin.get() != '\n');
//}


// nie uzywana funkcja
void print_image()
{

}


//	HSV_to_BGR - test
//void HSV_to_BGR()
//{
//	Mat test_picture, test_hsv;
//	vector<Mat> test_hsv_split(3), test_new(3);
//	vector<int> paleta(vector<int>(255));
//
//	cout << "test 1 \n\n" << paleta.size();
//	
//	for (int j=0; j < 255; j++)
//	{
//		if (test_hsv_split[0][j] >= alfa || test_hsv_split[0][j] <= beta)
//			test_new[0][j] = test_hsv_split[0][j];
//		else
//			test_new[0].push_back(0);
//	}
//	
//	test_new[1] = Mat::zeros(img.rows, img.cols, CV_8UC1);
//	test_new[2] = Mat::zeros(img.rows, img.cols, CV_8UC1);
//	
//	//cvtColor(test_hsv, test_picture, CV_HSV2BGR);
//
//	const string named_window[] = { "test_hsv_to_BGR" };
//	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
//	imshow(named_window[0], test_new);
//
//	cout << "test 3 \n\n";
//	
//}


