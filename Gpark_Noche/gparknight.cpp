//conteo de carros en la noche

//libs
#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "scontour.cpp"
#include "smatch.cpp"
#include "sbss.cpp"

using namespace std;
using namespace cv;


void colorReduceEfficient(cv::Mat &image, int div)//para imagenes que no estan rellenas del todo
{
    int nl=image.rows;
    int nc=image.cols;

    if(image.isContinuous())
    {
        //then no padded pixels
        nc=nc*nl;
        nl=1;//it is now a 1D array
    }
    //this loop is executed only once in case of a continuous image
    for(int j=0; j<nl; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for(int i=0; i<nc; i++)
        {
            //process each pixel
            data[i]=data[i]/div*div +div/2;
            //end pixel processing
        }//end for
    }//end for

}


int main(int argc, char** argv){


//counters
	int acum=0;
	int BuffPoss=0;
	int PixDiff=0;
	long ImageMean=0;
	int sumcounter=0;
	int k=0;//cambios entre oclusion y no oclusion

//Umbrals

	float perimeter=0;
	float perimeterMin=0.7;

//Colors

	CvScalar BLACK=cvScalar(0,0,0);
	CvScalar WHITE=cvScalar(255,255,255);

//Image Regions

	CvRect rect;


//get frames from video
	CvCapture* capture= cvCreateFileCapture("video_686.avi");

//Images
	IplImage* frame=NULL;
	IplImage* FrameSeed=NULL;
	IplImage* frameRain=NULL;
	IplImage* frameAnt=NULL;
	IplImage* frameSub=NULL;
	IplImage* FrameGray=NULL;
	IplImage* FrameGray2=NULL;
	IplImage* FrameGray3=NULL;//para inpaint
	IplImage* FrameMedian=NULL;
	IplImage* frameSobel=NULL;
	IplImage* frameSobel2=NULL;	
	IplImage* frameSobelNC=NULL;
	IplImage* div=NULL;
	IplImage* inpaint=NULL;
	IplImage* RainSpace=NULL;
	IplImage* RainSpaceGray=NULL;
	Mat resultado2;
	cv::VideoCapture videoApi;//para conocer numero de frames
	videoApi.open("video_686.avi"); 
	int NumberFrames=(int)videoApi.get(CV_CAP_PROP_FRAME_COUNT); //obtiene numero de frames del video
	int  HistPix[((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH))][((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))];
	int  profundidad[((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH))][((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))];
	//int  HistPixOclusion[((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH))][((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))][10];//limite de memoria
	bool Ocupado[((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH))][((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))];
	int cambios[((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH))][((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))];
	vector<vector<vector<int> > > HistPixOclusion;

 	// Set up sizes. (HEIGHT x WIDTH)
	HistPixOclusion.resize((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT));
	  for (int i = 0; i < (int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT); ++i) 
	  {
	    HistPixOclusion[i].resize((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH));

	    for (int j = 0; j < (int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH); ++j)
	      HistPixOclusion[i][j].resize(NumberFrames);
          }

	
	
	
	

//Buffer images
	IplImage* frameBuf1=NULL;
	IplImage* frameBuf2=NULL;
	IplImage* frameBuf3=NULL;
	IplImage* frameBuf4=NULL;
	IplImage* frameBuf5=NULL;
	IplImage* frameBuf6=NULL;
	IplImage* frameBuf7=NULL;
	IplImage* frameBuf8=NULL;
	IplImage* frameBuf9=NULL;
	IplImage* frameBuf10=NULL;
	IplImage* frameBuf11=NULL;
	IplImage* frameBuf12=NULL;
	IplImage* frameBuf13=NULL;
	IplImage* frameBuf14=NULL;
	IplImage* frameBuf15=NULL;
	IplImage* frameBuf16=NULL;
	IplImage* frameBuf17=NULL;
	IplImage* frameBuf18=NULL;
	IplImage* frameBuf19=NULL;
	IplImage* frameBuf20=NULL;
	
	IplImage* frameBuf1Rain=NULL;
	IplImage* frameBuf2Rain=NULL;
	IplImage* frameBuf3Rain=NULL;
	IplImage* frameBuf4Rain=NULL;
	IplImage* frameBuf5Rain=NULL;
	IplImage* frameBuf6Rain=NULL;
	IplImage* frameBuf7Rain=NULL;
	IplImage* frameBuf8Rain=NULL;
	IplImage* frameBuf9Rain=NULL;
	IplImage* frameBuf10Rain=NULL;
	IplImage* frameBuf11Rain=NULL;
	IplImage* frameBuf12Rain=NULL;
	IplImage* frameBuf13Rain=NULL;
	IplImage* frameBuf14Rain=NULL;
	IplImage* frameBuf15Rain=NULL;
	IplImage* frameBuf16Rain=NULL;
	IplImage* frameBuf17Rain=NULL;
	IplImage* frameBuf18Rain=NULL;
	IplImage* frameBuf19Rain=NULL;
	IplImage* frameBuf20Rain=NULL;

	IplImage* frameBuf1Gray=NULL;
	IplImage* frameBuf2Gray=NULL;
	IplImage* frameBuf3Gray=NULL;
	IplImage* frameBuf4Gray=NULL;
	IplImage* frameBuf5Gray=NULL;
	IplImage* frameBuf6Gray=NULL;
	IplImage* frameBuf7Gray=NULL;
	IplImage* frameBuf8Gray=NULL;
	IplImage* frameBuf9Gray=NULL;
	IplImage* frameBuf10Gray=NULL;
	IplImage* frameBuf11Gray=NULL;
	IplImage* frameBuf12Gray=NULL;
	IplImage* frameBuf13Gray=NULL;
	IplImage* frameBuf14Gray=NULL;
	IplImage* frameBuf15Gray=NULL;
	IplImage* frameBuf16Gray=NULL;
	IplImage* frameBuf17Gray=NULL;
	IplImage* frameBuf18Gray=NULL;
	IplImage* frameBuf19Gray=NULL;
	IplImage* frameBuf20Gray=NULL;

	IplImage* frameBuf1Mask=NULL;
	IplImage* frameBuf2Mask=NULL;
	IplImage* frameBuf3Mask=NULL;
	IplImage* frameBuf4Mask=NULL;
	IplImage* frameBuf5Mask=NULL;
	IplImage* frameBuf6Mask=NULL;
	IplImage* frameBuf7Mask=NULL;
	IplImage* frameBuf8Mask=NULL;
	IplImage* frameBuf9Mask=NULL;
	IplImage* frameBuf10Mask=NULL;
	IplImage* frameBuf11Mask=NULL;
	IplImage* frameBuf12Mask=NULL;
	IplImage* frameBuf13Mask=NULL;
	IplImage* frameBuf14Mask=NULL;
	IplImage* frameBuf15Mask=NULL;
	IplImage* frameBuf16Mask=NULL;
	IplImage* frameBuf17Mask=NULL;
	IplImage* frameBuf18Mask=NULL;
	IplImage* frameBuf19Mask=NULL;
	IplImage* frameBuf20Mask=NULL;
	

	IplImage* buffer[20] = {frameBuf1, frameBuf2, frameBuf3, frameBuf4, frameBuf5,frameBuf6, frameBuf7, frameBuf8, frameBuf9, frameBuf10,frameBuf11, frameBuf12, frameBuf13, frameBuf14, frameBuf15,frameBuf16, frameBuf17, frameBuf18, frameBuf19, frameBuf20 };
	IplImage* bufferRain[20] = {frameBuf1Rain, frameBuf2Rain, frameBuf3Rain, frameBuf4Rain, frameBuf5Rain,frameBuf6Rain, frameBuf7Rain, frameBuf8Rain, frameBuf9Rain, frameBuf10Rain,frameBuf11Rain, frameBuf12Rain, frameBuf13Rain, frameBuf14Rain, frameBuf15Rain,frameBuf16Rain, frameBuf17Rain, frameBuf18Rain, frameBuf19Rain, frameBuf20Rain };		
	IplImage* bufferGray[20] = {frameBuf1Gray, frameBuf2Gray, frameBuf3Gray, frameBuf4Gray, frameBuf5Gray,frameBuf6Gray, frameBuf7Gray, frameBuf8Gray, frameBuf9Gray, frameBuf10Gray,frameBuf11Gray, frameBuf12Gray, frameBuf13Gray, frameBuf14Gray, frameBuf15Gray,frameBuf16Gray, frameBuf17Gray, frameBuf18Gray, frameBuf19Gray, frameBuf20Gray };	
	IplImage* bufferMask[20] = {frameBuf1Mask, frameBuf2Mask, frameBuf3Mask, frameBuf4Mask, frameBuf5Mask,frameBuf6Mask, frameBuf7Mask, frameBuf8Mask, frameBuf9Mask, frameBuf10Mask,frameBuf11Mask, frameBuf12Mask, frameBuf13Mask, frameBuf14Mask, frameBuf15Mask,frameBuf16Mask, frameBuf17Mask, frameBuf18Mask, frameBuf19Mask, frameBuf20Mask };	


	sContour *handlercontour=new sContour;
	sMatch *handlermatch=new sMatch;



//loop
	while(1){


		//objets

		
		

		//vintage frame copy

		if(frame){
			frameAnt=cvCreateImage(cvGetSize(frame),8,3);//Get size and depth 
			cvCopy(frame,frameAnt);
			//cout<<"estoy aca"<<endl;

		}



		//cvSetImageROI();// for speed
		frame=cvQueryFrame(capture);//catch frames
		if(!frame) break;//Go out if aren't frames
		




		////////////////////filling buffer//////////////////////////

		cvReleaseImage(&buffer[BuffPoss]);//clean buffer position
		buffer[BuffPoss]=cvCreateImage(cvGetSize(frame),8,3);//Get size and depth 
                cvCopy(frame,buffer[BuffPoss]);//copy current frame in buffer position               
		BuffPoss++;//
		if(BuffPoss==19) BuffPoss=0;//Reset buffer position


////////////////////////////////////////////////////////////////////////////////////////////////


		
		FrameGray=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth 
		FrameGray2=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth 
		FrameGray3=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth	
		inpaint=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth 
		frameSub=cvCreateImage(cvGetSize(frame),8,3);//Get size and depth 
		RainSpace=cvCreateImage(cvGetSize(frame),8,3);//Get size and depth
		RainSpaceGray=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth
		frameRain=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth
		div=cvCreateImage(cvGetSize(frame),8,3);//Get size and depth 
		FrameMedian=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth


		//Resta
		if(frameAnt)cvSub(frame, frameAnt, frameSub );
		cvShowImage("Diferencia",frameSub);
		frameSobel=cvCreateImage(cvGetSize(frame),8,1); //Get size and depth
		frameSobel2=cvCreateImage(cvGetSize(frame),8,1); //Get size and depth
		FrameSeed=cvCreateImage(cvGetSize(frame),8,1); //Get size and depth
		frameSobelNC=cvCreateImage(cvGetSize(frame),8,1); //Get size and depth
		cvCvtColor( frameSub,FrameGray, CV_BGR2GRAY);//Change color space to gray
		cvCvtColor( frame,FrameGray2, CV_BGR2GRAY);//Change color space to gray
		
		
		/*while(acum<10){
		
			cvSmooth(FrameGray,FrameGray,CV_GAUSSIAN,3,0,0,0);
			acum++;
		}*/
		
		acum=0;

		//cvShowImage("sin sobel",FrameGray);
		cvSobel(FrameGray,frameSobel2,1,0,1);
		//cvShowImage("sobel",frameSobel2);
		cvThreshold(frameSobel2,frameSobel,20,255,CV_THRESH_BINARY);
		cvDilate(frameSobel,frameSobel,NULL,2);
		//cvMorphologyEx(frameSobel,frameSobel,NULL,NULL,CV_MOP_CLOSE,10);
		cvCopy(frameSobel,frameSobelNC);
		
		/////////////////////////Contours//////////////////////////

		CvSeq *contours= handlercontour->sGetContourn(frameSobel);//Get contours



		for(CvSeq* c=contours; c!=NULL; c=c->h_next)//Erase noise
		{  
	   		perimeter=cvArcLength(c, CV_WHOLE_SEQ,-1);//calculo el largo del contorno

	   		if(perimeter < perimeterMin)//compara si el largo del contorno recien allado es mayor que el ultimo contorno mas largo
	   		{ 
		   		  cvDrawContours(frameSobel,
		                 c,//dibuja el contorno c
		                 BLACK, //color externo
		                 WHITE, //color interno
		                 0,    //indica q solo son dibujados el contorno selesccionado y sus vecinos
		                 -1,    //grueso de la linea
		                 8); // tipo de linea		      
	   		}     
 		}
		
////////////////////////////////////////////////////////////////////////////
		
		/*for(CvSeq* c=contours; c!=NULL; c=c->h_next)//recorre cada contorno
		{  

			rect = cvBoundingRect(c,1);//rectangulo contenedor
			for(int buffNum=0;buffNum<5;buffNum++){//recorre cada imagen
				if(buffer[buffNum]!=NULL){//si hay algo en esa posicion del buffer
                        		cvSetImageROI(buffer[buffNum],rect);//-------------------->reemplazar no usar rectangulo,dibujar contornos
					bufferGray[buffNum]=cvCreateImage(cvGetSize(buffer[buffNum]),8,1);//Get size and depth 
					cvCvtColor( buffer[buffNum],bufferGray[buffNum], CV_BGR2GRAY);//Change color space to gray
					PixDiff=handlermatch->pixval(bufferGray[buffNum],180);//encuentra numero de pixeles que superan un valor
 //cout<<PixDiff<<endl;
						
					if(PixDiff<5){//si la imagen en esa zona no esta muy iluminada
					ImageMean=ImageMean+ (handlermatch->pixval(bufferGray[buffNum]));//calcula valor promedio de intensidad en esa zona
					//cambiar para que en cuentre el valor promedio pixel a pixel a traves del buffer

//cout<<ImageMean<<endl;
					}
					
					
				}
				PixDiff=0;
				

			}
			ImageMean=ImageMean/5;
			cvSetImageROI(FrameGray,rect);

			handlermatch->pixval(FrameGray,ImageMean);
			cout<<ImageMean<<endl;
			ImageMean=0;
			cvResetImageROI(FrameGray);
			

		}*/

////////////////////////////////////////////////////////////////////////////////////////////	

/////////////////////////////operations with buffer images///////////////////////////////

		
                cvSub(FrameGray2,frameSobel,frameRain);//sub scalar from matrix
		
		//cvShowImage("sobel a original",frameSobel2);
		//cvShowImage("sin filtro",frameSobelNC);
		cvShowImage("Video Original",frame);
		
		//cvSet(frameSobel,cvScalar(0,0,0));
		
                cvAdd(FrameGray,frameSobel,FrameGray);

		FrameSeed = handlercontour->gSetMaskSeed2(FrameGray,0,50,255,20);
		cvThreshold(FrameSeed,FrameSeed,200,255,CV_THRESH_BINARY);

////////////////////////////////Pix value correction//////////////////////////////
//cvShowImage("bufferMask antes",buffer[3]);


		float valor=0;;
		float valorMask=0;
		int valorReplace=0;
		CvScalar intensidad;
		CvScalar intensidadMask;
		CvScalar intensidadSet=cvScalar(140,140,140);
		int i=0,j=0;
		long pix=0;
		while(i< frame->width){
			while(j< frame->height){
				    intensidad = cvGet2D(FrameSeed,j, i);
				    valor = intensidad.val[0] ;
				    if(valor>230){
					
					for(int buffNum=0;buffNum<20;buffNum++){
						if(bufferMask[buffNum]){
							intensidadMask = cvGet2D(bufferMask[buffNum],j, i);
							valorMask = intensidadMask.val[0] ;
							//printf("entre %f \n",valorMask);
							if(valorMask>200){
								//cvSet(buffer[buffNum],cvScalar(0,0,0));//set pixels to 0
								intensidadSet=cvScalar(valorReplace,valorReplace,valorReplace);
								cvSet2D( buffer[buffNum], j, i,intensidadSet);
								
								}
							if(valorMask<200){
								intensidadSet = cvGet2D(buffer[buffNum],j, i);
								valorReplace=intensidadSet.val[0] ;
								//printf("entre %d \n",valorReplace);
							}
						}
					}
			            }
				//
				j++;
				}
			j=0;
			i++;
			}


		cvDilate(FrameSeed,FrameSeed,NULL,2);
		cvShowImage("FrameSeed",FrameSeed);
		
		Mat PixOcupados(FrameSeed);

		//Verificacion de pixeles oclusionados por gotas
		int value=0;
		for(int i=0;i< PixOcupados.size().width;i++){//hasta el ancho de la imagen
			    for(int j=0;j< PixOcupados.size().height;j++){//hasta el alto de la imagen
				 value=PixOcupados.at<uchar>(j,i);
				
				if(value > 2 &&  Ocupado[j][i]==false)profundidad[j][i]++;			



				 if(value > 2){
					HistPix[j][i]=HistPix[j][i]+1;
					Ocupado[j][i]=true;
				}

				if(value > 2 &&  Ocupado[j][i]==true)	
				{
					HistPixOclusion[j][i][profundidad[j][i]]=HistPixOclusion[j][i][profundidad[j][i]] + 1;
				}	


 				if(value < 2 && Ocupado[j][i]==true)
				{
					cambios[j][i]++;
					Ocupado[j][i]=false;
				}

				value=0;

			    }
			}



		cvInpaint(FrameGray2,FrameSeed,inpaint,2,CV_INPAINT_TELEA);
		cvShowImage("inpaint",inpaint);

///////////////////////////////Creatin rain replace/////////////////////////////

		cvSet( div, cvScalar(19,19,19), NULL);

                //images to paste rain copy
		sumcounter=1;
                for(int buffNum=0;buffNum<20;buffNum++){

			if(buffer[buffNum]!=NULL){//si hay algo en esa posicion del buffer

				bufferRain[buffNum]=cvCreateImage(cvGetSize(buffer[buffNum]),8,3);//Get size and depth
				bufferGray[buffNum]=cvCreateImage(cvGetSize(buffer[buffNum]),8,3);//Get size and depth 
				cvCopy(buffer[buffNum],bufferRain[buffNum],FrameSeed);
				cvDiv( bufferRain[buffNum], div,  bufferRain[buffNum], 1 );
				if(sumcounter>3)sumcounter=0;
				if(bufferRain[sumcounter]!=NULL){
					cvAdd(RainSpace,bufferRain[buffNum],RainSpace);
					
				}
				sumcounter++;
			}

		}


		cvCvtColor( RainSpace,RainSpaceGray, CV_BGR2GRAY);//Change color space to gray

		cvSub(FrameGray2,FrameSeed, FrameGray2);//sub rain drops
		//cvErode(FrameSeed,FrameSeed,NULL,2);
		cvCopy(RainSpaceGray,FrameGray2,FrameSeed);//place new values in rain drops space


//////////////////////////////////////filtro/////////////////////////////////////////////////////
		/*int a=0;
		while(a<2){
		cvSmooth(FrameGray2,FrameGray2,CV_GAUSSIAN,3,0,0,0);
		a++;
		}*/
		
		
		//cvShowImage("FrameSeed antes",FrameSeed);
		/*FrameSeed = handlercontour->rotate(FrameSeed,180);
		FrameSeed = handlercontour->gSetMaskSeed2(FrameSeed,0,50,0,100);
		FrameSeed = handlercontour->gSetMaskSeed(FrameSeed,0,30,0,100);
		//FrameSeed = handlercontour->gSetMaskSeed(FrameSeed,0,30,0,30);
		FrameSeed = handlercontour->rotate(FrameSeed,180);
		//FrameSeed = handlercontour->gSetMaskSeed(FrameSeed,0,30,0,30);*/

               // cvInpaint(FrameGray2,FrameSeed,FrameGray3,1,CV_INPAINT_TELEA);


		cvShowImage("Video Procesado",FrameGray2);
		Mat resultado(FrameGray2,false);
		cvtColor(resultado,resultado2,CV_GRAY2BGR);
		//pyrMeanShiftFiltering(resultado2, resultado2, 20, 40, 2);
		colorReduceEfficient(resultado,32);
		//imshow("Discretizacion",resultado);

////////////////////////////////////filling Mask buffer//////////////////////////////////////////

		cvReleaseImage(&bufferMask[BuffPoss]);//clean buffer position
		bufferMask[BuffPoss]=cvCreateImage(cvGetSize(frame),8,1);//Get size and depth 
                cvCopy(FrameSeed ,bufferMask[BuffPoss]);//copy current frame in buffer position               
		//BuffPoss++;//
		//if(BuffPoss==4) BuffPoss=0;//Reset buffer position



		
		
		//cvShowImage("FrameSeed",FrameSeed);

                
		cvSet(RainSpace,cvScalar(0,0,0));//set pixels to 0

		//delete handlercontour;//-------------------->fuga
		cvReleaseImage(&FrameMedian);
		cvReleaseImage(&FrameSeed);
		cvReleaseImage(&FrameGray);
		cvReleaseImage(&FrameGray2);
		cvReleaseImage(&frameSobel);
		cvReleaseImage(&frameSobelNC);
		cvReleaseImage(&frameSub);
		cvReleaseImage(&frameRain);
		cvReleaseImage(&frameAnt);
		cvReleaseImage(&div);
		cvReleaseImage(&RainSpace);
		cvClearMemStorage( (handlercontour->tempStorage) );
		//cvClearSeq(contours);

		char c= cv::waitKey(10);
		 	if(c==27)break;
		

	}


int PixMedia=0;

for(int i=0;i<videoApi.get(CV_CAP_PROP_FRAME_HEIGHT);i++)
{
	for(int j=0;j<videoApi.get(CV_CAP_PROP_FRAME_WIDTH);j++)

	PixMedia=PixMedia+HistPix[i][j];
	//cout<<HistPix[i][j]<<" ";
}

double MediaPixChange[((int)videoApi.get(CV_CAP_PROP_FRAME_WIDTH))][((int)videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))];
int PixAcum=0;

for(int i=0;i<videoApi.get(CV_CAP_PROP_FRAME_HEIGHT);i++)
{
	for(int j=0;j<videoApi.get(CV_CAP_PROP_FRAME_WIDTH);j++)
	{
		
		for(int k=0;k<NumberFrames;k++)MediaPixChange[i][j]=HistPixOclusion[i][j][k] + MediaPixChange[i][j];

		if(profundidad[i][j]!= 0)
		MediaPixChange[i][j]=MediaPixChange[i][j]/profundidad[i][j];
		cout<<MediaPixChange[i][j]<<" ";



 		
	}
cout<<"cambio de fila";
//cout<<HistPix[i][j]<<" ";
}

for(int i=0;i<videoApi.get(CV_CAP_PROP_FRAME_HEIGHT);i++)
{
	for(int j=0;j<videoApi.get(CV_CAP_PROP_FRAME_WIDTH);j++)

	MediaPixChange[i][j]=MediaPixChange[i][j]/cambios[i][j];
	//cout<<HistPix[i][j]<<" ";
}


cout<<"Media de oclusion = "<<PixMedia/((videoApi.get(CV_CAP_PROP_FRAME_HEIGHT))*(videoApi.get(CV_CAP_PROP_FRAME_WIDTH)))<<endl;
cout<<"Numero de Frames ="<<NumberFrames<<endl;//imprime numero de frames del video
cvReleaseCapture(&capture);
cvDestroyWindow("video");
}























