#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/// Global variables
const string file_name = ("choinka.jpg");	//nazwa obrazu do obróbki
Mat img, img_range, img_s_range, hsv, binary;
vector<Mat> hsv_split, bgr_split, image_split;
vector<int> compression_params;
int alfa = 0, beta = 0;
Mat img_B, img_G, img_R;
Mat binary_0, img_split_0, img_s;

void BGR_to_HSV();		/*Funkcja odpowiedzialna za konwersje obrazu BGR na HSV.*/
void BGR();				/*Funkcja odpowiedzialna za wyœwietlenie kana³ów i sk³adowych BGR.*/
void Blue();			/*Funkcja wyœwietlaj¹ca sk³adow¹ Blue obrazu.*/
void Green();			/*Funkcja wyœwietlaj¹ca sk³adow¹ Green obrazu.*/
void Red();				/*Funkcja wyœwietlaj¹ca sk³adow¹ Red obrazu.*/
void zakres();			/*Funkcja pozwalaj¹ca wprowadzenie zakresu kolorów.*/
void range_img();		/*Funkcja wyœwietlaj¹ca zakres wybranych kolorów.*/
void Test();			/*Funkcja testowa.*/
void print_image();		/*      Funkcja nie u¿ywana     */
int alfa_range();		/*Dolny zakres.*/
int beta_range();		/*Górny zakres.*/

//void HSV_to_BGR();

int main(void)
{
	///wczytanie obrazów
	img = imread("../data/" + file_name);
	img_range = imread("../data/img_range_0.jpg");
	img_s_range = imread("../data/img_range.jpg");

	///Ustawienia parametrów obrazów
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);		//Konwersja jpg 
	compression_params.push_back(100);							//Jakosc 100 
	
	///Stworzenie ogna na grafike
	const string window_0[] = { "Range"};
	namedWindow(window_0[0], CV_WINDOW_AUTOSIZE);
	imshow(window_0[0], img_range);	//Wyœwietlenie grafiki zakresu w oknie

	///Sprawdzenie poprawnoœci za³adowanie obrazu do obróbki
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
	///Wyœwietlenei wybranego zakresu kolorów
	range_img();

	///Konwersja obrazu z BGR na HSV
	BGR_to_HSV();
	
	Test();
	
	///Funkcje chwilowo nie u¿ywane
	//BGR();
	//HSV_to_BGR();
			
	cout << "test#100" << endl;	//Informacja testowa

	waitKey(0);
	return 0;
}

///Wprowadzenie zakresu progowania kolorów
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
///Wprowadzenie dolnego(alfa) i górnego(beta) zakresu koloru
int alfa_range()
{
	cout << "dolna wartosc: \n";
	cin >> alfa;

	if (alfa >= 0 && alfa <= 179)
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

	if (beta >= 0 && beta <= 179 && beta != alfa)
	{
		return 0;
	}
	else
	{
		cout << "Zla wartosc gornego zakresy\n";
		return 1;
	}
}

///Konwersja przestrzeni barw w OpenCV
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
	split(hsv, hsv_split);										//Rozdzielenie HSV na poszczególne kana³y 

	///Wyswietlenie poszczegolnych obrazow
	imshow(named_window[0], img);								//Obraz oryginalny 
	imshow(named_window[1], hsv);								//Obraz w wersji HSV 
	imshow(named_window[2], hsv_split[0]);						//Barwa
	imshow(named_window[3], hsv_split[1]);						//Nasycenie 
	imshow(named_window[4], hsv_split[2]);						//Wartosc 

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
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);    
	namedWindow(named_window[1], CV_WINDOW_AUTOSIZE);
	namedWindow(named_window[2], CV_WINDOW_AUTOSIZE);

	split(img, bgr_split);	//rozdzielenie kana³ów obrazu

	///Wyœwietlenie obrazów poszczególnych kana³ów BGR (czarno-bia³e; macierz wartoœci)
	imshow(named_window[0], bgr_split[0]);						//B
	imshow(named_window[1], bgr_split[1]);						//G
	imshow(named_window[2], bgr_split[2]);						//R
	
	///Wyœwietlenie obrazów poszczególnych kana³ów BGR (w poszczególnych kolorach)
	Blue();
	Green();
	Red();

	///Zapisanie obrazów
	imwrite("../data/Blue.jpg", bgr_split[0], compression_params);
	imwrite("../data/Green.jpg", bgr_split[1], compression_params);
	imwrite("../data/Red.jpg", bgr_split[2], compression_params);
}
void Blue()
{
	vector<Mat>  split_img;
	split(img, split_img);	//podzia³ obrazu na kana³y

	///wyzerowanie kana³ów G i R
	split_img[1] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	split_img[2] = Mat::zeros(img.rows, img.cols, CV_8UC1);

	merge(split_img, img_B);	//scalenie kana³ów
	
	///Stworzenie okien
	const string named_window[] = { "Blue" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], img_B);	//Wyœwietlenie sk³adowej Blue

	imwrite("../data/img_Blue.jpg", img_B, compression_params);	//Zapisanie sk³adowej obrazu Blue
}
void Green()
{
	vector<Mat>  split_img;
	split(img, split_img);	//podzia³ obrazu na kana³y

	///wyzerowanie kana³ów B i R
	split_img[0] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	split_img[2] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	merge(split_img, img_G);	//scalenie kana³ów

	///Stworzenie okien
	const string named_window[] = { "Green" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], img_G);	//Wyœwietlenie sk³adowej Green

	imwrite("../data/img_Green.jpg", img_G, compression_params);	//Zapisanie sk³adowej obrazu Green
}
void Red()
{
	vector<Mat>  split_img;
	split(img, split_img);	//podzia³ obrazu na kana³y

	///wyzerowanie kana³ów B i G
	split_img[0] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	split_img[1] = Mat::zeros(img.rows, img.cols, CV_8UC1);
	merge(split_img, img_R);	//scalenie kana³ów

	///Stworzenie okien
	const string named_window[] = { "Red" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], img_R);	//Wyœwietlenie sk³adowej Red

	imwrite("../data/img_Red.jpg", img_R, compression_params);	//Zapisanie sk³adowej obrazu Red
}

///wyœwietlenie wybranego zakresu
void range_img()
{
	Mat img_hsv;
	vector<Mat> img_hsv_split;
	Mat element(3, 3, CV_8U, cv::Scalar(1));	//Okreslenie opcji erozji 

	cvtColor(img_s_range, img_hsv, CV_BGR2HSV);	//Konwersja BGR->HSV
	split(img_hsv, img_hsv_split);	//Rozdzielenie HSV na poszczególne kana³y 
	
	///Progowanie zgodnie z wartosciami lowerb, i upperb (hsv_split[0] - HUE - barwa)
	if (alfa > beta)
	{
		inRange(img_hsv_split[0], beta, alfa, binary);	
		inRange(binary, 0, 1, binary);
	}
	else
	{
		inRange(img_hsv_split[0], alfa, beta, binary);
	}

	blur(binary, binary, cv::Size(3, 3));	//Rozmycie 
	erode(binary, binary, element);	//Erozja 

	img_hsv_split[2] = binary;
	merge(img_hsv_split, img_hsv);	//scalenie kana³ów
	cvtColor(img_hsv, img_s_range, COLOR_HSV2BGR);	//Konwersja HSV -> BGR

	///Stworzenie okien
	const string named_window[] = { "zakres", "binary" };
	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
	imshow(named_window[0], img_s_range);
	
	///Zapis poszczegolnych obrazow 
	imwrite("../data/range_selected.jpg", img_s_range, compression_params);
}

void Test()
{

}

///Funkcja testowa - progowanie kolorow wg zakresu
//void Test()
//{
//	Mat element(3, 3, CV_8U, cv::Scalar(1));	//Okreslenie opcji erozji 
//
//	if (alfa > beta)
//	{
//		inRange(hsv_split[0], beta, alfa, binary_0);
//		inRange(binary_0, 0, 1, binary_0);
//	}
//	else
//	{
//		inRange(hsv_split[0], alfa, beta, binary_0);
//	}
//
//	blur(binary_0, binary_0, cv::Size(3, 3));	//Rozmycie 
//	erode(binary_0, binary_0, element);	//Erozja 
//
//	hsv_split[2] = binary_0;
//	merge(hsv_split, img_split_0);	//scalenie kana³ów
//	cvtColor(img_split_0, img_s, COLOR_HSV2BGR);	//Konwersja HSV -> BGR
//
//	///Stworzenie okien
//	const string named_window[] = { "obraz po progowaniu" };
//	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
//	imshow(named_window[0], img_s);
//
//	///Zapis poszczegolnych obrazow 
//	imwrite("../data/after.jpg", img_s, compression_params);
//}

///range_img ver 1.0
//void range_img()
//{
//	vector<Mat> range_hsv_split = hsv_split;
//	Mat range_hsv, range_bgr;
//	Mat element(3, 3, CV_8U, cv::Scalar(1));						//Okreslenie opcji erozji 
//	const string named_window[] = { "zakres", "binary"};
//	namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
//	namedWindow(named_window[1], CV_WINDOW_AUTOSIZE);
//
//	if (alfa > beta)
//	{
//		inRange(hsv_split[0], beta, alfa, binary);                  //Progowanie zgodnie z wartosciami lowerb, i upperb			//hsv_split[0] - HUE - barwa
//		inRange(binary, 0, 50, binary);
//	}
//	else
//	{
//		inRange(hsv_split[0], alfa, beta, binary);                  //Progowanie zgodnie z wartosciami lowerb, i upperb			//hsv_split[0] - HUE - barwa
//	}
//
//	blur(binary, binary, cv::Size(3, 3));							//Rozmycie 
//	erode(binary, binary, element);									//Erozja 
//		
//	range_hsv_split[2] = binary;
//	merge(range_hsv_split, range_hsv);
//	cvtColor(range_hsv, range_bgr, COLOR_HSV2BGR);
//		
//	imshow(named_window[0], range_bgr);				
//	imshow(named_window[1], range_hsv_split[2]);
//
//}

///tworzenie obrazu zakresu
//void range_img()
//{
//	///inicjalizacja zmiennych
//	int step_size = 300;
//	int range_size = beta - alfa + 1;
//	int range_step_i = 255 / range_size;
//	int range_step_j = 255 / step_size;
//	
//	///Utworzenie wstepnej macierzy zakresu
//	Mat range_hue(step_size, range_size, CV_64F);
//	Mat range_val(step_size, range_size, CV_64F);
//	Mat range_sat(step_size, range_size, CV_64F);
//
//
//		
//	for (int j = 0; j < range_hue.cols; j++)
//	{
//		for (int i = 0; i < range_hue.rows; i++)
//		{
//			range_hue.at<double>(i, j) = alfa + j;
//			range_val.at<double>(i, j) = range_step_i*(1 + j);
//			range_sat.at<double>(i, j) = range_step_j*(1 + i);
//		}
//	}	
//		
//	//Wyœwietlenie macierzy range_...
//	cout << range_hue << endl;
//	cout << range_val << endl;
//	cout << range_sat << endl;
//
//	///utworzenie macierzy zakresu
//	Mat range_hsv, range_bgr=img;
//	vector<Mat> range_hsv_split = hsv_split;
//
//	///zmiana rozmiaru macierzy.
//	range_hsv_split[0].create(step_size, range_size, CV_64F);
//	range_hsv_split[1].create(step_size, range_size, CV_64F);
//	range_hsv_split[2].create(step_size, range_size, CV_64F);
//	range_bgr.create(step_size, range_size, CV_64F);
//	
//	///zapisanie macierzy do kanalow
//	range_hsv_split[0] = range_hue;
//	range_hsv_split[1] = range_val;
//	range_hsv_split[2] = range_sat;
//			
//	//Wyœwietlenie macierzy range_...
//	/*cout << range_hue << endl;
//	cout << range_val << endl;
//	cout << range_sat << endl;*/
//
//
//	merge(range_hsv_split, range_hsv);
//
//	//cvtColor(range_hsv, range_bgr, COLOR_HSV2BGR);
//
//	//const string named_window[] = { "zakres" };
//	//namedWindow(named_window[0], CV_WINDOW_AUTOSIZE);
//	//imshow(named_window[0], range_bgr);						//G+R
//
//	//imwrite("../data/range_hsv.jpg", range_bgr, compression_params);
//
//	cout << "test#100" << endl;
//		
//}

/// funkcja zakres opcja 2
//void zakres()
//{
//	Mat binary;
//	alfa = 0;		//inicjalizacja pocz¹tkowego dolnego progu 
//	beta = 255;		//inicjalizacja pocz¹tkowego górnego progu 
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
//	inRange(hsv_split[0], alfa, beta, binary);			//okreœlenie parametrów progowania
//	cv::Mat element(3, 3, CV_8U, cv::Scalar(1));
//	blur(binary, binary, cv::Size(3, 3));				//Rozmycie 
//	erode(binary, binary, element);						//Erozja 
//	imshow(named_window[0], img);				        //Obrazek Orginalny 
//	imshow(named_window[1], binary);					//Obraz binarny 
//}

/// funkcja zakres opcja 3
//void zakres()
//{
//	alfa = 0;		//inicjalizacja pocz¹tkowego dolnego progu 
//	beta = 255;		//inicjalizacja pocz¹tkowego górnego progu 
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

///funkcja zakres opcja 4 (1+3)
//void zakres()
//{
//	alfa = 0;		//inicjalizacja pocz¹tkowego dolnego progu 
//	beta = 255;		//inicjalizacja pocz¹tkowego górnego progu 
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


///	HSV_to_BGR - test
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


