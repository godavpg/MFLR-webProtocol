Action()
{
	lr_start_transaction(TName("sample01"));
	
	lr_end_transaction(TName("sample01"), LR_AUTO);
	
	lr_start_transaction(TName("sample02"));
	
	lr_end_transaction(TName("sample02"), LR_AUTO);
	
	lr_start_transaction(TName("sample03"));
	
	lr_end_transaction(TName("sample03"), LR_AUTO);
	
	lr_start_transaction(TName("sample04"));
	
	lr_end_transaction(TName("sample04"), LR_AUTO);


	return 0;
}


