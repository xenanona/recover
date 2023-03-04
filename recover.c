#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

  //verifica sa fie mai mult de un argument
  if(argc != 2)
  {
    printf("Usage: ./recover IMAGE");
    return 1;
  }
  else
  {
  //open card.raw
    char *input_file_name = argv[1];
    FILE *input_pointer = fopen(input_file_name, "r");

    if (input_pointer == NULL)
        {
            printf("Error: cannot open %s\n", input_file_name);
            return 2;
        }
        //creem variabilele de carre o sa avem nevoie
    BYTE buffer[512];
    int counter=0;
    FILE *img_pointer = NULL;
    char filename[8];
  //repet until the end of the card
    while (fread (&buffer, 1, 512, input_pointer) == 1)
    {
      if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
      {
        //if its not the first jpeg close previous
          if(!(counter == 0))
          {
            fclose(img_pointer);
          }
        //initialise file
        sprintf(filename, "%03i.jpg", counter);
        img_pointer = fopen(filename,"w");
        counter++;
      }
      //if jpeg had been found write to file
      if(!(counter == 0))
      {
          fwrite(&buffer, 512, 1 ,img_pointer);
      }
    }

 fclose(img_pointer);
 fclose(input_pointer);
}
}


