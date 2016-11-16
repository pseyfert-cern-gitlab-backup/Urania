void runMain(char* arg1 = "", char* arg2 = "", char* arg3 = "", 
             char* arg4 = "", char* arg5 = "", char* arg6 = "", 
             char* arg7 = "", char* arg8 = "", char* arg9 = "", 
             char* arg10 = "", char* arg11 = "", char* arg12 = "", 
             char* arg13 = "")
{
  //load the shared library
  gSystem->Load("libFoo");
  
  //set up main, eg command line opts
  TList* args = new TList();
  args->Add(new TObjString("foo_exe"));//program name
  args->Add(new TObjString(arg1));
  args->Add(new TObjString(arg2));
  args->Add(new TObjString(arg3));
  args->Add(new TObjString(arg4));
  args->Add(new TObjString(arg5));
  args->Add(new TObjString(arg6));
  args->Add(new TObjString(arg7));
  args->Add(new TObjString(arg8));
  args->Add(new TObjString(arg9));
  args->Add(new TObjString(arg10));
  args->Add(new TObjString(arg11));
  args->Add(new TObjString(arg12));
  args->Add(new TObjString(arg13));
  

  //run the code
  Main m(args);
  int returnCode = m.run();
  // Prevent ROOT from hanging (encountered with ROOT 5.26.00.b)
  //gApplication->Terminate();


  return;
}
