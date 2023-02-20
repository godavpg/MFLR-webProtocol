Action()
{
	
	//Using web convert Param function we have failed to convert required parameter from HTML to URL Mode
	
	lr_save_string("670523 X", "sourceString");
	
	web_convert_param(
        "convertedParam",
        "SourceString={sourceString}",
        "SourceEncoding=HTML",
        "TargetEncoding=URL",
         LAST ); 
	
	lr_output_message("converted string to URL format = %s ", lr_eval_string("{convertedParam}"));
	
	
	// current output is 670523+X but our requried value is   670523%20X
	
	
	// I have wrote a custom JavaScript to encode require value to URL format
	
	lr_save_string("670523 X", "sourceString");
	
	web_js_run("Code=EncURI(LR.getParam('sourceString'));",
        "ResultParam=EURI",
        SOURCES,
        "Code= var EncURI = function(uri) { return encodeURIComponent(uri);}", ENDITEM,
        LAST);

	lr_output_message("Encoded string to URL format = %s ", lr_eval_string("{EURI}"));
	
	// by using above code the value is successfully encoded to URI mode as per ASCII Encoding Reference
	
	
	web_js_run("Code=EncURI(\"abshabhdgyuagdyuaduijbdauduiada0@@1kdnfkdskfnsd##$$%ksksnk12345\");",
        "ResultParam=EURI-1",
        SOURCES,
        "Code= var EncURI = function(uri) { return encodeURIComponent(uri);}", ENDITEM,
        LAST);

	lr_output_message("Encoded string to URL format = %s ", lr_eval_string("{EURI-1}"));
	
	return 0;
}
