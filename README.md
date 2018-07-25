# string plus plus
extend standard string and easy to use

   //create String from number;
   xmh::String test1;
   test1.format_number(1024);
   std::cout<<test1<<std::endl;

   //String to number
   xmh::String test2 = "10.555";
   std::cout<<test2.to_double()+10<<std::endl;

   //split a string by spliter

   xmh::String test3 = "a=b&c=d&e=f";
   auto split_vec = test3.split("&");
   for(auto& iter :split_vec)
   {
      std::cout<<iter<<std::endl;
   }

   //join a string_vec by str
   auto test4 = xmh::String().join(split_vec,"*");
   std::cout<<test4<<std::endl;

   //replace a  keywords

   xmh::String test5 = "a*b*c*";
   test5.replace("*","+",xmh::reg_mode::signle);
   std::cout<<test5<<std::endl;

   //replace all  keywords
   xmh::String test6 = "a*b*c*";
   test6.replace("*","+",xmh::reg_mode::global);
   std::cout<<test6<<std::endl;

   //format string lower
   xmh::String test7 = "ABCDEFG";
   std::cout<<test7.to_lower()<<std::endl;

   //format string upper
   xmh::String test8 = "abcdefg";
   std::cout<<test8.to_upper()<<std::endl;

   //url_encode
   xmh::String test9 = "中文";
   std::cout<<test9.url_encode()<<std::endl;

   //url_decode
   std::cout<<test9.url_encode().url_decode()<<std::endl;

   //read_from_file
   xmh::String file_text;
   file_text.read_from_file("./CMakeCache.txt");
   std::cout<<file_text<<std::endl;


   //write_to_file
   xmh::String file_text2 = "just a plain text";
   file_text2.write_to_file("./file.log");

   //Append to file
   file_text2 = "\r\nand this is append string";
   file_text2.write_to_file("./file.log",xmh::write_file_mode::add);


