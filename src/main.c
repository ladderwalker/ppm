#define CNFG_IMPLEMENTATION
#define CNFGOGL
#define HAS_XSHAPE
#define HAS_XINERAMA
#include "include/rawdraw_sf.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void HandleKey( int keycode, int bDown ) {
    if(bDown==1){
        if(keycode==65307) {
            exit(0);
        }
    }
    printf("%d\n",keycode);
}
void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { } 
void HandleDestroy() { }
int main()
{ 
    FILE *dfp;
    char face_data[1684];
    dfp = fopen("ppmtest.dat", "r");
    int index=0;
    while( fread(face_data, sizeof(char), 1650, dfp) == 1 ){
        printf("%c",face_data[index++]);
    }
    fclose(dfp);
    const int width = 800, height = 600;
    const int pwidth = 51, pheight = 33;
    unsigned char face_dataR[33][51];
    unsigned char face_dataG[33][51];
    unsigned char face_dataB[33][51];
    for(int y = 0; y < 33; y++){
        for(int x = 0; x < 51; x++){
            
            if(face_data[51 * y + x] == '0'){ 
                //white
                face_dataR[y][x] = 255;
                face_dataG[y][x] = 255;
                face_dataB[y][x] = 255;
            } else if(face_data[51 * y + x] == '1'){
                //skin
                face_dataR[y][x] = 204;
                face_dataG[y][x] = 133;
                face_dataB[y][x] = 116;
            } else if(face_data[51 * y + x] == '2'){
                //black
                face_dataR[y][x] = 0;
                face_dataG[y][x] = 0;
                face_dataB[y][x] = 0;
            }
            
        }
    }
    
    CNFGSetup( "PPM Experiment", width, height );
    FILE *fp;
    fp = fopen("ppmtesty.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", pwidth, pheight);
    int counter1 = 0;
    for(int i = 0; i < pheight; i++){
        for(int j = 0; j < pwidth; j++){
            static unsigned char color[3];
            color[0] = face_dataR[i][j];
            color[1] = face_dataG[i][j];
            color[2] = face_dataB[i][j];
            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
    while(CNFGHandleInput())
    {
        
        CNFGBGColor = 0x0000ffff; //Dark Blue Background
        short w, h;
        CNFGClearFrame();
        CNFGGetDimensions( &w, &h );
        
        //-----------------------------//
        //          put shit here      //
        //          put shit here      //
        //          put shit here      //
        //-----------------------------//
        
        //Display the image and wait for time to display next frame.
        CNFGSwapBuffers();
        
        usleep(100000);
    }
    
}
