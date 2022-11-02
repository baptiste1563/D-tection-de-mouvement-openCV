#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "fonction.h"
#include <ctime>
#include <ratio>
#include <chrono>


using namespace cv;
using namespace std;

int main()
{
	int ct = 1;
	bool repeat = true;
	std::string file = "111.mp4";
	VideoCapture video(file);
	if (!video.isOpened()) {
		//error in opening the video input
		cerr << "\n\n\nUnable to open: " << file <<"   : C'est la gigas sauce la en gros\n\n\n" << endl;
		return 0;
	}

	int nb_frame = int(video.get(CAP_PROP_FRAME_COUNT));

	Ptr<BackgroundSubtractor> pBackSub_MOG2;
	pBackSub_MOG2 = createBackgroundSubtractorMOG2();

	Ptr<BackgroundSubtractor> pBackSub_KNN;
	pBackSub_KNN = createBackgroundSubtractorKNN();

	Mat frame;
	Mat first_frame;
	Mat mask;

	Mat frameG, first_frameG, maskG, mask_MOG2, mask_KNN;

	Algorithm test;

	//chonometre 
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	
	std::chrono::duration<double> time_algo_maison;
	std::chrono::duration<double> time_algo_MOG2;
	std::chrono::duration<double> time_algo_KNN;


	video >> first_frame; // recup premiere image

	cvtColor(first_frame, first_frameG, COLOR_BGR2GRAY ); // convert 1er image en niveau gris

	//--------------------------------------test vitesse algo------------------------------------//

	video >> frame;

	//avec Algo maison
	t1 = std::chrono::high_resolution_clock::now(); //heure de début
	cvtColor(frame, frameG, COLOR_BGR2GRAY); // la convertion en noir et blanc est inclue dans le temps de calcul pour le fait maison
	mask = compare_frame(first_frameG, frameG); 
	t2 = std::chrono::high_resolution_clock::now(); //heure de fin
	time_algo_maison = t2 - t1;  //calcul durée 

	//avec Algo MOG2
	t1 = std::chrono::high_resolution_clock::now();
	pBackSub_MOG2->apply(frame, mask_MOG2); 
	t2= std::chrono::high_resolution_clock::now();
	time_algo_MOG2 = t2 - t1;

	//avec Algo KNN
	t1 = std::chrono::high_resolution_clock::now();
	pBackSub_KNN->apply(frame, mask_KNN); 
	t2 = std::chrono::high_resolution_clock::now();	
	time_algo_KNN = t2 - t1;


	cout << "l'agorithme maison s'execute en : " << time_algo_maison << "\n";
	cout << "l'agorithme MOG2 s'execute en : " << time_algo_MOG2 << "\n";
	cout << "l'agorithme KNN s'execute en : " << time_algo_KNN << "\n";



	while (repeat && nb_frame > ct) 
	{
		//-----------------------------------------recup frame----------------------------------------------------------------//

		video >> frame; 

		//-----------------------------------------convert chaque frame en niveau de gris pour Algo maison--------------------//

		cvtColor(frame, frameG, COLOR_BGR2GRAY);  

		//-----------------------------------------creation du masque---------------------------------------------------------//

		mask = compare_frame(first_frameG, frameG); //avec Algo maison

		pBackSub_MOG2->apply(frame, mask_MOG2);  //avec Algo MOG2 

		pBackSub_KNN->apply(frame, mask_KNN);   //avec Algo MOG2 


		// ----------------------------------------pour sortir de l'affichage-------------------------------------------------//

		char esc = (char)waitKey(25);
		if (esc == 27)
			repeat = false;

		// ----------------------------------------affichage------------------------------------------------------------------//

		imshow("Video de base", frame); 
		imshow("Algorithm maison", mask); 
		imshow("Algorithm MOG2", mask_MOG2); 
		imshow("Algorithm KNN", mask_KNN); 

		ct++; // interiation du compteur
	}



	video.release();


}