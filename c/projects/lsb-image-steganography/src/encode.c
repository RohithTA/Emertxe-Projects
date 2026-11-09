#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "common.h"
#include<string.h>

/* Function Definitions */

/*
 * function name  : do_encoding
 * used to all all the required functions
 * used to print the whether each function is success or not
 */
Status do_encoding(EncodeInfo *encInfo)
{
	printf("INFO: Opening required files\n");
	if (open_files(encInfo) == e_success)
	{
		printf("INFO: Opened %s\nINFO: Opened %s\nINFO: opened %s\nINFO: Done\n",encInfo -> src_image_fname, encInfo -> secret_fname, encInfo -> stego_image_fname);
	}
	else
	{
		printf("INFO: Open file error\n");
		return e_failure;
	}
	printf("INFO: <---- Encoding Started ---->\n");
	if (check_capacity(encInfo) == e_success)
	{
		printf("INFO: Checking for %s size\n", encInfo -> secret_fname);
		if (encInfo -> size_secret_file)
			printf("INFO: Done file not empty\n");
		printf("INFO: Checking for beautiful.bmp capacity to handle secret.txt\nINFO: Done. Found OK\n");
	}
	else
	{
		printf("INFO: check capacity error\n");
		return e_failure;
	}
	printf("INFO: Copying image header\n");
	if (copy_bmp_header(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to copy bmp header\n");
		return e_failure;
	}
	printf("INFO: Encoding magic String Signature\n");
	if (encode_magic_string(MAGIC_STRING, encInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failure of Magic String\n");
		return e_failure;
	}
	printf("INFO: Encoding %s File extension size\n", encInfo -> secret_fname);
	if (encode_secret_file_extn_size(strlen(encInfo -> extn_secret_file), encInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to encode secret file extension size\n");
		return e_failure;
	}
	printf("INFO: Encoding %s File Extension\n", encInfo -> secret_fname);
	if (encode_secret_file_extn(encInfo -> extn_secret_file, encInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to encode secret file extension\n");
		return e_failure;
	}
	printf("INFO: Encoding %s File size\n", encInfo -> secret_fname);
	if (encode_secret_file_size(encInfo -> size_secret_file, encInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to encode Secret file size\n");
		return e_failure;
	}
	printf("INFO: Encoding %s File Data\n", encInfo -> secret_fname);
	if (encode_secret_file_data(encInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to encode secret data\n");
		return e_failure;
	}
	printf("INFO: Copying remaining image data\n");
	if (copy_remaining_img_data(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)
	{
		printf("INFO: Done\n");
		return e_success;
	}
	else
		printf("INFO: Failed to copy remaining image data\n");
	return e_success;
}




/*
 * Function to copy the bmp header to stego image
 * start to read each byte from 0 to 54 in the source image
 * read the data from the source and write to stego image 
 */
Status copy_bmp_header(FILE * fptr_src_image, FILE *fptr_dest_image)
{
	char arr[54];
	rewind(fptr_src_image);
	fread(arr, sizeof(char), 54, fptr_src_image);
	fwrite(arr, sizeof(char), 54, fptr_dest_image);
	return e_success;
}



/*
 * Function to read and validate all the arguments passed through the command line
 * check whether output file name is given or not
 * check if the image extension is of bmp or not
 * if output file name is not present then give a default name
 */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
	// check the image file is bmp or not
	if(strcmp(strstr(argv[2], "."), ".bmp") == e_success)
	{
		encInfo -> src_image_fname = argv[2];
	}
	else
		//return fail if not bmp file
		return e_failure;
	//check if the secret file name passed or not
	if (argv[3] != NULL)
	{
		encInfo ->secret_fname = argv[3];
		//copy the secret file name to the secret fptr
		strcpy(encInfo -> extn_secret_file, strstr(argv[3], "."));
	}

	//check if output name is given or not
	if (argv[4] != NULL)
	{
		encInfo -> stego_image_fname = argv[4];
	}
	else
	{
		//if not give a default name
		printf("INFO: Output File not mentioned. Creating default_steged.bmp\n");
		encInfo -> stego_image_fname = "default_steged.bmp";
	}
	return e_success;
}



/*
 * function to check the file size
 * change offset value to the last of the file
 * it will be the size of the file 
 */

uint get_file_size(FILE *fptr)
{
	fseek(fptr, 0, SEEK_END);
	return ftell(fptr);
}


/*
 * function to check the image is large enough to hold the secret file or not
 * check the length of th each required objects
 * check size of datatype of the length of the extension and file
 * compare with imgae size whether image size is larger than sum of all the required object size
 */


Status check_capacity(EncodeInfo *encInfo)
{
	uint bmp_image_size = get_image_size_for_bmp(encInfo ->fptr_src_image);
	encInfo -> size_secret_file = get_file_size(encInfo -> fptr_secret);
	if(((strlen(MAGIC_STRING) * 8) + (sizeof(int) * 8) + (strlen(encInfo -> extn_secret_file) * 8) + (sizeof(int) * 8) + (encInfo -> size_secret_file * 8)) < bmp_image_size)
		return e_success;
	else
		return e_failure;
}



// function is used to change each bit of the data to last bit of a byte of the image data
Status encode_byte_to_lsb(char data, char *image_buffer)
{
	for (int i = 0; i < 8; i++)
	{
		image_buffer[i] = ((data & (1 << (7 - i))) >> (7 - i) | (image_buffer[i] & -2));
	}
}



/*
 * function is used to store secret file to the image
 * read each byte from the source image then store it into a buffer
 * call the function to change byte to lsb of image
 * write the each byte to the stego output image file
 */
Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image,FILE *fptr_stego_image, EncodeInfo *encInfo)
{
	for (int i = 0; i < size; i++)
	{
		fread(encInfo -> image_data, sizeof(char), 8, fptr_src_image);
		encode_byte_to_lsb(data[i],encInfo -> image_data);
		fwrite(encInfo -> image_data, sizeof(char), 8, fptr_stego_image);
	}
}



/*
 * function to encode magic string to the stego image file
 * call the function to encode data to image then by passing the magic string
 */
Status encode_magic_string(const char * magic_string, EncodeInfo* encInfo)
{
	encode_data_to_image(magic_string, strlen(magic_string), encInfo -> fptr_src_image, encInfo -> fptr_stego_image, encInfo);
	return e_success;
}



/*
 * function to change size of a data to lsb of the byte of image file
 * lsb of image byte is replaced with each bu=it of the size of the data
 */



Status encode_size_to_lsb(int size, char* str)

{
	for (int i = 0; i < 32; i++)
	{
		str[i] = (size >> (31 - i)) & 1 | str[i] & -2;
	}
	return e_success;
}



/*
 * Function to encode the extension size of the secret file to the image
 * read required bytes from (1 byte for 1 bit) image and give it to the function to change size to lsb
 * write to data to stego image file
 */


Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
	char str[32];
	fread(str, 32, 1, encInfo -> fptr_src_image);
	encode_size_to_lsb(4, str);
	fwrite(str, 32, 1, encInfo -> fptr_stego_image);
	return e_success;
}



/*
 * function to encode secret file extension to image
 *take the file extension and give it to encode data to image function with length of the extension
 * return success if done
 */


Status encode_secret_file_extn(const char* file_extn, EncodeInfo *encInfo)
{

	encode_data_to_image(file_extn, strlen(file_extn), encInfo -> fptr_src_image, encInfo -> fptr_stego_image, encInfo);
	return e_success;
}




/*
 * encode secret file size to image function
 * create a buffer to read bytes from the source image
 * call the function to encode size to lsb and write the new buffer result to the stego image
 */

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
	char str[32];
	fread(str, 32, 1, encInfo -> fptr_src_image);
	encode_size_to_lsb(file_size, str);
	fwrite(str, 32, 1, encInfo -> fptr_stego_image);
	return e_success;
}



/*
 * Encode secret file data to the output function create the buffer with size of the secret data and read bytes from the src image
 *call the function to encode and store it to the new image file
 */


Status encode_secret_file_data(EncodeInfo *encInfo)
{
	char buffer[encInfo -> size_secret_file];
	fseek(encInfo -> fptr_secret, 0, SEEK_SET);
	fread(buffer, 1, encInfo -> size_secret_file, encInfo -> fptr_secret);
	encode_data_to_image(buffer, encInfo -> size_secret_file, encInfo -> fptr_src_image, encInfo -> fptr_stego_image, encInfo);
	return e_success;
}




/*
 * copy all the remaining data to the new file
 * input source image and stego image
 * read each byte and write it to the stego image until the EOF 
 */


Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
	char ch;
	while(fread(&ch, sizeof(char), 1, fptr_src) > e_success)
	{
		fwrite(&ch, sizeof(char), 1, fptr_dest);
	}
	return e_success;
}





/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
	uint width, height;
	// Seek to 18th byte
	fseek(fptr_image, 18, SEEK_SET);

	// Read the width (an int)
	fread(&width, sizeof(int), 1, fptr_image);
	//	printf("width = %u\n", width);

	// Read the height (an int)
	fread(&height, sizeof(int), 1, fptr_image);
	//	printf("height = %u\n", height);

	// Return image capacity
	//	printf("%d\n", width * height * 3);
	return width * height * 3;

}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
	// Src Image file
	encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
	// Do Error handling
	if (encInfo->fptr_src_image == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

		return e_failure;
	}

	// Secret file
	encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
	// Do Error handling
	if (encInfo->fptr_secret == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

		return e_failure;
	}

	// Stego Image file
	encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
	// Do Error handling
	if (encInfo->fptr_stego_image == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

		return e_failure;
	}

	// No failure return e_success
	return e_success;
}
