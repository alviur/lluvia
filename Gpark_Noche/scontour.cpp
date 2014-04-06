#include "scontour.h"


/***************************************************************************************************
Constructor
Autor:  German Diez Valencia - Alexander Gómez villa - Sebastian Guzman Obando 
Descripcion:
***************************************************************************************************/
sContour::sContour()
{
    tempStorage = cvCreateMemStorage();
    perimetromax=0;
    perimetro=0;
}


/***************************************************************************************************
Metodos
Autor:  German Diez Valencia - Alexander Gómez villa - Sebastian Guzman Obando 
Descripcion: Retorna una secuencia con los puntos de todos los contornos de una imagen de un solo canal

***************************************************************************************************/

CvSeq* sContour::sGetContourn(IplImage *source)//Retorna una secuencia con los puntos de todos los contornos de una imagen de un solo canal
{
	//cvFindContours(source,tempStorage,&contorno);
	numcont=cvFindContours(source,tempStorage,&contorno,sizeof(CvContour), CV_RETR_LIST);	
	return contorno;       
}



/***************************************************************************************************
Metodos
Autor:  German Diez Valencia - Alexander Gómez villa - Sebastian Guzman Obando 
Descripcion: Retorna un CvRect con la ubicación del contorno mas grande
***************************************************************************************************/
CvSeq * sContour::sGetBC(CvSeq* contorno)//Retorna un CvRect con la ubicación del contorno mas grande
{
      
	for(CvSeq* c=contorno; c!=NULL; c=c->h_next)//va pasando uno a uno los contornos
	{  
   		perimetro=cvArcLength(c, CV_WHOLE_SEQ,-1);//calculo el largo del contorno
   		if(perimetro > perimetromax)//compara si el largo del contorno recien allado es mayor que el ultimo contorno mas largo
   		{ 
   		   perimetromax=perimetro;//reemplaza el contorno allado en el contorno mas grande pues ahora es el mas grande
   		   Bc=cvCloneSeq(c);//el apuntador al contorno mas largo (Bc) ahora apunta a la estructura que contiene el cntorno mas 					      argo       
   		}     
 	}
 
	return Bc;
}


/***************************************************************************************************
Metodos
Autor:  German Diez Valencia - Alexander Gómez villa - Sebastian Guzman Obando 
Descripcion: Retorna un CvRect con la ubicación del contorno q este entre los 2 limites
***************************************************************************************************/
bool sContour::sBandPassC(CvSeq *ce, int minh,  int minw, int maxh, int maxw)//Retorna un CvRect con la ubicación del contorno q este entre los 2 limites
{
   CvRect rect = cvBoundingRect(ce,1);
//if(handlercontour->sBandPassC(Bc, placa->height,placa->width,250,250)  )
   if( maxh>rect.height && minh<rect.height && maxw>rect.width && minw<rect.width )//compara la longitud del contorno comprobando que este dentro de la sbandas
   {
       return 1;
   }
   else
   {
       return 0;
   }

}



/***************************************************************************************************
Metodos
Autor:  German Diez Valencia - Alexander Gómez villa - Sebastian Guzman Obando 
Descripcion: Retorna la imagen dentro de un contorno
***************************************************************************************************/
IplImage *sContour::sGetContournImage(CvRect r,IplImage* src)//Retorna la imagen dentro de un contorno
{
     cvSetImageROI(src, r);
     return src;
}

CvSeq* sContour::sGetContB(IplImage *source)// retorna el contorno mas grande de una imagen de un solo canal
{
    cvFindContours(source,tempStorage,&contorno,sizeof(CvContour), CV_RETR_LIST);
     
	for(CvSeq* c=contorno; c!=NULL; c=c->h_next)//va pasando uno a uno los contornos
	{  
   		perimetro=cvArcLength(c, CV_WHOLE_SEQ,-1);//calculo el largo del contorno
   		if(perimetro > perimetromax)//compara si el largo del contorno recien allado es mayor que el ultimo contorno mas largo
   		{ 
   		   perimetromax=perimetro;//reemplaza el contorno allado en el contorno mas grande pues ahora es el mas grande
   		   Bc=cvCloneSeq(c);//el apuntador al contorno mas largo (Bc) ahora apunta a la estructura que contiene el cntorno mas 					      argo       
   		}     
 	}
return Bc;
	
}


/***************************************************************************************************
Metodos
Autor:   Alexander Gómez villa - German Diez Valencia - Sebastian Guzman Obando 
Descripcion:si encuentra una semilla cuyo valor este entre lowThreshold y highThreshold pondra los 
pixeles vecinos en el valor SetValue si este vecino cumple ser mayor que condition
***************************************************************************************************/

IplImage*  sContour::gSetMaskSeed(IplImage* src, int lowThreshold, int highThreshold, int SetValue, int condition){


IplImage* src2;
src2=cvCloneImage(src);
cv::Mat image(src2);

float valor=0;
    CvScalar intensidad;
    CvScalar intensidad1;
    intensidad1.val[0] =SetValue;
    int i=0,j=0,pix=0,b=-1;
    int a=0;
    
    while(i < (450)){
	while(j < (320)){
		    intensidad = cvGet2D(src,j, i);
		    valor = intensidad.val[0] ;	

		    if((valor < highThreshold) && (valor >= lowThreshold)){
			while(a<2){
				while(b<2){
					if(((j+b) <320) && ((i+a) < 450) && ((j+b) >0) && ((i+a) > 0)) {
						intensidad = cvGet2D(src,j+b,i+a);
						if((intensidad.val[0] > condition) ){
							cvSet2D( src2, j+b,i+a,intensidad1);
						}
		                        }
					b++;
				}
			a++;
			b=-1;
			
			}
		         a=-1;
			
			}

			
		    j++;
		}
	j=0;
	i++;
	}

//i=0,j=0;
j=310;
/*
while(i >(0)){
	while(j > (0)){
//printf("%d \n",i);
		      intensidad = cvGet2D(src2,j, i);
// printf("entre!! \n");
		     valor = intensidad.val[0] ;	

		    if((valor < highThreshold) && (valor > lowThreshold)){

			while(a<2){
				while(b<2){
					if(((j+b) <320) && ((i+a) < 450) && ((j+b) >0) && ((i+a) > 0)){ 
						intensidad = cvGet2D(src,j+b,i+a);

						if((intensidad.val[0] > condition) ){
printf("entre!! \n");
							cvSet2D( src2, j+b,i+a,intensidad1);
						}
		                        }
					b++;
				}
			a++;
			b=-1;
			
			} 	
		         a=-1;
			
			}

			
		    j--;
		}
	j=0;
	i--;
	}*/										

  return src2;

}




/***************************************************************************************************
Metodos
Autor:   Alexander Gómez villa - German Diez Valencia - Sebastian Guzman Obando 
Descripcion: Rota la imagen
***************************************************************************************************/



IplImage*  sContour::rotate(IplImage *Ioriginal, int angulo)
{
   // IplImage *imageRotated1 = cvCloneImage(Ioriginal);
            IplImage * imageRotated1 = cvCreateImage(cvSize(Ioriginal->width,Ioriginal->height),Ioriginal->depth,Ioriginal->nChannels);
            cvCopy(Ioriginal,imageRotated1);
            //se crea una matriz para alojar la rotaicon
            CvMat* rot_mat = cvCreateMat(2,3,CV_32FC1);

            // se halla el centro para rotar la matriz
            CvPoint2D32f center = cvPoint2D32f( cvGetSize(imageRotated1).width/2, cvGetSize(imageRotated1).height/2 );
            cv2DRotationMatrix( center, angulo, 1, rot_mat );

            // transformacion
            cvWarpAffine(Ioriginal, imageRotated1, rot_mat );
            cvReleaseMat(&rot_mat);
            return   imageRotated1;

}



/***************************************************************************************************
Metodos
Autor:   Alexander Gómez villa - German Diez Valencia - Sebastian Guzman Obando 
Descripcion:si encuentra una semilla cuyo valor este entre lowThreshold y highThreshold pondra los 
pixeles vecinos en el valor SetValue si este vecino cumple ser mayor que condition

***************************************************************************************************/

IplImage*  sContour::gSetMaskSeed2(IplImage* src, int lowThreshold, int highThreshold, int SetValue, int condition){


IplImage* src2;
src2=cvCloneImage(src);
cv::Mat image(src2);

float valor=0;
    CvScalar intensidad;
    CvScalar intensidad1;
    intensidad1.val[0] =SetValue;
    int i=0,j=0,pix=0,b=-1;
    int a=0;
	int c=0;
    int x=0;
    int y=0;
    int contpix=0; 
    int contpix2=0; 

    int pixa[3]={-1,0,1};
    
    while(i < (450)){
	while(j < (320)){
		    intensidad = cvGet2D(src,j, i);
		    valor = intensidad.val[0] ;	

		    if((valor < highThreshold) && (valor > lowThreshold)){
			x=i;
			y=j;
			while(a<2){
				while(b<2){

					if(((j+b) <320) && ((i+a) < 450) && ((j+b) >0) && ((i+a) > 0)) {
						intensidad = cvGet2D(src,j+b,i+a);
						if((intensidad.val[0] > condition) ){
							cvSet2D( src2, j+b,i+a,intensidad1);
							while(contpix2<3){
								while(contpix<3){
									if((intensidad.val[0] > condition) && ((j+ pixa[contpix]) <320) && ((i+ pixa[contpix2]) < 450) && ((j+ pixa[contpix]) >0) && ((i+ pixa[contpix2]) > 0)){
									cvSet2D( src2, j+ pixa[contpix],i,intensidad1);
									}
								contpix++;
								}
							contpix=0;
							contpix2++;
							}

							
							contpix2=0;
							i=i+a;
							j=j+b;

b++;

						}
						else{
							b++;
						}
		                        }

					else{
						b++;

					}

					
				}
c=0;
//printf("aca estoy \n");	
			a++;
			b=-1;
			i=x;
			j=y;
			
			}
		         a=-1;
			
			}

			
		    j++;
		}
	j=0;
	i++;
	}

								

  return src2;

}

/***************************************************************************************************
Destructor
Autor:  German Diez Valencia - Alexander Gómez villa - Sebastian Guzman Obando 
Descripcion:
***************************************************************************************************/
sContour::~sContour()
{
	//cvClearSeq(Bc);
	cvClearSeq(contorno);
	cvReleaseMemStorage( &tempStorage );
			
}

