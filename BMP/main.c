#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>




//Meter la imagen que quieran aca
char* iamgenarchivo = "lala.bmp";


//Meter archivo donde quieran el resultado CREO que ya tiene que
//existir
char* resu = "resultado.txt";

int main(){

	BMP* imagen = bmp_read(iamgenarchivo);
	uint32_t* alto = bmp_get_h(imagen);
	uint32_t* ancho = bmp_get_w(imagen);
	uint32_t altoVerdadero = *(alto);
	uint32_t anchoVerdadero = *(ancho);

	uint32_t* datos = bmp_get_data(imagen);

	for(uint32_t i = 0; i < (altoVerdadero*altoVerdadero*4); i +=4){
		//Recordar la componente de trasparencia
		//Sumo las otras 3 RGB y saco el promedio
		uint32_t suma = datos[i+1] + datos[i+2] + datos[i+3];
		float suma_d = (float)suma;
		suma_d /= 3;
		uint32_t sumaF = (uint32_t)suma_d;

		FILE *fp;
		fp = fopen(resu, "a+");
		fprintf(fp, "%u", sumaF); 

		if((i/4) == (altoVerdadero*altoVerdadero)-1){
			fprintf(fp, "%s", "\n");
		}
		else{
			fprintf(fp, "%s", ",");
		}
		fclose(fp);
	}

	return 0;
		
}
