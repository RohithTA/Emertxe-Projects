/*
Name: Rohith T A
Date: 17/02/2023
Description: LSB Image Stegenography
Sample Input: INFO: Opening required files                                                                                                                        
			  INFO: Opened beautiful.bmp
			  INFO: Opened secret.txt                                                                                                                    
			  INFO: opened stego.bmp                                                                                                                          
			  INFO: Done                                                                                                                        
			  INFO: ## Encoding Started ##                                                                                                                 
			  INFO: Checking for secret.txt size                                                                                                                 
			  INFO: Done file not empty                                                                                                                         
			  INFO: Checking for beautiful.bmp capacity to handle secret.txt                                                                                      
			  INFO: Done. Found OK                                                                                                                                
			  INFO: Copying image header                                                                                                                           
			  INFO: Done                                                                                                                                           
			  INFO: Encoding magic String Signature                                                                                                                 
			  INFO: Done                                                                                                                                      
			  INFO: Encoding secret.txt File extension size                                                                                                       
			  INFO: Done                                                                                                                                         
			  INFO: Encoding secret.txt File Extension                                                                                                          
			  INFO: Done                                                                                                                                        
			  INFO: Encoding secret.txt File size                                                                                                                   
			  INFO: Done                                                                                                                                            
			  INFO: Encoding secret.txt File Data                                                                                                            
			  INFO: Done                                                                                                                                         	
			  INFO: Copying remaining image data                                                                                                                    
			  INFO: Done                                                                                                                                       
			  INFO: ## Encoding successfully done ##
Sample Output: INFO: ##Decoding Procedure Started ##                                                                                                                
			   INFO: Opening required files                                                                                                                         
			   INFO: Opened stego.bmp                                                                                                                         
			   INFO: Decoding Magic string Signature                                                                                                                
			   INFO: Done                                                                                                                                        
			   INFO: Decoding Output File Extension size                                                                                                          
			   INFO: Done                                                                                                                                     
			   INFO: Decoding Output File Extension                                                                                                                 
			   INFO: Done                                                                                                                                            
			   INFO: Opened decode.txt                                                                                                                          
			   INFO: Opened all required files                                                                                                                      
			   INFO: Decoding decode.txt File Size                                                                                                                  
			   INFO: Done                                                                                                                                          
			   INFO: Decoding decode.txt File Data                                                                                                                 
			   INFO: Done                                                                                                                                        
			   INFO: ## Decoding Done Successfully ## 
*/


#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include <string.h>


/*
 * check the operation type
 * input command line arguments
 * check whether the 1st argument is -d or -e
 */
OperationType check_operation_type(char **str)
{
	if (strcmp(str[1], "-d") == 0)
	{
		//return decode if the -d is passed
		return e_decode;
	}
	else if (strcmp(str[1], "-e") == 0)
	{
		//return encode if -e is passed
		return e_encode;
	}
	else
	{
		//return unsupported if none of the above is passed
		return e_unsupported;
	}
}




int main(int argc, char* argv[])
{
	//check if arguments is passed throught the command line
	if (argc >= 2)
	{
		// call the function to determine the type of operation
		int option = check_operation_type(argv);
		if (option == e_encode)
		{
			// if encode operation is choosen check if 4 arguments is minimum passed or not
			if (argc >= 4)
			{
				//give name to encode structure
				EncodeInfo encInfo;
				// call the function to read and validate the arguments are correct or not
				if (read_and_validate_encode_args(argv, &encInfo) == e_success)
				{
					//do encoding function if all args are correct
					if (do_encoding(&encInfo) == e_success)
					{
						printf("INFO: <---- Encoding Done successfully ---->\n");
					}
					else
						printf("INFO: Encoding error!!\n");
				}
				else
					printf("INFO: Validation error!!\n");
			}
			else
				printf("INFO: Pass all the arguments required\n");
		}
		else if (option == e_decode)
		{
			//if decode selected then check if minimum 3 args are passed
			if (argc >= 3)
			{
				// read and validate the variable call the function
				DecodeInfo decInfo;
				if (read_and_validate_decode_args(argv, &decInfo) == e_success)
				{
					printf("INFO: <---- Decoding Started ---->\n");
					//start decoding
					if(do_decoding(&decInfo) == e_success)
					{
						printf("INFO: <---- Decoding Done Successfully ---->\n");
					}
					else
					{
						printf("INFO: Decoding Failed\n");
					}
				}
				else 
					printf("INFO: Validation error\n");
			}
		}
		else
			printf("INFO: Invalid option\n");
	}
	else
		printf("INFO: Pass arguments through command line\n");
	return 0;
}

