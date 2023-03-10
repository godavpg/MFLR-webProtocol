
/*=======================================================================================================================================================================
The following function is to capture the Script Name, Script Name will be captured by tokenizing the script location path.
Example: D:\Testing-workshop\PerformanceEngineering\Performance_Scripts\webScripts\S001_Generate_Transaction_Name_Dynamically\S001_Generate_Transaction_Name_Dynamically.usr
 ========================================================================================================================================================================*/

#include <string.h>
void captureScriptName(){
	char *token = (char*)strtok(lr_get_attrib_string("usr"),".\\"); // The first part/output from the tokenized string will be stored in the 'token'
	char *pathArray[24];
	int ctr1=0;
	
	while(token!=NULL){
		pathArray[ctr1]=token; //All the token will be stored in the patharray one by one, until the WHILE condition is being statisfied.
		ctr1++;
		token = (char*)strtok(NULL,".\\");		
	}
	
/*The required Script Name part is at the index of 'n-2' in the 'patharray[]' as NULL value is stored at 'n' index and hence, checking if the captured script name is NULL and display the error message accordingly
Example: D:\Testing-workshop\PerformanceEngineering\Performance_Scripts\webScripts\S001_Generate_Transaction_Name_Dynamically\S001_Generate_Transaction_Name_Dynamically.usr */
	
	if(pathArray[ctr1-2]==NULL){
		lr_error_message("ERROR:Null value has been found");	
	}else{
		lr_save_string(pathArray[ctr1-2],"script_name");
		lr_output_message("%s", lr_eval_string("{script_name}"));
	}
	memset(pathArray,0,sizeof(pathArray)); // To reset the values of the particular block of memory
}

/*===================================================================================================================================================================================
The following function is to generate Transaction Name. Please keep the "TName("<transactiondescription>")" funtion inside thee lr_start_transaction() and lr_end_transaction().

Example:

lr_start_transaction(TName("Search"));

web_custom_request{

};

lr_end_transaction(TName("Search"));
 ===================================================================================================================================================================================*/

/* Defining 100 as fixed maximum number of transaction count.If the Transaction Count in the script is more than 100, please update it accordingly.*/

#define MAX_TRANSACTION_NUMBER 100
int flag=0, transactionNumber=0,ctr2=0;
char *tempTranDescription[MAX_TRANSACTION_NUMBER];
int tempTranNumber[MAX_TRANSACTION_NUMBER];

char *TName(char *tranDescription){
	
/*The following 'if condition is to call CaptureScriptame() function only once to capture the script name at the begining of the script execution.
This 'if' condition is executed only once as flag will be set to 1 later*/ 

	if(flag==0){
		captureScriptName();
		tempTranDescription[0]="";
		tempTranNumber[0]=0;
		flag++;
	}
	
	lr_save_int(transactionNumber,"tn");
	lr_output_message("current transaction Number: %s ", lr_eval_string("{tn}"));
	
/*To check if the Same Transaction Description is repeated and if it is repeated, save the corresponding transaction number and generate the transaction name
Basically, it is to make sure the transaction number is same for all the interations of any particular transaction*/
	
	for(ctr2=1;ctr2<=transactionNumber;ctr2++){
			
		lr_save_int(ctr2,"counter2");
		lr_output_message("array : %s ", lr_eval_string("{counter2}"));
		lr_message("array stored value : %s",tempTranDescription[ctr2]);
		
		
		if(strcmp(tempTranDescription[ctr2],tranDescription)==0){
			transactionNumber=tempTranNumber[ctr2];
			
			lr_save_int(tempTranNumber[ctr2],"temptn");
			lr_output_message("end temp transaction number %s",lr_eval_string("{temptn}"));
			
			lr_param_sprintf("transaction_name", "%s_T%d_%s", lr_eval_string("{script_name}"),transactionNumber,tranDescription);
			lr_output_message("End transaction name :%s",lr_eval_string("{transaction_name}"));
			
			return lr_eval_string("{transaction_name}");
		}
	}
	
		transactionNumber++; // Increment 'transactionNumber for every transaction.
		tempTranNumber[ctr2]=transactionNumber; //Saves each transaction numbers into temporary transaction number array. tempTranDescription [ctr3] - tranDescription;
		
		lr_save_int(transactionNumber,"utn");
		lr_output_message("updated transaction number :  %s",lr_eval_string("{utn}"));
		
		tempTranDescription[ctr2]=tranDescription; //Saves each transaction description into temporary transaction description
		
		lr_param_sprintf("transaction_name", "%s_T%d_%s", lr_eval_string("{script_name}"),transactionNumber,tranDescription);
		lr_output_message("start transaction name : %s ",lr_eval_string("{transaction_name}")); 
		
		return lr_eval_string("{transaction_name}");
			
}
