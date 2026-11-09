#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
	/* Source Image info */
	char *stego_image_fname;
	FILE *fptr_stego_image;

	/* Secret File Info */
	char *secret_fname;
	char *output_fname;
	FILE *fptr_secret;
	int size_extn;
	char extn_secret_file[MAX_FILE_SUFFIX];
	char secret_data[MAX_SECRET_BUF_SIZE];
	long size_secret_file;

} DecodeInfo;


/* Encoding function prototype */

/* Check operation type */
OperationType check_operation_type(char *argv[]);

/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(char *argv[],DecodeInfo *decInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_stego_file(DecodeInfo *decInfo);

/* Store Magic String */
Status decode_magic_string(DecodeInfo *decInfo);

/* Encode secret file extenstion */
Status decode_secret_file_extn(DecodeInfo *decInfo);

/* Encode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* Encode secret file data*/
Status decode_secret_file(DecodeInfo *decInfo);

/* Encode a byte into LSB of image data array */
Status decode_data_from_image(char *buffer, int size, FILE *fptr_image);

Status decode_byte_from_lsb(char *data, char* buffer);

/* Encode secret file extension size*/
Status decode_size_of_extn(DecodeInfo *decInfo);
/* opening the output file*/
Status open_output_file(DecodeInfo* decInfo);
/* Encode size to lsb */
int decode_size_from_lsb(char* size_buffer, DecodeInfo *decInfo);

#endif
