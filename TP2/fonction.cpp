#include "fonction.h"

cv::Mat compare_frame(cv::Mat first_frame, cv::Mat current_frame)
{
	cv::Mat mask(first_frame.rows, first_frame.cols, CV_8UC1);
	int pixel;

	for (int i = 0; i < current_frame.rows ; i++) // pour chaque ligne
	{
		for (int y = 0; y < current_frame.cols ; y++) // et chaque colonne
		{
			
			pixel = abs((int)current_frame.at<unsigned char>(i, y) - (int)first_frame.at<unsigned char>(i, y));
			if(pixel > 10)
				mask.at<unsigned char>(i, y) = 255;
			else
				mask.at<unsigned char>(i, y) = 0;
		}
	}
	return mask;
}










































































//Mat diff(Mat img1, Mat img2)
//{
//	Mat imgDiff(img1.rows, img1.cols, img1.type());
//	for (size_t i = 0; i < img1.rows; i++)
//	{
//		for (size_t j = 0; j < img1.cols; j++)
//		{
//			int pix = abs((int)img1.at<unsigned char>(i, j) - (int)img2.at<unsigned char>(i, j));
//			imgDiff.at<unsigned char>(i, j) = (unsigned char)pix;
//		}
//	}
//	return imgDiff;
//}

//if (first_frame.at<unsigned int>(i, y) != current_frame.at<unsigned int>(i, y))    // compare composante bleu
			//{
			//	// met le pixel du masque en noir
			//	mask.at<unsigned int>(i, y) = 255;
			//}																					          
			//else
			//{
			//	// met le pixel du masque en blanc
			//	mask.at<unsigned int>(i, y) = 0;
			//}

