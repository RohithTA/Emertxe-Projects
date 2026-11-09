#include <stdio.h>
#include "decode.h"
#include "types.h"
#include "common.h"
#include <string.h>

/* Function Definitions */
int flag = 0;



/*
 * do encoding function
 * input structure
 * call all the rquired function to decode the data
 * success if all the functions goes smoothely
 * give failure if any function fails 
 */
Status do_decoding(DecodeInfo *decInfo)
{
	printf("INFO: Opening required files\n");
	if(open_stego_file(decInfo) == e_success)
	{
		printf("INFO: Opened %s\n", decInfo -> stego_image_fname );
	}
	else
	{
		printf("INFO: Open file error\n");
		return e_failure;
	}
	printf("INFO: Decoding Magic string Signature\n");
	if (decode_magic_string(decInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Decode magic string failure\n");
		return e_failure;
	}
	printf("INFO: Decoding Output File Extension size\n");
	if (decode_size_of_extn(decInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to decode size of extension\n");
		return e_failure;
	}
	printf("INFO: Decoding Output File Extension\n");
	if(decode_secret_file_extn(decInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to decode the secret file extension\n");
		return e_failure;
	}
	if (flag == 0)
		printf("Output File not mentioned. Creating %s as default\n", decInfo -> secret_fname);
	if (open_output_file(decInfo) == e_success)
	{
		printf("INFO: Opened %s\nINFO: Opened all required files\n", decInfo -> secret_fname);
	}
	printf("INFO: Decoding %s File Size\n", decInfo -> secret_fname);
	if(decode_secret_file_size(decInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to decode the secret file size\n");
		return e_failure;
	}
	printf("INFO: Decoding %s File Data\n", decInfo -> secret_fname);
	if(decode_secret_file(decInfo) == e_success)
	{
		printf("INFO: Done\n");
	}
	else
	{
		printf("INFO: Failed to decode the secret file\n");
		return e_failure;
	}
	return e_success;
}




/*
 * read an validate arguments 
 * inputs cmd line args structure
 * check and give success or not
 */


Status read_and_validate_decode_args(char *argv[], DecodeInfo* decInfo)
{
	//check if the stego image is bmp type or not
	if (strcmp(strstr(argv[2], "."), ".bmp") == e_success)
	{
		decInfo -> stego_image_fname = argv[2];
	}
	else
		// else return failure
		return e_failure;
	// check if the output file name is given or not
	if(argv[3] != NULL)
	{
		//if given change the flag to 1 and take the name without extension to the structure
		flag = 1;
		decInfo -> secret_fname = strtok(argv[3], ".");
	}
	else
	{
		//if not given then create a default struct name
		decInfo -> secret_fname = "default_decoded";
	}
	return e_success;
}





/*
 * decode data from image
 * input buffer, size, image pointer
 * read each byte from stego image give it to the function to decode byte from lsb along with output buffer
 */

Status decode_data_from_image(char *buffer, int size, FILE *fptr_image)
{
	char data[8];
	for(int i = 0; i < size; i++)
	{
		buffer[i] = 0;
		fread(data, 8, 1, fptr_image);
		decode_byte_from_lsb(&buffer[i], data);
	}
	buffer[size] = '\0';
	return e_success;
}



/*
 * Decode byte from lsb
 * inputs are input buffer and output buffer
 * take the last bit of the iput buffer character and create a character and save it in output buffer 
 */
Status decode_byte_from_lsb(char *data, char* buffer)
{
	char ch = 0;
	for (int i = 0; i < 8; i++)
	{
		ch |= ((buffer[i] & (1)) << (7 - i));
	}
	*data = ch;
}





/*
 * decode size from lsb function
 * input are size buffer and struct
 * take the buffer data and take the last bit and convert it to intiger
 * return the size to the function which called it
 */

int decode_size_from_lsb(char *size_buffer, DecodeInfo *decInfo)
{
	int size = 0;
	for (int i = 0; i < 32; i++)
	{
		if (size_buffer[i] & 1)
			size = size | (1 << (31 - i));

	}
	return size;
}






/*
 * function to decode the magic string 
 * structure
 * create buffer read bytes from the image give it to decode data from image funcction
 * compare the new buffer data and magic string
 */


Status decode_magic_string(DecodeInfo* decInfo)
{
	char magic_buffer[8];
	rewind(decInfo -> fptr_stego_image);
	fseek(decInfo -> fptr_stego_image, 54, SEEK_SET);
	int size = strlen(MAGIC_STRING);
	char str[size];
	decode_data_from_image(str, size, decInfo -> fptr_stego_image);
	if(strcmp(str,MAGIC_STRING) == 0)
		return e_success;
	else
		return e_failure;
}





/*
 * function to decode the secret extension 
 * structure
 * create buffer read bytes from the image give it to decode data from image funcction
 * write the new buffer data as the extension and add with the file name
 */



Status decode_secret_file_extn(DecodeInfo* decInfo)
{
	char extn_buffer[decInfo -> size_extn];
	decode_data_from_image(extn_buffer, decInfo -> size_extn, decInfo -> fptr_stego_image);
	strcpy(decInfo -> extn_secret_file, extn_buffer);
	static char name[50];
	strcpy(name, decInfo -> secret_fname);
	strcat(name, decInfo -> extn_secret_file);
	decInfo -> secret_fname = name;
	return e_success;
}



/*
 * function to decode the secret file extension size
 * structure
 * create buffer read bytes from the image give it to decode size from lsb funcction
 * take back the value to the structure element
 */


Status decode_size_of_extn(DecodeInfo* decInfo)
{
	char extn_size_buffer[32];
	fread(extn_size_buffer, sizeof(char), 32, decInfo -> fptr_stego_image);
	decInfo -> size_extn = decode_size_from_lsb(extn_size_buffer, decInfo);
	return e_success;
}





/*
 * function to decode the secret file size
 * structure
 * create buffer read bytes from the image give it to decode size from lsb funcction
 * take back the value to the structure element
 */



Status decode_secret_file_size(DecodeInfo *decInfo)
{
	char size_buffer[32];
	fread(size_buffer, sizeof(char), 32, decInfo -> fptr_stego_image);
	decInfo -> size_secret_file = decode_size_from_lsb(size_buffer, decInfo);
	return e_success;
}





/*
 * function to decode the secret file 
 * structure
 * create buffer read bytes from the image give it to decode data from image funcction
 * write the new buffer data to the secret file
 */

Status decode_secret_file(DecodeInfo *decInfo)
{
	char data_buffer[decInfo -> size_secret_file];
	decode_data_from_image(data_buffer,decInfo -> size_secret_file, decInfo -> fptr_stego_image);
	fwrite(data_buffer, sizeof(char), decInfo -> size_secret_file, decInfo -> fptr_secret);
	return e_success;
}



/*
 * Get File pointers for i/p file
 * Inputs: stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file error
 */ 

Status open_stego_file(DecodeInfo *decInfo)
{
	//stego image file opening
	decInfo -> fptr_stego_image = fopen(decInfo -> stego_image_fname, "r");
	//do error handling
	if (decInfo -> fptr_stego_image == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo -> stego_image_fname);
		return e_failure;
	}
	//No failure
	return e_success;
}



/*
 * Get File pointers for o/p file
 * Output: FILE pointer for output file
 * Return Value: e_success or e_failure, on file error
 */ 

Status open_output_file(DecodeInfo *decInfo)
{
	decInfo -> fptr_secret = fopen(decInfo -> secret_fname, "w");
	if(decInfo -> fptr_secret == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: unable to open file %s\n", decInfo -> secret_fname);
		return e_failure;
	}
	return e_success;
}
