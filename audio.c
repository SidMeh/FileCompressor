#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define PI 3.142
#define AMPLITUDE 5000


void make_audio(int meta_size);
void convert_audio_to_txt(FILE *faudio, FILE *ftxt);
void read_audio(FILE *audio, FILE *ftxt);         //this function converts audio into txt;
void write_audio(FILE *audio, FILE *ftxt);        //this function converts txt into audio



int main(){
	make_audio(90000);
    FILE *pipein;
    pipein = popen("ffmpeg -i beep.wav -f s16le -ac 1 -", "r");
    FILE *csvfile;
    csvfile = fopen("samples.txt", "w");
    read_audio(pipein,csvfile);	
    csvfile = fopen("samples.txt", "r");
    pipein = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - beep1.wav", "w");
    write_audio(pipein,csvfile);
	return 0;
}

void make_audio(int meta_size){
	FILE *faudio, *ftxt;
     faudio = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - beep.wav", "w");
//	faudio = popen("beep.wav","w");
     ftxt = fopen("sample.txt","w");
     int *audio_part = (int*)malloc(sizeof(int)*(meta_size+1));
	int i;                // buffer index
     double Fs = 2*PI;
     audio_part[0] = meta_size*4;
     printf("Audio part :\n");
     for(i=1;i<meta_size;i++){
     	if(i < meta_size/2)
   		  	audio_part[i] = (int)(AMPLITUDE * cos(i*1000.0*2.0*PI/Fs));
     	else
     		audio_part[i] = (int)(AMPLITUDE * tan(i*1000.0*2.0*PI/Fs));
     	if(audio_part[i] < 0)
     		audio_part[i] = audio_part[i]*(-1);
     	fprintf(ftxt,"%d ",audio_part[i]);
     }
     audio_part[meta_size] = 5555;
     audio_part[meta_size - 1] = 5555;
    fwrite(audio_part, 4, meta_size+1,faudio);
    pclose(faudio);
}     


void read_audio(FILE *faudio, FILE *ftxt){
	//assuming faudio is opened and ftxt is opened
	int buffer[90000];
	fread(buffer, 4, 90000, faudio);
	fclose(faudio);
	int i;
	for(i=0;i<40000;i++){
		fprintf(ftxt,"%d ",buffer[i]);
	}
	fclose(ftxt);
}

void write_audio(FILE *faudio, FILE *ftxt){
	//assuming faudio is opened and ftxt is opened
	int buffer[90000];
	fread(buffer, 4, 90000, ftxt);
	fclose(ftxt);
	fwrite(buffer, 4, 90000, faudio);
	fclose(faudio);
}














