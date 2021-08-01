/* PNG Finder */
/* Author : Arjun Mehta */

/* Include required header files. */
#include <stdio.h> 
#include <string.h>
#include <dirent.h>
#include "png_additional_methods.c"  

int list_png(char* dir_name, int *png_found){ /* Recursive function to list the PNG  files. */

	/* Initialize variables and check directory. */
	DIR *dir = opendir(dir_name);
	struct dirent *p_dirent;
	char new_path[600];
	if(dir == NULL){
		return -1;
	}

	/* Loop till directory is not null. */ 
	while((p_dirent=readdir(dir))!=NULL){

		/* Check that d_name does not refer to current or parent directory. */
		if (strcmp(p_dirent->d_name,".")!=0&&strcmp(p_dirent->d_name,"..")!=0){

			/* Create a new updated path*/
			sprintf(new_path,"%s/%s",dir_name,p_dirent->d_name);

			/* Open file at new path and check if it is PNG. If yes, print path to console.*/
			FILE* file = fopen(new_path,"rb");
			if(is_png(file,8)==0){
				printf("%s\n", new_path);
				(*png_found)++;
			}

			/* Call list_png with new path. */
			list_png(new_path,png_found);
		}
	}

	/* Close the opened directory and return. */
	closedir(dir);
	return 0;
}

int main (int argc, char **argv){ /* Main function. */

	/* Declare png_found which keeps track of number of PNGs found. */
	int png_found = 0;

	/* Call recursive function list_png with passed directory. */
	list_png(argv[1], &png_found);

	/* If no PNGs are found, print suitable output. */
	if(png_found==0){
		printf("findpng: No PNG file found\n");
	}
	return 0;
}
